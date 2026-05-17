;definiere DATEN abschnitt
;speicher       erstelle variable "speicher" mit 1000 1 byte Elementen
;primzahlen     erstelle variable "primzahlen" mit 1 2 byte Element    

;definiere CODE abschnitt

;****************SIEB****************
;               setzte R1 als pointer für "speicher"
;               setze den ersten byte an "speicher" = 0xFF

;FOR-01         lade wert 4 in R3
;DO-01          StrB 0xFF an [R1, R3]
;               erhöhe R3 um 2
;UNTIL-01       wenn R3 <= 1000 springe zu DO-01

;FOR-02         lade den wert 3 in R2
;UNTIL-02       lade den wert R2*R2 in R3
;               wenn R3 > 1000 springe zu ENDFOR-02
;DO-02          lade Byte [speicher, R3] in R4

;IF-01          wenn R4 == 0xFF springe zu THEN-01
;ELSE-WHILE     lade 0xFF in [speicher, R3]
;               erhöhe R3 um R2
;               wenn R3 <= 1000 springe zu ELSE-WHILE

;Then-01        erhöhe R2 um 2
;               springe zu UNTIL-02
;ENDFOR-02

;*************Abspeichern*************
;               setze R2 als pointer für "primzahlen"
;FOR-03         lade wert 0 in R3
;DO-03          lade byte [R1,R3] in R4

;IF-02          wenn R4 == 0xFF springe zu THEN-02
;               lade HalbWort R3,#1 in [R2],#2

;Then-02        erhöhe R3 um 1
;UNTIL-03       wenn R3 <= 1000 springe zu DO-03
