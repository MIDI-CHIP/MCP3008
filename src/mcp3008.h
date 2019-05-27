/*

   ESP32 Arduino Library for:
	
   MCP3008 Chip 

   Provides 8 additional Analog inputs, 10 bits each 

   Uses Hardware SPI Interface

   05/2019 Bill Row

*/

#ifndef mcp3008_arduino
#define mcp3008_arduino

#include <arduino.h>
#include <SPI.h>

static const int spiClk = 1000000; // 1 MHz



class mcp3008 {

public:

	mcp3008();

	void begin(uint8_t, uint8_t, uint8_t, uint8_t);

	uint16_t analogRead(uint8_t);

private:

	SPIClass hspi;

	uint8_t outbuffer[3];  // SPI miso and mosi

	uint8_t inbuffer[3];

        uint8_t SSpin = 15;   // default hardware SS pin for ESP32

};


#endif // #ifndef mcp3008