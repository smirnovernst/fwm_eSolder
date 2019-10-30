
/*******************************************************************************
* font
* filename: unsaved
* name: specific_symbol
* family: MS Shell Dlg 2
* size: 36
* style: Normal
* included characters: ←⇦
* antialiasing: no
* type: proportional
* encoding: UTF-32
* unicode bom: no
*
* preset name: Monochrome
* data block size: 8 bit(s), uint8_t
* RLE compression enabled: no
* conversion type: Monochrome, Diffuse Dither 128
* bits per pixel: 1
*
* preprocess:
*  main scan direction: top_to_bottom
*  line scan direction: forward
*  inverse: no
*******************************************************************************/

/*
 typedef struct {
     long int code;
     const tImage *image;
     } tChar;
 typedef struct {
     int length;
     const tChar *chars;
     } tFont;
*/

#include <stdint.h>
#include "ili9341.h"


static const uint8_t image_data_specific_symbol_0x20[32] = {
    0xfe, 0xff, 
    0xfc, 0xff, 
    0xf8, 0xff, 
    0xf0, 0xff, 
    0xe2, 0x00, 
    0xc6, 0x00, 
    0x8f, 0xfc, 
    0x1f, 0xfc, 
    0x1f, 0xfc, 
    0x8f, 0xfc, 
    0xc6, 0x00, 
    0xe2, 0x00, 
    0xf0, 0xff, 
    0xf8, 0xff, 
    0xfc, 0xff, 
    0xfe, 0xff
};
static const tImage specific_symbol_0x20 = { image_data_specific_symbol_0x20, 16, 16};


static const tChar specific_symbol_array[] = {

  // character: '⇦'
  {0x20, &specific_symbol_0x20}

};


const tFont specific_symbol = { 1, specific_symbol_array };
