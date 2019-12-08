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

#include "hard/lcd/lcd.h"

//#include "Image.h"
#include "Fonts/Fonts.h"

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
#define UI_COL_INTCONTOUR   (uint16_t)0x18E3
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


void UI_MainWindowRendering(void);
void UI_DrawMenu();
#endif //UI_h



