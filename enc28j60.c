#include "config.h"

#include "enc28j60reg.h"
#include "enc28j60.h"
#include "enc28j60buffer.h"
#include "spi.h"
#include "usart.h"

#include <avr/io.h>
#include <util/delay.h>



uint8_t (*exchangebyte) (uint8_t data);
uint8_t lastbank;
unsigned char localmac[6];
uint16_t nextPacketPtr;


static inline void select(void)
{
  //Do not forget to implement select
  PORTB &= ~(1 << PB4);
}

static inline void deselect(void)
{
  //Do not forget to implement deselect
  PORTB |= ( 1 << PB4 );
}

static inline void enc28j60_writeOp( uint8_t op, uint8_t reg, uint8_t data )
{
  select();
  
  exchangebyte( op | ( reg & ENC28j60_NOREGEXTENSION ) );
  exchangebyte( data );
  
  deselect();
}

static inline uint8_t enc28j60_readOp( uint8_t op, uint8_t reg )
{
  uint8_t data;
  
  select();
  
  exchangebyte( op | ( reg & ENC28j60_NOREGEXTENSION ) );
  
  data = exchangebyte( 0x00 );
  
  if( !( reg & 0x80 ) )
  {
    data = exchangebyte( 0x00 );
  }
  
  deselect();
  
  return data;
}

static inline void setbank( uint8_t bank )
{
  bank &= 0x03;
  
  enc28j60_writeOp( ENC28j60_BFC, ENC28j60_ECON1, 0x03); 
  
  enc28j60_writeOp( ENC28j60_BFS, ENC28j60_ECON1, bank );
}

void enc28j60_writeReg( uint8_t reg, uint8_t  data )
{
  uint8_t tempbank = ( ( reg & 0x60 ) >> 5 );
  
  if( ( ( reg & ENC28j60_NOREGEXTENSION ) < ( ENC28j60_EIE & ENC28j60_NOREGEXTENSION ) ) && ( lastbank != tempbank ) )
  {
    setbank( tempbank );
    lastbank = tempbank;
  } 
  
  enc28j60_writeOp( ENC28j60_WCR, reg, data );
  
}

uint8_t enc28j60_readReg( uint8_t reg )
{
  uint8_t tempbank = ( reg & 0x60 ) >> 5;
  
  if( ( ( reg & ENC28j60_NOREGEXTENSION ) < ( ENC28j60_EIE & ENC28j60_NOREGEXTENSION ) ) && ( lastbank != tempbank ) )
  {
    setbank( tempbank );
    lastbank = tempbank;
  } 
  
  return enc28j60_readOp( ENC28j60_RCR, reg );
}

void enc28j60_writePhyReg( uint8_t reg, uint16_t data )
{
  
 enc28j60_writeReg( ENC28j60_MIREGADR, reg );
 enc28j60_writeReg( ENC28j60_MIWRL, data );
 enc28j60_writeReg( ENC28j60_MIWRH, ( data >> 8 ) );
 
 while( enc28j60_readReg( ENC28j60_MISTAT ) & ENC28j60_MISTAT_BUSY );
}

uint16_t enc28j60_readPhyReg ( uint8_t reg )
{
  uint8_t micmdtemp;
  uint16_t result=0;
  
  enc28j60_writeReg( ENC28j60_MIREGADR, reg );
  micmdtemp = enc28j60_readReg ( ENC28j60_MICMD );
  micmdtemp |= ENC28j60_MICMD_MIIRD;
  enc28j60_writeReg( ENC28j60_MICMD, micmdtemp );
  
  while( enc28j60_readReg( ENC28j60_MISTAT ) & ENC28j60_MISTAT_BUSY );
  
  micmdtemp &= ~ENC28j60_MICMD_MIIRD;
  
  enc28j60_writeReg( ENC28j60_MICMD, micmdtemp );
  
  result |= enc28j60_readReg( ENC28j60_MIRDL );
  result |= ( enc28j60_readReg( ENC28j60_MIRDH ) << 8 );
  
  return result;
}

void enc28j60_init( uint8_t (*pexchangebyte) (uint8_t data), unsigned char plocalmac[6] )
{
  uint8_t i;
  
  exchangebyte = pexchangebyte;
  _delay_ms(2);
  enc28j60_writeOp( ENC28j60_SOFTRESET, 0, ENC28j60_SOFTRESET );
  
  lastbank=0;
  
  nextPacketPtr = 0;
  
  
  //Wait for ESTAT_CLKRDY
  //Not reliable!!!!! Errata issue 2
  //while( !( enc28j60_readReg( ESTAT ) & ESTAT_CLKRDY ) );
  _delay_ms(2);
  
  //Now we init the MAC like described in the Datasheet
  
  
  
  // START: Init Recv Buffer
  //Writing start Pointer of RX BUFFER
  enc28j60_writeReg( ENC28j60_ERXSTL, RXBUFFERSTPTR & 0x00FF );
  enc28j60_writeReg( ENC28j60_ERXSTH, RXBUFFERSTPTR >> 8 );

  
  //Writing end Pointer of RX BUFFER
  enc28j60_writeReg( ENC28j60_ERXNDL, RXBUFFERNDPTR & 0x00FF );
  enc28j60_writeReg( ENC28j60_ERXNDH, RXBUFFERNDPTR >> 8 );
  
  
  //Bug workaround ERXRDPTR may mess up recive Buffer if it contains an even address
  enc28j60_writeReg( ENC28j60_ERXRDPTL, RXBUFFERNDPTR & 0x00FF );
  enc28j60_writeReg( ENC28j60_ERXRDPTH, RXBUFFERNDPTR >> 8 );
  
  // END: Init Recv Buffer
  
  
  
  // START: Init Recv Filter
  
  //For default operation we dont need to change anything. Description in Line 59
  
  //We dont need to change anything, the default Values only accept Packets with local MAC adress and Broadcast adress
  
  // END: Init Recv Filter
  
  
  
  // START: Init the Media Access Controller
 
  //This clears the MARST bit to wake up the MAC - Bit Manipulation is unnessary because all other bits are zero
  enc28j60_writeReg( ENC28j60_MACON2, 0x00 );
  
  //Like the Datasheet describe we set MARXEN to enable the MAC an TXPAUS and RXPAUS for flow control
  //enc28j60_writeReg( MACON1, MACON1_MARXEN );
  
  //Now the Padding is configured. The best way is to configure automatic padding with adding zeros for small packets an CRC checksum
  //the pattern for this configuration is 101 for PADCFG2:PADCFG1
  enc28j60_writeReg( ENC28j60_MACON3, ENC28j60_MACON3_PADCFG2 | ENC28j60_MACON3_PADCFG0 );
  
  //You may want to change the Maximum Packet length for RX, TX
  //enc28j60_writeReg( MAMXFLL, 0x00 );
  //enc28j60_writeReg( MAMXFLH, 0x06 );
  
  //MABBIPG: Programm with 15h for fullduplex and 12h for halfduplex
  enc28j60_writeReg( ENC28j60_MABBIPG, 0x12 );
  
  //MAIPGL: Datasheet recommends 12h
  enc28j60_writeReg( ENC28j60_MAIPGL, 0x12 );
  
  //MAIPGH: Programm this if halfduplex is used Datasheet recommends 0Ch
  enc28j60_writeReg( ENC28j60_MAIPGH, 0x0C );
  
  //MACLCON 1, 2: If halfduplex you can change this values but the reset values are OK
  //It's recommended to increase the MACLCON2 value if long cables are used
  //enc28j60_writeReg( MACLCON1, 0x0F );
  //enc28j60_writeReg( MACLCON2, 0x37 );
  
  //Setting MAC Adress
  enc28j60_writeReg( ENC28j60_MAADR0,  plocalmac[0] );
  enc28j60_writeReg( ENC28j60_MAADR1,  plocalmac[1] );
  enc28j60_writeReg( ENC28j60_MAADR2,  plocalmac[2] );
  enc28j60_writeReg( ENC28j60_MAADR3,  plocalmac[3] );
  enc28j60_writeReg( ENC28j60_MAADR4,  plocalmac[4] );
  enc28j60_writeReg( ENC28j60_MAADR5,  plocalmac[5] );
  
  // END: Init the Media Access Controller
  
  for( i = 0; i < 6; i++)
  {
    localmac[i] = plocalmac[i];
  }
  
  // START: Init Phy
  
 uint16_t temp;
  
  //We get the default config of PHCON1
  temp = enc28j60_readPhyReg( ENC28j60_PHCON1 );
  
  //Deactivating PDPXMD - we are in HalfDuplex
  temp &= ~ENC28j60_PHCON1_PDPXMD;
  
  //Writing back manipulated value
  enc28j60_writePhyReg( ENC28j60_PHCON1, temp );
  
  //Preventing Loopback with PHCON2.HDLDIS
  temp = enc28j60_readPhyReg( ENC28j60_PHCON2 );
  temp |= ENC28j60_PHCON2_HDLDIS;
  enc28j60_writePhyReg( ENC28j60_PHCON2, temp );
  
  
  //You may change the LED output behavior
  enc28j60_writePhyReg( ENC28j60_PHLCON, 0x3122 );
  
  // END: Init Phy
  
}

static inline void enc28j60_setBufWrPtr( uint16_t addr )
{
  enc28j60_writeReg( ENC28j60_EWRPTL, addr );
  enc28j60_writeReg( ENC28j60_EWRPTH, addr >> 8 );
}

static inline void enc28j60_writeBuffer( unsigned char data[],  uint16_t size )
{ 
  uint16_t i;
  
  select();
  
  exchangebyte( ENC28j60_WBM );
  
  for( i = 0; i < size; i++ )
  {
    exchangebyte( data[i] );
  }
  
  deselect();
}


void enc28j60_sendPacket( unsigned char dst[5],  unsigned char *data, uint16_t size )
{
  uint16_t error_timer;
  
  
  enc28j60_setBufWrPtr( TXBUFFERSTPTR );
  
  //Control Byte
  enc28j60_writeOp( ENC28j60_WBM, 0, 0x00 );
  
  //writing the destination MAC address
  enc28j60_writeBuffer( dst, 6 );
  
  //Writing source MAC address
  enc28j60_writeBuffer( localmac, 6 );
  
  //Writing data
  enc28j60_writeBuffer( data, size );
  
  //Writing start pointer address for send
  enc28j60_writeReg( ENC28j60_ETXSTL, TXBUFFERSTPTR & 0x00FF );
  enc28j60_writeReg( ENC28j60_ETXSTH, TXBUFFERSTPTR >> 8 );
  
  //Writing end pointer address for send
  enc28j60_writeReg( ENC28j60_ETXNDL, ( (TXBUFFERSTPTR+12) + size ) & 0x00FF );
  enc28j60_writeReg( ENC28j60_ETXNDH,  ( (TXBUFFERSTPTR+12) + size ) >> 8 );
  
  /*
  enc28j60_writeReg( ENC28j60_EWRPTL, ( (TXBUFFERSTPTR+13) + size ) & 0x00FF );
  enc28j60_writeReg( ENC28j60_EWRPTH,  ( (TXBUFFERSTPTR+13) + size ) >> 8 );
  
  select();
  
  exchangebyte(WBM);
  
  for( i = 0; i < 7; i++)
  {
    exchangebyte( 0x00 );
  }
  
  deselect();
  */
  
  
  transmissionRestart:
  //Clearing error flags
  enc28j60_writeOp( ENC28j60_BFC, ENC28j60_EIR, ENC28j60_EIR_TXERIF );
  enc28j60_writeOp( ENC28j60_BFC, ENC28j60_EIR, ENC28j60_EIR_TXIF );
  enc28j60_writeOp( ENC28j60_BFC, ENC28j60_ESTAT, ENC28j60_ESTAT_TXABRT );
  
  //Let's go
  enc28j60_writeOp( ENC28j60_BFS, ENC28j60_ECON1, ENC28j60_ECON1_TXRTS );
  
  error_timer=1210;
  while( enc28j60_readReg( ENC28j60_ECON1 ) & ENC28j60_ECON1_TXRTS  )
  {
    _delay_us(1);
    if( error_timer  )
    {
      error_timer--;
    }
    
    else
    {
      usart_puts("Error\r\n");
      enc28j60_writeOp( ENC28j60_BFC, ENC28j60_ECON1, ENC28j60_ECON1_TXRTS );
      //enc28j60_writePhyReg( ENC28j60_PHLCON, 0x3AA2 );
      goto transmissionRestart;
    }
    
  }
  
  
  
  
  /*
  enc28j60_writeReg( ENC28j60_ERDPTL, ( (TXBUFFERSTPTR+13) + size ) & 0x00FF );
  enc28j60_writeReg( ENC28j60_ERDPTH,  ( (TXBUFFERSTPTR+13) + size ) >> 8 );
  */
}

