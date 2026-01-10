<!DOCTYPE html>
<html lang="en">
       <body>

<h1>SHRIKE-LITE FPGA Configuration with LED Blink Test</h1>

<p>
This document provides step-by-step instructions to configure the <strong>SHRIKE-LITE FPGA</strong>
and run a simple <strong>LED blink test</strong>.
</p>

<hr>

<h2>1. Required Software</h2>
<ul>
    <li>
        <strong>Go Configure Software Hub</strong><br>
        <a href="https://www.renesas.com/en/software-tool/go-configuresoftware-hub" target="_blank">
            Download here
        </a>
    </li>
    <li>
        <strong>Thonny IDE</strong><br>
        <a href="https://thonny.org/" target="_blank">
            Download here
        </a>
    </li>
</ul>

<hr>

<h2>2. Create FPGA Project</h2>
<ol>
    <li>Open <strong>Go Configure Software Hub</strong>.</li>
    <li>Navigate to <strong>Develop → ForgeFPGA</strong>.</li>
    <li>Under <strong>Part Number</strong>, double-click:
        <code>SLG47910V (Rev BB)</code>
    </li>
    <li>In the popup window, create a new project and rename it as desired.</li>
</ol>

<hr>

<h2>3. Project Settings</h2>
<ol>
    <li>In the project settings popup, select <strong>Specs</strong>.</li>
    <li>Click the <strong>upward arrow</strong> for all operating condition parameters.</li>
</ol>

<h3>Recommended Operating Conditions</h3>
<table border="1" cellpadding="8" cellspacing="0">
    <tr>
        <th>Parameter</th>
        <th>Min</th>
        <th>Typ</th>
        <th>Max</th>
    </tr>
    <tr>
        <td>VDD (V)</td>
        <td>1.05</td>
        <td>1.10</td>
        <td>1.15</td>
    </tr>
    <tr>
        <td>VDDIO (V)</td>
        <td>1.710</td>
        <td>2.500</td>
        <td>3.465</td>
    </tr>
    <tr>
        <td>Temperature (°C)</td>
        <td>-40</td>
        <td>25</td>
        <td>85</td>
    </tr>
</table>

<p>Click <strong>OK</strong> to proceed.</p>

<hr>

<h2>4. FPGA Editor & Code Upload</h2>
<ol>
    <li>Open <strong>FPGA Core</strong> or click <strong>FPGA Editor</strong> from the toolbar.</li>
    <li>The <code>main.v</code> file and <strong>I/O Planner</strong> will open side by side.</li>
    <li>Open <code>main.v</code> and upload the LED blink code from:
        <br>
        <a href="https://github.com/vicharakin/shrike/tree/main/examples/led_blink" target="_blank">
            LED Blink Example Repository
        </a>
    </li>
</ol>

<hr>

<h2>5. I/O Planner Pin Assignment</h2>
<p>Assign the following signals in the <strong>I/O Planner</strong>:</p>

<ul>
    <li><code>GPIO16_OUT [PIN 7]</code> → LED</li>
    <li><code>GPIO16_OE [PIN 7]</code> → LED_en</li>
    <li><code>OSC_CLK</code> → clk</li>
    <li><code>OSC_EN</code> → clk_en</li>
</ul>

<hr>

<h2>6. Synthesis & Bitstream Generation</h2>
<ol>
    <li>Click <strong>Synthesize</strong>.</li>
    <li>After completion, click <strong>Generate Bitstream</strong>.</li>
    <li>Close <strong>Go Configure Software Hub</strong> once finished.</li>
</ol>

<hr>

<h2>7. Flash Shrike-Lite Firmware</h2>
<ol>
    <li>Download the UF2 file:
        <br>
        <a href="https://github.com/vicharakin/shrike/blob/main/shrike-lite_v_1.uf2" target="_blank">
            shrike-lite_v_1.uf2
        </a>
    </li>
    <li>Press and hold the <strong>BOOT</strong> button on the Shrike-Lite board.</li>
    <li>Connect the board to your computer via USB.</li>
    <li>A new drive named <strong>RPI-RP2</strong> will appear.</li>
    <li>Copy the downloaded UF2 file into the <strong>RPI-RP2</strong> drive.</li>
</ol>

<div class="note">
    The drive will disappear automatically after copying. This indicates successful flashing.
</div>

<hr>

<h2>8. Upload FPGA Bitstream via Thonny</h2>

<h3>Thonny Configuration</h3>
<ol>
    <li>Open <strong>Thonny IDE</strong>.</li>
    <li>Select interpreter:
        <br>
        <code>MicroPython (RP2040) – Board CDC @ &lt;COM Port&gt;</code>
    </li>
    <li>Enable <strong>View → Files</strong>.</li>
</ol>

<h3>Upload Bitstream</h3>
<ol>
    <li>Navigate to:
        <pre>
project_folder/
 └─ ffpga/
    └─ build/
       └─ bitstream/
       </pre>
    </li>
    <li>Right-click <code>FPGA_bitstream_MCU.bin</code>.</li>
    <li>Select <strong>Upload to /</strong>.</li>
</ol>

<hr>

<h2>9. Flash FPGA from MicroPython</h2>

<pre>
import shrike
shrike.flash("FPGA_bitstream_MCU.bin")
</pre>

<ol>
    <li>Save this file to the RP2040 device.</li>
    <li><strong>File name must be:</strong> <code>main.py</code></li>
    <li>Click <strong>Run</strong> (Play button).</li>
</ol>

<hr>

<h2>10. Result</h2>
<p>
🎉 The built-in FPGA LED on the <strong>Shrike-Lite</strong> board should now start blinking.
</p>
</body>
</html>
<hr>

<p><strong>Author / Reference:</strong> Shrike FPGA Examples</p>

</body>
</html>
