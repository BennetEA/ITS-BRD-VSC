#Bennet Stahmleder Dokumentation GTP Aufgabe2

Effekte der Anweisungen Anw01-Anw06 auf die Register R0,R2,R3 und den Speicher ab der Adresse VariableA:

Inhalt vom Speicher ab Adresse VariableA LSB --> MSB: 0xef 0xbe

Anw01: Schreibt die Adresse VariableA in R0. -> R0 wird zum Pointer von Adresse VariableA.
Anw02: Schreibt den Inhalt von dem LSB an der Adresse VariableA in R2. -> R2 = 0xef
Anw03: Schreibt den Inhalt von dem LSB an der Adresse VariableA+1 in R3. -> R3 = 0xbe
Anw04: Verschiebt den Inhalt von R2 um 8 bits nach links und fuelt Nullen nach rechts auf. -> R2 = 0xfe00
Anw05: Setzt alle Bits die in R3 auf 1 gestellt sind, in R2 ebenfalls auf 1. -> R2 = 0xefbe
Anw06: Speichert den Inhalt von R2 an der Adresse VariableA. -> Speicher ab Adresse VariableA LSB -> MSB = 0xbe 0xef

