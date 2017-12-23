#include "OW_Headers\LCD.h"
#include "OW_Headers\DS18B20.h"
#include "OW_Headers\OW.h"
#include "io430.h"
#define ROLE_OUT P2OUT_bit.P5 
#define ROLE_DIR P2DIR_bit.P5
#define ON 1
#define OFF 0
#define OUT 1
#define IN 0;
unsigned int wISIHam1,wISIHam2;
unsigned int fark;
int main( void )
{
  unsigned int romCode1[] = {0x28,0xFF ,0xA9,0x20,0xA1,0x15,0x03,0x54}; //Son Nosu Dec :84
  unsigned int romCode2[] = {0x28,0xFF,0xED,0x47,0xA1,0x15,0x03,0xB4};  //Son Nosu Dec :180
  WDTCTL = WDTPW + WDTHOLD;
  //Setup
  lcd_start();
  DS18B20_Ayarla(); // DS18B20 ayarla
  //Loop
  /********************************************
  romOku();   // romCode'unu LCD ekrana yaz.      
  *********************************************/
  
  lcd_set(DISPLAY_ON | CURSOR_OFF);             // Ekran acik tutulup, cursor kapatildi.
  unsigned count = 1;
  while(1){                                     // Sonsuz döngü 
    wISIHam1=DS18B20_Oku(romCode1);             // DS18B20'den romCode1 adresli sensorden sýcaklýðý oku
    lcd_go(1,1);
    lcd_string("S1 : ");                        // Ekrana S1 yazdýr.
    lcd_string(DS18B20_Yaziya_Cevir(wISIHam1));
    lcd_char(0xDF);
    lcd_char('C');
    __delay_cycles(20);
    
    wISIHam2=DS18B20_Oku(romCode2);             // DS18B20'den romCode1 adresli sensorden sýcaklýðý oku
    lcd_go(2,1);
    lcd_string("S2 : ");                         // Ekrana S2 yazdýr.
    lcd_string(DS18B20_Yaziya_Cevir(wISIHam2));
    lcd_char(0xDF);
    lcd_char('C');
    fark = abs(DS18B20_Float_Cevir(wISIHam2) - DS18B20_Float_Cevir(wISIHam1));
    __delay_cycles(20);
    if(fark > 3){
      ROLE_DIR = 1;
      ROLE_OUT = 1;
    }
    else{
      ROLE_DIR = 1;
      ROLE_OUT = 0;
    }
  }
  
  return 0;
}
