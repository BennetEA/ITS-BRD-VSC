#ifndef COLOR_PALETT_H
#define COLOR_PALETT_H

#include "BMP_types.h"
#include "exception.h"
#include <stdint.h>

RGBTRIPLE nxt_color();
Error read_colors(uint8_t count);
RGBTRIPLE *get_pallet();

#endif /* COLOR_PALETT_H */
