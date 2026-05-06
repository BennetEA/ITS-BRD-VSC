;************************************************
;* Beginn der globalen Daten *
;************************************************
                   AREA MyData, DATA, align = 2
Base
VariableA          DCW 0x1234
VariableB          DCW 0x4711

VariableC          DCD  0

MeinHalbwortFeld   DCW 0x22 , 0x3e , -52, 78 , 0x27 , 0x45

MeinWortFeld       DCD 0x12345678 , 0x9dca5986
                   DCD -872415232 , 1308622848
                   DCD 0x27000000
                   DCD 0x45000000

MeinTextFeld       DCB "ABab0123",0

                   EXPORT VariableA
                   EXPORT VariableB
                   EXPORT VariableC
                   EXPORT MeinHalbwortFeld
                   EXPORT MeinWortFeld
                   EXPORT MeinTextFeld

;***********************************************
;* Beginn des Programms *
;************************************************
    AREA |.text|, CODE, READONLY, ALIGN = 3
; ----- S t a r t des Hauptprogramms -----
                EXPORT main
                EXTERN initITSboard
main            PROC
2                bl    initITSboard                 ; HW Initialisieren

; Laden von Konstanten in Register
;lädt 0x12 in r0
                mov   r0,#0x12                      ; Anw-01
;lädt -128d in r1
                mov   r1,#-128                      ; Anw-02
;lädt 0x12345678 in r2
                ldr   r2,=0x12345678                ; Anw-03

; Zugriff auf Variable
; lädt die Speicheradresse von VariableA in r0
                ldr   r0,=VariableA                 ; Anw-04
; lädt die ersten 2 bytes, an der Speicheradresse, in r0, in r1
                ldrh  r1,[r0]                       ; Anw-05
; lädt die ersten 2 bytes, an der Speicheradresse, in r0, in r2
                ldr   r2,[r0]                       ; Anw-06
; lädt die ersten 2 bytes, an der Speicheradresse, in r0+Speicheradresse von VariableC-Speicheradresse von VariableA, in r2
                str   r2,[r0,#VariableC-VariableA]  ; Anw-07

; Zugriff auf Felder (Speicherzellen)
;lädt die Speicheradresse der Variable MeinHalbwortFeld in r0
                ldr   r0,=MeinHalbwortFeld          ; Anw-08
;lödt die ersten 2 bytes an der Adresse, die in r0 gespeichert ist, in r1
                ldrh  r1,[r0]                       ; Anw-09
;lödt die ersten 2 bytes an der Adresse, die in r0 gespeichert ist +2, in r2
                ldrh  r2,[r0,#2]                    ; Anw-10
;lädt den wert 10d in r3
                mov   r3,#10                        ; Anw-11
;lädt die ersten 2 bytes an der adresse, die in r0 gespeichert ist + den wert der in r3 gespeichert ist, in r4
                ldrh  r4,[r0,r3]                    ; Anw-12

;lädt die ersten 2 bytes an der adresse [r0] +2 in r5 und speichert [r0] +2 in r0
                ldrh  r5,[r0,#2]!                   ; Anw-13
;lädt die ersten 2 bytes an der adresse [r0] +2 in r6 und speichert [r0] +2 in r0
                ldrh  r6,[r0,#2]!                   ; Anw-14
;lädt die 2 niedersten bytes aus r6 an der addresse [r0]+2 und speichert [r0] +2 in r0
                strh  r6,[r0,#2]!                   ; Anw-15

; Addition und Subtraktion von unsigned / signed Integer-Werten
; lädt adresse von MeinWortFeld in r0
                ldr  r0,=MeinWortFeld               ; Anw-16
; lädt inhalt an adresse in r0 in r1
                ldr  r1,[r0]                        ; Anw-17
; lädt inhalt an adresse r0 + 4 in r2
                ldr  r2,[r0,#4]                     ; Anw-18
; addiert r1 und r2, speichert das Ergebniss in r3 und setzt die flags im CSPR
                adds r3,r1,r2                       ; Anw-19

; lädt inhalt an adresse r0+8 in r4
                ldr  r4,[r0,#8]                     ; Anw-20
; lädt inhalt an adresse r0+12 in r5
                ldr  r5,[r0,#12]                    ; Anw-21
; subtrahiert wert in r4 mit wert in r5, speichert das Ergebniss in r6 und setzt die flags im CSPR 
                subs r6,r4,r5                       ; Anw-22

; lädt inhalt an adresse r0+16 in r7
                ldr  r7,[r0,#16]                    ; Anw-23
; lädt inhalt an adresse r0+20 in r8
                ldr  r8,[r0,#20]                    ; Anw-24
; subtrahiert wert in r7 mit wert in r8, speichert adresse in r9 und setzt flags im CSPR
                subs r9,r7,r8                       ; Anw-25

; ein unendlicher loop der das Programms am leben hält
forever         b   forever                         ; Anw-26
                ENDP
                END