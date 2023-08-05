/*
 * File:   main.c
 * Author: fernando
 *
 * Created on 31 de Julho de 2023, 23:01
 */

#pragma config WDTE=OFF, LVP=OFF, FOSC=HS, DEBUG=OFF, BOREN=ON, PWRTE=ON
#define _XTAL_FREQ 11059200

#include <xc.h>
#include <stdlib.h>
#include <stdio.h>

#define DEBUG_OFF



typedef struct{
  uint8_t pressed;
  uint8_t x;
  uint16_t y;
}Key_t;

Key_t pressedKeys[5] = {0};
uint8_t pressedKeyIndex = 0;


void addPressedKey(Key_t key){
  if(pressedKeyIndex == 4){
    pressedKeyIndex = 0;
  }
  key.pressed = 1;
  pressedKeys[pressedKeyIndex] = key;
  pressedKeyIndex++;
}

void removePressedKey(int8_t pos){
  Key_t key={0};
  pressedKeys[pos] = key;
}

int8_t keyIsPressed(Key_t key){
  for(int8_t i=0; i < 5; i++){
    if(pressedKeys[i].x == key.x && pressedKeys[i].y == key.y && pressedKeys[i].pressed == 1){
      return i;
    }
  }
  return -1;
}


void pressKey(Key_t key){
  if(keyIsPressed(key) == -1){
    addPressedKey(key);
    //printf("PRESS: x=%02d y=%02d\r\n", key.x+1, key.y+1);
    printf("P%02d%02d;", key.x, key.y);
  }
}

void releaseKey(Key_t key){
  int8_t pressedPos=keyIsPressed(key);
  if(pressedPos >= 0){
    removePressedKey(pressedPos);
    //printf("RELEASE: x=%02d y=%02d\r\n", key.x+1, key.y+1);
    printf("R%02d%02d;", key.x, key.y);
  }
}



void putch(char data)
{
  while( ! TXIF)
    continue;
  TXREG = data;
}

void initPic(){
  ADCON1=0x06;
  TRISA=0xFF;
  TRISB=0xFF;
  nRBPU=0;
  TRISC=0xFF;
  TRISD=0xFF;
  TRISE=0xFF;
}


void initUsart(){
  TRISC7 = 1;
  TRISC6 = 0;
  TX9 = 0;
  RX9 = 0;
  TXEN = 1; 
  SYNC=0;
  BRGH=1;
  SPBRG=5;
  SPEN=1;
  CREN = 1;
}


void setXpos(uint8_t x){
  TRISC=0xFF;
  PORTC=0xFF;
  TRISD=0xFF;
  PORTD=0xFF;
  uint8_t tris = (uint8_t)~(1U << x);
  uint8_t port = (uint8_t)~(1U << x);
  if(x < 8){
    TRISD = tris;
    PORTD = port;
  }
  else{
    x = x-8;
    tris = (uint8_t)~(1U << x);
    port = (uint8_t)~(1U << x);
    TRISC = tris;
    PORTC = port;
  }
}
/*
uint16_t readAllYpos(){
  uint16_t ret=0;
  uint16_t row=0;
  if(PORTB != 0xFF){
    ret = ~PORTB;
    row = PORTC & 0x0F;
    row = row << 8;
    nRBPU=1;
    row = ~(row | PORTD);
    nRBPU=0;
    __delay_ms(10);
    printf("Y=%x, row=%x \r\n", ret, row);
  }
  return ret;
}*/

uint8_t readYpos(uint8_t y){
  uint8_t ret = 0;
  if(y < 8){
      ret = (~(PORTB) >> (7-y)) & 1;
      __delay_us(500);
  }
  else{
      ret = (~RA0) & 1;
      __delay_us(500);
  }
  return ret;
}





void scanKeyboard(){
  const uint8_t xMax=12;
  const uint8_t yMax=9;
  Key_t key;
  uint8_t ret;

  for(uint8_t x=0; x < xMax; x++){
    setXpos(x);
    key.x = x;
    for(uint8_t y=0; y < yMax; y++){
      key.y = y;
      ret = readYpos(y);
      if(ret != 0){
	pressKey(key);
      }
      else{
	releaseKey(key);
      }
    }
  }    
}			  

void main(void) {
  initPic();
  initUsart();
  printf("boot\r\n");
  while(1){

    scanKeyboard();

  }
  return;
}
