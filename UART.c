#include <lpc21xx.h>
#include "fuartheader.h"

void uart0_init(unsigned int baud)
{
int a[]={15,60,30,15,15};
unsigned int pclk,result;
pclk=a[VPBDIV]*1000000;
result=pclk/(16*baud);
PINSEL0 |=0x05;
U0LCR = 0x83; //8N1
U0DLL = result & 0xff; //DLAB=1
U0DLM = (result>>8) & 0xff;
U0LCR = 0x03;

}

#define THRE ((U0LSR>>5)&1)
void uart0_tx(unsigned char data)
{
U0THR = data;
while(THRE==0);
}

#define RDR (U0LSR&1)
unsigned char uart0_rx(void)
{
while(RDR==0);
return U0RBR;
}


void uart0_tx_string(char *ptr)
{
while(*ptr)
{
U0THR = *ptr;
while(THRE==0);
ptr++;
}
}


void uart0_rx_string(char *s, int len)
{
int i;
for(i=0;i<len;i++)
{
while(RDR==0);
s[i]=U0RBR;
if(s[i]=='\r')
break;
}
s[i]='\0';
}

void uart0_tx_integer(int num)
{
int i;
char a[10];
if(num<0)
{
uart0_tx('-');
num=-num;
}

if(num==0)
{
uart0_tx('0');
return;
}

for(i=0;num;i++,num=num/10)
a[i]=num%10+48;

for(i=i-1;i>=0;i--)
uart0_tx(a[i]);
}


 void uart0_tx_float(float f)
{
int num;

if(f<0)
{
uart0_tx('-');
f=-f;
}

if(f==0)
{
uart0_tx_string("0.0");
return;
}

num=f;
uart0_tx_integer(num);
lcd_data('.');
num=(f-num)*1000000;
uart0_tx_integer(num);

}
