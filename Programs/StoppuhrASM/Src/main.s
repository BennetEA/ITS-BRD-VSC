;******************** (C) COPYRIGHT HAW-Hamburg ********************************
;* File Name          : main.s
;* Author             : Franz Korf	
;* Version            : V1.0
;* Date               : 11.05.2022
;* Description        : Rahmen zur Loesung von GTP Woche 7-9 (Stoppuhr).
;
;*******************************************************************************

; Define address of selected GPIO and Timer registers
PERIPH_BASE     	equ	0x40000000                 ;Peripheral base address
AHB1PERIPH_BASE 	equ	(PERIPH_BASE + 0x00020000)
APB1PERIPH_BASE     equ PERIPH_BASE

GPIOD_BASE			equ	(AHB1PERIPH_BASE + 0x0C00)
GPIOF_BASE			equ	(AHB1PERIPH_BASE + 0x1400)
TIM2_BASE           equ (APB1PERIPH_BASE + 0x0000)
	
GPIO_F_PIN        	equ	(GPIOF_BASE + 0x10)

GPIO_D_PIN			equ	(GPIOD_BASE + 0x10)
GPIO_D_SET			equ (GPIOD_BASE + 0x18)
GPIO_D_CLR			equ	(GPIOD_BASE + 0x1A)
	
Timer				equ  0x40000024
TIM2_PSC			equ (TIM2_BASE + 0x28)   ; Prescaler  resolution
TIM2_ERG			equ (TIM2_BASE + 0x14)   ; 16 Bit register, Bit 0 : 1 Restart Timer


    EXTERN initITSboard
    EXTERN GUI_init
	EXTERN TP_Init
	EXTERN initTimer
	EXTERN lcdSetFont
	EXTERN lcdGotoXY      		; TFT goto x y function
	EXTERN lcdPrintS			; TFT output function	
    EXTERN lcdPrintC            ; TFT output one character		
	EXTERN Delay				; Delay (ms) function


;********************************************
; Data section, aligned on 4-byte boundery
;********************************************

STATE_INIT          equ     0
STATE_RUN           equ     1
STATE_HOLD          equ     2

SW7                 equ     0x80
SW6                 equ     0x40
SW5                 equ     0x20

INIT_TRUE           equ     1
INIT_FALSE          equ     0

	AREA MyData, DATA, align = 2

DEFAULT_BRIGHTNESS	DCW     800

ZERO_TIME           DCB     "00:00.00", 0
MIN                 DCB     "00:", 0
SEC                 DCB     "00.", 0
MS                  DCB     "00", 0

CURRENT_STATE       DCB     STATE_INIT
INIT                DCB     0

;********************************************
; Code section, aligned on 8-byte boundery
;********************************************
	AREA |.text|, CODE, READONLY, ALIGN = 3


;--------------------------------------------
; main subroutine
;--------------------------------------------
	EXPORT main [CODE]
	
main	PROC
                BL		initITSboard
                ldr   	r1, =DEFAULT_BRIGHTNESS
                ldrh 	r0, [r1]
                bl   	GUI_init
                bl  	initTimer
                ldr 	R1,=TIM2_PSC   			; Set pre scaler such that 1 timer tick represents 10 us
                mov 	R0,#(90*10-1) 
                strh	R0,[R1]
                ldr 	R1,=TIM2_ERG   			; Restart timer	
                mov		R0,#0x01
                strh	R0,[R1]					; Set UG Bit
                MOV 	R0, #24
                bl  	lcdSetFont

;--------------------------------------------
; Zustands-Automat
;--------------------------------------------

superloop
                LDR     R0,=CURRENT_STATE
                ldrb    R0,[R0]

if_init         cmp     R0,#STATE_INIT
                bne     endif_init
then_init       bl      init
endif_init

if_run          cmp     R0,#STATE_RUN
                bne     endif_run
then_run        bl      run
endif_run

if_hold         cmp     R0,#STATE_HOLD
                bne     endif_hold
then_hold       bl      hold
endif_hold
                BAL		superloop				
                ENDP

;--------------------------------------------
; init
;--------------------------------------------

init            PROC
                push    {R4-R5,LR}
                LDR     R4,=GPIO_D_SET
                mov     R5,#SW5
                strb    R5,[R4]
                LDR     R4,=INIT
                ldrb    R5,[R4]
if_01           cmp     R5,#INIT_TRUE
                beq     endif_01
then_01         mov     R5,#INIT_TRUE
                strb    R5,[R4]
                mov     R0,#10
                mov     R1,#6
                bl      lcdGotoXY
                LDR     R0,=ZERO_TIME
                bl      lcdPrintS
endif_01        
                bl      zustand_init
                pop     {R4-R5,PC}
                ENDP

;--------------------------------------------
; zustand_init
;--------------------------------------------

zustand_init    PROC
                push    {R4-R5,LR}
                bl      get_button
if_02           cmp     R0,#SW7
                bne     endif_02
then_02         LDR     R0,=CURRENT_STATE
                mov     R4,#STATE_RUN
                strb    R4,[R0]
                LDR     R0,=INIT
                mov     R4,#INIT_FALSE
                strb    R4,[R0]
                LDR     R0,=GPIO_D_CLR
                mov     R4,#SW5
                strb    R4,[R0]
                ldr 	R0,=TIM2_ERG   			
                mov		R4,#0x01
                strh	R4,[R0]
endif_02        pop     {R4-R5,PC}
                ENDP

;--------------------------------------------
; get_button
;--------------------------------------------

get_button      PROC
                LDR     R0,=GPIO_F_PIN
                ldrb    R0,[R0]
                and     R0,#0xFF
                eor     R0,#0xFF
                bx      LR
                ENDP

;--------------------------------------------
; run
;--------------------------------------------

run             PROC
                push    {LR}
                LDR     R0,=GPIO_D_SET
                mov     R1,#SW7
                strb    R1,[R0]
                bl      zustand_run
                bl      get_time
                push    {R1,R2}
                bl      ascii
                bl      print_min
                pop     {R0}
                bl      ascii
                bl      print_sec
                pop     {R0}
                bl      ascii
                bl      print_ms
                pop     {PC}
                ENDP

;--------------------------------------------
; zustand_run
;--------------------------------------------

zustand_run     PROC
                push    {R4-R5,LR}
                bl      get_button
if_03           cmp     R0,#SW6
                bne     endif_03
then_03         LDR     R0,=CURRENT_STATE
                mov     R4,#STATE_HOLD
                strb    R4,[R0]
                b       clr_led
endif_03
if_04           cmp     R0,#SW5
                bne     endif_04
then_04         LDR     R0,=CURRENT_STATE
                mov     R4,#STATE_INIT
                strb    R4,[R0]
clr_led         LDR     R0,=GPIO_D_CLR
                mov     R4,#SW7
                strb    R4,[R0]
endif_04
                pop     {R4-R5,PC}
                ENDP

;--------------------------------------------
; get_time
;--------------------------------------------
get_time        PROC                ; keine Argumente
                LDR     R2,=Timer
                ldr     R2,[R2]
                mov     R3,#100
                udiv    R2,R2,R3    ; zeit in ms
                mov     R3,#1000
                udiv    R1,R2,R3    ; zeit in s
                mul     R3,R1,R3
                sub     R2,R2,R3    ; ms von Zeit
                mov     R3,#60
                udiv    R0,R1,R3    ; Minuten von Zeit
                mul     R3,R0,R3
                sub     R1,R1,R3    ; Sekunden von Zeit
                bx      LR
                    ENDP
;--------------------------------------------
; ascii
;--------------------------------------------

ascii           PROC
                mov     R1,#100
                udiv    R2,R0,R1
                mul     R2,R2,R1
                sub     R0,R0,R2
                mov     R1,#10
                udiv    R2,R0,R1
                mul     R1,R2,R1
                sub     R0,R0,R1
                add     R0,R0,#'0'
                add     R2,R2,#'0'
                lsl     R0,R0,#8
                orr     R0,R0,R2
                bx      LR
                ENDP

;--------------------------------------------
; print_min
;--------------------------------------------

print_min       PROC
                push    {LR}
                LDR     R1,=MIN
                ldrh    R2,[R1]
if_05           cmp     R0,R2
                beq     endif_05
then_05         strh    R0,[R1]
                mov     R0,#10
                mov     R1,#6
                bl      lcdGotoXY
                LDR     R0,=MIN
                bl      lcdPrintS
endif_05
                pop     {PC}
                ENDP

;--------------------------------------------
; print_sec
;--------------------------------------------

print_sec       PROC
                push    {LR}
                LDR     R1,=SEC
                ldrh    R2,[R1]
if_06           cmp     R0,R2
                beq     endif_05
then_06         strh    R0,[R1]
                mov     R0,#13
                mov     R1,#6
                bl      lcdGotoXY
                LDR     R0,=SEC
                bl      lcdPrintS
endif_06
                pop     {PC}
                ENDP

;--------------------------------------------
; print_min
;--------------------------------------------

print_ms        PROC
                push    {LR}
                LDR     R1,=MS
                ldrh    R2,[R1]
if_07           cmp     R0,R2
                beq     endif_05
then_07         strh    R0,[R1]
                mov     R0,#16
                mov     R1,#6
                bl      lcdGotoXY
                LDR     R0,=MS
                bl      lcdPrintS
endif_07
                pop     {PC}
                ENDP

;--------------------------------------------
; hold
;--------------------------------------------

hold            PROC
                push    {LR}
                LDR     R0,=GPIO_D_SET
                mov     R1,#SW6
                strb    R1,[R0]
                bl      get_button
if_08           cmp     R0,#SW7
                bne     endif_08
then_08         LDR     R0,=CURRENT_STATE
                mov     R4,#STATE_RUN
                strb    R4,[R0]
                b       clr_led_02
endif_08
if_09           cmp     R0,#SW5
                bne     endif_09
then_09         LDR     R0,=CURRENT_STATE
                mov     R4,#STATE_INIT
                strb    R4,[R0]
clr_led_02      LDR     R0,=GPIO_D_CLR
                mov     R4,#SW6
                strb    R4,[R0]
endif_09
                pop     {PC}
                ENDP

                ALIGN
                END
