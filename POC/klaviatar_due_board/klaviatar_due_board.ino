#include "Keyboard.h"

char buffer[10];

char keyMap[12][9] = { { '-', 0, 0, 0, 0, '7', '8', '9', 0 },
                        { KEY_ESC, KEY_TAB, 0, 0, 0, 0, 0, 0, 0 },
                        { '1', 'q', 'a', 0, 0, 0, 0, 0, 0 },
                        { KEY_F1, '2', 'a', 0, 0, 0, 0, 0, 0 },
                        { KEY_F2, '3', 0, 0, 0, 0, 0, 0, 0 },
                        { 0, 0, 0, 0, 0, 0, 0, 0, 0 },
                        { '%', 0, 0, 0, 0, 0, 0, 0, 0 },
                        { KEY_F4, 0, 0, 0, 0, 0, 0, 0, 0 },
                        { 0, 0, 0, 0, 0, 0, 0, 0, 0 },
                        { '*', 0, 0, 0, 0, 0, 0, 0, 0 },
                        { '(', 'o', 'l', 0, '/', ';', 'p', ')', 0 },
                        { 0, 0, 0, 0, 0, 0, 0, 0, 0 } };

char keyMap[12][9] = { { '-', 0, 0, 0, 0, 0, 0, 0, 0 },
                        { KEY_ESC, KEY_TAB, 0, 0, 0, 0, 0, 0, 0 },
                        { '!', 0, 0, 0, 0, 0, 0, 0, 0 },
                        { KEY_F1, '@', 0, 0, 0, 0, 0, 0, 0 },
                        { KEY_F2, 0, 0, 0, 0, 0, 0, 0, 0 },
                        { 0, 0, 0, 0, 0, 0, 0, 0, 0 },
                        { '%', 0, 0, 0, 0, 0, 0, 0, 0 },
                        { KEY_F4, 0, 0, 0, 0, 0, 0, 0, 0 },
                        { 0, 0, 0, 0, 0, 0, 0, 0, 0 },
                        { '*', 0, 0, 0, 0, 0, 0, 0, 0 },
                        { '(', 'O', 'L', 0, '?', ':', 'P', ')', 0 },
                        { 0, 0, 0, 0, 0, 0, 0, 0, 0 } };


void setup() { 
  pinMode(0, OUTPUT);
  pinMode(1, OUTPUT);
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(22, INPUT_PULLUP);
  pinMode(23, INPUT_PULLUP);
  pinMode(24, INPUT_PULLUP);
  pinMode(25, INPUT_PULLUP);
  pinMode(26, INPUT_PULLUP);
  pinMode(27, INPUT_PULLUP);
  pinMode(28, INPUT_PULLUP);
  pinMode(29, INPUT_PULLUP);
  pinMode(30, INPUT_PULLUP);
  pinMode(31, INPUT_PULLUP);
  pinMode(32, INPUT_PULLUP);
  pinMode(33, INPUT_PULLUP);

  digitalWrite(0, HIGH);
  digitalWrite(1, HIGH);
  digitalWrite(2, HIGH);
  digitalWrite(3, HIGH);
  digitalWrite(4, HIGH);
  digitalWrite(5, HIGH);
  digitalWrite(6, HIGH);
  digitalWrite(7, HIGH);
  digitalWrite(8, HIGH);
  digitalWrite(9, HIGH);


  Keyboard.begin();
}

void loop() {
  for (int x = 1; x < 10; x++) {
    digitalWrite(x, LOW);
    for (int y = 22; y < 34; y++) {
      if (digitalRead(y) == LOW) {
        sprintf(buffer, "Key - x=%d y=%d", x, y - 21);
        Keyboard.println(buffer);
        Keyboard.write(keyMap[y-22][x-1]);
        
        delay(200);
      }
    }
    digitalWrite(x, HIGH);
  }
}
