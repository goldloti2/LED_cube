This is for 8\*8\*8 LED cube, using 8 + 1 shift registers, version 4

vertex[z][x]

function:
+	show:	send data to registers once, need external loop to keep light
+	update:	update data showing when the next show() being called
+	light:	turn on all the LEDs
+	clear:	turn off all the LEDs
+	shift:	move LEDs, and the tail will put back to the head
+	move:	move LEDs, and the head will turn off

ver.2 added:
+	put vertex[][] back to private
	
+	get_cube:	copy vertex[][] to the outside array
+	change_vertex: change the status of the given LED (coordinate using (x, y, z))
	
ver.3 added:
+	change_row:	change whole row of LEDs in positive x, y, or z direction, coordinate using (xy, yz)
+	change_layer: change whole layer of LEDs, in positive direction, input should be [x]\<y>, [z]\<y>, [z]\<x>, which <> is byte

ver.4 added:(untested)
+	reverse:	change all LEDs status
+	turn:	turn the cube 90 degrees, where sight is parrelled to the positive coordinate directions
+	swap:	swap the order in one of the 3 directions