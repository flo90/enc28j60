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