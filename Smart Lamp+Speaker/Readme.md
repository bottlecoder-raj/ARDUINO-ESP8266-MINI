<h1 align="center" id="title">SMART LAMP + SPEAKER</h1>

<p id="description">A smart iot operated lamp controlled through a webpage provided by the device that is connected to a home network. Webpage can be accessed by entering the IP address of the home network on browser.</p>

<h2>🧐 Features:</h2>

Here're some of the project's best features:

*   WIFI CONTROLLED
*   RECHARGEABLE
*   OLED DISPLAY FOR ANIMATIONS/TIME
*   RGB ENABLED LIGHT
*   PORTABLE
*   Show Time
<br>
<h2>🛠️ Installation Steps:</h2>
 Install <a href="https://www.arduino.cc/en/software/">Arduino IDE</a> and necessary extension at the start of code.</p>
<p>1. CLICK ON THIS LINK TO OPEN AND UPLOAD IT ON 
<a href="https://github.com/bottlecoder-raj/ARDUINO-ESP8266-MINI/blob/main/Smart%20Lamp%2BSpeaker/main.ino">ESP8266 CODE MAIN</a>
</p>
<p>2.CLICK ON THE LINK BELOW TO CHANGE UI OF WEBPAGE
<a href="https://github.com/bottlecoder-raj/ARDUINO-ESP8266-MINI/blob/main/Smart%20Lamp%2BSpeaker/Seperate/index.html">WEBSITE</a>
</p>

  <br><hr>
  
<h2>💻 Built with</h2>

Technologies used in the project:
*   ARDUINO
*   HTML
*   CSS
*   JAVASCRIPT
<br>
<hr>
<h2>👷‍♂️How to make this project?</h2>
<h3>Things required to make this:</h3>
<ul><li>ESP8266 microcontroller</li>
<li>18650 li-on battery</li>
<li>TP4056 battery charging module</li>
<li>0.96 inch monochrome oled display</li>
<li>ULN2003 IC</li>
<li>XL6009 STEP UP CONVERTER</li>
<li>LM2596 STEP DOWN CONVERTER</li>
<li>Wires </li>
<li>5V BLUETOOTH AUDIO MODULE AND 5V AMPLIFIER</li>
<li>Physical switches {SPRING,TOGGLE}</li>
<li>LM7805 IC</li>
</ul>
<h3>Note: If you are going to make lamp+speaker ,2 batteries are required because the step up/down converters produces noise which the amplifier catches making the music sound terrible.<br> If you just want to make the lamp then there is no need to use second battery.</h3>
<br>
<h3>PROCESS 1: For Lamp Only condition</h3>
<ul>
<li>Connect the battery with TP4056 input</li>
<li>Join the output of TP4056 with XL6009 input. Insert a Switch in between OUT of TP4056 and IN of XL6009.</li>
<li>Set the Output of XL6009 to 12-13v by rotating the potentiometer</li>
<li>Connect the Output(+ve) of XL6009 to VCC of lights(Assuming 12V RGB leds) and also to LM2596(both +ve and -ve).</li>
<li>Set the OUT of LM2596 to 6-7V for Nodemcu...... [Don't exceed more than 7v]</li>
<li>Make a rail for 6-7v output on a breadboard as many pins are required for connections on the rail of 6-7v.</li>
</ul>
<br>
<h3>ESP8266 Connections:</h3>
<ul>
<li>Connect VCC and GND of ESP to the rail from OUT of LM2596. </li>
<li>Connect Oled Display with 3v3,GND,D1,D2 accordingly.</li>
<li>Connect D6,D7,D8 with IN1,IN2,IN3 of ULN2003 IC2</li>
<li>Connect OUT1,OUT2,OUT3 of ULN2003 with R,G,B on Led</li>
<li>Connect GND pin with GND of ULN2003,[PIN 8]
</ul>
<br>
You can add more, if you need but remember to do the changes in the code also and the speaker is not controlled by wifi,it has its own seperate switch.

</p>
<h3>PROCESS 2: With Speaker </h3>
<ul>
<li>Connect IN and GND of LM7805 with 6-7v rail</li>
<li>Connect OUT and GND with Bluetooth module</li>
<li>Connect the amp with the other battery. Make a connection of tp4056 and physical switch.</li>
<li>Connect the audio signals with bluetooth out and amp in with connection of speakers  also.</li>
</ul>
</p>
<p>
 <h3>DO THE CHANGES IN CODE</h3>
 <ul>
  <li> BEFORE UPLOADING: Update with your wifi credentials at line 230 and 231.</li>
  <li>Check the pins connected from line 12-16</li>
  <li>Required instruction will be provided in code as comments</li>
 
 </ul>
 
</p>
<h2>CONGRATULATIONS!!!!!!</h2>
</p>
<hr>
<h4>If you face any problem/want to give appreciation, email me at. hazrarajnarayan55@gmail.com.

