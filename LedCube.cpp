#include <Arduino.h>
#include <SPI.h>
#include <string.h>
#include "LedCube.h"

LedCube::LedCube(uint8_t select)
{
	CS = select;
	clear();
}

LedCube::~LedCube()
{
	
}

void LedCube::test_show()
{
	for(uint8_t i = 0; i < SIZE; i++)
  {
    for(uint8_t j = 0; j < SIZE; j++)
      Serial.println(vertex[i][j], BIN);
    Serial.println(i);
    Serial.println();
  }
}

void LedCube::show()
{
	for(uint8_t i = 0; i < SIZE; i++)
	{
		digitalWrite(CS, LOW);
		
		SPI.transfer(0x01 << i);
		
		SPI.transfer(vertex[i], SIZE);
		
		digitalWrite(CS, HIGH);
	}
}

void LedCube::update(uint8_t in[][SIZE])
{
	memcpy(vertex, in, SQUARE);
}

void LedCube::get_cube(uint8_t out[][SIZE])
{
	memcpy(out, vertex, SQUARE);
}

void LedCube::light()
{
	memset(vertex, ~0x00, SQUARE);
}

void LedCube::clear()
{
	memset(vertex, 0x00, SQUARE);
}

void LedCube::shift(uint8_t dir)
{
	uint8_t temp[SIZE];
	switch(dir)
	{
		case POS_X:
			for(uint8_t i = 0; i < SIZE; i++)
			{
				uint8_t temp = vertex[i][SIZE - 1];
				for(uint8_t j = SIZE - 1; j > 0; j--)
					vertex[i][j] = vertex[i][j - 1];
				vertex[i][0] = temp;
			}
			break;
		case NEG_X:
			for(uint8_t i = 0; i < SIZE; i++)
			{
				uint8_t temp = vertex[i][0];
				for(uint8_t j = 0; j < SIZE - 1; j++)
					vertex[i][j] = vertex[i][j + 1];
				vertex[i][SIZE - 1] = temp;
			}
			break;
		case POS_Y:
			for(uint8_t i = 0; i < SIZE; i++)
			{
				for(uint8_t j = 0; j < SIZE; j++)
				{
					uint8_t temp = vertex[i][j] & (0x01 << (SIZE - 1));
					vertex[i][j] = vertex[i][j] << 1;
					vertex[i][j] = vertex[i][j] | (temp >> (SIZE - 1));
				}
			}
			break;
		case NEG_Y:
			for(uint8_t i = 0; i < SIZE; i++)
			{
				for(uint8_t j = 0; j < SIZE; j++)
				{
					uint8_t temp = vertex[i][j] & 0x01;
					vertex[i][j] = vertex[i][j] >> 1;
					vertex[i][j] = vertex[i][j] | (temp << (SIZE - 1));
				}
			}
			break;
		case POS_Z:
			memcpy(temp, vertex[SIZE - 1], SIZE);
			memmove(vertex[1], vertex[0], SIZE * (SIZE - 1));
			memcpy(vertex[0], temp, SIZE);
			break;
		case NEG_Z:
			memcpy(temp, vertex[0], SIZE);
			memmove(vertex[0], vertex[1], SIZE * (SIZE - 1));
			memcpy(vertex[SIZE - 1], temp, SIZE);
			break;
	}
}

void LedCube::move(uint8_t dir)
{
	switch(dir)
	{
		case POS_X:
			for(uint8_t i = 0; i < SIZE; i++)
			{
				for(uint8_t j = SIZE - 1; j > 0; j--)
					vertex[i][j] = vertex[i][j - 1];
				vertex[i][0] = 0;
			}
			break;
		case NEG_X:
			for(uint8_t i = 0; i < SIZE; i++)
			{
				for(uint8_t j = 0; j < SIZE - 1; j++)
					vertex[i][j] = vertex[i][j + 1];
				vertex[i][SIZE - 1] = 0;
			}
			break;
		case POS_Y:
			for(uint8_t i = 0; i < SIZE; i++)
			{
				for(uint8_t j = 0; j < SIZE; j++)
					vertex[i][j] = vertex[i][j] << 1;
			}
			break;
		case NEG_Y:
			for(uint8_t i = 0; i < SIZE; i++)
			{
				for(uint8_t j = 0; j < SIZE; j++)
					vertex[i][j] = vertex[i][j] >> 1;
			}
			break;
		case POS_Z:
			memmove(vertex[1], vertex[0], SIZE * (SIZE - 1));
			memset(vertex[0], 0x00, SIZE);
			break;
		case NEG_Z:
			memmove(vertex[0], vertex[1], SIZE * (SIZE - 1));
			memset(vertex[SIZE - 1], 0x00, SIZE);
			break;
	}
}

void LedCube::change_vertex(uint8_t x, uint8_t y, uint8_t z)
{
	vertex[z][x] = vertex[z][x] ^ (0x01 << y);
}

void LedCube::change_row(uint8_t data, uint8_t type, uint8_t xy, uint8_t yz)
{
	if(type == X_ROW)
	{
		uint8_t target = 0x01 << xy;
		for(uint8_t i = 0; i < SIZE; i++)
		{
			uint8_t temp = data & (0x01 << i);
			if(temp)
				vertex[yz][i] = vertex[yz][i] | target;
			else
				vertex[yz][i] = vertex[yz][i] & ~target;
		}
	}
	else if(type == Y_ROW)
	{
		vertex[yz][xy] = data;
	}
	else if(type == Z_ROW)
	{
		uint8_t target = 0x01 << yz;
		for(uint8_t i = 0; i < SIZE; i++)
		{
			uint8_t temp = data & (0x01 << i);
			if(temp)
				vertex[i][xy] = vertex[i][xy] | target;
			else
				vertex[i][xy] = vertex[i][xy] & ~target;
		}
	}
}

void LedCube::change_layer(uint8_t data[], uint8_t type, uint8_t layer)
{	//[x]<y>, [z]<y>, [z]<x>
	if(type == XY_S)
	{
		memcpy(vertex[layer], data, SIZE);
	}
	else if(type == YZ_S)
	{
		for(uint8_t i = 0; i < SIZE; i++)
			vertex[i][layer] = data[i];
	}
	else if(type == XZ_S)
	{
		uint8_t target = 0x01 << layer;
		for(uint8_t i = 0; i < SIZE; i++)
		{
			for(uint8_t j = 0; j < SIZE; j++)
			{
			uint8_t temp = data[i] & (0x01 << j);
			if(temp)
				vertex[i][j] = vertex[i][j] | target;
			else
				vertex[i][j] = vertex[i][j] & ~target;
			}
		}
	}
}

void LedCube::reverse()
{
	for(uint8_t i = 0; i < SIZE; i++)
	{
		for(uint8_t j = 0; j < SIZE; j++)
			vertex[i][j] = ~vertex[i][j];
	}
}

void LedCube::turn(uint8_t dir)
{
	uint8_t temp[SIZE][SIZE];
	
	if(dir == X_CLK)
	{
		memset(temp, 0, SQUARE);
		
		for(uint8_t i = 0; i < SIZE; i++)
		{
			uint8_t t = SIZE - i - 1;
			uint8_t putB = 0x01 << i;
			for(uint8_t j = 0; j < SIZE; j++)
			{
				uint8_t getB = 0x01 << j;
				for(uint8_t k = 0; k < SIZE; k++)
				{
					uint8_t ck = vertex[t][k] & getB;
					if(ck)
						temp[j][k] = temp[j][k] | putB;
				}
			}
		}
		memcpy(vertex, temp, SQUARE);
	}
	else if(dir == X_CNT)
	{
		memset(temp, 0, SQUARE);
		
		for(uint8_t i = 0; i < SIZE; i++)
		{
			uint8_t getB = 0x01 << (SIZE - i - 1);
			for(uint8_t j = 0; j < SIZE; j++)
			{
				uint8_t putB = 0x01 << j;
				for(uint8_t k = 0; k < SIZE; k++)
				{
					uint8_t ck = vertex[j][k] & getB;
					if(ck)
						temp[i][k] = temp[i][k] | putB;
				}
			}
		}
		memcpy(vertex, temp, SQUARE);
	}
	else if(dir == Y_CLK)
	{
		memcpy(temp, vertex, SQUARE);
		
		for(uint8_t i = 0; i < SIZE; i++)
		{
			uint8_t t = SIZE - i - 1;
			for(uint8_t j = 0; j < SIZE; j++)
				vertex[i][j] = temp[j][t];
		}
	}
	else if(dir == Y_CNT)
	{
		memcpy(temp, vertex, SQUARE);
		
		for(uint8_t i = 0; i < SIZE; i++)
		{
			uint8_t t = SIZE - i - 1;
			for(uint8_t j = 0; j < SIZE; j++)
				vertex[j][i] = temp[t][j];
		}
	}
	else if(dir == Z_CLK)
	{
		memset(temp, 0, SQUARE);
		
		for(uint8_t i = 0; i < SIZE; i++)
		{
			uint8_t getB = 0x01 << (SIZE - i - 1);
			for(uint8_t j = 0; j < SIZE; j++)
			{
				uint8_t putB = 0x01 << j;
				for(uint8_t k = 0; k < SIZE; k++)
				{
					uint8_t ck = vertex[k][j] & getB;
					if(ck)
						temp[k][i] = temp[k][i] | putB;
				}
			}
		}
		memcpy(vertex, temp, SQUARE);
	}
	else if(dir == Z_CNT)
	{
		memset(temp, 0, SQUARE);
		
		for(uint8_t i = 0; i < SIZE; i++)
		{
			uint8_t putB = 0x01 << i;
			uint8_t t = SIZE - i - 1;
			for(uint8_t j = 0; j < SIZE; j++)
			{
				uint8_t getB = 0x01 << j;
				for(uint8_t k = 0; k < SIZE; k++)
				{
					uint8_t ck = vertex[k][t] & getB;
					if(ck)
						temp[k][j] = temp[k][j] | putB;
				}
			}
		}
		memcpy(vertex, temp, SQUARE);
	}
}

uint8_t swap_T[16] = {0x0, 0x8, 0x4, 0xc, 0x2, 0xa, 0x6, 0xe,
					  0x1, 0x9, 0x5, 0xd, 0x3, 0xb, 0x7, 0xf};

void LedCube::swap(uint8_t dir)
{
	if(dir == X_DIR)
	{
		for(uint8_t i = 0; i < SIZE; i++)
		{
			for(uint8_t j = 0; j < 4; j++)
			{
				uint8_t temp = vertex[i][j];
				vertex[i][j] = vertex[i][SIZE - j - 1];
				vertex[i][SIZE - j - 1] = temp;
			}
		}
	}
	else if(dir == Y_DIR)
	{
		for(uint8_t i = 0; i < SIZE; i++)
		{
			for(uint8_t j = 0; j < SIZE; j++)
				vertex[i][j] = swap_T[vertex[i][j] & 0xf] << 4 | swap_T[vertex[i][j] >> 4];
		}
	}
	else if(dir == Z_DIR)
	{
		for(uint8_t i = 0; i < 4; i++)
		{
			uint8_t temp[SIZE];
			memmove(temp, vertex[i], SIZE);
			memmove(vertex[i], vertex[SIZE - i - 1], SIZE);
			memmove(vertex[SIZE - i - 1], temp, SIZE);
		}
	}
}
