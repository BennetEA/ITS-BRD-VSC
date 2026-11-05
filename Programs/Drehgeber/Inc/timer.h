// apb1 = 45000000
// apb2 = 90000000
// TIM9-TIM11 = 180MHz
// TIM12-14 = 90MHz
// TIM2-5 = 90MHz

#ifndef TIMER_U
#define TIMER_U

typedef enum {
   US = 0,
   MS,
   S,
   MIN,
} time_unit;

void init_timer();
void reset_timer();
double time(time_unit unit);

#endif // !TIMER_U
