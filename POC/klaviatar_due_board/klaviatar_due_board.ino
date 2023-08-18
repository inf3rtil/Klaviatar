#include "Keyboard.h"

#define KEY_RUF 0xFF
#define KEY_FUNC 0x01

#define MACRO_MODE
#define LAYOUT_MODE_COMPAT

#define PIC_nMCLR 9

#ifdef LAYOUT_MODE_REAL
const uint8_t keyMap[12][9] = {
  { KEY_KP_MINUS, 0, 0, 0, KEY_LEFT_SHIFT, KEY_KP_7, KEY_KP_8, 0, KEY_KP_9 },                              //0
  { KEY_ESC, KEY_TAB, KEY_CAPS_LOCK, KEY_LEFT_ALT, KEY_LEFT_CTRL, KEY_KP_0, KEY_KP_DOT, 0, KEY_KP_PLUS },  //1
  { '1', 'q', 'a', 'z', KEY_FUNC, KEY_KP_1, KEY_KP_2, 0, KEY_KP_3 },                                       //2
  { KEY_F1, '2', 'w', 's', 'x', KEY_KP_4, '5', 0, '6' },                                                   //3
  { KEY_F2, '3', 'e', 'd', 'c', KEY_NUM_LOCK, KEY_F8, 0, KEY_F9 },                                         //4
  { KEY_F3, '4', 'r', 'f', 'v', KEY_BACKSPACE, KEY_F7, 0, KEY_F6 },                                        //5
  { '5', 't', 'g', 'b', ' ', KEY_RIGHT_ARROW, KEY_RETURN, 0xFF, 0 },                                       //6
  { KEY_F4, '6', 'y', 'h', 'n', KEY_DOWN_ARROW, KEY_UP_ARROW, '\\', 0 },                                   //7
  { KEY_F5, '7', 'u', 'j', 'm', '`', ']', 0, '=' },                                                        //8
  { '8', 'i', 'k', ',', KEY_LEFT_ARROW, '[', 0, '-', 0 },                                                  //9
  { '9', 'o', 'l', '.', '/', ';', 'p', '0', 0 },                                                           //10
  { KEY_F10, 0, 0, 0, 0, 0, 0, 0, 0 },                                                                     //11
};

const uint8_t altKeyMap[12][9] = {
  { KEY_KP_MINUS, 0, 0, 0, KEY_LEFT_SHIFT, KEY_KP_7, KEY_KP_8, KEY_KP_9, 0 },                              //0
  { KEY_ESC, KEY_TAB, KEY_CAPS_LOCK, KEY_LEFT_ALT, KEY_LEFT_CTRL, KEY_KP_0, KEY_KP_DOT, KEY_KP_PLUS, 0 },  //1
  { '!', 'Q', 'A', 'Z', KEY_FUNC, KEY_KP_1, KEY_KP_2, 0, KEY_KP_3 },                                       //2
  { KEY_F1, '@', 'W', 'S', 'X', KEY_KP_4, KEY_KP_5, 0, KEY_KP_6 },                                         //3
  { KEY_F2, '#', 'E', 'D', 'C', KEY_NUM_LOCK, KEY_F8, 0, KEY_F11 },                                        //4
  { KEY_F3, '$', 'R', 'F', 'V', KEY_BACKSPACE, KEY_F7, 0, KEY_F6 },                                        //5
  { '%', 'T', 'G', 'B', ' ', 0, KEY_RETURN, 0xFF, 0 },                                                     //6
  { KEY_F4, '^', 'Y', 'H', 'N', 0, KEY_UP_ARROW, 0, '|' },                                                 //7
  { KEY_F5, '&', 'U', 'J', 'M', '~', ']', 0, '+' },                                                        //8
  { '*', 'I', 'K', '<', KEY_LEFT_ARROW, '¨','{', 0, '_'},                                                  //9
  { '(', 'O', 'L', '>', '?', ':', 'P', 0, ')' },                                                           //10
  { 0, 0, 0, 0, 0, 0, 0, KEY_F12, 0 }                                                                      //11

};
#endif

#ifdef LAYOUT_MODE_COMPAT

const uint8_t keyMap[12][9] = {
  { KEY_KP_MINUS, 0, 0, 0, KEY_LEFT_CTRL, KEY_KP_7, KEY_KP_8, KEY_KP_9, 0 },                            //0
  { KEY_ESC, KEY_TAB, KEY_CAPS_LOCK, KEY_FUNC, KEY_LEFT_SHIFT, KEY_KP_0, KEY_KP_DOT, KEY_KP_PLUS, 0 },  //1
  { '1', 'q', 'a', 'z', KEY_LEFT_ALT, KEY_KP_1, KEY_KP_2, KEY_KP_3, 0 },                                //2
  { KEY_F1, '2', 'w', 's', 'x', KEY_KP_4, '5', KEY_KP_6, },                                                //3
  { KEY_F2, '3', 'e', 'd', 'c', KEY_NUM_LOCK, KEY_F8, KEY_F9, 0 },                                      //4
  { KEY_F3, '4', 'r', 'f', 'v', KEY_BACKSPACE, KEY_F7,  KEY_F6, 0 },                                     //5
  { '5', 't', 'g', 'b', ' ', KEY_RIGHT_ARROW, KEY_RETURN, 0xFF, 0 },                                    //6
  { KEY_F4, '6', 'y', 'h', 'n', KEY_DOWN_ARROW, KEY_UP_ARROW, '\\', 0 },                                //7
  { KEY_F5, '7', 'u', 'j', 'm', '`', ']', '=', 0 },                                                     //8
  { '8', 'i', 'k', ',', KEY_LEFT_ARROW, '\'', '[', '-', 0 },                                                  //9
  { '9', 'o', 'l', '.', '/', ';', 'p', '0', 0 },                                                        //10
  { 0, 0, 0, 0, 0, 0, 0, 0, KEY_F10 }                                                                   //11

};

const uint8_t altKeyMap[12][9] = {
  { KEY_KP_MINUS, 0, 0, 0, KEY_LEFT_CTRL, KEY_KP_7, KEY_KP_8, 0, KEY_KP_9 },                            //0
  { KEY_ESC, KEY_TAB, KEY_CAPS_LOCK, KEY_LEFT_SHIFT, KEY_FUNC, KEY_KP_0, KEY_KP_DOT, 0, KEY_KP_PLUS },  //1
  { '!', 'Q', 'A', 'Z', KEY_LEFT_ALT, KEY_KP_1, KEY_KP_2, 0, KEY_KP_3 },                                //2
  { KEY_F1, '@', 'W', 'S', 'X', KEY_KP_4, KEY_KP_5, 0, KEY_KP_6 },                                      //3
  { KEY_F2, '#', 'E', 'D', 'C', KEY_NUM_LOCK, KEY_F8, 0, KEY_F11 },                                     //4
  { KEY_F3, '$', 'R', 'F', 'V', KEY_BACKSPACE, KEY_F7, 0, KEY_F6 },                                     //5
  { '%', 'T', 'G', 'B', ' ', KEY_RIGHT_ARROW, KEY_RETURN, 0xFF, 0 },                                    //6
  { KEY_F4, '^', 'Y', 'H', 'N', 0, KEY_UP_ARROW, 0, '|' },                                              //7
  { KEY_F5, '&', 'U', 'J', 'M', '~', ']', 0, '+' },                                                     //8
  { '*', 'I', 'K', '<', KEY_LEFT_ARROW, '{', 0, '_' },                                                  //9
  { '(', 'O', 'L', '>', '?', ':', 'P', 0, ')' },                                                        //10
  { 0, 0, 0, 0, 0, 0, 0, KEY_F12, 0 }                                                                   //11
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
