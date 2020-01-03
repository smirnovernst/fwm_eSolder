#include "hard/keyboard.h"

Keyboard_t keyboard = {
    .buttons = {
        //KeyboardButton_DRY
        { GPIOD, 12, ButtonInverted_NO},
        //KeyboardButton_SOLDER
        { GPIOD, 11, ButtonInverted_NO},
        //KeyboardButton_ENCODER
        { GPIOC, 8, ButtonInverted_YES}
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