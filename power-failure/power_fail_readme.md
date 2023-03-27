- it has 2 sketches
- one on secondry esp [one with keypad]
- another for primary [one with camera]

### working
- on boot, secondry sends trigger[100ms pulse] to primary according to setSecondryMode func
- interrupt in primary is triggered by hardware pin getting high
- it sends serial message as "normal" to secondry
- baud rate is 9600. can be made 115200 for faster communication and thus boot
- setSecondryMode function keeps an eye for incoming comm at port 0
- if it recieves 'normal' then boot_mode variable is set to normal
- if not, boot_mode is by default power_failure and not changed by the function