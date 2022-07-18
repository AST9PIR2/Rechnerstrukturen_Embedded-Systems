//
// Created by Pirmin on 01.06.2022.
//

#ifndef AUFGABE_1_BITOPERATIONS_H
#define AUFGABE_1_BITOPERATIONS_H

//Schiebe die 1 auf die richtige Position (nach links)
#define BIT(pos) ( 1<<(pos) )

//SB(VALUE, POSITION): setzt das Bit (d.h. das Bit nimmt den Wert 1 an) an der Stelle POSITION.
#define SB(VALUE, POSITION) ( (VALUE) |= (BIT(POSITION)) )

//CB(VALUE, POSITION): löscht das Bit (d.h. das Bit nimmt den Wert 0 an) an der Stelle POSITION.
#define CB(VALUE, POSITION) ( (VALUE) &= ~(BIT(POSITION)) )

//IBS(VALUE, POSITION): prüft, ob das bit an der Stelle POSITION gesetzt ist (d.h. ob es den Wert 1 hat).
#define IBS(VALUE, POSITION) ( ( 0u == ( (VALUE)&(BIT(POSITION)) ) ) ? 0u : 1u )

//TB(VALUE, POSITION): "toggelt" (hin- und herschalten) das Bit an der Stelle POSITION.
#define TB(VALUE, POSITION) ( (VALUE) ^= (BIT(POSITION)) )


#endif //AUFGABE_1_BITOPERATIONS_H
