#ifndef __DS18B20_H
#define __DS18B20_H

// Fonksiyon prototipleri
void DS18B20_Ayarla();
unsigned int DS18B20_Oku();
char* DS18B20_Yaziya_Cevir(unsigned int);
void byteToChar(unsigned char sonuc);
unsigned char Detect_Slave_Device(void);
void romOku(void);
int DS18B20_Int_Cevir(unsigned int sayi);


#include "DS18B20.c"
#endif