<h3>Command to upload code via Arduino using Isp. Upload code in arduino as arduino as isp and then upload your code for 8051 in terminal running the command mentioned below.</h3>
<ul>
  <li>Download the AVR8051.conf file in C drive</li>
  <li>Locate the avrdude.exe file in arduino folders in user</li>
  <li>Create your HEX file and upload through terminal using the code below making changes accordingly for:</li>
    <ol>
      <li>COM PORT</li>
      <li>BAUD RATE (Should be same as ARDUINO CODE <strong>b -9600 </strong>)</li>
      <li>CHIP NAME (AT89S51/AT89S52)</li>
      <li>Path Address of avrdude.exe,AVR8051.conf and .hex file </li>
    </ol>


</ul>
<pre>"C:\Users\BOTTLE\AppData\Local\Arduino15\packages\arduino\tools\avrdude\6.3.0-arduino17\bin\avrdude.exe" -C C:/AVR8051.conf -c stk500v1 -P COM15 -p 89s51 -b 19200 -U flash:w:"S:\2.SE_Progress\Keil\Blink\Objects\Blink_AT89S51.hex":a</pre>
<hr>

<h3>How to program arduino using arduino as ISP?</h3>
<ul>
  <li>Upload the ArduinoISP program from Examples in the programmer board.</li>
  <li>Now write your code to upload on the target arduino setting the programmer as Arduino as ISP and CAUTION: Upload using programmer only (Dont' click on the upload button).Go to sketch and look for upload using programmer.</li>
  <br>
  <pre>
Arduino Uno	→	Arduino Nano | Arduino Uno(check for ICSP pinout)
5V	→	5V    | 5V
GND	→	GND   | GND
D10	→	RESET | RESET
D11	→	D11   | MOSI
D12	→	D12   | MISO 
D13	→	D13   | SCK
  </pre>
  <li>Make the connections as mentioned above.</li>
  <li>Before uploading, select the proper board from tools and setting programmer as <strong>Arduino as ISP</strong>.</li>
  <li><strong>NOTE:</strong>For arduino Uno SMD versions the device signature are not same so download this board using the link below. </li>
  <li>GO to file → Preferences → Additional board urls → Copy the link below → Paste → Ok </li>
  <li>Tools → Board → Board Manager → Search for MiniCore → Install.</li>
  <li>After installing → Tools → Board → MiniCore → Atmega328</li>
  <pre>https://mcudude.github.io/MiniCore/package_MCUdude_MiniCore_index.json</pre>
  <li>check for the chip on the board using camera and select the chip in tools</li>
</ul>
