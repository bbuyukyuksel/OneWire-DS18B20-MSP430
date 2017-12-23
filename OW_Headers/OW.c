#include "io430.h"
#include "OW.h"


// One wire iletiþim için hattý hazýrlar.
void HatAyarla (){
	OW_DIR_IN;
	OW_OUT_HIGH;
}

// One wire iletiþim için hatta reset iþareti gönderir.
unsigned char HatReset(){
	OW_OUT_LOW;
	OW_DIR_OUT;
	__delay_cycles(500); // 500us
	OW_DIR_IN;
	__delay_cycles(100); // 100us
	if(OW_INPUT_READ){
		__delay_cycles(400); // 400us
		return 1;
	}
	else{
		__delay_cycles(400); // 400us
	return 0;
	}
}

// One wire iletiþim için hatta 1 bit veri yazar.
void BitYaz (unsigned char bit){
	__delay_cycles(2); // 2us
	OW_DIR_OUT;
	OW_OUT_LOW;
	if(bit)
		__delay_cycles(4); // 4us
	else
		__delay_cycles(64); // 64us
		OW_DIR_IN;
	if(bit)
		__delay_cycles(64); // 64us
	else
		__delay_cycles(4); // 4us
}
// One wire iletiþim için hattan 1 bit veri okur.
unsigned char BitOku (){
	unsigned char bit;
	__delay_cycles(2); // 2us
	OW_OUT_LOW;
	OW_DIR_OUT;
	__delay_cycles(2); // 2us
	OW_DIR_IN;
	__delay_cycles(15); // 15us
	bit=OW_INPUT_READ;
	__delay_cycles(60); // 60us
return bit;
}

// One wire iletiþimde hatta 1 byte veri yazar.

void ByteYaz(unsigned char veri){
	unsigned char sayac;
	for(sayac = 0; sayac < 8; sayac++){
		BitYaz(veri & 0x01);
		veri >>= 1;
	}
}
// One wire iletiþimde hattan bir byte veri okur.
unsigned char ByteOku(){
	unsigned char sayac;
	unsigned char veri;
	for(sayac = 0; sayac < 8; sayac++){
		veri >>= 1;
		if (BitOku()) 
			veri |= 0x80;
		else
			veri &= 0x7F;
	}
return veri;
}