#ifndef KEYBOARD_H_
#define KEYBOARD_H_

#include "Drivers/button.h"

typedef enum {
    KeyboardButton_DRY = 0,
    KeyboardButton_SOLDER,
    KeyboardButton_ENCODER,
    KeyboardButton_COUNT
}KeyboardKey_t;

typedef struct {
    Button_t buttons[KeyboardButton_COUNT];
}Keyboard_t;

extern Keyboard_t keyboard;

void keyboardInit(void);
void keyboardClearAllPress(void);
uint8_t  keyboardScan(void);

#endif // !KEYBOARD_H_
