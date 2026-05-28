                AREA MyData, DATA, align = 2
Speicher        FILL    1002,0
Primzahlen      FILL    336,0

                AREA |.text|, CODE, READONLY, ALIGN = 3
                EXPORT main
                EXTERN initITSboard
main            PROC

                LDR     R0,=Speicher                        ;erstelle pointer
                MOV     R1,#0xFF                            ;erstelle nicht Primzahl Markierung
                STRB    R1,[R0]                             ;markiere Element 0 nicht Primzahl 
                STRB    R1,[R0,#1]                          ;markiere Element 1 nicht Primzahl
FOR_GERADE      MOV     R3,#4                               ;setze Start-Index für gerade Zahlen loop
DO_GERADE       STRB    R1,[R0,R3]                          ;markiere Index Element nicht Primzahl
STEP_GERADE     ADD     R3,#2                               ;erhöhe Index
UNTIL_GERADE    CMP     R3,#1000                            ;prüfe ob Index im vorgegebenen Bereich ist
                BLS     DO_GERADE
END_GERADE
FOR_UNGERADE    MOV     R2,#3                               ;setze Start-Index für ungerade Zahlen loop
UNTIL_UNGERADE  MUL     R3,R2,R2                            ;setze Index für Vielfache
                CMP     R3,#1000                            ;prüfe ob Index im vorgegebenen Bereich ist
                BHI     END_UNGERADE

DO_UNGERADE     LDRB    R4,[R0,R3]                          ;lade Element des Vielfachen Index
IF_STEP         CMP     R4,#0xFF                            ;prüfe ob Vielfaches bereits als nicht Primzahl markiert ist 
                BEQ     THEN_STEP

WHILE           STRB    R1,[R0,R3]                          ;streiche Vielfache
                ADD     R3,R3,R2                            ;erhöhe Vielfaches
                CMP     R3,#1000                            ;prüfe ob Vielfaches im vorgegebenen Bereich ist
                BLS     WHILE

THEN_STEP       ADD     R2,#2                               ;erhöhe Index
                b       UNTIL_UNGERADE
END_UNGERADE

Abspeichern
                LDR     R2,=Primzahlen                      ;erstelle pointer
FOR_AS          MOV     R3,#0                               ;setze Primzahl-Index
DO_AS           LDRB    R4,[R0,R3]                          ;lade Primzahl-Markierung aus dem speicher

IF_AS           CMP     R4,#0xFF                            ;prüfe Primzahl-Markierung
                BEQ     THEN_AS
                STRH    R3,[R2],#2                          ;speicher Primzahl

THEN_AS         ADD     R3,#1                               ;erhöhe Primzahl-Index
UNTIL_AS        CMP     R3,#1000                            ;prüfe ob Index im vorgegebenen Bereich ist
                BLS     DO_AS

                b       .
                ENDP
                END
