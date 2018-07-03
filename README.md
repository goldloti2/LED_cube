This is for 8\*8\*8 LED cube, using 8 + 1 shift registers, version 2

vertex\[z\]\[x\]

function:
+	show:	send data to registers once, need external loop to keep light
+	update:	update data showing when the next show() being called
+	light:	turn on all the LEDs
+	clear:	turn off all the LEDs
+	shift:	move LEDs, and the tail will put back to the head
+	move:	move LEDs, and the head will turn off

ver.2 added:
+	put vertex[][] back to private
	
+	get_cube: copy vertex[][] to the outside array
+	change vertex: change the status of the given LED (coordinate using (x, y, z))





also testing Markdown on github