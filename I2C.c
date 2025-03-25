#include<lpc21xx.h>
#include"fuartheader.h"

void i2c_init(void)
{
PINSEL0 |= 0x50;  // P0.2=scl, P0.3= SDA
I2SCLH = I2SCLL = 75; // standard speed 100 kbps;
I2CONSET = (1<<6); // enable i2c interface and select master mode
}

#define SI ((I2CONSET>>3)&1)
void i2c_byte_write_frame(unsigned char sa, unsigned char mr, unsigned char data)
{
/* generate start bit condition */

I2CONSET = (1<<5); //STA=1
I2CONCLR = (1<<3); // clear SI  mandatory
while(SI==0);
I2CONCLR = (1<<5); // STA = 0  mandatory


/* send SA+W and check ACK */
I2DAT = sa; // send SA+W
I2CONCLR = (1<<3); // clear SI mandatory
while(SI==0);
if(I2STAT==0x20)
{
uart0_tx_string("ERR: SA+W\r\n");
goto exit;
}

/*send mr addr and chack ACK */

I2DAT = mr; //send memory address
I2CONCLR = (1<<3); // clear SI mandatory

while(SI==0);
if(I2STAT==0x30)
{
uart0_tx_string("ERR: Memory address\r\n");
goto exit;
}

/* send data and check ACK*/

I2DAT = data; /// send data
I2CONCLR = (1<<3); // clear SI mandatory

while(SI==0);
if(I2STAT==0x30)
{
uart0_tx_string("ERR: Data\r\n");
goto exit;
}

/* stop condition */

exit:
I2CONSET = (1<<4); // STO=1
I2CONCLR = (1<<3);
}

unsigned char i2c_byte_read_frame(unsigned char sa, unsigned char mr)
{
unsigned char temp;
/* generate start bit condition */

I2CONSET = (1<<5); //STA=1
I2CONCLR = (1<<3); // clear SI  mandatory
while(SI==0);
I2CONCLR = (1<<5); // STA = 0  mandatory

/* send SA+W and check ACK */
I2DAT = sa; // send SA+W
I2CONCLR = (1<<3); // clear SI mandatory
while(SI==0);
if(I2STAT==0x20)
{
uart0_tx_string("ERR: SA+W\r\n");
goto exit;
}

/*send mr addr and chack ACK */

I2DAT = mr; //send memory address
I2CONCLR = (1<<3); // clear SI mandatory

while(SI==0);
if(I2STAT==0x30)
{
uart0_tx_string("ERR: Memory address\r\n");
goto exit;
}

/* Restart bit */
I2CONSET = (1<<5);
I2CONCLR = (1<<3);
while(SI==0);
I2CONCLR = (1<<5);

/* send SA+R and check ACK */

I2DAT = sa|1; // SA+R
I2CONCLR = (1<<3); // clear SI mandatory
while(SI==0);
if(I2STAT==0x48)
{
uart0_tx_string("ERR: SA+R\r\n");
goto exit;
}

/*Master wait for data to receive and send NOACKNOWLEDGEMENT upon Rx data */

I2CONCLR = (1<<3); // clear SI mandatory
while(SI==0);
temp=I2DAT;

/*generate stop bit condition */

exit:
I2CONSET = (1<<4);
I2CONCLR = (1<<3);

/* return data */

return temp;
}
