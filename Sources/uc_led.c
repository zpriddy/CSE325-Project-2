//*******************************************************************************************************
// uc_led.c
//
// DESCRIPTION:
//
// AUTHORS:
// 	Abdulla Al Braiki (ayalbrai@asu.edu)
//	Zachary Priddy (zpriddy@asu.edu)
//
// Computer Science & Engineering
// Arizona State University
// Tempe, AZ 85287-8809
// 
//********************************************************************************************************

#include "common.h"



//Calls uc_led_off() four times to turn all LED's off.
void uc_led_all_off()
{
    uc_led_off(UC_LED1);
    uc_led_off(UC_LED2);
    uc_led_off(UC_LED3);
    uc_led_off(UC_LED4);
}

//Calls uc_led_on() four times to turn all LED's on.
void uc_led_all_on()
{
    uc_led_on(UC_LED1);
    uc_led_on(UC_LED2);
    uc_led_on(UC_LED3);
    uc_led_on(UC_LED4);
}

//Calls gpio_port_init() four times to initialize the pins of port TC that each LED is connected to.
void uc_led_init()
{
    gpio_port_init(PORT_TC, UC_LED1, FUNCT_GPIO, DATA_DIR_OUT, OFF);
    gpio_port_init(PORT_TC, UC_LED2, FUNCT_GPIO, DATA_DIR_OUT, OFF);
    gpio_port_init(PORT_TC, UC_LED3, FUNCT_GPIO, DATA_DIR_OUT, OFF);
    gpio_port_init(PORT_TC, UC_LED4, FUNCT_GPIO, DATA_DIR_OUT, OFF);
}

//Calls gpio_port_set_pin_state() to set the state of the pin in port TC for LED p_led to turn the LED off.
void uc_led_off(int p_led)
{
	gpio_port_set_pin_state(PORT_TC,p_led,OFF);
    //gpio_port_set_pin_state(p_port, p_pin, p_state);
}

//Calls gpio_port_set_pin_state() to set the state of the pin in port TC for LED p_led to turn the LED on.
void uc_led_on(int p_led)
{
	gpio_port_set_pin_state(PORT_TC,p_led,ON);
    //gpio_port_set_pin_state(p_port, p_pin, p_state);
}

//Calls gpio_port_get_pin_state() to determine if LED p_led is on or off. It it is on, turn it off and if it is off, turn it on.
void uc_led_toggle(int p_led)
{
	if(gpio_port_get_pin_state(PORT_TC,p_led)) //Check if the LED is on
	{
		//If its on, then turn it off
		gpio_port_set_pin_state(PORT_TC,p_led,OFF);
	}
	else
	{
		//If its off then turn it on
		gpio_port_set_pin_state(PORT_TC,p_led,ON);
	}
}
