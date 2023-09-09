#include <avr/io.h>
#include "GIE_Interface.h"
#include "BIT_MATH.h"
#include "STD_TYPES.h"
void GIE_voidEnable(void)
{
	SET_BIT(SREG, 7);
}

void GIE_voidDisable(void)
{
	CLR_BIT(SREG, 7);
}
