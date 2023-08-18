
// CONFIG1L
#pragma config PLLDIV = 1       // PLL Prescaler Selection bits (No prescale (4 MHz oscillator input drives PLL directly))
#pragma config CPUDIV = OSC1_PLL2// System Clock Postscaler Selection bits ([Primary Oscillator Src: /1][96 MHz PLL Src: /2])
#pragma config USBDIV = 1       // USB Clock Selection bit (used in Full-Speed USB mode only; UCFG:FSEN = 1) (USB clock source comes directly from the primary oscillator block with no postscale)

// CONFIG1H
#pragma config FOSC = INTOSC_HS        // Oscillator Selection bits (HS oscillator (HS))
#pragma config FCMEN = ON       // Fail-Safe Clock Monitor Enable bit (Fail-Safe Clock Monitor enabled)
#pragma config IESO = ON        // Internal/External Oscillator Switchover bit (Oscillator Switchover mode enabled)

// CONFIG2L
#pragma config PWRT = ON        // Power-up Timer Enable bit (PWRT enabled)
#pragma config BOR = OFF         // Brown-out Reset Enable bits (Brown-out Reset enabled in hardware only (SBOREN is disabled))
#pragma config BORV = 3         // Brown-out Reset Voltage bits (Minimum setting 2.05V)
#pragma config VREGEN = OFF     // USB Voltage Regulator Enable bit (USB voltage regulator disabled)

// CONFIG2H
#pragma config WDT = OFF        // Watchdog Timer Enable bit (WDT disabled (control is placed on the SWDTEN bit))
#pragma config WDTPS = 32768    // Watchdog Timer Postscale Select bits (1:32768)

// CONFIG3H
#pragma config CCP2MX = ON      // CCP2 MUX bit (CCP2 input/output is multiplexed with RC1)
#pragma config PBADEN = OFF      // PORTB A/D Enable bit (PORTB<4:0> pins are configured as analog input channels on Reset)
#pragma config LPT1OSC = OFF    // Low-Power Timer 1 Oscillator Enable bit (Timer1 configured for higher power operation)
#pragma config MCLRE = OFF       // MCLR Pin Enable bit (MCLR pin enabled; RE3 input pin disabled)

// CONFIG4L
#pragma config STVREN = ON      // Stack Full/Underflow Reset Enable bit (Stack full/underflow will cause Reset)
#pragma config LVP = OFF         // Single-Supply ICSP Enable bit (Single-Supply ICSP enabled)
#pragma config ICPRT = OFF      // Dedicated In-Circuit Debug/Programming Port (ICPORT) Enable bit (ICPORT disabled)
#pragma config XINST = OFF      // Extended Instruction Set Enable bit (Instruction set extension and Indexed Addressing mode disabled (Legacy mode))

// CONFIG5L
#pragma config CP0 = OFF        // Code Protection bit (Block 0 (000800-001FFFh) is not code-protected)
#pragma config CP1 = OFF        // Code Protection bit (Block 1 (002000-003FFFh) is not code-protected)
#pragma config CP2 = OFF        // Code Protection bit (Block 2 (004000-005FFFh) is not code-protected)
#pragma config CP3 = OFF        // Code Protection bit (Block 3 (006000-007FFFh) is not code-protected)

// CONFIG5H
#pragma config CPB = OFF        // Boot Block Code Protection bit (Boot block (000000-0007FFh) is not code-protected)
#pragma config CPD = OFF        // Data EEPROM Code Protection bit (Data EEPROM is not code-protected)

// CONFIG6L
#pragma config WRT0 = OFF       // Write Protection bit (Block 0 (000800-001FFFh) is not write-protected)
#pragma config WRT1 = OFF       // Write Protection bit (Block 1 (002000-003FFFh) is not write-protected)
#pragma config WRT2 = OFF       // Write Protection bit (Block 2 (004000-005FFFh) is not write-protected)
#pragma config WRT3 = OFF       // Write Protection bit (Block 3 (006000-007FFFh) is not write-protected)

// CONFIG6H
#pragma config WRTC = OFF       // Configuration Register Write Protection bit (Configuration registers (300000-3000FFh) are not write-protected)
#pragma config WRTB = OFF       // Boot Block Write Protection bit (Boot block (000000-0007FFh) is not write-protected)
#pragma config WRTD = OFF       // Data EEPROM Write Protection bit (Data EEPROM is not write-protected)

// CONFIG7L
#pragma config EBTR0 = OFF      // Table Read Protection bit (Block 0 (000800-001FFFh) is not protected from table reads executed in other blocks)
#pragma config EBTR1 = OFF      // Table Read Protection bit (Block 1 (002000-003FFFh) is not protected from table reads executed in other blocks)
#pragma config EBTR2 = OFF      // Table Read Protection bit (Block 2 (004000-005FFFh) is not protected from table reads executed in other blocks)
#pragma config EBTR3 = OFF      // Table Read Protection bit (Block 3 (006000-007FFFh) is not protected from table reads executed in other blocks)

// CONFIG7H
#pragma config EBTRB = OFF      // Boot Block Table Read Protection bit (Boot block (000000-0007FFh) is not protected from table reads executed in other blocks)

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.

//#define _XTAL_FREQ 11059200
#define _XTAL_FREQ 8000000

#include <xc.h>
#include <stdlib.h>
#include <stdio.h>

//#define DEBUG_PRESS_KEY
//#define DEBUG_X_SCAN
#define DEBUG_Y_SCAN

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
#ifdef DEBUG_PRESS_KEY
    printf("PRESS: x=%02d y=%02d\r\n", key.x+1, key.y+1);
#else
    printf("P%02d%02d;", key.x, key.y);
#endif
  }
}

void releaseKey(Key_t key){
  int8_t pressedPos=keyIsPressed(key);
  if(pressedPos >= 0){
    removePressedKey(pressedPos);
#ifdef DEBUG_PRESS_KEY
    printf("RELEASE: x=%02d y=%02d\r\n", key.x+1, key.y+1);
#else
    printf("R%02d%02d;", key.x, key.y);
#endif
  }
}

void putch(char data)
{
  while( ! TXIF)
    continue;
  TXREG = data;
}


// refactor
void initPic(){
  TRISB=0xFF;
  TRISA=0xFF;
  nRBPU=0;
  
  ADCON1=0x0F;
  /*TRISA=0xFF;
  TRISB=0xFF;
  nRBPU=0;
  TRISC=0xFF;
  TRISD=0xFF;
  TRISE=0xFF;
  */
}


void initUsart(){
  TRISC7 = 1;
  TRISC6 = 0;
  TX9 = 0;
  RX9 = 0;
  TXEN = 1; 
  SYNC=0;
  BRGH=1;
  SPBRG=51;
  SPEN=1;
  CREN = 1;
}


// refactor
void initTimer(){
  T0CS=0; // fosc/4 = 2764800 Hz
  PSA = 0;
  T0PS0 = 1;
  T0PS1 = 1;
  T0PS2 = 1;
}


// refactor
void setXpos(uint8_t x){
  TRISC=0xFF;
  PORTC=0xFF;
  TRISD=0xFF;
  PORTD=0xFF;
  TRISE=0xFF;
  PORTE = 0xFF;
  uint8_t tris = (uint8_t)~(1U << x);
  uint8_t port = (uint8_t)~(1U << x);
  if(x < 8){
    TRISD = tris;
    PORTD = port;
#ifdef DEBUG_X_SCAN
    printf("PORTD_SCAN-X=%d, T=%x, P=%x\r\n", x, tris, port);
    __delay_ms(500);
#endif
  }
  else if(x < 11){
    x = x-8;
    tris = (uint8_t)~(1U << x);
    port = (uint8_t)~(1U << x);
    TRISC = tris;
    PORTC = port;
  }
  else{
    TRISE=0;
    PORTE=0;
  }
}

// refactor
uint8_t readYpos(uint8_t y){
  uint8_t ret = 1;
  TRISB=0xFF;
  TRISA=0xFF;
  if(y < 6){
    ret = (PORTB >> y) & 1;
    __delay_us(500);
  }
  else {
    y = y - 6;
    ret = (PORTA >> y) & 1;
    __delay_us(500);
  }
  return ret;
}


void sendKeepAlive(){
  static uint32_t time=0;
  if(TMR0IF){
    TMR0IF = 0;
    time++;
  }
  if(time > 50){
    printf("L;");
    time = 0;
    }
}


void scanKeyboard(){
  const uint8_t xMax=12; //12
  const uint8_t yMax=9; //9
  Key_t key;
  uint8_t ret;

  for(uint8_t x=0; x < xMax; x++){
    setXpos(x);
    key.x = x;
    for(uint8_t y=0; y < yMax; y++){
      key.y = y;
      ret = readYpos(y);
      if(ret == 0){
	pressKey(key);
      }
      else{
	releaseKey(key);
      }
    }
  }
}			  

void main(void) {
  IRCF0=1;
  IRCF1=1;
  IRCF2=1;
  uint8_t rcon=RCON;
  initPic();
  initUsart();
  initTimer();
  printf("boot:%x\r\n", rcon);
  while(1){
    scanKeyboard();
    sendKeepAlive();
  }
  return;
}
