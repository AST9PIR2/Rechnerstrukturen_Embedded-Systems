#include <Arduino.h>
#include "sleep_delay.h"
#include <avr/wdt.h>
#include <avr/sleep.h>
#include <avr/power.h>

#define LED 12
#define BLINK 2

sleep::ISR(WDT_vect){}


void sleep::sleep_delay(uint32_t sec){
	set_sleep_mode(SLEEP_MODE_PWR_DOWN);
	wdt_enable(WDTO_1S);				
	sleep_enable();						
	uint32_t time = 0;						
	while(time < sec){

		WDTCSR |= (1 << WDIE)
		sleep_mode();		
		time++;					
	}

	sleep_disable();	
	wdt_disable();	
}
