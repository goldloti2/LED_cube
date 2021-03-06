/*
This is for 8*8*8 LED cube, using 8 + 1 shift registers, version 4.1

vertex[z][x]

function:
	show:	send data to registers once, need external loop to keep light
	update:	update data showing when the next show() being called
	light:	turn on all the LEDs
	clear:	turn off all the LEDs
	shift:	move LEDs, and the tail will put back to the head
	move:	move LEDs, and the head will turn off

ver.2 added:
	put vertex[][] back to private
	
	get_cube:	copy vertex[][] to the outside array
	change_vertex: change the status of the given LED (coordinate using (x, y, z))
	
ver.3 added:
	change_row:	change whole row of LEDs in positive x, y, or z direction, coordinate using (xy, yz)
	change_layer: change whole layer of LEDs, in positive direction, input should be [x]<y>, [z]<y>, [z]<x>, which <> is byte

ver.4 added:
	reverse:	change all LEDs status
	turn:	turn the cube 90 degrees, where sight is parrelled to the positive coordinate directions
	swap:	swap the order in one of the 3 directions

ver.4.1 added:
	add some extra code for the new features below
	
	boolean clr_sts:	if no LED is lit, then it will be TRUE; otherwise will be FALSE
	ifClear:	return clr_sts
*/

#ifndef LED_CUBE_H
#define LED_CUBE_H

#define SIZE 8
#define SQUARE 64
#define CUBE 512

#define POS_X 0
#define NEG_X 1
#define POS_Y 2
#define NEG_Y 3
#define POS_Z 4
#define NEG_Z 5

#define X_ROW 0
#define Y_ROW 1
#define Z_ROW 2

#define XY_S 0
#define YZ_S 1
#define XZ_S 2

#define X_CLK 0
#define X_CNT 1
#define Y_CLK 2
#define Y_CNT 3
#define Z_CLK 4
#define Z_CNT 5

#define X_DIR 0
#define Y_DIR 1
#define Z_DIR 2


class LedCube
{
	public:
		LedCube(uint8_t select);
		~LedCube();
		
		void test_show();
		void show();
		void update(uint8_t in[][SIZE]);
		void get_cube(uint8_t out[][SIZE]);
		void light();
		void clear();
		void shift(uint8_t dir);
		void move(uint8_t dir);
		void change_vertex(uint8_t x, uint8_t y, uint8_t z);
		void change_row(uint8_t data, uint8_t type, uint8_t xy, uint8_t yz);
		void change_layer(uint8_t data[], uint8_t type, uint8_t layer);
		
		void reverse();
		void turn(uint8_t dir);
		void swap(uint8_t dir);
		
		bool ifClear();
	
	private:
		uint8_t vertex[SIZE][SIZE];
		uint8_t CS;
		bool clr_sts;
};


#endif
