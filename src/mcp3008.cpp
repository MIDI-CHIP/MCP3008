/*

   ESP32 Arduino Library for:
	
   MCP3008 Chip 

   Provides 8 additional Analog inputs, 10 bits each 

   Uses Hardware SPI Interface

   05/2019 Bill Row

*/

#include <arduino.h>
#include <SPI.h>
#include <mcp3008.h>




mcp3008::mcp3008() {

	hspi = SPIClass(HSPI);  // create hardware SPI object, get handle
}    


uint16_t mcp3008::analogRead(uint8_t _Apin) {

	outbuffer[1] = 0x80 | (_Apin << 4 );  //   flagbit  |or|  pin-to-read

	hspi.beginTransaction(SPISettings(spiClk, MSBFIRST, SPI_MODE0));
	digitalWrite(this->SSpin, LOW);
	this->inbuffer[0] = hspi.transfer(this->outbuffer[0]);
	this->inbuffer[1] = hspi.transfer(this->outbuffer[1]);
	this->inbuffer[2] = hspi.transfer(this->outbuffer[2]);
	digitalWrite(this->SSpin, HIGH);
	hspi.endTransaction();

	return ((this->inbuffer[1] & 0x03) << 8) | (this->inbuffer[2]);

}    


void mcp3008::begin(uint8_t _sck, uint8_t _miso, uint8_t _mosi, uint8_t _ss) {

	this->SSpin = _ss;

	hspi.begin(_sck, _miso, _mosi, _ss); //SCLK, MISO, MOSI, SS

	pinMode(this->SSpin, OUTPUT);       //HSPI SS
	digitalWrite(this->SSpin, HIGH);    // be invisible on the bus to begin

	this->outbuffer[0] = 0x01; // start bit
	this->outbuffer[1] = 0x80; // range 80-F0 for pins 0-7, default 0x80=pin 0
	this->outbuffer[2] = 0x00; // trigger for 2nd input byte

}






/**/