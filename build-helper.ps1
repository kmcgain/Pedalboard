
# https://community.spiceworks.com/scripts/show/4656-powershell-create-menu-easily-add-arrow-key-driven-menu-to-scripts
Function Create-Menu (){
    
    Param(
        [Parameter(Mandatory=$True)][String]$MenuTitle,
        [Parameter(Mandatory=$True)][array]$MenuOptions
    )

    $MaxValue = $MenuOptions.count-1
    $Selection = 0
    $EnterPressed = $False
    
    Clear-Host

    While($EnterPressed -eq $False){
        
        Write-Host "$MenuTitle"

        For ($i=0; $i -le $MaxValue; $i++){
            
            If ($i -eq $Selection){
                Write-Host -BackgroundColor Cyan -ForegroundColor Black "[ $($MenuOptions[$i]) ]"
            } Else {
                Write-Host "  $($MenuOptions[$i])  "
            }

        }

        $KeyInput = $host.ui.rawui.readkey("NoEcho,IncludeKeyDown").virtualkeycode

        Switch($KeyInput){
            13{
                $EnterPressed = $True
                Return $Selection
                Clear-Host
                break
            }

            38{
                If ($Selection -eq 0){
                    $Selection = $MaxValue
                } Else {
                    $Selection -= 1
                }
                Clear-Host
                break
            }

            40{
                If ($Selection -eq $MaxValue){
                    $Selection = 0
                } Else {
                    $Selection +=1
                }
                Clear-Host
                break
            }
            Default{
                Clear-Host
            }
        }
    }
}

function Get-Comm-Port {
    if (-Not [System.Environment]::GetEnvironmentVariable("ARDUINO_COMM_PORT", [System.EnvironmentVariableTarget]::User)) {
        $portNames =[System.IO.Ports.SerialPort]::getportnames()

        $sel = (Create-Menu "Please choose a COM port the arduino is plugged into" $portNames)
        [System.Environment]::SetEnvironmentVariable("ARDUINO_COMM_PORT", $portNames[$sel], [System.EnvironmentVariableTarget]::User)
    }
    return [System.Environment]::GetEnvironmentVariable("ARDUINO_COMM_PORT", [System.EnvironmentVariableTarget]::User)
}

function createSerialPort() {
    $portName = Get-Comm-Port

    $port= new-Object System.IO.Ports.SerialPort $portName,9600,None,8,one
    $port.ReadTimeout = 100
    $port
}

