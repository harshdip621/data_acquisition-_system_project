#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include "uart.h"

#if !defined(__SOFT_FP__) && defined(__ARM_FP)
  #warning "FPU is not initialized, but the project is compiling for an FPU. Please initialize the FPU before use."
#endif

int main(void)
{
	char str[16];
	UartInit(9600);
	UartPuts("Enter Strings\r\n");
	while(1) {
		UartGets(str);
		strupr(str);
		UartPuts(str);
	}
}


