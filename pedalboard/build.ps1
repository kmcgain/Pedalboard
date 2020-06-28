arduino-builder -compile -logger=machine -hardware "C:\Program Files (x86)\Arduino\hardware" -tools "C:\Program Files (x86)\Arduino\tools-builder" `
    -tools "C:\Program Files (x86)\Arduino\hardware\tools\avr" -built-in-libraries "C:\Program Files (x86)\Arduino\libraries" `
    -fqbn=arduino:avr:diecimila:cpu=atmega328 -ide-version=10813 `
    -build-path "$PSScriptRoot\.build" -build-cache "$PSScriptRoot\.build-cache" `
    "$PSScriptRoot\pedalboard.ino"



#-prefs=build.warn_data_percentage=75 
# -prefs=runtime.tools.avr-gcc.path="C:\Program Files (x86)\Arduino\hardware\tools\avr" `
#     -prefs=runtime.tools.avr-gcc-7.3.0-atmel3.6.1-arduino7.path="C:\Program Files (x86)\Arduino\hardware\tools\avr" `
#     -prefs=runtime.tools.avrdude.path="C:\Program Files (x86)\Arduino\hardware\tools\avr" `
#     -prefs=runtime.tools.avrdude-6.3.0-arduino17.path="C:\Program Files (x86)\Arduino\hardware\tools\avr" `
#     -prefs=runtime.tools.arduinoOTA.path="C:\Program Files (x86)\Arduino\hardware\tools\avr" `
#     -prefs=runtime.tools.arduinoOTA-1.3.0.path="C:\Program Files (x86)\Arduino\hardware\tools\avr" `