//*******************************************************************************************************
// main.c
//
// DESCRIPTION:
//
// AUTHORS:
//  Abdulla Al Braiki (ayalbrai@asu.edu)
//  Zachary Priddy (zpriddy@asu.edu)
//
// Computer Science & Engineering
// Arizona State University
// Tempe, AZ 85287-8809
// 
//********************************************************************************************************

#include "common.h"
#include "uc_led.h"

#define forever for(;;)

//Reads DIP sub-switches 2, 3, and 4 to see what the delay should be set to. Returns the delay in ms.
static int dipsw_delay_poll()
{
	int delay;
    int dipsw = (uc_dipsw_get_state(UC_DIPSW4) << 2) | (uc_dipsw_get_state(UC_DIPSW3) << 1) | uc_dipsw_get_state(UC_DIPSW2);
    
    switch(dipsw)
    {
    	case 0: // 000
    		delay = 2000;
    		break;
    	case 1: // 001
    	    delay = 1000;
    		break;
    	case 2: // 010
    	    delay = 800;
    	    break;
    	case 3: // 011
    	    delay = 600;
    	    break;
    	case 4: // 100
    	    delay = 400;
    	    break;
    	case 5: // 101
    	    delay = 200;
    	    break;
    	case 6: // 110
    	    delay = 100;
    	    break;
    	case 7: // 111
    	    delay = 50;
    	    break;
    }
    
    dtim0_busy_delay_ms(delay);
    
    
    
    
}

//Polls DIP sub-switch 1 to see if the program should be paused because sub-switch 1 has been moved to the Off position or
//if the program should resume because sub-switch 1 has been moved to the On position. If the sub-switch is on the Off
//position, then start an infinite loop which repeatedly polls sub-switch 1 until it is moved to the On position.
static void dipsw_onoff_poll()
{

		while(!uc_dipsw_get_state(UC_DIPSW1)){}
	
}

//Calls uc_dipsw_init() to initialize the GPIO port to access the DIP switch, uc_led_init() to initialize the port to access
//the LED's, and dtim0_init() to initialize DTIM0.
static void hw_init()
{
	uc_dipsw_init();
	uc_led_init();
	dtim0_init();
}

//Called by count_up() with p_value equal to value of the for loop in count_up(). Determines which LED's to turn on
//based on value and turns them on by calling uc_led_on().
static int leds_on(int p_value)
{
	dipsw_onoff_poll();
	
	uc_led_all_off();
	//Check First Bit
	if (p_value >= 1)
	{
		if(p_value %2 == 1)
			uc_led_on(UC_LED1);
	}
	
	//Check Second Bit
	if (p_value >= 2)
	{
		p_value = p_value/2;
		if(p_value %2 == 1)
			uc_led_on(UC_LED2);
	}
	
	//Check Third Bit
	if (p_value >= 2)
	{
		p_value = p_value/2;
		if(p_value %2 == 1)
			uc_led_on(UC_LED3);
	}
	//Check Fourth Bit
	if (p_value >= 2)
	{
		p_value = p_value/2;
		if(p_value %2 == 1)
			uc_led_on(UC_LED4);
	}
    return -1;
}

//Call dipsw_delay_poll() to determine the initial state of the DIP sub-switches which becomes our original delay. Then
//drops into an infinite loop calling count_up(delay) forever.
static void run()
{
	//uc_led_all_off();
	//uc_led_all_on();
	//uc_led_off(UC_LED3);

	while(1)
	{
	for( int i = 0; i < 16; i++)
	{
		dipsw_delay_poll();
		leds_on(i);
	}
	}

	
	
	
}

// Calls hw_init() to initialize the hardware. Then calls run() to perform the main execution loop. Note that main() never
// returns, so omit the return statement at the end and use __declspec(noreturn) to tell the compiler that main() does
// not return.
__declspec(noreturn) int main()
{
	hw_init();
	run();
}