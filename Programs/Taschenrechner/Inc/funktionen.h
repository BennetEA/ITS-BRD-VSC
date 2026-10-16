#ifndef FUNKTIONEN_H
#define FUNKTIONEN_H
#include "error.h"

Error add();   // Addiert die obersten beiden Stackelemente
Error sub();   // Subtrahiert das oberste Stackelement von dem darunter
Error mul();   // Multipliziert die beiden obersten Stackelemente
Error div();   // Dividiert das Stackelement vor dem obersten durch das Oberste
Error p(void); // Druckt das oberste Stackelement aus
Error P(void); // Druckt die obersten 3 Stackelement aus
void C(void);  // Lösch alle Stackelement
Error d(void); // Dupliziert das oberste Stackelement
Error r(void); // Vertausch die beiden höchsten Stackelemente

#endif // !FUNKTIONEN_H
#define FUNKTIONEN_H
