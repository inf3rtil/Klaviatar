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

#define Y_0 RB0
#define Y_1 RB1
#define Y_2 RB2
#define Y_3 RB3
#define Y_4 RB4
#define Y_5 RB5
#define Y_6 RB6
#define Y_7 RB7
#define Y_8 RA0

#define X_0 RD0
#define X_1 RD1
#define X_2 RD2
#define X_3 RD3
#define X_4 RD4
#define X_5 RD5
#define X_6 RD6
#define X_7 RD7
#define X_8 RC0
#define X_9 RC1
#define X_10 RC2
#define X_11 RC3

struct Key_t{
  uint8_t x;
  uint16_t y;
};

void putch(char data)
{
  while( ! TXIF)
    continue;
  TXREG = data;
}

void initPic(){
  ADCON1=0x06;
  TRISA=0xCF;
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
  PORTC=0xFF;
  uint8_t tris = ~((uint8_t) 1 << x);
  uint8_t port = ~((uint8_t) 1 << x);
  if(x < 8){
    TRISD = tris;
    PORTD = port;
#ifdef DEBUG_ON
    __delay_ms(1000);
    printf("x=%d, TRISD=%x, PORTD=%x \r\n", x, tris, port);
#endif
  }
  else{
    x = x-8;
    tris = ~((uint8_t) 1 << x);
    port = ~((uint8_t) 1 << x);
    TRISC = tris;
    PORTC = port;
#ifdef DEBUG_ON
    __delay_ms(1000);
    x= x+8;
    printf("x=%d, TRISC=%x, PORTC=%x \r\n", x, tris, port);
#endif
  }
}

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
}

uint8_t readYpos(uint8_t y){
  uint8_t ret = 0;
  if(y <8){
    ret = (~(PORTB) >> y) & 1;
  }
  else{
    y = y-8;
    ret = (~RA0) & 1;
  }
  return ret;
}

void scanKeyboard(){
  const uint8_t xMax=12;
  const uint8_t yMax=9;
  struct Key_t key;
  uint8_t ret;

  for(uint8_t x=0; x < xMax; x++){
    setXpos(x);
    for(uint8_t y=0; y < yMax; y++){
      ret = readYpos(y);
      if(ret != 0){
	key.x = x;
	key.y = y;
	__delay_ms(10);
	printf("%02d%02d;", key.x, key.y);
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
