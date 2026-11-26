#include "gui.h"
#include "LCD_GUI.h"
#include "lcd.h"
#include <stdio.h>

#define DISPLAY_BUFFER_SIZE 12
#define DISPLAY_VALUE_COLUMN 26

static char speed[DISPLAY_BUFFER_SIZE];   // Winkelgeschwindigkeit
static int len_speed; 
static char angel[DISPLAY_BUFFER_SIZE];   // Winkel
static int len_angel;
static int update_counter;

void init_overlay() {
   lcdGotoXY(1, 2);
   lcdPrintlnS("Winkel                :            Grad");

   lcdGotoXY(1, 4);
   lcdPrintlnS("Winkelgeschwindigkeit :            Grad/s");
}

void update_display_values(Angular_values values) {                     // Zahlen in Text umwandeln
   len_speed = snprintf(speed, sizeof(speed), "%09.3f", values.speed);
   len_angel = snprintf(angel, sizeof(angel), "%09.3f", values.angle);
   update_counter = len_speed + len_angel - 1;
}

void update_char() {                   
   if (update_counter < 0) {                                               // Wenn alle Zeichen ausgegeben worden sind = EOF
      return;
   }
   if (update_counter < len_speed) {                                       // Schreiben der Wineklgeschwindigkeit
      lcdGotoXY(DISPLAY_VALUE_COLUMN + update_counter, 4);
      lcdPrintC(speed[update_counter]);
   } else {                                                                // Schreiben des Winkels
      lcdGotoXY(DISPLAY_VALUE_COLUMN + update_counter - len_speed, 2);
      lcdPrintC(angel[update_counter - len_speed]);
   }
   update_counter--;
}
