#include "Keyboard.h"

#define SR_SERIAL 9
#define SR_nOE 10
#define SR_RCLK 16
#define SR_SRCLK 14
#define SR_nSRCLR 15

char buffer[20];


const char keyMap[12][9] = {  { 0, 0, 0, 0, 0, 0, 0, 0, 0 }, //0
                        { 0, 0, 0, 0, 0, 0, KEY_CAPS_LOCK, KEY_TAB, KEY_ESC }, //1
                        { 0, 0, 0, 0, 0, 'z', 'a', 'q', '1' }, //2
                        { 0, 0, 0, 0, 'x', 's', 'w', '2', KEY_F1 }, //3
                        { KEY_F9, 0, KEY_F8, 0, 'c', 'd', 'e', '3', KEY_F2 }, //4
                        { KEY_F6, 0, KEY_F7, KEY_BACKSPACE, 'v', 'f', 'r', '4', KEY_F3 }, //5
                        { 0, 0, KEY_RETURN, KEY_RIGHT_ARROW, ' ', 'b', 'g', 't', '5' }, //6
                        { '\\', 0, KEY_UP_ARROW, KEY_DOWN_ARROW, 'n', 'h', 'y', '6', KEY_F4 }, //7
                        { 0, 0, ']', '`', 'm', 'j', 'u', '7', KEY_F5 }, //8
                        { '-', 0, '[', '\'', KEY_LEFT_ARROW, ',', 'k', 'i', '8' }, //9
                        { '0', 0, 'p', ';', '/', '.', 'l', 'o', '9' }, //10
                        { 0, KEY_F10, 0, 0, 0, 0, 0, 0, 0 } //11
                        };

const char altKeyMap[12][9] = {  { 0, 0, 0, 0, 0, 0, 0, 0, 0 }, //0
                        { 0, 0, 0, 0, 0, 0, KEY_CAPS_LOCK, KEY_TAB, KEY_ESC }, //1
                        { 0, 0, 0, 0, 0, 'Z', 'A', 'Q', '!' }, //2
                        { 0, 0, 0, 0, 'X', 'S', 'W', '@', KEY_F1 }, //3
                        { KEY_F9, 0, KEY_F8, 0, 'C', 'D', 'E', '#', KEY_F2 }, //4
                        { KEY_F6, 0, KEY_F7, KEY_BACKSPACE, 'V', 'F', 'R', '$', KEY_F3 }, //5
                        { 0, 0, KEY_RETURN, 0, ' ', 'B', 'G', 'T', '%' }, //6
                        { '|', 0, KEY_UP_ARROW, 0, 'N', 'H', 'Y', '^', KEY_F4 }, //7
                        { 0, 0, ']', '~', 'M', 'J', 'U', '&', KEY_F5 }, //8
                        { '_', 0, '{', '¨', KEY_LEFT_ARROW, '<', 'K', 'I', '*' }, //9
                        { ')', 0, 'P', ':', '?', '>', 'L', 'O', '(' }, //10
                        { 0, KEY_F10, 0, 0, 0, 0, 0, 0, 0 } //11
                        };

typedef struct {
  char id;
  uint8_t x;
  uint8_t y;
}specialKey_t;

const specialKey_t specialKeys[5]={
  {.id=KEY_LEFT_SHIFT, .x=0, .y=4},
  {.id=KEY_LEFT_CTRL, .x=1, .y=4},
  {.id=KEY_LEFT_ALT, .x=1, .y=5},
  {.id=0xFE, .x=0, .y=7},
  {.id=0xFF, .x=2, .y=4}
};

void writeRegister(uint16_t value)
{
  //digitalWrite(SR_nOE, HIGH); //3 state out on
  
  //digitalWrite(SR_nSRCLR, LOW);
  digitalWrite(SR_nSRCLR, HIGH); //clear

  for(uint8_t x = 0; x < 12; x++)
  {
    digitalWrite(SR_SERIAL, (value & 1));
    digitalWrite(SR_SRCLK, LOW);

    digitalWrite(SR_SRCLK, HIGH);

    value = value >> 1;
  }
    digitalWrite(SR_RCLK, HIGH);
    delay(1);
    digitalWrite(SR_RCLK, LOW);
    delay(1);
  
  digitalWrite(SR_nOE, LOW); //3 state out off
}

void setup() { 
  pinMode(0, INPUT_PULLUP);
  pinMode(1, INPUT_PULLUP);
  pinMode(2, INPUT_PULLUP);
  pinMode(3, INPUT_PULLUP);
  pinMode(4, INPUT_PULLUP);
  pinMode(5, INPUT_PULLUP);
  pinMode(6, INPUT_PULLUP);
  pinMode(7, INPUT_PULLUP);
  pinMode(8, INPUT_PULLUP);
  pinMode(SR_SERIAL, OUTPUT);
  pinMode(SR_nOE, OUTPUT);
  pinMode(SR_RCLK , OUTPUT);
  pinMode(SR_SRCLK, OUTPUT);
  pinMode(SR_nSRCLR, OUTPUT);
  
  Keyboard.begin();
}

void loop() {
uint16_t srValue = 0xFFFE;
bool counterStarted = false;
bool specialKey = false;
char lastKey = 0;
char key = 0;
unsigned long time;
unsigned long timeLastKeyPress;
while (1) {
  writeRegister(0xFFFF);
  srValue = 0xFFFE;
  for (int x = 0; x < 12; x++) {
    digitalWrite(SR_SERIAL, (srValue & 1));
    digitalWrite(SR_SRCLK, LOW);
    digitalWrite(SR_SRCLK, HIGH);
    delay(1);
    digitalWrite(SR_RCLK, HIGH);
    digitalWrite(SR_RCLK, LOW);
    srValue = srValue >> 1;
    if(millis() - timeLastKeyPress > 60){
      timeLastKeyPress = 0;
      lastKey = 0;
    }
    for (int y = 0; y < 9; y++) {

      for (int key = 0; key < 5; key++) {
        if (specialKeys[key].x == x && specialKeys[key].y == y) {
          specialKey = true;
          break;
        }
      }
      if (specialKey == true) {
        specialKey = false;
        continue;
      } else if (digitalRead(y) == LOW) {
        //sprintf(buffer, "Key - x=%d y=%d", x, y);
        //Keyboard.println(buffer);
        key = keyMap[x][y];
        timeLastKeyPress = millis();
        if (lastKey == key) {
          
          if(counterStarted == false){
            time = millis();
            counterStarted=true;
            continue;
          }
          else if((millis() - time) > 500){
            counterStarted=false;
          }
          else{
            continue;
          }
        }
        else{
          counterStarted=false;
        }
        Keyboard.write(key);
        lastKey = key;
        delay(20);
      }
    }
  }
}
}
