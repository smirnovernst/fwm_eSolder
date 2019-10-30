/*
*@File      UI.h 
*@Author    EricMarina
*@Version   0.1
*@Date      18.11.2016
*@Breif     
*/
#ifndef UI_h
#define UI_h
/*!****************************************************************************
* Include
*/
#include "stdio.h"
#include "stationState.h"

#include "lcd.h"

//#include "Image.h"
#include "Fonts.h"

/*!****************************************************************************
* User define
*/
#define UI_VERSION "V. 0.1"

    //=========PANELS=========//
#define UI_UPPER_X  0
#define UI_UPPER_Y  0
#define UI_UPPER_W  320
#define UI_UPPER_H  28

#define UI_UPPER_TEXT_Y 5
#define UI_UPPER_TEMP_X 280


#define UI_CENTERPANEL_X    0
#define UI_CENTERPANEL_Y    (UI_UPPER_Y + UI_UPPER_H)    
#define UI_CENTERPANEL_W    320
#define UI_CENTERPANEL_H    22

#define UI_CENTERPANEL_INLINE    1

#define UI_CENTER_X    158
#define UI_CENTER_Y    UI_CENTERPANEL_Y
#define UI_CENTER_W    4
#define UI_CENTER_H    (240 - UI_CENTER_Y)

#define UI_PANEL_Y      (UI_CENTERPANEL_Y + UI_CENTERPANEL_H)  
#define UI_PANEL_W      158
#define UI_PANEL_H      (240 - UI_PANEL_Y)  

#define UI_LEFTPANEL_X     0
#define UI_RIGHTPANEL_X    162
    

#define UI_SYMBOLSOFFSET_X      10

#define UI_TEXTSET_Y            UI_PANEL_Y+4
#define UI_TEXTFLOW_Y           UI_PANEL_Y+70
#define UI_TEXTREAL_Y           UI_PANEL_Y+135

#define UI_VALUEOFFSET_Y        20

//-----------MENU--------------
#define UI_MENU_PANNEL_X    UI_CENTERPANEL_X
#define UI_MENU_PANNEL_Y    UI_CENTERPANEL_Y
#define UI_MENU_PANNEL_W    320
#define UI_MENU_PANNEL_H    240-UI_UPPER_H

#define UI_MENU_BORD_THINK      5

#define MENU_STRING_ON_PAGE     12
#define MENU_TEXT_START_X       UI_MENU_PANNEL_X+UI_MENU_BORD_THINK+5
#define MENU_TEXT_START_Y       UI_MENU_PANNEL_Y+UI_MENU_BORD_THINK+5
#define MENU_TEXT_HEIGHT        20


#define MENU_TEXT_LENGTH_PARAM_MAX   10
#define MENU_PARAM_START_X      MENU_TEXT_START_X+200


    //=========COLORS=========//
#define UI_COL_INTCONTOUR   (lcd_color_t)0x18E3
/*!****************************************************************************
* User enum
*/
typedef enum
{
    menuElMemType_U8,
    menuElMemType_U16,
    menuElMemType_BOOL,
}menuElMemType_t;
/*!****************************************************************************
* User typedef
*/
 
typedef struct
{
    lcd_color_t    centralPannel;  //Центральная панель и разделитель
    lcd_color_t    ExtContour;     //Внешний контур обводки панелей
    lcd_color_t    IntContour;     //Внутренний контур обводки панелей
    lcd_color_t    PanelOK;        
    lcd_color_t    PanelFail;
    lcd_color_t    PanelHeat;
    lcd_color_t    PanelOff;
    lcd_color_t    RegulatorSelected;
    lcd_color_t    Background;
}UI_Colors_t;

typedef struct
{
    lcdParam_t  mainFont;
    lcdParam_t  headFont;
    lcdParam_t  bigDigitFont;
    lcdParam_t  smallDigitFont;
    lcdParam_t  RegulatorSelectedFont;
    lcdParam_t  menuSelectedFont;
}UI_Fonts_t; 

typedef struct
{
    UI_Fonts_t      fonts;
    UI_Colors_t     colors; 
}UI_t;



typedef struct
{
    char            *name;
    void            *param;
    menuElMemType_t memType;
    uint16_t        min;
    uint16_t        max;
}menuEl_t;

typedef struct
{
    menuEl_t    *elements;
    uint8_t     selectedEl;
    uint8_t     elementsAmount;
}UI_menu_t;

/*!****************************************************************************
* Extern viriables
*/

/*!****************************************************************************
* Macro functions
*/

/*!****************************************************************************
* Prototypes for the functions
*/
void UI_DrawBootScreen(void);
void UI_Update(stationState_t *data);
void UI_WindowRendering();
void UI_DrawMenu();
void UI_updateMenu(UI_menu_t *menu);
void UI_Init();
#endif //UI_h



