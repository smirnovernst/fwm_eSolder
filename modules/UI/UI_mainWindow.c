#include "UI_private.h"

#define UI_MAIN_WINDOW_SEPARATOR_Y          (UI_LCD_H/2)
#define UI_MAIN_WINDOW_SEPARATOR_X_START    (UI_X_START + 30) 
#define UI_MAIN_WINDOW_SEPARATOR_X_END      (UI_X_END - 30)

#define UI_MAIN_WINDOW_SOLDER_SET_X
#define UI_MAIN_WINDOW_SOLDER_SET_y


void UI_MainWindowRendering(void){
  lcd_DrawBackground(ui.colors.background);

  lcd_SetPixel(UI_X_START + 2, UI_MAIN_WINDOW_SEPARATOR_Y, ui.colors.mainColor);
  lcd_SetPixel(UI_X_START + 3, UI_MAIN_WINDOW_SEPARATOR_Y, ui.colors.mainColor);
  lcd_SetPixel(UI_X_END - 2, UI_MAIN_WINDOW_SEPARATOR_Y, ui.colors.mainColor);
  lcd_SetPixel(UI_X_END - 3, UI_MAIN_WINDOW_SEPARATOR_Y, ui.colors.mainColor);

  lcd_FastHLine(UI_MAIN_WINDOW_SEPARATOR_X_START, 
                UI_MAIN_WINDOW_SEPARATOR_Y, 
                UI_MAIN_WINDOW_SEPARATOR_X_END - UI_MAIN_WINDOW_SEPARATOR_X_START,
                ui.colors.mainColor
                );


}