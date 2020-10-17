# Setup
We need to install a few external libraries.

Adafruit GFX Library 1.10.1
AxeFxControl 1.1 
You can download this from [https://github.com/tysonlt/AxeFxControl/archive/v1.1.zip](AxeFxControl) and extract to C:\Program Files (x86)\Arduino\libraries\AxeFxControl (or appropriate location on mac/linux)
I have included a modified version of Adafruit_ST7735 library
* Their latest version does not work with my screens - corrupt display, haven't found the reason yet.
* Their library adds a lot of uncessery sleeping during initialisation and screen writing. It's essentially a naive implementation to try to be more reliable (less bad screen writes).
 * TODO: Try to get onto the latest version + contribute back the performance improvements

# Midi Settings 
The software uses midi channel 1 and makes a few other assumptions. Here are the recommended settings to change on the AxeFx->Setup->MIDI/Remote
* General / Midi Channel: 1
* General / Send Realtime Sysex: On
* General / Program Change: On
* General / Send Midi PC: CHAN 1
* General / Initial Value / External Control 1/2: 100% (This is optional but recommended so if you don't have an expression pedal plugged in your patches default to 100% volume etc)
* External / External Control # 1: CC #63
* External / External Control # 2: CC #62
* Other / Output 1 Volume: CC #100

# Layouts
If you want to setup your own layouts then just modify src/Domain/layout_definition.h 

# Adding new functions
[How to add a new function](docs/new_function.md)

