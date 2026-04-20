Original State:

    MOV     R0, #0x01           ; load mask 0b0001
    MOV     R1, #0x02           ; load mask 0b0010
    MOV     R2, #0x40           ; load mask 0b0100
    MOV     R3, #0x80           ; load mask 0b1000

    STRB    R2, [R6]    ; switch on LED D14
    STRB    R3, [R6]    ; switch on LED D15
    STRB    R0, [R6]    ; switch on LED D08
    STRB    R0, [R7]    ; switch off LED D08
    STRB    R0, [R6]    ; switch on LED D08
    STRB    R1, [R6]    ; switch on LED D09
    STRB    R2, [R7]    ; switch off LED D14
    STRB    R3, [R7]    ; switch off LED D15
    b .

Beobachtungen:
1. Wenn ein hexwert in der Speicher Adresse [R6] gespeichert wird, geht eine LED an.
2. Wenn ein hexwert in der Speicher Adresse [R7] gespeichert wird, geht eine LED aus.
--> macht Sinn weil [R6] ist als "GPIO data set register" kommentiert und [R7] als "GPIO clear register"

3. die Binaer Nummern der hexwerte die in R0-R3 gesetzt werden, folgen einen bestimmten muster, in welchem die 1
   von rechts beginnend nach links wandert. Ausserdem kann man dieses Muster direkt auf auf das LED-Muster abbilden.
--> Vermutung: 0b1111 in [R6] wuerde die LEDs D8-D11 einschalten, vielleicht wuerde 0b0000 in [6] die LEDs ausschalten.

First Test:

    MOV     R4, #0x0f           ; load mask 0b1111
    MOV     R5, #0x00           ; load mask 0b0000

    STRB    R4,[R6]             ; turn on LED D8-D11
    STRB    R5,[R6]             ; turn off LED D8-D11
    b .

Ergebniss:
0b1111 schaltet die LEDs D8-D11 an, 0b0000 schaltet die LEDs NICHT aus.

Korrektur des codes:

    MOV     R4, #0x0f           ; load mask 0b1111

    STRB    R4,[R6]             ; turn on LED D8-D11
    STRB    R4,[R7]             ; turn off LED D8-D11
    b .
