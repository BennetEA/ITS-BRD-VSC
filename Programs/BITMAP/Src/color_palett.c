#include "color_palett.h"
#include "BMP_types.h"
#include "error.h"
#include "errorhandler.h"
#include "exception.h"
#include "input.h"
#include <stdint.h>
#include <stdlib.h>

#define COLOR_BYTE_SIZE

static RGBTRIPLE pallet[256];
static uint8_t size;

RGBTRIPLE nxt_color() {
   RGBTRIPLE color;

   color.rgbtBlue = nxt_chr() >> 3;
   color.rgbtGreen = nxt_chr() >> 2;
   color.rgbtRed = nxt_chr() >> 3;
   nxt_chr();

   return color;
}

Error read_colors(uint8_t count) {
   if (count == 0) {
      count = 255;
   }
   for (int i = 0; i <= count; i++) {
      pallet[i] = nxt_color();
   }
   size = count;

   return ERR_OK;
}

RGBTRIPLE *get_pallet() { return pallet; }
