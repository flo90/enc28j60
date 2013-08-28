/*
    This file is part of the enc28j60 driver project
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

#ifndef _USART_H_
#define _USART_H_

//Baudrate
#define BAUD 19200UL
 
 
#ifndef F_CPU
#define F_CPU 16000000UL
#endif
 
// Berechnungen

// clever runden
#define UBRR_VAL ((F_CPU+BAUD*8)/(BAUD*16)-1)

// Reale Baudrate
#define BAUD_REAL (F_CPU/(16*(UBRR_VAL+1)))


// Fehler in Promille, 1000 = kein Fehler.
#define BAUD_ERROR ((BAUD_REAL*1000)/BAUD)
 
#if ((BAUD_ERROR<990) || (BAUD_ERROR>1010))
  #error Systematischer Fehler der Baudrate grösser 1% und damit zu hoch! 
#endif 

void usart_init(void);

void usart_puts( char *data );

#endif