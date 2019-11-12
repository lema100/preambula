#include "main.h"
#include "../preambula/preambula.h"
#include <stdio.h>
#include <stdint.h>
#include <string.h>

const uint8_t protD_preambula[] =	{0x97, 0x15, 0x7A, 0x6F};
const uint8_t bad_preambula[] =		{0xff, 0xff, 0x00, 0x00};

uint32_t max_iter[DISPLAY_ARR], max_coeff[DISPLAY_ARR], x, sum, max_max_iter;
uint32_t ret, coeff, iter, mode;

void print_binary32(uint32_t data)
{
	printf("0b");
	for(uint32_t i = 0; i < 32; i++)
		data & (0x80000000 >> i) ? printf("1") : printf("0");
	printf("\n");
}

int main(int argn, char *arg[])
{
	if (argn < 2)
	{
		printf("Too few arguments.");
		return -1;
	}

	if (strcmp(arg[1], "generator") == 0)
		mode = MODE_GENERATOR;
	else if (strcmp(arg[1], "statistic") == 0)
		mode = MODE_STATISTIC;
	else
	{
		printf("Unknown work mode.");
		return -1;
	}
	
	if (mode == MODE_STATISTIC)
	{
		for (uint32_t i = 0; i < DISPLAY_ARR; i++)
			printf("%d\t", i);
		printf("sum\n\n\n");
	}

	while (1)
	{
		ret = preambula(x++, &iter, &coeff);
		if (mode == MODE_STATISTIC)
		{
			max_max_iter = iter > max_max_iter ? iter : max_max_iter;
			max_iter[iter > (DISPLAY_ARR - 1) ? (DISPLAY_ARR - 1) : iter]++;
			max_coeff[coeff > (DISPLAY_ARR - 1) ? (DISPLAY_ARR - 1) : coeff]++;
			if (iter >= MAX_ITER / 2)
				printf("\n%d\n\n\n", x - 1);
			if (x % 1000 == 0)
			{
				sum = 0;
				printf("\033[A\033[A\r");
				for (uint32_t i = 0; i < DISPLAY_ARR; i++)
				{
					printf("%d\t", max_iter[i]);
					sum += max_iter[i];
				}
				printf("%d\n", sum);
				for (uint32_t i = 0; i < DISPLAY_ARR; i++)
					printf("%d\t", max_coeff[i]);
				
				printf("\nmaximum %d iteration", max_max_iter);
			}
		}
		else if (mode == MODE_GENERATOR)
			print_binary32(ret);
		if (x == UINT32_MAX)
		{
			printf("\nAll 32 bit combinations are tested.\n");
			return 0;
		}
	}
	return 0;
}
