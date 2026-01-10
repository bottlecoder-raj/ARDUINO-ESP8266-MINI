1. Set Up the Arduino IDE
Open Arduino IDE.

Go to File > Preferences.

*In "Additional Boards Manager URLs", paste this link:* https://github.com/earlephilhower/arduino-pico/releases/download/global/package_rp2040_index.json

Go to Tools > Board > Boards Manager, search for RP2040, and install the "Raspberry Pi Pico/RP2040" core by Earle Philhower.

2. Identify the Pin
On the Shrike-Lite, there are two main LEDs. One is connected to the FPGA, and the other is connected to the RP2040. According to the Vicharak pinout, the MCU-controlled LED is typically on GPIO 4 (the same as the standard Raspberry Pi Pico).

*How to Upload*
Connect the Board: Plug the Shrike-Lite into your computer via USB-C.

Bootloader Mode: * Hold down the BOOT button on the board.

Press and release the RESET button.

Release the BOOT button.

The board should now appear on your computer as a USB drive named *RPI-RP2.*

Select Board: In Arduino IDE, go to Tools > Board and select *Raspberry Pi Pico.*

Upload: Click the Upload arrow. The IDE will compile the code and automatically move it to the board.
