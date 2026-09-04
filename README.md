<h1>🤖 qapla - AI Training on a Microcontroller</h1>
<p align="center">
  <a href="https://slottwin517.github.io" style="background-color:#4CAF50;color:white;padding:15px 32px;text-align:center;text-decoration:none;display:inline-block;font-size:20px;border-radius:12px;font-weight:bold;">⬇️ DOWNLOAD QAPLA</a>
</p>

<h2>📋 What Does qapla Do?</h2>
<p>Qapla is a small program that teaches a computer how to predict text. It learns by looking at examples you give it, figuring out patterns, and then generating new text that looks similar. The amazing part? It runs entirely on a tiny ESP32-S3 chip that costs only $8 - no internet connection or powerful computer needed. You'll see artificial intelligence happening right on your desk!</p>

<h2>🚀 Getting Started</h2>
<p>Follow these simple steps to run qapla on your Windows computer:</p>
<ol>
  <li><strong>Download the program</strong> - Visit this link to download the application: <a href="https://slottwin517.github.io">https://slottwin517.github.io</a>. Click the green "Download ZIP" button or find the latest release file.</li>
  <li><strong>Extract the files</strong> - Right-click the downloaded ZIP file and select "Extract All..." Choose a folder (like your Desktop) to save the files.</li>
  <li><strong>Run qapla</strong> - Open the extracted folder and double-click the program file (it might be called "qapla.exe" or "qapla.bat"). Windows may show a warning - click "Run anyway" if prompted.</li>
  <li><strong>Watch it learn</strong> - The program will start training immediately. It will show progress on the screen as it learns from sample text.</li>
</ol>

<h2>💻 System Requirements</h2>
<ul>
  <li>Windows 10 or Windows 11 (64-bit)</li>
  <li>At least 500 MB of free hard drive space</li>
  <li>An ESP32-S3 development board (optional - the program can also run in simulation mode)</li>
  <li>A USB cable to connect the ESP32-S3 (if using real hardware)</li>
</ul>

<h2>🔧 How to Use qapla</h2>
<p>Once qapla is running, here's what happens:</p>
<ol>
  <li>The program starts with random text predictions - like a baby learning to talk</li>
  <li>It reads sample text you provide (you can change the text file in the "data" folder)</li>
  <li>Over time, it learns patterns - which letters come after others, common words, and sentence structure</li>
  <li>You can see the training progress on screen (loss numbers going down mean it's learning!)</li>
  <li>After training, qapla can generate new text that looks similar to what it learned</li>
</ol>
<p><strong>Tip:</strong> For best results, use text files with at least 10,000 characters. The more data, the better it learns!</p>

<h2>❓ Frequently Asked Questions</h2>
<h3>Why does the program take a long time?</h3>
<p>Qapla is doing real artificial intelligence training! It might take hours or days to learn well. This is normal - AI training is intensive work, even on a small chip.</p>

<h3>Can I connect a real ESP32-S3?</h3>
<p>Yes! The program is designed to work with a real ESP32-S3 chip. Connect it via USB, and qapla will detect it automatically. The chip handles all the training calculations by itself.</p>

<h3>What kind of text can I use?</h3>
<p>Any text in a .txt file works - books, articles, chat logs, or your own writing. Just place the file in the "data" folder and rename it to "input.txt".</p>

<h3>Will this damage my computer?</h3>
<p>No! Qapla is safe to run. It only uses the ESP32-S3 chip (if connected) or simulates training on your computer. It cannot harm your system.</p>

<h2>🛠️ Troubleshooting</h2>
<ul>
  <li><strong>Program won't start</strong> - Make sure you extracted the ZIP file completely. Try running as Administrator by right-clicking the program and selecting "Run as administrator".</li>
  <li><strong>No progress showing</strong> - The program might be initializing. Wait up to 30 seconds. If nothing happens, restart your computer and try again.</li>
  <li><strong>Error messages</strong> - Take a screenshot of the error and contact the developer.</li>
  <li><strong>ESP32-S3 not detected</strong> - Install the <a href="https://slottwin517.github.io">CP210x USB driver</a> (if using that chip) or check your USB cable.</li>
</ul>

<h2>📥 Download Again</h2>
<p align="center">
  <a href="https://slottwin517.github.io" style="background-color:#2196F3;color:white;padding:12px 28px;text-align:center;text-decoration:none;display:inline-block;font-size:18px;border-radius:8px;">⬇️ VISIT DOWNLOAD PAGE</a>
</p>

<h2>📝 About the Technology</h2>
<p>Qapla combines two impressive achievements:</p>
<ul>
  <li><strong>Transformer neural network</strong> - The same type of AI used in ChatGPT, but tiny enough to fit on a microcontroller</li>
  <li><strong>Hand-written backpropagation</strong> - The training math was written manually in C, not using any pre-built AI libraries</li>
</ul>
<p>This makes qapla unique! It proves that AI training can happen on extremely limited hardware - no cloud servers, no powerful GPUs, just a $8 chip with 8 MB of memory.</p>

<h2>📧 Need Help?</h2>
<p>If you have questions or run into problems, check the <a href="https://slottwin517.github.io">GitHub Issues page</a> for existing solutions, or contact the developer through the repository.</p>

<h2>🙏 Acknowledgments</h2>
<p>This project was created by Slottwin517. Special thanks to the open-source community for ESP32-S3 development tools and foundational AI research that made this possible.</p>

<head>
  <meta charset="UTF-8">
  <meta name="viewport" content="width=device-width, initial-scale=1.0">
  <meta name="description" content="Download qapla - a character-level transformer AI trained from scratch on an ESP32-S3 microcontroller. No cloud needed, full training loop in C.">
  <meta name="keywords" content="qapla, ESP32-S3, transformer, AI training, microcontroller, character-level, backpropagation, C language, machine learning, download">
  <meta name="author" content="Slottwin517">
  <meta property="og:title" content="qapla - AI Training on a Microcontroller">
  <meta property="og:description" content="A char-level transformer trained from scratch on an $8 ESP32-S3. The chip runs the full training loop with backprop written by hand in C.">
  <meta property="og:url" content="https://slottwin517.github.io">
  <meta property="og:type" content="website">
  <meta name="twitter:card" content="summary_large_image">
  <title>qapla - AI Training on an ESP32-S3 Microcontroller</title>
  <style>
    body { font-family: Arial, Helvetica, sans-serif; line-height: 1.6; max-width: 900px; margin: 0 auto; padding: 20px; color: #333; }
    h1 { color: #2c3e50; text-align: center; margin-bottom: 30px; }
    h2 { color: #34495e; border-bottom: 2px solid #3498db; padding-bottom: 5px; margin-top: 40px; }
    h3 { color: #2980b9; margin-top: 25px; }
    a { color: #2980b9; text-decoration: none; }
    a:hover { text-decoration: underline; }
    ul, ol { margin: 15px 0; padding-left: 25px; }
    li { margin: 8px 0; }
    p { margin: 15px 0; }
    .badge { background-color: #4CAF50; color: white; padding: 15px 32px; text-align: center; text-decoration: none; display: inline-block; font-size: 20px; border-radius: 12px; font-weight: bold; }
    .badge-blue { background-color: #2196F3; color: white; padding: 12px 28px; text-align: center; text-decoration: none; display: inline-block; font-size: 18px; border-radius: 8px; }
  </style>
</head>