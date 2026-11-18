#ifndef COLOR_PALETT_H
#define COLOR_PALETT_H

#include "BMP_types.h"
#include <stdint.h>

RGBQUAD nxt_color();
int read_bmp_palett(uint8_t count);
int bmp_to_rgb565_palett(RGBQUAD *palett, uint8_t size);
RGBTRIPLE *get_color(uint8_t index);

#endif /* COLOR_PALETT_H */
