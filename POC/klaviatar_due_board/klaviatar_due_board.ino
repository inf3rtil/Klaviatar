#include "Keyboard.h"

#define SR_SERIAL 9
#define SR_nOE 10
#define SR_RCLK 16
#define SR_SRCLK 14
#define SR_nSRCLR 15

#define KEY_RUF 0xFF
#define KEY_FUNC 0x01

#define MACRO_MODE
#define LAYOUT_MODE COMPAT

char buffer[20];



#ifndef LAYOUT_MODE == REAL
const uint8_t keyMap[12][9] = {
  { KEY_KP_9, 0, KEY_KP_8, KEY_KP_7, KEY_LEFT_SHIFT, 0, 0, 0, KEY_KP_MINUS },                              //0
  { KEY_KP_PLUS, 0, KEY_KP_DOT, KEY_KP_0, KEY_LEFT_CTRL, KEY_LEFT_ALT, KEY_CAPS_LOCK, KEY_TAB, KEY_ESC },  //1
  { KEY_KP_3, 0, KEY_KP_2, KEY_KP_1, KEY_FUNC, 'z', 'a', 'q', '1' },                                       //2
  { '6', 0, '5', KEY_KP_4, 'x', 's', 'w', '2', KEY_F1 },                                                   //3
  { KEY_F9, 0, KEY_F8, KEY_NUM_LOCK, 'c', 'd', 'e', '3', KEY_F2 },                                         //4
  { KEY_F6, 0, KEY_F7, KEY_BACKSPACE, 'v', 'f', 'r', '4', KEY_F3 },                                        //5
  { 0xFF, 0, KEY_RETURN, KEY_RIGHT_ARROW, ' ', 'b', 'g', 't', '5' },                                       //6
  { '\\', 0, KEY_UP_ARROW, KEY_DOWN_ARROW, 'n', 'h', 'y', '6', KEY_F4 },                                   //7
  { '=', 0, ']', '`', 'm', 'j', 'u', '7', KEY_F5 },                                                        //8
  { '-', 0, '[', '\'', KEY_LEFT_ARROW, ',', 'k', 'i', '8' },                                               //9
  { '0', 0, 'p', ';', '/', '.', 'l', 'o', '9' },                                                           //10
  { 0, KEY_F10, 0, 0, 0, 0, 0, 0, 0 }                                                                      //11
};

const uint8_t altKeyMap[12][9] = {
  { KEY_KP_9, 0, KEY_KP_8, KEY_KP_7, KEY_LEFT_SHIFT, 0, 0, 0, KEY_KP_MINUS },                              //0
  { KEY_KP_PLUS, 0, KEY_KP_DOT, KEY_KP_0, KEY_LEFT_CTRL, KEY_LEFT_ALT, KEY_CAPS_LOCK, KEY_TAB, KEY_ESC },  //1
  { KEY_KP_3, 0, KEY_KP_2, KEY_KP_1, KEY_FUNC, 'Z', 'A', 'Q', '!' },                                       //2
  { KEY_KP_6, 0, KEY_KP_5, KEY_KP_4, 'X', 'S', 'W', '@', KEY_F1 },                                         //3
  { KEY_F11, 0, KEY_F8, KEY_NUM_LOCK, 'C', 'D', 'E', '#', KEY_F2 },                                        //4
  { KEY_F6, 0, KEY_F7, KEY_BACKSPACE, 'V', 'F', 'R', '$', KEY_F3 },                                        //5
  { 0xFF, 0, KEY_RETURN, 0, ' ', 'B', 'G', 'T', '%' },                                                     //6
  { '|', 0, KEY_UP_ARROW, 0, 'N', 'H', 'Y', '^', KEY_F4 },                                                 //7
  { '+', 0, ']', '~', 'M', 'J', 'U', '&', KEY_F5 },                                                        //8
  { '_', 0, '{', '¨', KEY_LEFT_ARROW, '<', 'K', 'I', '*' },                                                //9
  { ')', 0, 'P', ':', '?', '>', 'L', 'O', '(' },                                                           //10
  { 0, KEY_F12, 0, 0, 0, 0, 0, 0, 0 }                                                                      //11
};

#elif LAYOUT_MODE == COMPAT

const uint8_t keyMap[12][9] = {
  { KEY_KP_9, 0, KEY_KP_8, KEY_KP_7, KEY_LEFT_CTRL, 0, 0, 0, KEY_KP_MINUS },                              //0
  { KEY_KP_PLUS, 0, KEY_KP_DOT, KEY_KP_0, KEY_LEFT_SHIFT, KEY_FUNC, KEY_CAPS_LOCK, KEY_TAB, KEY_ESC },  //1
  { KEY_KP_3, 0, KEY_KP_2, KEY_KP_1, KEY_LEFT_ALT, 'z', 'a', 'q', '1' },                                       //2
  { '6', 0, '5', KEY_KP_4, 'x', 's', 'w', '2', KEY_F1 },                                                   //3
  { KEY_F9, 0, KEY_F8, KEY_NUM_LOCK, 'c', 'd', 'e', '3', KEY_F2 },                                         //4
  { KEY_F6, 0, KEY_F7, KEY_BACKSPACE, 'v', 'f', 'r', '4', KEY_F3 },                                        //5
  { 0xFF, 0, KEY_RETURN, KEY_RIGHT_ARROW, ' ', 'b', 'g', 't', '5' },                                       //6
  { '\\', 0, KEY_UP_ARROW, KEY_DOWN_ARROW, 'n', 'h', 'y', '6', KEY_F4 },                                   //7
  { '=', 0, ']', '`', 'm', 'j', 'u', '7', KEY_F5 },                                                        //8
  { '-', 0, '[', '\'', KEY_LEFT_ARROW, ',', 'k', 'i', '8' },                                               //9
  { '0', 0, 'p', ';', '/', '.', 'l', 'o', '9' },                                                           //10
  { 0, KEY_F10, 0, 0, 0, 0, 0, 0, 0 }                                                                      //11
};

const uint8_t altKeyMap[12][9] = {
  { KEY_KP_9, 0, KEY_KP_8, KEY_KP_7, KEY_LEFT_CTRL, 0, 0, 0, KEY_KP_MINUS },                              //0
  { KEY_KP_PLUS, 0, KEY_KP_DOT, KEY_KP_0, KEY_LEFT_SHIFT, KEY_FUNC, KEY_CAPS_LOCK, KEY_TAB, KEY_ESC },  //1
  { KEY_KP_3, 0, KEY_KP_2, KEY_KP_1, KEY_LEFT_ALT, 'Z', 'A', 'Q', '!' },                                       //2
  { KEY_KP_6, 0, KEY_KP_5, KEY_KP_4, 'X', 'S', 'W', '@', KEY_F1 },                                         //3
  { KEY_F11, 0, KEY_F8, KEY_NUM_LOCK, 'C', 'D', 'E', '#', KEY_F2 },                                        //4
  { KEY_F6, 0, KEY_F7, KEY_BACKSPACE, 'V', 'F', 'R', '$', KEY_F3 },                                        //5
  { 0xFF, 0, KEY_RETURN, 0, ' ', 'B', 'G', 'T', '%' },                                                     //6
  { '|', 0, KEY_UP_ARROW, 0, 'N', 'H', 'Y', '^', KEY_F4 },                                                 //7
  { '+', 0, ']', '~', 'M', 'J', 'U', '&', KEY_F5 },                                                        //8
  { '_', 0, '{', '¨', KEY_LEFT_ARROW, '<', 'K', 'I', '*' },                                                //9
  { ')', 0, 'P', ':', '?', '>', 'L', 'O', '(' },                                                           //10
  { 0, KEY_F12, 0, 0, 0, 0, 0, 0, 0 }                                                                      //11
};

#endif



typedef struct {
  uint8_t id;
  uint8_t x;
  uint8_t y;
} specialKey_t;

const specialKey_t specialKeys[5] = {
  { .id = KEY_LEFT_SHIFT, .x = 0, .y = 4 },
  { .id = KEY_LEFT_CTRL, .x = 1, .y = 4 },
  { .id = KEY_LEFT_ALT, .x = 1, .y = 5 },
  { .id = 0xFE, .x = 0, .y = 7 },
  { .id = KEY_FUNC, .x = 2, .y = 4 }
};

void writeRegister(uint16_t value) {
  //digitalWrite(SR_nOE, HIGH); //3 state out on

  //digitalWrite(SR_nSRCLR, LOW);
  digitalWrite(SR_nSRCLR, HIGH);  //clear

  for (uint8_t x = 0; x < 12; x++) {
    digitalWrite(SR_SERIAL, (value & 1));
    digitalWrite(SR_SRCLK, LOW);

    digitalWrite(SR_SRCLK, HIGH);

    value = value >> 1;
  }
  digitalWrite(SR_RCLK, HIGH);
  delay(1);
  digitalWrite(SR_RCLK, LOW);
  delay(1);

  digitalWrite(SR_nOE, LOW);  //3 state out off
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
  pinMode(SR_RCLK, OUTPUT);
  pinMode(SR_SRCLK, OUTPUT);
  pinMode(SR_nSRCLR, OUTPUT);

  Keyboard.begin();
}

void writeKeyMatrix(uint16_t *value)
{
  digitalWrite(SR_SERIAL, (*value & 1));
  digitalWrite(SR_SRCLK, LOW);
  digitalWrite(SR_SRCLK, HIGH);
  delay(1);
  digitalWrite(SR_RCLK, HIGH);
  digitalWrite(SR_RCLK, LOW);
  *value = *value >> 1;
}

uint8_t getKey(const bool enableAltKeyMap, const uint8_t x, const uint8_t y)
{
  uint8_t key=0;
  if (false == enableAltKeyMap) {
    key = keyMap[x][y];
  } else {
    key = altKeyMap[x][y];
  }
  return key;
}

bool isSpecialKey(const uint8_t key){
  bool ret=false;
  for (int keySpecial = 0; keySpecial < 5; keySpecial++){
    if (specialKeys[keySpecial].id == key) {
      ret=true;
      break;
    }
  }
  return ret;
}

//void processKeyPress(const uint8_t key){
  

void loop() {
  uint16_t srValue = 0xFFFF;
  bool counterStarted = false;
  bool specialKey = false;
  bool caps = false;
  uint8_t lastKey = 0;
  uint8_t key = 0;
  unsigned long time;
  unsigned long timeLastKeyPress;
  bool macroMode = false;
  while (1) {
    writeRegister(0xFFFF);
    srValue = 0xFFFE;
    if (millis() - timeLastKeyPress > 100) {
      timeLastKeyPress = 0;
      lastKey = 0;
    }  
    for (int x = 0; x < 12; x++) {
      writeKeyMatrix(&srValue);
      for (int y = 0; y < 9; y++) {
	if (digitalRead(y) == LOW) {
	  timeLastKeyPress = millis();
	  key = getKey(false, x, y);
	  specialKey = isSpecialKey(key);
	  
	  if (lastKey == key) {
	    if (counterStarted == false) {
	      time = millis();
	      counterStarted = true;
	      continue;
	    } else if ((millis() - time) > 500) {
	      counterStarted = false;
	    } else {
	      continue;
	    }
	  }
	    counterStarted = false;
	  lastKey = key;
	  //check if special key
	  if(specialKey){
	      Keyboard.press(key);
	      break;
	  }
	    
	  if (!specialKey) {
	    Keyboard.write(key);
	    Keyboard.releaseAll();
	  }
	  specialKey = false;
#ifdef DEBUG
	  sprintf(buffer, "Key=%x x=%d y=%d", key, x, y);
	  Keyboard.println(buffer);
#endif
	  while(digitalRead(y) == LOW);
	  delay(10);
	}
      }
    }
  }
}
  
