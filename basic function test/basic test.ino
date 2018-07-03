#include "LedCube.h"
/*
 * tested:
 *  show
 *  shift POS_X, NEG_X, POS_Y, NEG_Y, POS_Z, NEG_Z
 *  move POS_X, NEG_X, POS_Y, NEG_Y, POS_Z, NEG_Z
 *  light
 *  clear
 *  update
 *  
 * ver.2 tested:
 *  change_vertex
 * 
 * ver.3 tested:
 *  change_row X_ROW, Y_ROW, Z_ROW
 *  change_layer XY_S, YZ_S, XZ_S
 * 
 * ver.4 tested:
 *  reverse
 *  swap X_DIR, Y_DIR, Z_DIR
 *  turn X_CLK, X_CNT, Y_CLK, Y_CNT, Z_CLK, Z_CNT
 */
const int CS = 7;

LedCube cube(7);

uint8_t cntr;
uint8_t testC[SIZE][SIZE];

void setup() {
  Serial.begin(9600);
  pinMode(CS, OUTPUT);
  cntr = 0;
  cube.light();
  for(byte i = 0; i < SIZE; i++)
  {
    testC[i][0] = 157; //10011101
    testC[i][1] = 129; //10000001
    testC[i][2] = 177; //10110001
    testC[i][3] = 171; //10101011
    testC[i][4] = 230; //11100110
    testC[i][5] = 207; //11001111
    testC[i][6] = 131; //10000011
    testC[i][7] = 201; //11001001
  }
  cube.change_layer(testC[2], XY_S, 0);
}

void loop() {
  cube.test_show();
  while(!Serial.available()) ;
  while(Serial.available())
    Serial.read();
  Serial.println("-----------------");
  unsigned long fin;
  unsigned long sta = micros();
  cube.turn(X_CNT);
  //cube.swap(Z_DIR);
  //cube.reverse();
  //cube.change_layer(testC[0], XY_S, 5);
  //cube.change_row(157, X_ROW, 3, 5);
  //cube.change_vertex(3, 2, 6);
  //cube.shift(POS_Z);
  //cube.move(POS_Z);
  //cube.light();
  //cube.clear();
  //cube.update(testC);
  fin = micros();
  Serial.println(fin - sta);
  Serial.println("------------------");
  cntr++;
  /*uint8_t t = 0x01;
  Serial.println(t);
  t=t>>1;
  Serial.println(t);*/
  
}
