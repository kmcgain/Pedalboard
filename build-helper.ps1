function createSerialPort() {
    $portNames =[System.IO.Ports.SerialPort]::getportnames()
    $explicitPort = $env:ARDUINO_COMM_PORT

    if ((-Not $explicitPort) -and ($portNames.Length -ne 1)) {
        Write-Output "We found ports:"
        Write-Output $portNames
        Write-Output "Please define an environment variable ARDUINO_COMM_PORT"
        exit
    }

    $commPort = if ($explicitPort) {$explicitPort} else {$portNames[0]} 

    $port= new-Object System.IO.Ports.SerialPort COM3,9600,None,8,one
    $port.ReadTimeout = 100
    $port
}