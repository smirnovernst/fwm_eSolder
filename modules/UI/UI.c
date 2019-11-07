/*
*@File      UI.c 
*@Author    EricMarina
*@Version   0.1
*@Date      18.11.2016
*@Breif     
*/
/*!****************************************************************************
* Include
*/
#include "UI.h"
/*!****************************************************************************
* Typedef
*/
typedef struct{
    uint16_t    centralPannel;  //Центральная панель и разделитель
    uint16_t    ExtContour;     //Внешний контур обводки панелей
    uint16_t    IntContour;     //Внутренний контур обводки панелей
    uint16_t    PanelOK;
    uint16_t    PanelFail;
    uint16_t    PanelHeat;
    uint16_t    PanelOff;
    uint16_t    RegulatorSelected;
    uint16_t    Background;
}UI_Colors_t;

typedef struct{
    lcdParam_t  mainFont;
    lcdParam_t  headFont;
    lcdParam_t  bigDigitFont;
    lcdParam_t  smallDigitFont;
}UI_Fonts_t;

typedef struct{
    UI_Fonts_t      fonts;
    UI_Colors_t     colors;
    uint8_t a;
}UI_t;


/*!****************************************************************************
* defines
*/

/*!****************************************************************************
* Memory
*/
 const static UI_t ui = {
    //----Colors----
    .colors.centralPannel       = LCD_COLOR_GRAY,
    .colors.ExtContour          = LCD_COLOR_WHITE,
    .colors.IntContour          = UI_COL_INTCONTOUR,
    .colors.PanelFail           = LCD_COLOR_RED,
    .colors.PanelHeat           = LCD_COLOR_YELLOW,
    .colors.PanelOff            = LCD_COLOR_BLACK,
    .colors.PanelOK             = LCD_COLOR_GREEN,
    .colors.RegulatorSelected   = LCD_COLOR_WHITE,
    
    //----Fonts----
    .fonts.headFont.color           = LCD_COLOR_WHITE,
    .fonts.headFont.distance        = 1,
    .fonts.headFont.font            = &Arial,
    .fonts.headFont.background      = LCD_COLOR_GRAY,

    .fonts.mainFont.background      = LCD_COLOR_BLACK,
    .fonts.mainFont.color           = LCD_COLOR_WHITE,
    .fonts.mainFont.distance        = 1,
    .fonts.mainFont.font            = &Arial,
    
    .fonts.bigDigitFont.background  = LCD_COLOR_BLACK,
    .fonts.bigDigitFont.color       = LCD_COLOR_WHITE,
    .fonts.bigDigitFont.distance    = 3,
    .fonts.bigDigitFont.font        = &DS_Digital,
    
    .fonts.smallDigitFont.background= LCD_COLOR_BLACK,
    .fonts.smallDigitFont.color     = LCD_COLOR_WHITE,
    .fonts.smallDigitFont.distance  = 1,
    .fonts.smallDigitFont.font      = &DS_Digital_Small,
};
/*!****************************************************************************
* Functions
*/

void UI_MainWindowRendering(void){
    lcd_DrawBackground(LCD_COLOR_BLACK);
    //****UPPER PANEL***///
    lcd_Rect(UI_UPPER_X, UI_UPPER_Y, UI_UPPER_W, UI_UPPER_H-1, ui.colors.ExtContour);       //контур верхней панели
     
    
    
    //****CENTER PANEL***///
    lcd_FillRect (UI_CENTERPANEL_X, 
                  UI_CENTERPANEL_Y, UI_CENTERPANEL_W, 
                  UI_CENTERPANEL_H, 
                  ui.colors.centralPannel);   //Отрисовка центральной панели
    
    lcd_FillRect (UI_CENTER_X, UI_CENTER_Y, UI_CENTER_W, 
                  UI_CENTER_H, ui.colors.centralPannel);  //Отрисовка разделителя
    
    lcd_Rect (UI_LEFTPANEL_X+UI_CENTERPANEL_INLINE,  
              UI_CENTERPANEL_Y+UI_CENTERPANEL_INLINE, 
              UI_PANEL_W-2*UI_CENTERPANEL_INLINE,
              UI_CENTERPANEL_H-2*UI_CENTERPANEL_INLINE,  
              ui.colors.IntContour);   //Внутренний контур левой части
    
    lcd_Rect (UI_RIGHTPANEL_X+UI_CENTERPANEL_INLINE, 
              UI_CENTERPANEL_Y+UI_CENTERPANEL_INLINE, 
              UI_PANEL_W-2*UI_CENTERPANEL_INLINE,
              UI_CENTERPANEL_H-2*UI_CENTERPANEL_INLINE,  
              ui.colors.IntContour);   //Внутренний контур правой части

    lcd_String(60,  30, "DRY", &ui.fonts.headFont);
    lcd_String(200, 30, "SOLDER", &ui.fonts.headFont); 
    
    //****LEFT PANEL (DRY)***///
    lcd_Rect(UI_LEFTPANEL_X, UI_PANEL_Y, UI_PANEL_W, UI_PANEL_H, LCD_COLOR_WHITE);     //контур левой панели
    
    lcd_String(UI_LEFTPANEL_X+UI_SYMBOLSOFFSET_X, UI_TEXTSET_Y,  "SET",  &ui.fonts.mainFont);
    lcd_String(UI_LEFTPANEL_X+UI_SYMBOLSOFFSET_X, UI_TEXTFLOW_Y, "FLOW", &ui.fonts.mainFont);
    lcd_String(UI_LEFTPANEL_X+UI_SYMBOLSOFFSET_X, UI_TEXTREAL_Y, "REAL", &ui.fonts.mainFont);
    //****RIGHT PANEL  (SOLDER)***///
    lcd_Rect(UI_RIGHTPANEL_X, UI_PANEL_Y, UI_PANEL_W, UI_PANEL_H, LCD_COLOR_WHITE);  //контур правой панели
    
    lcd_String(UI_RIGHTPANEL_X+UI_SYMBOLSOFFSET_X, UI_TEXTSET_Y, "SET", &ui.fonts.mainFont);
    lcd_String(UI_RIGHTPANEL_X+UI_SYMBOLSOFFSET_X, UI_TEXTREAL_Y, "REAL", &ui.fonts.mainFont);
}
/*
void UI_Update(stationState_t *data)
{
     
    //=========Memory==========//
    char    str[10];
    lcd_color_t Color_panelDry;
    lcd_color_t Color_panelSolder;
    //=======Upper panel=======//
    if (data->internalTemp > 0)
    {
        sprintf(str, "%02d%s", data->internalTemp, "'C"); 
        lcd_String(UI_UPPER_TEMP_X, UI_UPPER_TEXT_Y, str, &ui.fonts.mainFont);
    }
    else
    {
        lcd_String(UI_UPPER_TEMP_X, UI_UPPER_TEXT_Y, "<0'C", &ui.fonts.mainFont);
    }

    
    //===========Dry===========//

    if (data->dry.enable == enable_ON)
    {
        switch(data->dry.status)
        {
        case deviceStatus_Ok:    Color_panelDry = ui.colors.PanelOK;
            break;
        case deviceStatus_Fail:  Color_panelDry = ui.colors.PanelFail;
            break;
        case deviceStatus_Heating: Color_panelDry = ui.colors.PanelHeat; 
        }
    }
    else
    {
        Color_panelDry = ui.colors.PanelOff;
    }
    lcd_Rect(UI_LEFTPANEL_X+1, UI_PANEL_Y+1, UI_PANEL_W-2, UI_PANEL_H-3, Color_panelDry);  
    lcd_Rect(UI_LEFTPANEL_X+2, UI_PANEL_Y+2, UI_PANEL_W-4, UI_PANEL_H-5, Color_panelDry); 
    lcd_Rect(UI_LEFTPANEL_X+3, UI_PANEL_Y+3, UI_PANEL_W-6, UI_PANEL_H-6, Color_panelDry); 
    

    //---Regulator selector---
        
    if (data->regulator_selected != now_regulator_select)
    {
        lcd_color_t color_set, color_flow;
        lcdParam_t font_set, font_flow;
        if (data->regulator_selected == DryRegulatorSelected_Set)
        {
            color_set = ui.colors.RegulatorSelected;
            color_flow = ui.colors.Background;
            font_set = ui.fonts.RegulatorSelectedFont;
            font_flow = ui.fonts.mainFont;
        }
        else
        {
            color_set = ui.colors.Background;
            color_flow = ui.colors.RegulatorSelected;
            font_set = ui.fonts.mainFont;
            font_flow = ui.fonts.RegulatorSelectedFont;
        }
        
        lcd_FillRect(UI_LEFTPANEL_X+UI_SYMBOLSOFFSET_X, UI_TEXTSET_Y, 35, 18, color_set); 
        lcd_String(UI_LEFTPANEL_X+UI_SYMBOLSOFFSET_X, UI_TEXTSET_Y,  "SET",  &font_set);

        lcd_FillRect(UI_LEFTPANEL_X+UI_SYMBOLSOFFSET_X, UI_TEXTFLOW_Y,50 , 18,color_flow);
        lcd_String(UI_LEFTPANEL_X+UI_SYMBOLSOFFSET_X, UI_TEXTFLOW_Y, "FLOW", &font_flow);
        
        now_regulator_select = data->regulator_selected;
    }
    //-------Output data--------
    
    
    if (data->dry.enable == enable_ON)
    {
        sprintf(str, "%03u%s", data->dry.temperatueSet, "'C");    
        lcd_String(UI_LEFTPANEL_X + UI_SYMBOLSOFFSET_X, UI_TEXTSET_Y+UI_VALUEOFFSET_Y, str, &ui.fonts.bigDigitFont);
        
        sprintf(str, "%03u%s", data->dryFlow, "%");
        lcd_String(UI_LEFTPANEL_X + UI_SYMBOLSOFFSET_X, UI_TEXTFLOW_Y+UI_VALUEOFFSET_Y,  str, &ui.fonts.bigDigitFont);
        
        sprintf(str, "%03u%s", data->dry.temperatueReal, "'C");
        lcd_String(UI_LEFTPANEL_X + UI_SYMBOLSOFFSET_X, UI_TEXTREAL_Y+UI_VALUEOFFSET_Y, str, &ui.fonts.smallDigitFont);
    }
    else
    {
        lcd_String(UI_LEFTPANEL_X + UI_SYMBOLSOFFSET_X, UI_TEXTSET_Y+UI_VALUEOFFSET_Y,  "---'C", &ui.fonts.bigDigitFont);
        lcd_String(UI_LEFTPANEL_X + UI_SYMBOLSOFFSET_X, UI_TEXTFLOW_Y+UI_VALUEOFFSET_Y, "---%", &ui.fonts.bigDigitFont);
        lcd_String(UI_LEFTPANEL_X + UI_SYMBOLSOFFSET_X, UI_TEXTREAL_Y+UI_VALUEOFFSET_Y, "---'C", &ui.fonts.smallDigitFont);
    }

    
    //==========Solder=========//
    if (data->solder.enable == enable_ON)
    {
        switch(data->solder.status)
        {
        case deviceStatus_Ok:    Color_panelSolder = ui.colors.PanelOK;
            break;
        case deviceStatus_Fail:  Color_panelSolder = ui.colors.PanelFail;
            break;
        case deviceStatus_Heating: Color_panelSolder = ui.colors.PanelHeat; 
        }
    }
    else
    {
        Color_panelSolder = ui.colors.PanelOff;
    }
    lcd_Rect(UI_RIGHTPANEL_X+1, UI_PANEL_Y+1, UI_PANEL_W-3, UI_PANEL_H-3, Color_panelSolder);  
    lcd_Rect(UI_RIGHTPANEL_X+2, UI_PANEL_Y+2, UI_PANEL_W-5, UI_PANEL_H-5, Color_panelSolder); 
    lcd_Rect(UI_RIGHTPANEL_X+3, UI_PANEL_Y+3, UI_PANEL_W-7, UI_PANEL_H-7, Color_panelSolder);
    
    //-------Output data--------  
    if (data->solder.enable == enable_ON)
    {
        sprintf(str, "%03u%s", data->solder.temperatueSet , "'C");    
        lcd_String(UI_RIGHTPANEL_X + UI_SYMBOLSOFFSET_X, UI_TEXTSET_Y+UI_VALUEOFFSET_Y, str, &ui.fonts.bigDigitFont);
        
        if (data->solder.connection != 0)
        {
            sprintf(str, "%03u%s", data->solder.temperatueReal, "'C");
            lcd_String(UI_RIGHTPANEL_X + UI_SYMBOLSOFFSET_X, UI_TEXTREAL_Y+UI_VALUEOFFSET_Y, str, &ui.fonts.smallDigitFont);
        }
        else
        {
            lcd_String(UI_RIGHTPANEL_X + UI_SYMBOLSOFFSET_X, UI_TEXTREAL_Y+UI_VALUEOFFSET_Y, "---'C", &ui.fonts.smallDigitFont);
        }
    }
    else
    {
        lcd_String(UI_RIGHTPANEL_X + UI_SYMBOLSOFFSET_X, UI_TEXTSET_Y+UI_VALUEOFFSET_Y,  "---'C", &ui.fonts.bigDigitFont);
        lcd_String(UI_RIGHTPANEL_X + UI_SYMBOLSOFFSET_X, UI_TEXTREAL_Y+UI_VALUEOFFSET_Y, "---'C", &ui.fonts.smallDigitFont);
    }
}
*/


void UI_DrawMenu()
{
    //==========Drawing window=========//
    //----Clear----
    lcd_FillRect(UI_MENU_PANNEL_X, 
                 UI_MENU_PANNEL_Y, 
                 UI_MENU_PANNEL_W,
                 UI_MENU_PANNEL_H, 
                 LCD_COLOR_BLACK);
    //----borders----
    lcd_FillRect(UI_MENU_PANNEL_X, 
             UI_MENU_PANNEL_Y, 
             UI_MENU_PANNEL_W,
             UI_MENU_BORD_THINK,
             ui.colors.centralPannel);
    
    lcd_FillRect(UI_MENU_PANNEL_W-UI_MENU_BORD_THINK, 
             UI_MENU_PANNEL_Y+UI_MENU_BORD_THINK, 
             UI_MENU_BORD_THINK,
             UI_MENU_PANNEL_H-UI_MENU_BORD_THINK-UI_MENU_BORD_THINK,
             ui.colors.centralPannel); 
    
    lcd_FillRect(UI_MENU_PANNEL_X, 
         UI_MENU_PANNEL_Y+UI_MENU_PANNEL_H-UI_MENU_BORD_THINK, 
         UI_MENU_PANNEL_W,
         UI_MENU_BORD_THINK,
         ui.colors.centralPannel);
    
    lcd_FillRect(UI_MENU_PANNEL_X, 
             UI_MENU_PANNEL_Y+UI_MENU_BORD_THINK, 
             UI_MENU_BORD_THINK,
             UI_MENU_PANNEL_H-UI_MENU_BORD_THINK-UI_MENU_BORD_THINK,
             ui.colors.centralPannel); 
    

    

}