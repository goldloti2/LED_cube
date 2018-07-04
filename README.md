This is for 8\*8\*8 LED cube, using 8 + 1 shift registers, version 4.1
-----
variable:
+	uint8_t vertex[z][x][y]:	cube status storage
+	uint8_t CS:	chip select pin
+	boolean clr_sts:	if no LED is lit, then it will be TRUE; otherwise will be FALSE

function:
+	test_show:	print vertex[][] into Serial
+	show:	send data to registers once, need external loop to keep light
+	update:	update vertex[][]
+	get_cube:	copy vertex[][] to the pointer parameter
+	light:	turn on all the LEDs
+	clear:	turn off all the LEDs
+	shift:	move LEDs, and the tail will put back to the head
+	move:	move LEDs, and the head will turn off
+	change_vertex: change the status of the given LED (coordinate using (x, y, z))
+	change_row:	change whole row of LEDs in positive x, y, or z direction, coordinate using (x, y), (y, z), or (x, z)
+	change_layer: change whole layer of LEDs, in positive direction, input should be [x]\<y>, [z]\<y>, [z]\<x>, which <> is byte
+	reverse:	change all LEDs status
+	turn:	turn the cube 90 degrees, where sight is parrelled to the positive coordinate directions
+	swap:	swap the order in one of the 3 directions
+	ifClear:	return clr_sts
-----

-ver.2 added:
+	put vertex[][] back to private
+	get_cube() added
+	change_vertex() added
	
-ver.3 added:
+	change_row() added
+	change_layer() added

-ver.4 added:
+	reverse() added
+	turn() added
+	swap() added

-ver.4.1 added:
+	add some extra code for the new features below
	
+	clr_sts added
+	ifClear() added