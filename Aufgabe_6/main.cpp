#include <Arduino.h>

inline void division(uint8_t dividend, uint8_t divisor) {
    char outputBuffer[128];
    uint8_t quotient, rest;

    __asm__ (

            "ldi  r16, 1 \n"   // Dividend
            "mov r16, %[dividend] \n"
            "ldi  r17, 1 \n"   // Divisor
            "mov r17, %[divisor] \n"

            "ldi  r18,   8 \n"   // 8 Bit Division
            "clr  r19 \n"        // Register für die Zwischenergebnisse / Rest
            "clr  r20 \n"        // Ergebnis

        "divloop: \n"
            "lsl  r16 \n"        // Zwischenergebnis mal 2 nehmen und das
            "rol  r19 \n"        // nächste Bit des Dividenden anhängen

            "lsl  r20 \n"        // das Ergebnis auf jeden Fall mal 2 nehmen,
                                // das hängt effektiv eine 0 an das Ergebnis an.
                                // Sollte das nächste Ergebnis-Bit 1 sein, dann wird
                                // diese 0 in Folge durch eine 1 ausgetauscht

            "cp   r19, r17 \n"   // ist der Divisor größer?
            "brlo div_zero \n"   // wenn nein, dann bleibt die 0
            "sbr  r20, 1 \n"     // wenn ja, dann jetzt die 0 durch eine 1 austauschen ...
            "sub  r19, r17 \n"
            "cp r1, r18 \n"     //wenn 8 mal durchgelaufen
            "breq output \n"    //output

        "div_zero: \n"
            "dec  r18 \n"        // das Ganze 8 mal wiederholen
            "brne divloop \n"

        "output: \n"
            "mov %[quotient], r20 \n"
            "mov %[rest], r19 \n"

            /* output-operand-list */
            : [quotient] "=d" (quotient), [rest] "=d" (rest)
            /* input-operand-list */
            : [dividend] "d" (dividend), [divisor] "d" (divisor)
            /* clobber-list */
            : "r18"
    );

    snprintf(outputBuffer, 128, "%d/%d = %d Rest %d", dividend, divisor, quotient, rest);
    Serial.println(outputBuffer);

}

void setup() {
// write your initialization code here
    Serial.begin(115200);
}

void loop() {
// write your code here

    division(18, 5);
    division(7, 5);
    division(4, 2);
    division(8, 3);
    division(1, 5);

    delay(2000);
}