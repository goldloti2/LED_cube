#include "../../LedCube.h"

#define RAIN_TIME 80

const int CS = 7; //chip select pin

LedCube cube(CS);

uint64_t cube_timer;

void setup() {
  Serial.begin(9600);

  pinMode(CS, OUTPUT);
  SPI.begin();
  SPI.beginTransaction(SPISettings(8000000, MSBFIRST, SPI_MODE0));
  
  cube_timer = millis();

  for(uint8_t i = 0; i < 6; i++)
  {
    while(millis() - cube_timer <= 200)
      cube.show();
    
    if(cube.ifClear())
      cube.light();
    else
      cube.clear();

    cube_timer = millis();
  }

  randomSeed(millis());
}

void loop() {
  cube.show();
  rain();
}

void rain()
{
  if(millis() - cube_timer <= RAIN_TIME)
  {
    cube.move(NEG_Z);
    uint8_t rain_num = random(0, 5);
    for(uint8_t i = 0; i < rain_num; i++)
      cube.change_vertex(random(0, 8), random(0, 8), 7);
    cube_timer = millis();
  }
}

