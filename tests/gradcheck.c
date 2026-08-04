/* gradcheck.c — verify the hand-derived backward pass in src/handgpt.h.
 *
 * Compares each analytic gradient against a centred finite difference:
 *      dL/dp  ~=  ( L(p+eps) - L(p-eps) ) / (2*eps)
 *
 * Built in double precision with small dimensions, so the finite difference
 * is accurate enough to be meaningful. This checks the *published* header,
 * not a copy of it.
 *
 * Build & run:
 *      cc -O2 -DHANDGPT_DOUBLE -DNV=11 -DNC=16 -DNT=8 tests/gradcheck.c -lm -o gradcheck
 *      ./gradcheck
 *
 * Passes if the worst relative error stays below 1e-4.
 */
#include <stdio.h>
#include <math.h>
#include <string.h>
#include "../src/handgpt.h"

static Model M, G;
static Cache C;

static real *param(Model *m, int i) { return ((real *)m) + i; }

int main(void) {
    model_init(&M, 3);

    /* a fixed pseudo-random batch */
    int X[NT], Y[NT];
    unsigned int s = 7;
    for (int t = 0; t < NT; t++) {
        s ^= s << 13; s ^= s >> 17; s ^= s << 5;
        X[t] = s % NV;
        Y[t] = (s >> 3) % NV;
    }

    forward(&M, &C, X, Y);
    memset(&G, 0, sizeof(G));
    backward(&M, &C, &G);

    const real eps = 1e-4;
    real worst = 0;
    unsigned int r = 11;
    const int npar = (int)(sizeof(Model) / sizeof(real));

    printf("gradient check - analytic vs. centred finite differences\n");
    printf("  dims: NV=%d NC=%d NT=%d, %d parameters, double precision\n\n",
           NV, NC, NT, npar);

    for (int test = 0; test < 20; test++) {
        r ^= r << 13; r ^= r >> 17; r ^= r << 5;
        int idx = r % npar;
        real *p = param(&M, idx), old = *p;

        *p = old + eps; real lp = forward(&M, &C, X, Y);
        *p = old - eps; real lm = forward(&M, &C, X, Y);
        *p = old;

        real numeric  = (lp - lm) / (2 * eps);
        real analytic = *param(&G, idx);
        real rel = fabs(numeric - analytic) /
                   (fabs(numeric) + fabs(analytic) + 1e-12);
        if (rel > worst) worst = rel;

        printf("  param[%6d]  numeric %+.8f   analytic %+.8f   rel %.2e\n",
               idx, (double)numeric, (double)analytic, (double)rel);
    }

    printf("\n  worst relative error: %.2e  ->  %s\n",
           (double)worst, worst < 1e-4 ? "PASS" : "FAIL");
    return worst < 1e-4 ? 0 : 1;
}
