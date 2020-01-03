#include "hard/keyboard.h"

Keyboard_t keyboard = {
    .buttons = {
        //KeyboardButton_DRY
        { GPIOD, 12},
        //KeyboardButton_SOLDER
        { GPIOD, 11},
        //KeyboardButton_ENCODER
        { GPIOC, 11}
    }
};

void keyboardInit(void) {
    for (uint16_t i=0; i < KeyboardButton_COUNT; i++)
    {
        buttonInit(&keyboard.buttons[i]);
    }
}
void keyboardClearAllPress(void) {
    for (uint16_t i=0; i < KeyboardButton_COUNT; i++)
    {
        buttonClearPressed(&keyboard.buttons[i]);
    }
}
uint8_t keyboardScan(void) {
    uint16_t pressedButtonCount = 0;
    for (uint16_t i=0; i < KeyboardButton_COUNT; i++)
    {
        pressedButtonCount += (buttonScan(&keyboard.buttons[i]) > 0);
    }
    return pressedButtonCount;
}