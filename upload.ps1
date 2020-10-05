. .\build-helper.ps1


function build() {
    d:\apps\arduino\arduino-cli.exe compile --output-dir "$PSScriptRoot/.build-out" --build-path "$PSScriptRoot/.build" --build-cache-path "$PSScriptRoot/.build-cache" -b arduino:sam:arduino_due_x_dbg "$PSScriptRoot\Pedalboard.ino"
}

function upload() {
    $exitCode = -1
    while ($exitCode -ne 0) {
        d:\apps\arduino\arduino-cli.exe upload -b arduino:sam:arduino_due_x_dbg -p COM3 "$PSScriptRoot" --input-dir "$PSScriptRoot/.build-out"
        $exitCode = $LastExitCode

        if ($exitCode -ne 0) {
            write-output "Please reset the board"
            Start-Sleep -seconds 2
        }
    }
}

try {New-Item -Name "./.uploading" -ItemType File | Out-Null }catch{}

while (Test-Path ./.monitoring) {
    Write-Output "Waiting for monitoring to pause"
    Start-Sleep -milliseconds 1000
}

Write-Output "Resetting"

$port = createSerialPort
$port.RtsEnable = $true;
$port.DtrEnable = $true;
$port.open()

Start-Sleep -Seconds 3
$port.close()
$port.dispose()

try {
    build
    if ($LastExitCode -eq 0) {
        upload    
    }
}
finally {
    Remove-Item "./.uploading" | Out-Null
}
