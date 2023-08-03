#include "Keyboard.h"

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


void setup() {
  Serial1.begin(115200);
  Keyboard.begin();
}


  

void loop() {
  String key;
  String xStr;
  String yStr;
  String debug;
  uint8_t x;
  uint8_t y;
  if (Serial1.available() > 0) {
    // read incoming serial data:
    key = Serial1.readStringUntil(';');
    if(key){
      xStr.concat(key.charAt(0));
      xStr.concat(key.charAt(1));
      yStr.concat(key.charAt(2));
      yStr.concat(key.charAt(3));
      x = xStr.toInt();
      y = yStr.toInt();
      Keyboard.write(keyMap[x][y+1]);
    }
  }
}
  
