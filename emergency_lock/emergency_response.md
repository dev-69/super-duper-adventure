### FUNCTIONS
- check the reed lock status
- check virtual door status
- conditions
	- if VDoor= open and rdoor= close
		- //door is closed. this will allow resetting the vdoor variable to close 
	- if vdoor= close and rdoor = open
		- //emergence response trigger
- emergwncy action
	- buzzer for 30 secs + message to owner
	- capture the image/ audio sample and send to owner
	- live camera and audion controll to owner

int doorStatusUpdate() return integer
0 - both status are same
1 - door was closed and code is updated
2 - emergency response triggered
