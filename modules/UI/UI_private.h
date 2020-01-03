#ifndef UI_PRIVATE_H_
#define UI_PRIVATE_H_


/*!****************************************************************************
* Include
*/
#include "UI.h"
#include "UI_constants.h"
#include "hard/lcd/lcd.h"
#include "Fonts/Fonts.h"
#include "images/images.h"

/*!****************************************************************************
* User define
*/
#define UI_X_START  0
#define UI_X_END    320
#define UI_Y_START  0
#define UI_Y_END    240

/*!****************************************************************************
* User enum
*/
/*!****************************************************************************
* User typedef
*/
typedef struct{
    uint16_t    mainColor;
    uint16_t    selectColor;
    uint16_t    disableColor;
    uint16_t    background;
}UI_Colors_t;

typedef struct{
    const tFont *mainFont;
    const tFont *bigDigitFont;
    const tFont *smallDigitFont;
}UI_Fonts_t;

typedef struct{
    const UI_Fonts_t    fonts;
    const UI_Colors_t   colors;
}UI_t;
/*!****************************************************************************
* Extern viriables
*/
extern const UI_t ui;
/*!****************************************************************************
* Macro functions
*/
/*!****************************************************************************
* Prototypes for the functions
*/

void UI_prvt_drawCross(uint16_t x, uint16_t y, uint16_t len);

#endif //!UI_PRIVATE_H_