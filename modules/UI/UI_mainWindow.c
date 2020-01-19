#include <stdio.h>
#include "UI_private.h"
#include "eSolder/eSolder.h"
#include "OS/mainTSK.h"


#define LEFT_OF(base, width, offset) (base - width - offset)
#define BELLOW_OF(base, offset) (base + offset)
#define RIGHT_OF(base, offset) (base + offset)


#define UI_MAIN_WINDOW_SEPARATOR_Y          (UI_LCD_H/2)
#define UI_MAIN_WINDOW_SEPARATOR_X_START    (UI_X_START + 30) 
#define UI_MAIN_WINDOW_SEPARATOR_X_END      (UI_X_END - 30)


#define UI_MAIN_WINDOW_DRY_START_Y          (UI_Y_START)
#define UI_MAIN_WINDOW_SOLDER_START_Y       (UI_MAIN_WINDOW_SEPARATOR_Y)

#define UI_MAIN_WINDOW_ICON_THERMO_OFFSET_X (150)
#define UI_MAIN_WINDOW_ICON_THERMO_OFFSET_Y (15)

#define UI_MAIN_WINDOW_ICON_FLOW_OFFSET_X (150)
#define UI_MAIN_WINDOW_ICON_FLOW_OFFSET_Y (70)

void UI_MainWindowRendering(void)
{
    lcd_DrawBackground(ui.colors.background);
    
    
    lcd_FastHLine(UI_MAIN_WINDOW_SEPARATOR_X_START, 
                  UI_MAIN_WINDOW_SEPARATOR_Y, 
                  UI_MAIN_WINDOW_SEPARATOR_X_END - UI_MAIN_WINDOW_SEPARATOR_X_START,
                  ui.colors.mainColor
                      );
      
 
    
}





#define UI_MAIN_WINDOW_ICON_OFFSET_X        (10)
#define UI_MAIN_WINDOW_ICON_OFFSET_Y        (10)



#define UI_MAIN_WINDOW_SET_TEMP_OFFSET_X    (10)
#define UI_MAIN_WINDOW_SET_TEMP_OFFSET_Y    (35)
#define UI_MAIN_WINDOW_REAL_TEMP_OFFSET_X   (180)
#define UI_MAIN_WINDOW_REAL_TEMP_OFFSET_Y   (15)
#define UI_MAIN_WINDOW_FLOW_OFFSET_X        (UI_MAIN_WINDOW_REAL_TEMP_OFFSET_X)
#define UI_MAIN_WINDOW_FLOW_OFFSET_Y        (80)



#define UI_MAIN_WINDOW_BIG_SYM_DISTANCE     (2)
#define UI_MAIN_WINDOW_SMALL_SYM_DISTANCE   (1)




void drawTempSet(int16_t y_start, uint16_t value, uint8_t enabled, uint8_t connected, uint8_t selected)
{
    uint8_t tempStr[6] = "---'C"; 

    lcdFontParam_t fontParamTempSet = {
        .font = ui.fonts.bigDigitFont,
        .distance =  UI_MAIN_WINDOW_BIG_SYM_DISTANCE,
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
        .distance =  UI_MAIN_WINDOW_SMALL_SYM_DISTANCE   ,
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

void drawTempFlow(uint16_t value, uint8_t enabled, uint8_t connected)
{
    uint8_t tempStr[6] = "---%"; 

    lcdFontParam_t fontParamSet = {
        .font = ui.fonts.smallDigitFont,
        .distance =  UI_MAIN_WINDOW_SMALL_SYM_DISTANCE,
        .background = ui.colors.background,
        .color =  ui.colors.mainColor
    };

    if (!connected)
    {
        fontParamSet.color = ui.colors.disconnectedColor;
    }
    else 
    {    
        if (enabled)
        {
            sprintf((char*)tempStr, "%03u%s", value, "%");
        } 
    }
        
    lcd_String(RIGHT_OF(UI_X_START, UI_MAIN_WINDOW_REAL_TEMP_OFFSET_X),
                BELLOW_OF(UI_MAIN_WINDOW_DRY_START_Y, UI_MAIN_WINDOW_ICON_FLOW_OFFSET_Y),
                (char*)tempStr,
                &fontParamSet
                );
}



void UI_MainWindowUpdate(void)
{
    // ======== Icons ========
    const tImage16 *pSolderIcon, *pDryIcon, *pSolderThermometer, *pDryThermometer, *pFanFlow;
    if (eSolder.dry.devParam.connected)
    {
        pDryIcon = &solderingDry;
        pDryThermometer = &Thermometer;
        pFanFlow = &FanFlow;
    }
    else
    {
       pDryIcon = &solderingDryDisconnected;
       pDryThermometer = &ThermometerDark;
       pFanFlow = &FanFlowDark;
    }
    if (eSolder.solder.devParam.connected)
    {
        pSolderIcon = &solderingIron;
        pSolderThermometer = &Thermometer;
    }
    else
    {
       pSolderIcon = &solderingIronDisconnected;
       pSolderThermometer = &ThermometerDark;
    }
     lcd_Image( LEFT_OF(UI_X_END, pDryIcon->w, UI_MAIN_WINDOW_ICON_OFFSET_X), 
                BELLOW_OF(UI_MAIN_WINDOW_DRY_START_Y, UI_MAIN_WINDOW_ICON_OFFSET_Y), 
                pDryIcon
              );
     lcd_Image( LEFT_OF(UI_X_END, pSolderIcon->w, UI_MAIN_WINDOW_ICON_OFFSET_X), 
                BELLOW_OF(UI_MAIN_WINDOW_SOLDER_START_Y, UI_MAIN_WINDOW_ICON_OFFSET_Y), 
                pSolderIcon
              );

    lcd_Image(RIGHT_OF(UI_X_START, UI_MAIN_WINDOW_ICON_THERMO_OFFSET_X), 
              BELLOW_OF(UI_MAIN_WINDOW_DRY_START_Y, UI_MAIN_WINDOW_ICON_THERMO_OFFSET_Y), 
              pDryThermometer
            );

    lcd_Image(RIGHT_OF(UI_X_START, UI_MAIN_WINDOW_ICON_THERMO_OFFSET_X), 
              BELLOW_OF(UI_MAIN_WINDOW_SOLDER_START_Y, UI_MAIN_WINDOW_ICON_THERMO_OFFSET_Y), 
              pSolderThermometer
            );

            
    lcd_Image(RIGHT_OF(UI_X_START, UI_MAIN_WINDOW_ICON_FLOW_OFFSET_X), 
            BELLOW_OF(UI_MAIN_WINDOW_DRY_START_Y, UI_MAIN_WINDOW_ICON_FLOW_OFFSET_Y), 
            pFanFlow
            );
    
    // ======== Settings ======== //    
    mainTskEncoderSelected_t encSelected = mainTsk_GetEncoderSelected();

    drawTempSet(UI_MAIN_WINDOW_DRY_START_Y, 
                eSolder.dry.tempSet,
                eSolder.dry.devParam.enabled,
                eSolder.dry.devParam.connected,
                (encSelected == mainTskEncoderSelected_DRY_TEMP)  
                );

    drawTempSet(UI_MAIN_WINDOW_SOLDER_START_Y, 
                eSolder.solder.tempSet, 
                eSolder.solder.devParam.enabled, 
                eSolder.solder.devParam.connected, 
                (encSelected == mainTskEncoderSelected_SOLDER_TEMP)
                );

    drawTempReal(UI_MAIN_WINDOW_SOLDER_START_Y,
                eSolder.solder.tempReal,
                eSolder.solder.devParam.enabled,
                eSolder.solder.devParam.connected
                );

    drawTempReal(UI_MAIN_WINDOW_DRY_START_Y,
                eSolder.dry.tempReal,
                eSolder.dry.devParam.enabled,
                eSolder.dry.devParam.connected
                );

    drawTempFlow(eSolder.dry.flowSet,
                eSolder.dry.devParam.enabled,
                eSolder.dry.devParam.connected);
    
}