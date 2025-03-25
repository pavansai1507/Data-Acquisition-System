#include<lpc21xx.h>
#include"header.h"
void adc_init(void)
{
PINSEL1 |=0X15400000;
ADCR|=0X00200400;//select adcr
}
unsigned int adc_read(char ch_num)
{
unsigned int result;
ADCR|=1<<ch_num;//set adcr channel number1
ADCR|=1<<24;   //start adc
while(((ADDR>>31)&1)==0); //set done flag
ADCR^=1<<24;
ADCR^=1<<ch_num;
result=(ADDR>>6)&0x3FF;
return result;
}
