/*
This is for 8*8*8 LED cube, using 8 + 1 shift registers, version 1

vertex[z][x]

function:
	show:	send data to registers once, need external loop to keep light
	update:	update data showing when the next show() being called
	light:	turn on all the LEDs
	clear:	turn off all the LEDs
	shift:	move LEDs, and the tail will put back to the head
	move:	move LEDs, and the head will turn off
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

class LedCube
{
	public:
		LedCube(uint8_t select);
		~LedCube();
		
		void test_show();
		void show();
		
		void update(uint8_t in[][SIZE]);
		void light();
		void clear();
		void shift(uint8_t dir);
		void move(uint8_t dir);
	
	public:
		uint8_t vertex[SIZE][SIZE];
	
	private:
		uint8_t CS;
		bool standBy;
};


#endif
