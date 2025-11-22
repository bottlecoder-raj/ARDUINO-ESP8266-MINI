<h3><u>Command to upload code via Arduino using Isp. Upload code in arduino as arduino as isp and then upload your code for 8051 in terminal running the command mentioned below.</u></h3>
<ul>
  <li>Download the AVR8051.conf file in C drive</li>
  <li>Locate the avrdude.exe file in arduino folders in user</li>
  <li>Create your HEX file and upload through terminal</li>


</ul>
<p>"C:\Users\BOTTLE\AppData\Local\Arduino15\packages\arduino\tools\avrdude\6.3.0-arduino17\bin\avrdude.exe" -C C:/AVR8051.conf -c stk500v1 -P COM15 -p 89s51 -b 19200 -U flash:w:"S:\2.SE_Progress\Keil\Blink\Objects\Blink_AT89S51.hex":a</p>
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
  
</ul>
