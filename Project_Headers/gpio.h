//*******************************************************************************************************
// gpio.h
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


#ifndef GPIO_H_
#define GPIO_H_

int gpio_port_get_pin_state(int p_port, int p_pin);
void gpio_port_init(int p_port, int p_pin, int p_funct, int p_data_dir, int p_state);
void gpio_port_set_pin_state(int p_port, int p_pin, int p_state);

#endif // GPIO_H_