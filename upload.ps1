
function build() {
    d:\apps\arduino\arduino-cli.exe compile --build-path "$PSScriptRoot/.build" -b arduino:sam:arduino_due_x_dbg "$PSScriptRoot\Pedalboard.ino"
}

function upload() {
    $exitCode = -1
    while ($exitCode -ne 0) {
        d:\apps\arduino\arduino-cli.exe upload -b arduino:sam:arduino_due_x_dbg -p COM3 "$PSScriptRoot"
        $exitCode = $LastExitCode

        if ($exitCode -ne 0) {
            write-output "Please reset the board"
            Start-Sleep -seconds 2
        }
    }
}


build
if ($LastExitCode -eq 0) {
    upload
}
