if (-not (Test-Path "$PSScriptRoot\.build")) {
    mkdir "$PSScriptRoot\.build"
}

if (-not (Test-Path "$PSScriptRoot\.build-cache")) {
    mkdir "$PSScriptRoot\.build-cache"
}

arduino-builder -compile -logger=machine `
    -hardware "C:\Program Files (x86)\Arduino\hardware" `
    -hardware "$($env:LOCALAPPDATA)\Arduino15\packages" `
    -tools "C:\Program Files (x86)\Arduino\tools-builder" `
    -tools "C:\Program Files (x86)\Arduino\hardware\tools\avr" `
    -tools "$($env:LOCALAPPDATA)\Arduino15\packages" `
    -built-in-libraries "C:\Program Files (x86)\Arduino\libraries" `
    -libraries "$([Environment]::GetFolderPath("MyDocuments"))\Arduino\libraries" `
    -fqbn=arduino:sam:arduino_due_x_dbg -ide-version=10813 `
    -build-path "$PSScriptRoot\.build" -build-cache "$PSScriptRoot\.build-cache" `
    "$PSScriptRoot\Pedalboard.ino"
