#include "test.h"
#include "BMP_types.h"
#include "LCD_GUI.h"
#include "LCD_Touch.h"
#include "_timer.h"
#include "color_palett.h"
#include "error.h"
#include "errorhandler.h" /* EOK */
#include "fileHeader.h"   /* input_file_header */
#include "fontsFLASH.h"
#include "headers.h"
#include "init.h"
#include "input.h" /* ask_transport, init_input */
#include "lcd.h"
#include "stm32f429xx.h"
#include "usb_clock_config.h"
#include <timer.h>

void uint8_to_hex(uint8_t value, char *hex) {
   const char digits[] = "0123456789ABCDEF";

   hex[0] = digits[value >> 4];
   hex[1] = digits[value & 0x0F];
}

void print_color(RGBTRIPLE color) {
   uint8_t *p = (uint8_t *)&color;
   char hex[2];

   for (int i = 0; i < 3; i++) {
      uint8_to_hex(*(p + i), hex);
      lcdPrintC(hex[0]);
      lcdPrintC(hex[1]);
      lcdPrintC(' ');
   }
}

void test_init() {
   initITSboard();
   switch_to_168_MHz();
   initTimer();
   GUI_init(DEFAULT_BRIGHTNESS);
   TP_Init(false);
   if (!checkVersionFlashFonts()) {
      Error_Handler();
   }
   transport_t transport = ask_transport();
   init_input(transport);
}

void test_read_input() {
   test_init();
   init_timer();
   double old_time = time(S);

   open_nxt_file();

   GUI_clear(65535);
   lcdGotoXY(0, 0);
   while (1) {
      if (time(S) - old_time >= 1) {
         int a = nxt_chr();
         int b = a / 16;
         int c = a % 16;

         if (b > 9) {
            lcdPrintC(b - 10 + 'a');
         } else {
            lcdPrintInt(b);
         }
         if (c > 9) {
            lcdPrintC(c - 10 + 'a');
         } else {
            lcdPrintInt(c);
         }
         lcdPrintC(' ');
         old_time = time(S);
      }
   }
}

void test_get_headers() {
   test_init();
   open_nxt_file();

   read_hdrs();
   BITMAPFILEHEADER file_hdr;
   BITMAPINFOHEADER info_hdr;

   get_file_hdr(&file_hdr);
   get_info_hdr(&info_hdr);
   uint8_t color_count = info_hdr.biClrUsed;
   uint32_t height = info_hdr.biHeight;
   uint32_t width = info_hdr.biWidth;
   uint32_t pixel_offset = file_hdr.bfOffBits;

   GUI_clear(65535);
   lcdGotoXY(0, 0);

   lcdPrintS("Anzahl Farben:");
   lcdPrintInt(color_count);
   lcdPrintlnS(" ");

   lcdPrintS("Bild hoehe:");
   lcdPrintInt(height);
   lcdPrintlnS(" ");

   lcdPrintS("Bild breite:");
   lcdPrintInt(width);
   lcdPrintlnS(" ");

   lcdPrintS("Pixel offset:");
   lcdPrintInt(pixel_offset);
   lcdPrintlnS(" ");
}

void test_nxt_color() {
   test_init();
   open_nxt_file();

   read_hdrs();
   BITMAPFILEHEADER file_hdr;
   BITMAPINFOHEADER info_hdr;

   get_file_hdr(&file_hdr);
   get_info_hdr(&info_hdr);
   uint8_t color_count = info_hdr.biClrUsed;

   GUI_clear(65535);
   lcdGotoXY(0, 0);

   lcdPrintS("Anzahl Farben:");
   lcdPrintInt(color_count);
   lcdPrintlnS(" ");

   for (int i = 0; i < color_count; i++) {
      lcdPrintS("Farbe");
      lcdPrintInt(i);
      lcdPrintS(": ");
      RGBTRIPLE color = nxt_color();
      print_color(color);
      lcdPrintlnS(" ");
   }
}

void test_pallet() {
   test_init();
   open_nxt_file();

   read_hdrs();
   BITMAPFILEHEADER file_hdr;
   BITMAPINFOHEADER info_hdr;

   get_file_hdr(&file_hdr);
   get_info_hdr(&info_hdr);
   uint8_t color_count = info_hdr.biClrUsed;

   GUI_clear(65535);
   lcdGotoXY(0, 0);

   read_colors(color_count);
   RGBTRIPLE *pallet = get_pallet();

   lcdPrintS("Anzahl Farben:");
   lcdPrintInt(color_count);
   lcdPrintlnS(" ");

   for (int i = 0; i < color_count; i++) {
      lcdPrintS("Farbe");
      lcdPrintInt(i);
      lcdPrintS(": ");
      print_color(pallet[i]);
      lcdPrintlnS(" ");
   }
}

void test_print_color() {
   test_init();
   GUI_clear(65535);
   RGBTRIPLE color = {
       .rgbtBlue = 255,
       .rgbtGreen = 0,
       .rgbtRed = 255,
   };

   lcdGotoXY(1, 0);
   print_color(color);
}

void test_main() { test_pallet(); }
