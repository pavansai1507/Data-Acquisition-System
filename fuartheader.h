extern void delay_ms(unsigned int ms);
extern void delay_sec(unsigned int sec);

// ****** LCD *******

  extern void lcd_init(void);
  extern void lcd_data(unsigned char data);
  extern void lcd_cmd(unsigned char cmd);
  extern void lcd_string(char *ptr);
extern void lcd_float(float f);
extern void lcd_integer(int num);

// ***** UART ********

  extern void uart0_init(unsigned int baud);
  extern void uart0_tx(unsigned char data);
  extern void uart0_tx_string(char *ptr);
  extern void uart0_rx_string(char *s, int len);
extern void lcd_cgram(void);
extern void uart0_tx_integer(int);
extern void uart0_tx_float(float);
extern int uart0_rx_integer(void);
extern  float uart0_rx_float(void);


// ******* ADC *****

extern void adc_init(void);
extern unsigned int adc_read(char ch_num);
// ***** I2C ****

extern void i2c_init(void);
extern void i2c_byte_write_frame(unsigned char sa, unsigned char mr, unsigned char data);
extern unsigned char i2c_byte_read_frame(unsigned char sa, unsigned char mr);

// ***** SPI ******

extern void spi0_init(void);
extern unsigned char spi0(unsigned char data);

// **** MCP3204 ******

extern unsigned int read_mcp3204(unsigned char ch_num);
