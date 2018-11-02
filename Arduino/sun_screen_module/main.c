/*
* sun_screen_module.c
*
* Created: 2-11-2018 11:29:19
* Author : jeroe
*/

#include <avr/io.h>
#include <stdlib.h>
#include <avr/sfr_defs.h>
#define F_CPU 16E6
#include <util/delay.h>
#include <avr/interrupt.h>

#define UBBRVAL 51

#define TRUE 1
#define FALSE 0


uint8_t sensor_value = 0; // Can we handle light sensor in 8 bit?
uint8_t sensor_max_value = 0;
uint8_t sensor_min_value = 0;

uint8_t measure_timer = 0; // 40 for temperature and 30 for light sensor
uint8_t send_timer = 0; // send every 60 seconds: Sunscreen state and sensor state,  (handled by our python client)??

// Min and max and current distance of the sunscreen
int min_distance = 5;	//	min: 0.05m =    5cm
int max_distance = 160;	//  max: 1.60m		= 160cm
int cur_distance = 0;	//

// Pins to indicate if the sunscreen is rolling, out or in
uint8_t led_pin_out = 0;		// Red led
uint8_t led_pin_in = 0;			// Green led
uint8_t led_pin_rolling = 0;	// Blinking yellow led + steady out or in pin indicating it's rolling out or in

// Identifier
char id[4] = "TEMP"; // TEMP for temperature and LIGHT for light








void uart_init()
{
	// set the baud rate
	UBRR0H = 0;
	UBRR0L = UBBRVAL;
	// disable U2X mode
	UCSR0A = 0;
	// enable transmitter
	UCSR0B = _BV(TXEN0) | _BV(RXEN0);
	// set frame format : asynchronous, 8 data bits, 1 stop bit, no parity
	UCSR0C = _BV(UCSZ01) | _BV(UCSZ00);

	UCSR0B |= (1 << RXCIE0); // Enable interupt on rx

}

void transmit(char c) {
	loop_until_bit_is_set(UCSR0A, UDRE0); // Wait until data register empty
	UDR0 = c;
}

void transmit_word(int value){
	// Split short into two char

	uint8_t low_byte = value & 0xFF;
	uint8_t high_byte = value >> 8;

	// merge two char into short
	transmit(low_byte);
	transmit(high_byte);

}

void receive_word(){
	uint8_t high;
	uint8_t low;
	
	// merge two char into short
	// value = highbyte << 8 places | low byte;
	int received = (high << 8) | low;
}

void transmit_id(){
	for (int i = 0; i < 4; i++)
	{
		transmit(id[i]);
	}
}

uint8_t receive() {
	loop_until_bit_is_set(UCSR0A, RXC0); // Wait until data exists
	return UDR0;
}

int main(void)
{
	uart_init();
	
	/* Replace with your application code */
	while (1)
	{
		uint8_t data = receive();
		
		// if: detect
		if(data == 10){
			// send succeed
			transmit(10);
			// send id
			transmit_id();
		}else if(data == 29)
		{ // get distance max
			transmit(10); // Send succeed
			transmit_word(max_distance); // Send highest possible value
		}
		
		// Just wait for input i guess
		// Send some signal back
		// etc
	}
}