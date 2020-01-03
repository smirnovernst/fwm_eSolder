#include <stdio.h>
#include "UI_private.h"
#include "eSolder/eSolder.h"
#include "OS/mainTSK.h"

#define UI_MAIN_WINDOW_SEPARATOR_Y          (UI_LCD_H/2)
#define UI_MAIN_WINDOW_SEPARATOR_X_START    (UI_X_START + 30) 
#define UI_MAIN_WINDOW_SEPARATOR_X_END      (UI_X_END - 30)

#define UI_MAIN_WINDOW_SOLDER_SET_X
#define UI_MAIN_WINDOW_SOLDER_SET_y


void UI_MainWindowRendering(void)
{
    lcd_DrawBackground(ui.colors.background);
    
    
    lcd_FastHLine(UI_MAIN_WINDOW_SEPARATOR_X_START, 
                  UI_MAIN_WINDOW_SEPARATOR_Y, 
                  UI_MAIN_WINDOW_SEPARATOR_X_END - UI_MAIN_WINDOW_SEPARATOR_X_START,
                  ui.colors.mainColor
                      );
    
    lcd_Image(320 - solderingDry.w - 10, 10, &solderingDry);
    
    lcd_Image(320 - solderingIron.w - 10, UI_LCD_H/2 + 10, &solderingIron);
    //UI_prvt_drawCross(10,10, 32);
    
}

#define LEFT_OF(base, width, offset) (base - width - offset)
#define BELLOW_OF(base, offset) (base + offset)
#define RIGHT_OF(base, offset) (base + offset)


#define UI_MAIN_WINDOW_DRY_START_Y          (UI_Y_START)
#define UI_MAIN_WINDOW_SOLDER_START_Y       (UI_MAIN_WINDOW_SEPARATOR_Y)


#define UI_MAIN_WINDOW_ICON_OFFSET_X        (10)
#define UI_MAIN_WINDOW_ICON_OFFSET_Y        (10)
#define UI_MAIN_WINDOW_SET_TEMP_OFFSET_X    (10)
#define UI_MAIN_WINDOW_SET_TEMP_OFFSET_Y    (10)
#define UI_MAIN_WINDOW_REAL_TEMP_OFFSET_X   (150)
#define UI_MAIN_WINDOW_REAL_TEMP_OFFSET_Y   (70)


#define UI_MAIN_WINDOW_SET_SYM_DISTANCE     (1)




void drawTempSet(int16_t y_start, uint16_t value, uint8_t enabled, uint8_t connected, uint8_t selected)
{
    uint8_t tempStr[6] = "---'C"; 

    lcdFontParam_t fontParamTempSet = {
        .font = ui.fonts.bigDigitFont,
        .distance =  UI_MAIN_WINDOW_SET_SYM_DISTANCE,
        .background = ui.colors.background,
        .color =  ui.colors.mainColor
    };

    if (!connected)
    {
        fontParamTempSet.color = ui.colors.disconnectedColor;
    }
    else 
    {    
        if (selected)
        {
            fontParamTempSet.color = ui.colors.selectColor;
        }

        if (enabled)
        {
            sprintf((char*)tempStr, "%03u%s", value, "'C");
        } 
    }
        
    lcd_String(RIGHT_OF(UI_X_START, UI_MAIN_WINDOW_SET_TEMP_OFFSET_X),
                BELLOW_OF(y_start, UI_MAIN_WINDOW_SET_TEMP_OFFSET_Y),
                (char*)tempStr,
                &fontParamTempSet
                );
}

void drawTempReal(int16_t y_start, uint16_t value, uint8_t enabled, uint8_t connected)
{
    uint8_t tempStr[6] = "---'C"; 

    lcdFontParam_t fontParamTempSet = {
        .font = ui.fonts.smallDigitFont,
        .distance =  UI_MAIN_WINDOW_SET_SYM_DISTANCE,
        .background = ui.colors.background,
        .color =  ui.colors.mainColor
    };

    if (!connected)
    {
        fontParamTempSet.color = ui.colors.disconnectedColor;
    }
    else 
    {    
        if (enabled)
        {
            sprintf((char*)tempStr, "%03u%s", value, "'C");
        } 
    }
        
    lcd_String(RIGHT_OF(UI_X_START, UI_MAIN_WINDOW_REAL_TEMP_OFFSET_X),
                BELLOW_OF(y_start, UI_MAIN_WINDOW_REAL_TEMP_OFFSET_Y),
                (char*)tempStr,
                &fontParamTempSet
                );
}


void UI_MainWindowUpdate(void)
{
    // ======== Icons ========
    const tImage16 *pSolderIcon, *pDryIcon;
    if (eSolder.dry.connected)
    {
        pDryIcon = &solderingDry;
    }
    else
    {
       pDryIcon = &solderingDryDisconnected;
    }
    if (eSolder.solder.connected)
    {
        pSolderIcon = &solderingIron;
    }
    else
    {
       pSolderIcon = &solderingIronDisconnected;
    }
     lcd_Image( LEFT_OF(UI_X_END, pDryIcon->w, UI_MAIN_WINDOW_ICON_OFFSET_X), 
                  BELLOW_OF(UI_MAIN_WINDOW_DRY_START_Y, UI_MAIN_WINDOW_ICON_OFFSET_Y), 
                  pDryIcon
              );
     lcd_Image( LEFT_OF(UI_X_END, pSolderIcon->w, UI_MAIN_WINDOW_ICON_OFFSET_X), 
                  BELLOW_OF(UI_MAIN_WINDOW_SOLDER_START_Y, UI_MAIN_WINDOW_ICON_OFFSET_Y), 
                  pSolderIcon
                      );
    
    // ======== Settings ======== //    
    mainTskEncoderSelected_t encSelected = mainTsk_GetEncoderSelected();

    drawTempSet(UI_MAIN_WINDOW_DRY_START_Y, 
                eSolder.dry.tempSet,
                eSolder.dry.enabled,
                eSolder.dry.connected,
                (encSelected == mainTskEncoderSelected_DRY_TEMP)  
                );

    drawTempSet(UI_MAIN_WINDOW_SOLDER_START_Y, 
                eSolder.solder.tempSet, 
                eSolder.solder.enabled, 
                eSolder.solder.connected, 
                (encSelected == mainTskEncoderSelected_SOLDER_TEMP)
                );

    drawTempReal(UI_MAIN_WINDOW_SOLDER_START_Y,
                eSolder.solder.tempReal,
                eSolder.solder.enabled,
                eSolder.solder.connected
                );

    drawTempReal(UI_MAIN_WINDOW_DRY_START_Y,
                eSolder.dry.tempReal,
                eSolder.dry.enabled,
                eSolder.dry.connected
                );
    
}