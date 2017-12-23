#ifndef __ONEWIRE_H

#define __ONEWIRE_H

#define CONVERT_TMP 0x44 // Sýcaklýk ölçüm komutu

#define SKIPROM_CMD 0xCC // Rom atlama komutu

#define READ_SCRATCHPAD 0xBE // Scratchpad okuma komutu

#define MATCH_ROM	0x55

#define OW_PORT_OUT P2OUT // One wire bit portu

#define OW_PORT_DIR P2DIR // One wire biti yönlendirme kaydedicisi

#define OW_PORT_IN P2IN // One wire biti port okuma kaydedicisi

#define OW_PORT_BIT BIT4 // One wire iletiþim port biti

#define OW_OUT_HIGH (OW_PORT_OUT |= OW_PORT_BIT) //Cikisa High verildi.

#define OW_OUT_LOW (OW_PORT_OUT &= ~OW_PORT_BIT) //Cikisa Low verildi.

#define OW_DIR_OUT (OW_PORT_DIR |= OW_PORT_BIT) //Cikis olarak ayarlandi.

#define OW_DIR_IN (OW_PORT_DIR &= ~OW_PORT_BIT) //Giris Olarak Ayarlandi.

#define OW_INPUT_READ (OW_PORT_IN & OW_PORT_BIT) //Degerin 1 veya 0 olup olmadigi gozlemlendi.
#define LOW   0 
#define HIGH  1  

// Fonksiyon prototipleri

void HatAyarla ();

unsigned char HatReset();

void BitYaz (unsigned char bit);

unsigned char BitOku ();

void ByteYaz(unsigned char byte);

unsigned char ByteOku();
#include "OW.c"
#endif