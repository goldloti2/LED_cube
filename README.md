This is for 8\*8\*8 LED cube, using 8 + 1 shift registers, version 1

vertex\[z\]\[x\]

function:
	show:	send data to registers once, need external loop to keep light
	update:	update data showing when the next show() being called
	light:	turn on all the LEDs
	clear:	turn off all the LEDs
	shift:	move LEDs, and the tail will put back to the head
	move:	move LEDs, and the head will turn off





also testing Markdown on github