# Seed based preambula (32bit) generator

Maximum need 66 iteration for generate preambula with autocorrelation factor lower then 6.  
Tested on seeds from 0 to 840 000 000  

Atolic True Studio 9.2.0  
Performance tests  
MCU configuration STM32L071KB (Cortex M0+) tacted from HSI 16MHz  

|										|	Os		|	O3		|	O2	 	|	O1		|	O0		|
|---------------------------------------|-----------|-----------|-----------|-----------|-----------|
| ROM, byte								|	228		|	276		|	276		|	304		|	400		|
| 100 iterarion 100 times, ms			|	12898	|	7995	|	7994	|	7921	|	26287	|
