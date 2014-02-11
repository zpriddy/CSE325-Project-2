//*******************************************************************************************************
// gpio.c
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
#include "gpio.h"

const uint32 IPSBAR = 0x40000000;
const uint32 GPIO_BASE = IPSBAR + 0x00100000;
const uint32 GPIO_DDR_BASE = GPIO_BASE + 0x18;
const uint32 GPIO_SET_BASE = GPIO_BASE + 0x30;
const uint32 GPIO_CLR_BASE = GPIO_BASE + 0x48;
const uint32 GPIO_PAR_BASE = GPIO_BASE + 0x60;
const uint32 GPIO_PORT_TC = 0x0F;
const uint32 GPIO_PORT_DD = 0x14;
const uint32 GPIO_FUNCT_GPIO = 0x00;
const uint32 GPIO_FUNCT_PRIM = 0x01;
const uint32 GPIO_FUNCT_SEC = 0x02;
const uint32 GPIO_FUNCT_TERT = 0x03;
const uint32 GPIO_DATA_DIR_IN = 0x00;
const uint32 GPIO_DATA_DIR_OUT = 0x01;

#define GPIO_SET(n) (*(vuint8 *)(GPIO_SET_BASE + (n)))
#define GPIO_DDR(n) (*(vuint8 *)(GPIO_DDR_BASE + (n)))
#define GPIO_CLR(n) (*(vuint8 *)(GPIO_CLR_BASE + (n)))
#define GPIO_PAR(n) (*(vuint8 *)(GPIO_PAR_BASE + (n)))

//------------------------------------------------------------------------------------

//Accesses the SETn (n = p_port) register and returns the state of pin p_pin (0 or 1) in bit 0 of the return value.
int gpio_port_get_pin_state(int p_port, int p_pin)
{
	//int state;
	//state = ((GPIO_SET(p_port) & (1 << (p_pin))) >> (p_pin)); //>> p_pin));
    //return state;
	
	return (GPIO_SET(p_port) & (1 << (p_pin))) >> (p_pin);

}

/*Initializes pin p_pin of GPIO port p_port so the pin's function is p_funct (0, 1, 2, or 3). If the pin is configured for GPIO
mode (p_funct = 0), set the data direction to p_data_dir (1 = output, 0 = input) and the initial state of the pin to
p_state (0 or 1).If the pin is not configured for the GPIO function, then the parameters p_data_dir and p_state are not
used, so any value could be passed for those parameters.*/
void gpio_port_init(int p_port, int p_pin, int p_funct, int p_data_dir, int p_state)
{
    switch(p_port)
    {
        case GPIO_PORT_DD:
        	GPIO_PAR(GPIO_PORT_DD) &= ~( 1 << p_pin);
			GPIO_CLR(GPIO_PORT_DD) |= GPIO_CLR(GPIO_PORT_DD)||(1 << p_pin);
        	break;
            
        case GPIO_PORT_TC:
            GPIO_PAR(GPIO_PORT_TC) &= ( 1 << p_pin);
            GPIO_CLR(GPIO_PORT_TC) |= GPIO_CLR(GPIO_PORT_TC)||(1 << p_pin);
        	break;
    }
    
    if(!p_funct) //GPIO mode
    {
        if(p_data_dir == 0) //input
        {
            //GPIO_DDR(p_port) |= ~(1 << p_pin);
        }
        else//output
        {
        	GPIO_DDR(p_port) |= (1 << p_pin);
        }
        gpio_port_set_pin_state(p_port,p_pin,p_state);
    }
    
}


//Sets the state of p_pin of port p_port to p_state (0 or 1).
void gpio_port_set_pin_state(int p_port, int p_pin, int p_state)
{
	
    if(p_state) //HIGH?
    {
    	GPIO_SET(p_port) |= ( 1 << p_pin );
        
    }
    else //LOW?
    {
    	GPIO_CLR(p_port) |= ~(1 << p_pin);
    }
}
