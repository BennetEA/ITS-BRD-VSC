#include "calculations.h"
#include "encoder.h"

#define PHASE_ANGLE 0.3                      // gibt an, wie viele Grad einem gezählten Schritt entsprechen
#define MICROSECONDS_PER_SECOND 1000000.0    // Umrechnung von ms in s

static Phase_count old_phase_count = {.count = 0, .timestamp = 0};

void calculate(Angular_values *values) {
   Phase_count phase_count = get_phase_count();
   values->angle = phase_count.count * PHASE_ANGLE;   // Winkel = Zählstand * 0,3 Grad

   values->speed =                                                   // Berechnung der Winkelgeschwindigkeit
       (phase_count.count - old_phase_count.count) * PHASE_ANGLE /      // Alten Zählerstand vom neuen Abziehen
       ((phase_count.timestamp - (double)old_phase_count.timestamp) /   // Alten Zeitstempel vom neuen Abziehen
        MICROSECONDS_PER_SECOND);                                       // Zu sekunden umrechnen
   old_phase_count = phase_count;                                       // Alten Messwert überschreiben
}
