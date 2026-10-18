#ifndef FUNCTIONS_U
#define FUNCTIONS_U
#include "exception.h"
#include "terminal.h"

// arithmetische Funktionen
Exception add();
Exception sub();
Exception mul();
Exception div();

// aktionen
Exception display_last(Terminal terminal);
Exception display_last3(Terminal terminal);
void clear(Terminal terminal);
Exception dupe_last();
Exception swap_last2();

#endif // !FUNCTIONS_U
#define FUNCTIONS_U
