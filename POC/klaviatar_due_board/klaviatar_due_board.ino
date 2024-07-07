#include "Keyboard.h"

#define KEY_RUF 0xFF
#define KEY_FUNC 0x01

#define MACRO_MODE

#define PIC_nMCLR 9

const uint8_t keyMap[12][9] = {                          
  { 0, KEY_KP_9, KEY_KP_8, KEY_KP_7, KEY_LEFT_CTRL, 0, 0, 0, KEY_KP_MINUS },
  { 0, KEY_KP_PLUS, KEY_KP_DOT, KEY_KP_0, KEY_LEFT_SHIFT, KEY_LEFT_ALT, KEY_CAPS_LOCK, KEY_TAB, KEY_ESC },                                    
  { 0, KEY_KP_3, KEY_KP_2, KEY_KP_1, KEY_FUNC, 'z', 'a', 'q', '1' },         
  { 0, KEY_KP_6, KEY_KP_5, KEY_KP_4, 'x', 's', 'w', '2', KEY_F1 },                                       
  { KEY_F9, 0, KEY_F8, KEY_NUM_LOCK, 'c', 'd', 'e', '3', KEY_F2 },                                       
  { KEY_F6, 0, KEY_F7, KEY_BACKSPACE, 'v', 'f', 'r', '4', KEY_F3 },                                     
  { 0, 0xFF, KEY_RETURN, KEY_RIGHT_ARROW, ' ', 'b', 'g', 't', '5' },                                       
  { 0, '\\', KEY_UP_ARROW, KEY_DOWN_ARROW, 'n', 'h', 'y', '6', KEY_F4 },                                              
  { 0, '=', ']', '`', 'm', 'j', 'u', '7', KEY_F5 },                                     
  { 0, '-', '[', '\'', KEY_LEFT_ARROW, ',', 'k', 'i', '8' },                                                  
  { 0, '0', 'p', ';', '/', '.', 'l', 'o', '9' },                                                           
  { 0, 0, 0, 0, 0, 0, 0, 0, KEY_F10 }                                                                     
};

const uint8_t altKeyMap[12][9] = {                          
  { 0, KEY_KP_9, KEY_KP_8, KEY_KP_7, KEY_LEFT_CTRL, 0, 0, 0, KEY_KP_MINUS },
  { 0, KEY_KP_PLUS, KEY_KP_DOT, KEY_KP_0, KEY_LEFT_SHIFT, KEY_LEFT_ALT, KEY_CAPS_LOCK, KEY_TAB, KEY_ESC },                                    
  { 0, KEY_KP_3, KEY_KP_2, KEY_KP_1, KEY_FUNC, 'z', 'a', 'q', '1' },         
  { 0, KEY_KP_6, KEY_KP_5, KEY_KP_4, 'x', 's', 'w', '2', KEY_F1 },                                       
  { KEY_F9, 0, KEY_F8, KEY_NUM_LOCK, 'c', 'd', 'e', '3', KEY_F2 },                                       
  { KEY_F6, 0, KEY_F7, KEY_BACKSPACE, 'v', 'f', 'r', '4', KEY_F3 },                                     
  { 0, 0xFF, KEY_RETURN, KEY_RIGHT_ARROW, ' ', 'b', 'g', 't', '5' },                                       
  { 0, '\\', KEY_UP_ARROW, KEY_DOWN_ARROW, 'n', 'h', 'y', '6', KEY_F4 },                                              
  { 0, '=', ']', '`', 'm', 'j', 'u', '7', KEY_F5 },                                     
  { 0, '-', '[', '\'', KEY_LEFT_ARROW, ',', 'k', 'i', '8' },                                                  
  { 0, '0', 'p', ';', '/', '.', 'l', 'o', '9' },                                                           
  { 0, 0, 0, 0, 0, 0, 0, 0, KEY_F10 }                                                                  
};

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


void setup() {
  pinMode(PIC_nMCLR, OUTPUT);
  Serial1.begin(9600);
  Keyboard.begin();
}




void loop() {
  delay(1000);
  digitalWrite(PIC_nMCLR, HIGH);
  String key;
  String xStr;
  String yStr;
  char mode;
  uint8_t x;
  uint8_t y;
  uint8_t pressedKey;
  bool specialKey;
  unsigned long timeLastKey;
  specialKey_t pressedSpecialKeys[5] = { 0 };
  uint32_t lastKeepAlive = 0;
  delay(500);
  while (1) {
    if (Serial1.available() > 0) {
      // read incoming serial data:
      key = Serial1.readStringUntil(';');
      if (key) {
        if(key[0] == 'L'){
          lastKeepAlive = millis();
          continue;
        }
        xStr = "";
        yStr = "";
        timeLastKey = millis();
        mode = key[0];
        xStr.concat(key.charAt(1));
        xStr.concat(key.charAt(2));
        yStr.concat(key.charAt(3));
        yStr.concat(key.charAt(4));
        x = xStr.toInt();
        y = yStr.toInt();
        pressedKey = keyMap[x][y];
        //specialKey = false;
        /*for (uint8_t i = 0; i < 5; i++) {
          if (specialKeys[i].id == pressedKey) {
            specialKey = true;
          }
        }*/
        if (mode == 'P') {
          Keyboard.press(pressedKey);
        } else if (mode == 'R') {
          //if (!specialKey) {
            //Keyboard.releaseAll();
            Keyboard.release(pressedKey);
          //}
        }
      
    }
      if (millis() - timeLastKey > 10000) {
        Keyboard.releaseAll();
      }
    }
  }
}
