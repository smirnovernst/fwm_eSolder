#ifndef KEYBOARD_H_
#define KEYBOARD_H_

#include "Drivers/button.h"

typedef struct {
    Button_t dryButton;
    Button_t solderButton;
    Button_t encoderButton;
}Keyboard_t;

extern Keyboard_t keyboard;

void keyboardInit(void);
void keyboardClearAllPress(void);
uint8_t  keyboardScan(void);

#endif // !KEYBOARD_H_
