#include "config.h"

#include "spi.h"
#include "enc28j60.h"
#include "enc28j60packet.h"
#include "enc28j60reg.h"
#include "usart.h"

#include <avr/io.h>
#include <util/delay.h>




void delay_ms(uint16_t ms)
{
  for(; ms>0; ms--)
  {
    _delay_ms(1);
  }
}

int main(void)
{
  delay_ms(10);
  DDRB |= ( 1 << PB4 ) | (1 << PB5) | ( 1 << PB6 ) | ( 1 << PB7 );
  PORTB |= ( 1 << PB4 );
  
  unsigned char macaddr[6] = { 0x00, 0x22, 0xF9, 0x01, 0x6D, 0x5A };
  unsigned char dst[] = {0x1c, 0x6f, 0x65, 0x91, 0x69, 0x85};
  
  usart_init();
  
  spi_init( SPI_SPE | SPI_MSTR , SPI_CLK_2);
  
  enc28j60_init( &spi_exchangebyte, macaddr );
  
  unsigned char data[5] =  { 0x08, 0x00, 0x03, 0x04, 0x00};
  data[4] = enc28j60_readReg(ENC28j60_EREVID);
  while(1)
  {
   //delay_ms(2000);
   enc28j60_sendPacket(dst, data, sizeof(data));
  }
  
  
  while(1);
  return 0;
}
