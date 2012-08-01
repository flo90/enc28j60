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