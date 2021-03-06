#include "lpc11xx_syscon.h"
#include "lpc11xx_gpio.h"
#include "coos.h"

#define LED0      GPIO_Pin_1
#define LED1      GPIO_Pin_2

#define PRIORITY_BLINK_TASK0  2		/* Priority of Blink task 0 */
#define PRIORITY_BLINK_TASK1  3     /* Priority of Blink task 1 */

#define SIZE_BLINK_TASK0	  100    /* Stack size of Blink task 0 */
#define SIZE_BLINK_TASK1      100    /* Stack size of Blink task 1 */

OS_STK stkBlink0[SIZE_BLINK_TASK0];	/* Stack of Blink task 0 */
OS_STK stkBlink1[SIZE_BLINK_TASK1]; /* Stack of Blink task 0 */



void taskBlink0(void *param);
void taskBlink1(void *param);

int main(void)
{
	/* Enable GPIO block clock */
	SYSCON_AHBPeriphClockCmd(SYSCON_AHBPeriph_GPIO, ENABLE);

	CoInitOS();

	/* Create Blink Task 0 */
	CoCreateTask( taskBlink0,
				  (void *)0,
				  PRIORITY_BLINK_TASK0,
			      &stkBlink0[SIZE_BLINK_TASK0-1],
			      SIZE_BLINK_TASK0 );

	/* Create Blink Task 1 */
	CoCreateTask( taskBlink1,
				  (void *)0,
				  PRIORITY_BLINK_TASK1,
			      &stkBlink1[SIZE_BLINK_TASK1-1],
			      SIZE_BLINK_TASK1 );

	CoStartOS();

	while(1);
}

void taskBlink0(void *param)
{
	/* Set PIO2_0 as output. */
	GPIO_SetDir(PORT2, LED0, 1);

	for(;;) {
		/* Turn On Led */
		GPIO_ResetBits(PORT2, LED0);
		CoTickDelay(20);	/* Delay 200ms */

		/* Turn Off Led */
		GPIO_SetBits(PORT2, LED0);
		CoTickDelay(20);	/* Delay 200ms */
	}
}

void taskBlink1(void *param)
{
	/* Set PIO2_1 as output. */
	GPIO_SetDir(PORT2, LED1, 1);

	for(;;) {
		/* Turn On Led */
		GPIO_ResetBits(PORT2, LED1);
		CoTickDelay(40);	/* Delay 400ms */

		/* Turn Off Led */
		GPIO_SetBits(PORT2, LED1);
		CoTickDelay(40);	/* Delay 400ms */
	}
}



