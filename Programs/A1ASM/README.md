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

Vermutung: 0b1111 in [R6] wuerde die LEDs D8-D11 einschalten, vielleicht wuerde 0b0000 in [6] die LEDs ausschalten.

Test Code:

    MOV     R4, #0x0f           ; load mask 0b1111
    MOV     R5, #0x00		; load mask 0b0000

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


Frage: was ist mit "load mask" in den kommentaren gemeint? denn 0b0100 ist nicht 0x40.
--> Vermutung: "load mask" bzw. "mask" ist nur immer auf 4 bit bereiche bezogen,
		in denen mindestens 1 bit auf 1 gestellt ist bezogen.
		um die LEDs D12-D15 zu erreichen wird der bit bereich 4-7 benoetigt.

Rechnung: 0x40 = 16^1*4 + 16^0*0 = 2^2*16^1 = 0100 000 -> wenn der erste bit breich
	  D8-D11 ist und 0100 0000 D14, dann ist
	  der zweite bit breich(4-7) D12-D15 und die Maske bezieht sich entweder auf einen bitbereich oder
	  oder einen relevanten birbereich.

Test:

    MOV     R4, #0xf0           ; load mask 0b1111

    STRB    R4,[R6]             ; turn on LED D12-15
    STRB    R4,[R7]             ; turn off LED D12-15
    b .

Ergebniss: die LEDs D12-15 gehen an.
Antwort: immernoch unklar welcher Fall mit mask gemeint ist, vielleicht auch nicht wichtig.

Frage: STRB steht fuer store byte. kann ich also nur eine byte laden und damit nur den Zustand von 8 LEDs gleichzeitig
       aendern?

Test1: 
    MOV     R4, #0xffff         ; load mask 0b1111

    STRB    R4,[R6]             ; turn on LED D8-D23
    STRB    R4,[R7]             ; turn off LED D8-D23

Ergebniss1: nur die LEDs D8-D15 werden veraendert.

Test2:
    MOV     R3, #0x00ff
    MOV     R4, #0xff00         ; load mask 0b1111

    STEB    R3,[R6]             ; turn on LED D8-D15
    STRB    R4,[R6]             ; turn on LED D16-D23
    STRB    R3,[R7]             ; turn off LED D8-D15
    STRB    R4,[R7]             ; turn off LED D16-D23

Ergebniss2: es werden wieder nur die LEDs D8-D15 veraendert.
Antwort: Mit STRB ist nur der zustand von 8 LEDs aenderbar und zwar die ersten 8.


Frage: wie erreiche ich die LEDs D16-D23?

Vermutung: Falls das gegebene GPIO data set register fuer mehr als diese 8 LEDs "zustaendig" ist, muss ein befehl genommen werden,
	   der mindestens 2bytes in [R6] uebermitteln kann. Falls das GPIO data set register nur fuer diese 8 LEDs zustaendig ist,
	   muss ein weiters GPIO data set register definiert werden.

Test:
    MOV     R3, #0xffff

    STRH     R3,[R6]
    STRH     R3,[R7]             ; turn off LED D8-D23
    b .

Ergebniss: Nur die LEDs D8-D15 werden an und aus geschaltet.
Antwort: Die LEDs D15-23 liegen nicht im 2ten byte des GPIO data register. Ich vermute es ein anderes Register benoetigt.
