#include<lpc21xx.h>
#include"fuartheader.h"

#define CS0 (1<<7)
#define SPIF ((S0SPSR>>7)&1)
void spi0_init(void)
{
  PINSEL0|=0x1500;
  IODIR0|=CS0;
  IOSET0|=CS0;
  S0SPCR=0x20; // setting for cpol, cpha, master mode, msb first
  S0SPCCR=15;  // spi frequency or speed
}
unsigned char spi0(unsigned char data)
{
 S0SPDR=data;
 while(SPIF==0);
 return S0SPDR;
}


 

unsigned int read_mcp3204(unsigned char ch_num)
{
unsigned byteH=0, byteL=0;
unsigned result = 0;
ch_num <<=6; //set ch_num

IOCLR0 |= CS0;  // select slave
spi0(0x06);  // start bit, SGL mode
byteH = spi0(ch_num);
byteL = spi0(0x00);
IOSET0 = CS0; // diselect slave


byteH &= 0x0F; // mask b4-b7
result = (byteH<<8) | byteL;  // merge result;

return result;
}
