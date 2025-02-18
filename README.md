# Kemper PLayer Remote
You'll find in this repo 2 codes I'm using to control my Kemper Player.
## How to
To use these 2 codes, you'll need one Arduino Nano and one Arduino Micro Pro. When it comes to hardware you'll need a LCD display (ST7789 library compatible), 9 Leds and 9 foot switches.
## Libraries used
- "MIDIUSB.h"
- <SoftwareSerial.h>
- "ST7789_AVR.h"
## Assembly
I'm expliciting here how things should be wired :
| Arduino Nano Pin| Arduino Micro Pro Pin| Other Hardware|
| :--| :- | :-|
|GND|GND|LCD GND, LEDS GND, SWITCHES GND|
|D4| |LCD CS|
|D5| |LCD DC|
|D6| |LCD RST|
|D9 (MySerial RX)|TX|
|D10 (MySerial TX)|RX|
|D15| |LCD SCLK|
|D16| |LCD DIN|
| |D2 to D12|FOOT SWITCHES|
| |A1 to A7|LEDS|
| |D13|LED|

## What does this do

These 2 codes should let you control your Kemper Player : 
- Choose the rig you want to be on (1 to 5)
- Activate or deactivate buton I to IIII


## Known issues and improvements

First of all for the LCD to display then position you're at and the name of your bank, you must in Rig Manager write them in the custom parameters : 

- Rig > Comment for the Bank name (Your name)
- Rig > Author for the position (Position x-y)

Leds are working when control is set with your remote but not when changes come from the Kemper. (I don't know why i cant get the position from the Arduino micro to the Arduino Nano...)

Morphing works only one way from what I've experienced

Changing bank is on the Kemper Player not the remote, I find it easier this way.

