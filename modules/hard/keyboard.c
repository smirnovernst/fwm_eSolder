#include "hard/keyboard.h"

Keyboard_t keyboard;

void keyboardInit(void) {
    keyboard.dryButton.port = GPIOD;
    keyboard.dryButton.pin = 12;

    keyboard.solderButton.port = GPIOD;
    keyboard.solderButton.pin = 11;

    keyboard.encoderButton.port = GPIOC;
    keyboard.encoderButton.pin = 8;

    buttonInit(&keyboard.dryButton);
    buttonInit(&keyboard.solderButton);
    buttonInit(&keyboard.encoderButton);
}
void keyboardClearAllPress(void) {
    buttonClearPressed(&keyboard.dryButton);
    buttonClearPressed(&keyboard.solderButton);
    buttonClearPressed(&keyboard.encoderButton);
}
uint8_t keyboardScan(void) {
    int pressedButtonCount = 0;
    pressedButtonCount += (buttonScan(&keyboard.dryButton) > 0);
    pressedButtonCount += (buttonScan(&keyboard.dryButton) > 0);
    pressedButtonCount += (buttonScan(&keyboard.dryButton) > 0);
    return pressedButtonCount;

}