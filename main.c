/*
    This file is part of the enc28j60 driver Project
    Copyright (C) 2013  Florian Menne (florianmenne@t-online.de)

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see [http://www.gnu.org/licenses/].
*/

#include "config.h"

#include "spi.h"
#include "enc28j60.h"
#include "enc28j60packet.h"
#include "enc28j60reg.h"
#include "usart.h"

#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>

unsigned char data[500];
char txtbuf[500];
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
  //unsigned char dst[] = {0x1c, 0x6f, 0x65, 0x91, 0x69, 0x85};
  
  usart_init();
  
  spi_init( SPI_SPE | SPI_MSTR , SPI_CLK_2);
  
  enc28j60_init( &spi_exchangebyte, macaddr );
  
  //unsigned char data[] =  { 0x08, 0x00, 0x03, 0x04, 0x00};
  //data[4] = enc28j60_readReg(ENC28j60_EREVID);
  usart_puts("Start Done!\n\r");
  while(1)
  {
   //delay_ms(2000);
   //enc28j60_sendPacket(dst, data, sizeof(data));
   if( enc28j60_readReg( ENC28j60_EPKTCNT ) )
   {
     uint16_t recvsize = enc28j60_recvPacket(data, 500);
     uint16_t i;
     for( i = 0; i < recvsize; i++ )
     {
       snprintf( txtbuf, 500, "%X  ", data[i]);
       usart_puts( txtbuf );
     }
     usart_puts("\n\n\r");
   }
  
  }
  
  
  while(1);
  return 0;
}
