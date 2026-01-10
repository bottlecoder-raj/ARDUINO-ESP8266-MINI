<h2>1. Set Up the Arduino IDE</h2>

<ol>
  <li>Open the Arduino IDE.</li>
  <li>Go to <b>File &gt; Preferences</b>.</li>
  <li>
    In <b>Additional Boards Manager URLs</b>, paste the following link:
    <br>
    <code>https://github.com/earlephilhower/arduino-pico/releases/download/global/package_rp2040_index.json</code>
  </li>
  <li>
    Go to <b>Tools &gt; Board &gt; Boards Manager</b>, search for <b>RP2040</b>,
    and install the <b>Raspberry Pi Pico/RP2040</b> core by
    <b>Earle Philhower</b>.
  </li>
</ol>

<h2>2. Identify the Pin</h2>

<p>
On the Shrike-Lite, there are two main LEDs. One is connected to the FPGA,
and the other is connected to the RP2040.
</p>

<p>
According to the Vicharak pinout, the MCU-controlled LED is typically connected
to <b>GPIO 4</b>, which is the same as the standard Raspberry Pi Pico.
</p>

<h2>3. Blink LED Example Code</h2>

<p>
The following Arduino sketch blinks the onboard LED connected to <b>GPIO 4</b>.
</p>

<pre><code>

// Shrike-Lite RP2040 LED Blink Example
void setup() {
  pinMode(4, OUTPUT);
}

void loop() {
  digitalWrite(4, HIGH);  // LED ON
  delay(500);                   // Wait 500 ms
  digitalWrite(4, LOW);   // LED OFF
  delay(500);                   // Wait 500 ms
}
</code></pre>

<h2>How to Upload</h2>

<ol>
  <li>
    <b>Connect the Board:</b>
    Plug the Shrike-Lite into your computer using a USB-C cable.
  </li>

  <li>
    <b>Enter Bootloader Mode:</b>
    <ul>
      <li>Hold down the <b>BOOT</b> button.</li>
      <li>Press and release the <b>RESET</b> button.</li>
      <li>Release the <b>BOOT</b> button.</li>
    </ul>
    The board should appear on your computer as a USB drive named
    <b>RPI-RP2</b>.
  </li>

  <li>
    <b>Select Board:</b>
    In the Arduino IDE, go to <b>Tools &gt; Board</b> and select
    <b>Raspberry Pi Pico</b>.
  </li>

  <li>
    <b>Upload:</b>
    Click the <b>Upload</b> button. The IDE will compile the code and
    automatically upload it to the board.
  </li>
</ol>
