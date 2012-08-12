#ifndef _ENC28J60_H_
#define _ENC28J60_H_
#include <inttypes.h>

void enc28j60_writeReg( uint8_t reg, uint8_t  data );

uint8_t enc28j60_readReg( uint8_t reg );

void enc28j60_writePhyReg( uint8_t reg, uint16_t data );

uint16_t enc28j60_readPhyReg ( uint8_t reg );

void enc28j60_init( uint8_t (*pexchangebyte) (uint8_t data), unsigned char plocalmac[6] );

void enc28j60_sendPacket( unsigned char dst[5],  unsigned char data[], uint16_t size );

uint16_t enc28j60_recvPacket( unsigned char buf[], uint16_t maxlen );

#endif