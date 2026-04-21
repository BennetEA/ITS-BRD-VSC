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

-----------------------------------------------------------------

Frage: 		Wie funktioniert der Assembler code?

Beobachtungen: 	1. Wenn ein hexwert an der Speicheradresse [R6], welche als "GPIO data set register" kommentiert ist,
		    gespeichert wird, geht eine LED an.
		2. Wenn ein hexwert an der Speicheradresse [R7], welche als "GPIO clear register" kommentiert ist,
		    gespeichert wird, geht eine LED aus.
		3. Man kann eine direkte Verbindung zwischen den wert, der in [R6] oder [R7] gespeichert wird und 
		    der LED welche an oder aus geht erkennen.
		   -> Die LED auf dem Board entspricht der selben position, wie der position der 1 im binaer code.

Vermutung:	Fuer jede LED auf den Board exestiert eine Bit adresse, welche die LED anschaltet, wenn auf 1 gesetzt 
		 und eine Bit adresse, welche die LED auschaltet, wenn auf 1 gesetzt.
		Ausserdem sind die Bit adressen, welche LED anschalten in Register aufgeteilt, sowohl auch die Bit Adressen,
		 welche die LED auschalten.

Test:		Wenn die Vermutung stimmt, muss folgender code die LEDs D8-D11 an- und wieder ausschalten:

    MOV     R4, #0x0f           ; load mask 0b1111

    STRB    R4,[R6]             ; turn on LED D8-D11
    STRB    R4,[R7]             ; turn off LED D8-D11
    b .

Ergebniss:	Die LEDs D8-D11 wurden an- und wieder aussgeschaltet. Somit kann genannte theorie weiter geprueft
		 und nicht verworfen werden.

Probe von	
Ergebniss:	Folgender Code sollte die LEDs D8, D10 und D11 anschalten:

Egebniss von
Probe:		Die LEDs D8, D10 und D11 sind an- und ausgegangen.

-----------------------------------------------------------------

Frage:		Wie gross sind die Register?

Vermutung:	Die gegebenen Register laenge korreliert mit der LED reihen laenge D8-D23 und ist somit 16 Bit / 2 Bytes lang.

Test:		Wenn die Vermutung stimmt, muss folgender Code alle LEDs von D8 bis D23 an- und auschalten:

    MOV     R4, #0xffff         ; load mask

    STRH    R4,[R6]             ; turn on LED
    STRH    R4,[R7]             ; turn off LED
    b .

Ergebniss:	Nur die LEDs D8-D15 sind an- und ausgegangen. Vermutlich sind die Register nur 8 Bits / 1 Byte lang.

Probe
Ergebniss:	Folgender Code sollte keine LEDs an- oder ausschalten:

    MOV     R4, #0xff00         ; load mask

    STRH    R4,[R6]             ; turn on LED
    STRH    R4,[R7]             ; turn off LED
    b .

Ergebniss
Probe:		Keine LEDs sind angegangen.

-----------------------------------------------------------------

Frage:		Wo ist das Register, um die LEDs D16-D23 zu erreichen?

Vermutung:	Das Register, um die LEDs D16-D23 zu erreichen liegt im Bereich nach dem clear Register der LEDs D8-D15

Test:		Wenn die Vermutung stimmt, sollte folgender Code LEDs aus der LED reihe D16-D23  anschalten:

PERIPH_BASE         equ 0x40000000
AHB1PERIPH_BASE     equ (PERIPH_BASE + 0x00020000)
GPIOD_BASE          equ (AHB1PERIPH_BASE + 0x0C00)
    
GPIO_D_SET          equ (GPIOD_BASE + 0x18)
GPIO_D_CLR          equ (GPIOD_BASE + 0x1A)
test_SET            equ (GPIO_D_CLR + 0x01)

;* We need minimal memory setup of InRootSection placed in Code Section
    AREA  |.text|, CODE, READONLY, ALIGN = 3
    ALIGN
main
    BL initITSboard             ; needed by the board to setup
    nop                         ; no operation
    LDR     R6, =GPIO_D_SET     ; get address of the GPIO data set register
    LDR     R7, =GPIO_D_CLR     ; get address of the GPIO data clear register
    LDR     R8, =test_SET       ; test
    MOV     R4, #0xff           ; load mask

    STRH    R4,[R8]             ; turn on LED
    b .

    ALIGN
    END

Ergebniss:	Keine LEDs sind angegangen, das Register liegt wahrscheinlich woanders.

Folge
Vermutung:	Das Register um die LEDs anzuschalten ist 16-32 Bits vor dem GPIOD_SET Register.

Test:		Wenn die Vermutung stimmt, sollte folgender code LEDs aus der LED Reihe D16-D23 anschalten:

....		Nach mehreren Versuchen ein Register um dem GPIOD_BASE Register zu finde, konnte ich keins finden,
		 dass die LEDs beeinflusst.
