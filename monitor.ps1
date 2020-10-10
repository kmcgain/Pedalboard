# Monitor serial output of arduino. 
# Uses file watching to communicate with upload process and pause / resume monitoring so it doesn't interfere with upload process

. .\build-helper.ps1

$port = openSerialPort()

$performingUpload = $false

function markAsMonitoring() {
    if (-Not (Test-Path "./.monitoring")) {
        New-Item -Name "./.monitoring" -ItemType File | Out-Null
    }
}

function markAsPausedMonitoring() {
    if (Test-Path "./.monitoring") {
        Remove-Item "./.monitoring" | Out-Null
    }
}

function closeSerialPort() {
    $port.close()
}

function read() {
    while ($True) {
        $performingUpload = Test-Path  ./.uploading
        if ($performingUpload) {
            closeSerialPort
            markAsPausedMonitoring
        }
        else {
            markAsMonitoring
        }

        if ((-not $performingUpload) -and (-not $port.IsOpen)) {
            try {
                $port.open()
            }
            catch {
                Start-Sleep -seconds 1
            }
        }
        
        if ($port.IsOpen) {
            try {
                $line = $port.ReadLine()
                Write-Output "$line"        
            }            
            catch {}
        }
    }
}

try {
    markAsMonitoring
    read
}
finally {
    $port.close()
    Remove-Item "./.monitoring"
}
