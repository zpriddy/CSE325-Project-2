//*******************************************************************************************************
// uc_dipsw.c
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
#include "uc_dipsw.h"
#include "gpio.h"

//Calls gpio_port_get_pin_state() to return the state of the pin connected to sub-switch p_switch.
int uc_dipsw_get_state(int p_switch)
{
	
    return !gpio_port_get_pin_state(PORT_DD, p_switch);
    
}


//Calls gpio_port_init() to initialize port DD so we can use sub-switches 1, 2, 3, and 4.
void uc_dipsw_init() 
{
	gpio_port_init(PORT_DD,UC_DIPSW1,0,DATA_DIR_IN,ON);
	gpio_port_init(PORT_DD,UC_DIPSW2,0,DATA_DIR_IN,ON);
	gpio_port_init(PORT_DD,UC_DIPSW3,0,DATA_DIR_IN,ON);
	gpio_port_init(PORT_DD,UC_DIPSW4,0,DATA_DIR_IN,ON);
    //gpio_port_init(p_port, p_pin, p_funct, p_data_dir, p_state);
}