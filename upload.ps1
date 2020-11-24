. .\build-helper.ps1

function build() {
    $settings = (Get-Content -raw .\settings.json)
    $Utf8NoBomEncoding = New-Object System.Text.UTF8Encoding $False
    $cd = (Get-Location).Path
    [System.IO.File]::WriteAllLines("$($cd).\generated\settings.h", "const char *jsonSettings = R""""""""(`n$($settings)`n)"""""""";", $Utf8NoBomEncoding)

    d:\apps\arduino\arduino-cli.exe compile --output-dir "$PSScriptRoot/.build-out" --build-path "$PSScriptRoot/.build" --build-cache-path "$PSScriptRoot/.build-cache" -b arduino:sam:arduino_due_x_dbg "$PSScriptRoot\Pedalboard.ino"
}

function upload() {
    $commPort = Get-Comm-Port
    $exitCode = -1
    while ($exitCode -ne 0) {        
        d:\apps\arduino\arduino-cli.exe upload -b arduino:sam:arduino_due_x_dbg -p $commPort "$PSScriptRoot" --input-dir "$PSScriptRoot/.build-out"
        $exitCode = $LastExitCode

        if ($exitCode -ne 0) {
            write-output "Please reset the board"
            Start-Sleep -seconds 2
        }
    }
}

function reset() {
    $port = createSerialPort
    $port.RtsEnable = $true;
    $port.DtrEnable = $true;
    $port.open()

    Start-Sleep -Seconds 3
    $port.close()
    $port.dispose()
}

try {New-Item -Name "./.uploading" -ItemType File | Out-Null }catch{}

while (Test-Path ./.monitoring) {
    Write-Output "Waiting for monitoring to pause"
    Start-Sleep -milliseconds 1000
}


try {
    build
    if ($LastExitCode -eq 0) {
        upload 
    }
}
finally {
    Remove-Item "./.uploading" | Out-Null
}
