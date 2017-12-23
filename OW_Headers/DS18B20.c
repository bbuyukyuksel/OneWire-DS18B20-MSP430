#include "io430.h"
#include "DS18B20.h"
#include "OW.h"

char yazi[10];


void DS18B20_Ayarla(){
	HatAyarla();
}

// DS18B20'de ham olarak sýcaklýk verisini okuyan fonksiyon

unsigned int DS18B20_Oku(unsigned int* romCode){
	unsigned char high_byte,low_byte;
	unsigned int i = 0;
        while(HatReset());
	ByteYaz(MATCH_ROM);
        for(i = 0; i<8; i++)
          ByteYaz(romCode[i]);
	ByteYaz(CONVERT_TMP);
        __delay_cycles(120);
        while(HatReset());
        ByteYaz(MATCH_ROM);
       for(i = 0; i<8; i++)
          ByteYaz(romCode[i]);
	ByteYaz(READ_SCRATCHPAD);
	__delay_cycles(80000);
	low_byte = ByteOku();
	high_byte = ByteOku();
	return (high_byte<<8 & 0xff00) | low_byte;
}
// DS18B20_Oku fonkisyonu ile okunan deðeri iþaret,
// ondalýk ve tam sayý kýsýmlarýna ayýrýp asciiye çeviren fonksiyon
char* DS18B20_Yaziya_Cevir(unsigned int sayi){
	unsigned char gecici;
	if(sayi & 0xF000)
		yazi[0] = '-';
	else
		yazi[0] = '+';
	gecici = sayi>>4 & 0xff; //0'ýn solundaki bitler isleme tutuluyor.
	yazi[1] = gecici/100 + 0x30;
	gecici %= 100;
	yazi[2] = gecici/10 + 0x30;
	yazi[3] = gecici%10 + 0x30;
	yazi[4] = '.';
	gecici = sayi & 0x000f;//0'ýn sagindaki bitler isleme tutuluyor.
	sayi = gecici * 625; //0001 sayisi 625'e esit oldugundan 625'in katlari seklindesayiyi gorucez.
	yazi[5] = sayi/1000 + 0x30;
        /*
	sayi = sayi % 1000;
	yazi[6] = sayi/100 + 0x30;
	sayi = sayi % 100;
	yazi[7] = sayi / 10 + 0x30;
	yazi[8] = sayi % 10 + 0x30;
        */
	yazi[6] = '\0';
	return yazi;
}


void byteToChar(unsigned char sonuc){ 
  lcd_char((sonuc/100)%10+48);
  lcd_char((sonuc/10)%10+48);
  lcd_char(sonuc%10+48);
  lcd_char(' ');
}
	
unsigned char Detect_Slave_Device(void){
  if (!HatReset())return HIGH;   
  else  return LOW;
} 
void romOku(void){
  unsigned char temp,counter = 1;
  unsigned char serial_number[8];	
  if (!Detect_Slave_Device()){			
    lcd_clear();			
    lcd_go(1,1);			
    lcd_string("Hatta Cihaz yok!");		
   }
   else{
     lcd_clear();			
     lcd_go(1,1);
     ByteYaz(0x33);
     lcd_go(1,1);		
     for(temp = 0; temp<8; temp++){			
       serial_number[temp] = ByteOku();
       if(counter%5 == 0){
        lcd_go(2,1);
       }
       counter++;
       byteToChar(serial_number[temp]);
       __delay_mil(200);
       
     }
      while(1){
        lcd_blink(1000);
     }
     lcd_start();
   }
}

int DS18B20_Int_Cevir(unsigned int sayi){
	unsigned char gecici;
	int sayiTemp = 0;
	if(sayi & 0xF000)
		yazi[0] = '-';
	else
		yazi[0] = '+';
	gecici = sayi>>4 & 0xff; //0'ýn solundaki bitler isleme tutuluyor.
	yazi[1] = gecici/100;
	gecici %= 100;
	yazi[2] = gecici/10;
	yazi[3] = gecici%10;
	sayiTemp += 100    * yazi[1];
	sayiTemp += 10     * yazi[2];
	sayiTemp += 1      * yazi[3];
	return sayiTemp;
}












