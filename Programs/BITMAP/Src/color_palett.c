#include "color_palett.h"
#include "BMP_types.h"
#include "errorhandler.h"
#include "input.h"
#include <stdint.h>

#define COLOR_BYTE_SIZE

static PRGBTRIPLE rgb565_color_palett;

RGBQUAD nxt_color() {
   RGBQUAD color;

   color.rgbBlue = nxt_chr();
   color.rgbGreen = nxt_chr();
   color.rgbRed = nxt_chr();
   color.rgbReserved = nxt_chr();

   return color;
}
