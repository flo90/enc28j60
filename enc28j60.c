#include "enc28j60reg.h"
#include "enc28j60.h"
#include "enc28j60buffer.h"
#include "spi.h"
#include <avr/io.h>

#ifdef ENC28J60_DEBUG
#include <stdio.h>
char dbgmsgbuf[20];
void (*dbgmsgout) (char *msg);
#endif


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

static inline void bitFieldSet( uint8_t reg, uint8_t mask )
{
  select();
  
  exchangebyte ( ( BFS ) | reg );
  exchangebyte( mask );
  
  deselect();
}

static inline void bitFieldClear( uint8_t reg, uint8_t mask )
{
  select();
  
  exchangebyte( ( BFC ) | reg );
  exchangebyte( mask );
  
  deselect();
}

static inline void setbank( uint8_t bank )
{
  bank &= 0x03;
  
  bitFieldClear( ( ECON1 & NOREGEXTENSION ), 0x03 );
  
  bitFieldSet( ( ECON1 & NOREGEXTENSION ), bank );
}

static inline void initRecvBuffer(void)
{
  //Writing start Pointer of RX BUFFER
  enc28j60_writeReg( ERXSTL, RXBUFFERSTPTR & 0x00FF );
  enc28j60_writeReg( ERXSTH, RXBUFFERSTPTR >> 8 );

  #ifdef ENC28J60_DEBUG
  snprintf(dbgmsgbuf, 20, "RXBUFSTPTR %x\n\r", RXBUFFERSTPTR);
  dbgmsgout( dbgmsgbuf );
#endif
  
  //Writing end Pointer of RX BUFFER
  enc28j60_writeReg( ERXNDL, RXBUFFERNDPTR & 0x00FF );
  enc28j60_writeReg( ERXNDH, RXBUFFERNDPTR >> 8 );
  
   #ifdef ENC28J60_DEBUG
  snprintf(dbgmsgbuf, 20, "RXBUFNDPTR %x\n\r", RXBUFFERNDPTR);
  dbgmsgout( dbgmsgbuf );
#endif
  
  //Bug workaround ERXRDPTR may mess up recive Buffer if it contains an even address
  enc28j60_writeReg( ERXRDPTL, RXBUFFERNDPTR & 0x00FF );
  enc28j60_writeReg( ERXRDPTH, RXBUFFERNDPTR >> 8 );
  
}

static inline void initRecvFilter(void)
{
  //We dont need to change anything, the default Values only accept Packets with local MAC adress an Broadcast adress
}

static inline void initMAC( unsigned char mac[6] )
{
  
  //This clears the MARST bit to wake up the MAC - Bit Manipulation is unnessary because all other bits are zero
  enc28j60_writeReg( MACON2, 0x00 );
  
  //Like the Datasheet describe we set MARXEN to enable the MAC an TXPAUS and RXPAUS for flow control
  enc28j60_writeReg( MACON1, MACON1_MARXEN );
  
  //Now the Padding is configured. The best way is to configure automatic padding with adding zeros for small packets an CRC checksum
  //the pattern for this configuration is 101 for PADCFG2:PADCFG1 furthermore fulduplex is enabled
  enc28j60_writeReg( MACON3, MACON3_PADCFG2 | MACON3_PADCFG0 );
  
  //You may want to change the Maximum Packet length for RX, TX
  //enc28j60_writeReg( MAMXFLL, 0x00 );
  //enc28j60_writeReg( MAMXFLH, 0x06 );
  
  //MABBIPG: Programm with 15h for fullduplex and 12h for halfduplex
  enc28j60_writeReg( MABBIPG, 0x12 );
  
  //MAIPGL: Datasheet recommends 12h
  enc28j60_writeReg( MAIPGL, 0x12 );
  
  //MAIPGH: Programm this if halfduplex is used Datasheet recommends 0Ch
  enc28j60_writeReg( MAIPGH, 0x0C );
  
  //MACLCON 1, 2: If halfduplex you can change this values but the reset values are OK
  //It's recommended to increase the MACLCON2 value if long cables are used
  //enc28j60_writeReg( MACLCON1, 0x0F );
  //enc28j60_writeReg( MACLCON2, 0x37 );
  
  //Setting MAC Adress
  enc28j60_writeReg( MAADR0,  mac[0] );
  enc28j60_writeReg( MAADR1,  mac[1] );
  enc28j60_writeReg( MAADR2,  mac[2] );
  enc28j60_writeReg( MAADR3,  mac[3] );
  enc28j60_writeReg( MAADR4,  mac[4] );
  enc28j60_writeReg( MAADR5,  mac[5] );
  
}

static inline void initPHY(void)
{
  uint16_t temp;
  
  //We get the default config of PHCON1
  temp = enc28j60_readPhyReg( PHCON1 );
  
  //Activating PDPXMD
  temp &= ~PHCON1_PDPXMD;
  
  //Writing back manipulated value
  enc28j60_writePhyReg( PHCON1, temp );
  
  //You may change the LED output behavior
  enc28j60_writePhyReg(PHLCON, 0x3472 );
  
  
  
}

#ifndef ENC28J60_DEBUG
void enc28j60_init( uint8_t (*pexchangebyte) (uint8_t data), unsigned char plocalmac[6] )
{
  uint8_t i;
  
  exchangebyte = pexchangebyte;
  
  select();
  
  exchangebyte( SOFTRESET );
  
  deselect();
  
  lastbank=0;
  
  nextPacketPtr = 0;
  
  
  //Wait for ESTAT_CLKRDY 
  while( !( enc28j60_readReg( ESTAT ) & ESTAT_CLKRDY ) );
  
  
  //Now we init the MAC like described in the Datasheet
  
  initRecvBuffer();
  
  
  //For default operation we dont need to change anything. Description in Line 59
  //initRecvFilter();
  
  //init the Media Access Controller
  initMAC( plocalmac );
  
  for( i = 0; i < 6; i++)
  {
    localmac[i] = plocalmac[i];
  }
  
  initPHY();
  
}
#endif

#ifdef ENC28J60_DEBUG

void enc28j60_init( uint8_t (*pexchangebyte) (uint8_t data), void (*pdbgmsgout) (char *msg), unsigned char plocalmac[6] )
{
  uint8_t i;
  
  exchangebyte = pexchangebyte;
  dbgmsgout = pdbgmsgout;
  
  select();
  
  exchangebyte( SOFTRESET );
  
  deselect();
  
  lastbank=0;
  
  nextPacketPtr = 0;
  
  //Wait for ESTAT_CLKRDY 
  while( !( enc28j60_readReg( ESTAT ) & ESTAT_CLKRDY ) );
  
  dbgmsgout( "MAC init\n\r" );
  
  //Now we init the MAC like described in the Datasheet
  
  initRecvBuffer();
  
  
  //For default operation we dont need to change anything. Description in Line 59
  //initRecvFilter();
  
  //init the Media Access Controller
  initMAC( plocalmac );
  
  for( i = 0; i < 6; i++)
  {
    localmac[i] = plocalmac[i];
  }
  
  initPHY();
  
}

#endif






uint8_t enc28j60_readReg( uint8_t reg )
{
  uint8_t result;
  uint8_t tempbank = ( reg & 0x60 ) >> 5;
  
  select();
  
  if( ( ( reg & NOREGEXTENSION ) < ( EIE & NOREGEXTENSION ) ) && ( lastbank != tempbank ) )
  {
    setbank( tempbank );
    lastbank = tempbank;
  } 
  
  exchangebyte( RCR | ( reg & NOREGEXTENSION ) );
  
  if( reg & ETH )
  {   
     result = exchangebyte( DONT_CARE ); 
  }
  else
  {
    exchangebyte( DONT_CARE );
    result = exchangebyte( DONT_CARE );
  }
  
  deselect();
  
  return result;
}

void enc28j60_writeReg( uint8_t reg, uint8_t  data )
{
  uint8_t tempbank = ( ( reg & 0x60 ) >> 5 );
  
  if( lastbank != tempbank )
  {
    setbank( tempbank );
    lastbank = tempbank;
  }
  
  select();
  
  exchangebyte( WCR | ( reg & NOREGEXTENSION ) );
  exchangebyte( data );
  
  deselect();
}

uint16_t enc28j60_readPhyReg ( uint8_t reg )
{
  uint8_t micmdtemp;
  uint16_t result=0;
  
  enc28j60_writeReg( MIREGADR, reg );
  micmdtemp = enc28j60_readReg ( MICMD );
  micmdtemp |= MICMD_MIIRD;
  enc28j60_writeReg( MICMD, micmdtemp );
  
  while( enc28j60_readReg( MISTAT ) & MISTAT_BUSY );
  
  micmdtemp &= ~MICMD_MIIRD;
  
  enc28j60_writeReg( MICMD, micmdtemp );
  
  result |= enc28j60_readReg( MIRDL );
  result |= ( enc28j60_readReg( MIRDH ) << 8 );
  
  return result;
}

void enc28j60_writePhyReg( uint8_t reg, uint16_t data )
{
  
 enc28j60_writeReg( MIREGADR, reg );
 enc28j60_writeReg( MIWRL, data );
 enc28j60_writeReg( MIWRH, ( data >> 8 ) );
 
 while( enc28j60_readReg( MISTAT ) & MISTAT_BUSY );
}

static inline void writeBufMem( unsigned char data[],  uint16_t size )
{ 
  uint16_t i;
  
  select();
  
  exchangebyte(WBM);
  
  
  for( i = 0; i < size; i++ )
  {
    exchangebyte( data[i] );
  }
  
  deselect();
}

static inline void setTxBufStPtr( uint16_t addr )
{
  enc28j60_writeReg( EWRPTL, addr );
  enc28j60_writeReg( EWRPTH, addr >> 8 );
}

void enc28j60_sendPacket( unsigned char dst[5],  unsigned char *data, uint16_t size )
{
  uint16_t i;
  
  while( enc28j60_readReg( ECON1 ) & ECON1_TXRTS );
  
  //ToDo: Check if Transmit logic is dead
  setTxBufStPtr( TXBUFFERSTPTR );
  
  select();
  
  exchangebyte(WBM);
  
  //Control Byte
  exchangebyte( 0x00 );
  
  //writing the destination MAC address
  for( i = 0; i < 6; i++ )
  {
    exchangebyte( dst[i] );
  }
  
  //Writing source MAC address
  for( i = 0; i < 6; i++ )
  {
    exchangebyte( localmac[i] );
  }
  
  for( i = 0; i < size; i++ )
  {
    exchangebyte( data[i] );
  }
  
  deselect();
  
  //Writing start pointer address for send
  enc28j60_writeReg( ETXSTL, TXBUFFERSTPTR & 0x00FF );
  enc28j60_writeReg( ETXSTH, TXBUFFERSTPTR >> 8 );
  
  //Writing end pointer address for send
  enc28j60_writeReg( ETXNDL, ( (TXBUFFERSTPTR+12) + size ) & 0x00FF );
  enc28j60_writeReg( ETXNDH,  ( (TXBUFFERSTPTR+12) + size ) >> 8 );
  
  //Let's go
  enc28j60_writeReg( ECON1, ECON1_TXRTS );
  
}