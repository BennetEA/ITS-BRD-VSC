#include "gui.h"
#include "LCD_GUI.h"
#include "lcd.h"
#include <stdio.h>

static char speed[12];
static int len_speed;
static char angel[12];
static int len_angel;
static int update_counter;

void init_overlay() {
   lcdGotoXY(1, 2);
   lcdPrintlnS("Winkel                :            Grad");

   lcdGotoXY(1, 4);
   lcdPrintlnS("Winkelgeschwindigkeit :            Grad/s");
}

void update_display_values(double s, double a) {
   len_speed = snprintf(speed, sizeof(speed), "%09.3f", s);
   len_angel = snprintf(angel, sizeof(angel), "%09.3f", a);
   update_counter = len_speed + len_angel - 1;
}

void update_char() {
   if (update_counter < 0) {
      return;
   }
   if (update_counter < len_speed) {
      lcdGotoXY(26 + update_counter, 4);
      lcdPrintC(speed[update_counter]);
   } else {
      lcdGotoXY(26 + update_counter - len_speed, 2);
      lcdPrintC(angel[update_counter - len_speed]);
   }
   update_counter--;
}
