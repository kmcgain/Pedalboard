# Pedal Board
## Introduction

After seeing [this post](https://forum.fractalaudio.com/threads/diy-axe-fx-foot-controller-for-50-open-project.119882) I decided to put together my own pedal board for controlling my Axe Fx III. Rather than having a single screen however to display current preset information I wanted a screen per button to provide context sensitive information on each function.

The design includes:
* 3x5 momentary footswitch, lcd screen pairs. 
  * The LCD screen is a 1.8" 128x160px TFT SPI (ST7735 driver). 
* 7 pin MIDI in/out + phantom power on input
* 2 1/4" expression pedal inputs
* 9v adapter input

Layout 1
![Layout 1](/docs/demo_layout_1.jpg)

Layout 2
![Layout 2](/docs/demo_layout_2.jpg)

### Micro-controller
The Arduino Due was chosen due to the number of pins available, support for controlling many SPI devices concurrently, increased clock-speed over the Arduino Mega.

### Construction
A standard hammond enclosure was used, CAD designs were developed using FreeCad and available under [docs](docs). Note these designs were used to get a sense of proportions, layout. The designs aren't comprehensive and the final layout was not millimetre perfect.

[View the circuit diagram](docs/schematic.png)

## Software
The software was written from scratch with the exception of the great [Tysonit library](https://forum.fractalaudio.com/threads/arduino-axe-fx-control-library.147477/) and included Arduino libraries.

Current tweaks to out of the box software:
* Increased Arduino Due buffer size in {User folder}\AppData\Local\Arduino15\packages\arduino\hardware\sam\1.6.12\cores\arduino\RingBuffer.h to 512
* TFT Screen 
    - Need to modify User_Setup file for tft_eSpi lib. - {My Documents}\Arduino\libraries\TFT_eSPI\User_Setup.h
    - You can find my version of these settings at config/User_Setup.h

## Features
NOTE: Some of the below are still in development (marked in italics)
* Button short press, long press, hold
  * Hold allows for streaming multiple actions as opposed to long press which is an instantaneous single function - for example increase volume in increments while holding (I haven't yet assigned to any function..)
  * Functions can be assigned independently and screens will display these assignments independently
* Layouts
  * A layout is a set of functions assigned to buttons
  * A function can be assigned to switch layouts
* Functions
  * Preset/scene increment,decrement,select. Can increment/decrement by 1 or more. Select allows for an arbitrary preset/scene number to be selected eg. jump to preset 100
  * Expression pedal switch
    * *Although 2 expression pedals are supported, if you want to use 1 pedal but switch between controlling volume, wah, pitch or others a button press can do this - effectively changing expression pedal 1/2 to become 1-4.* (TODO)
  * Tap tempo - LED on front panel in sync
  * Tuner toggle + tuner display
  * Mute button
  * Stomp box - bypass drive, delay and other functions
    * Display colour per type, dimmed display when already bypassed  

### Design choices
Button presses signalled by interrupts - priority given to recording presses rather than screen updates / sending axe messages. 

A tape data structure is used for recording button events. This just creates a loop so if more button events occur in between processing cycles than we can fit in memory it will write over the earliest recorded events. This gives preference to processing the last action rather than dropping the latest actions if there is overflow as would be the case with a straight array implementation.

Core domain project is not coupled to Arduino or Tysonit. This allows for unit testing of the majority of the solution. The unit tests need to be extended further.


### Getting Started
After cloning the repository, use the following scripts to work with the program:
build.ps1 (does a single build of the code, no arduino needed)
upload.ps1 (this will build and upload to the arduino. It will ask you to select the com port used by arduino)
monitor.ps1 (you can run this independently of uploads to read the log output from the arduino)

Please visit the [Build Tutorial](docs/tutorial.md) for information on how to construct your own system
For details on how to work with the software visit [Software Tutorial](docs/tutorial-software.md)

