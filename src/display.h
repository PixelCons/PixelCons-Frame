#ifndef DISPLAY_H
#define DISPLAY_H
	
#include <Arduino.h>
#include <eagle_soc.h>
#include "utils.h"
#include "storage.h"

#define DISPLAY_WIDTH 8
#define DISPLAY_HEIGHT 8
#define DISPLAY_NUM_LEDS (DISPLAY_WIDTH*DISPLAY_HEIGHT)
#define DISPLAY_OUTPUT_PIN 14 //PIN D5
	
namespace display
{
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////  Interface  //////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	void init();
	void flush();
	
	void drawErrorScreen();
	void drawLoadingScreen();
	void drawWarningScreen();
	void drawBlankScreen();
	
	void drawPixelcon(const char* id, int xOffset, int yOffset);
	void drawText(const char* text, int xOffset, int yOffset);
	
	void setColor(int x, int y, uint32_t color);
	void setColor(int x, int y, int r, int g, int b);
		
	/* Helper Functions */
	uint32_t colors(char index);
	void dimAt(int x, int y);
	void lightAt(int x, int y);
	extern "C" void ICACHE_RAM_ATTR espShow(uint8_t *pixels, uint32_t numBytes);
	
	
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////  Data  //////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	uint8_t pixels[DISPLAY_NUM_LEDS*3];
	const char fontSegments[] PROGMEM = {0,1,1,3,5,7,9,11,11,12,13,15,17,18,20,20,22,24,24,26,28,30,32,34,36,38,40,40,41,43,45,47,49,51,53,55,57,59,61,63,65,67,69,71,73,75,77,79,81,83,85,87,89,91,93,95,97,99,
		101,103,104,106,107,109,111,112,114,116,118,120,122,124,126,128,128,129,131,131,133,135,137,139,141,142,143,145,147,149,151,153,155,157,159,159,161,163};
	const char fontData[] PROGMEM = {0x00,0x00,0x1d,0x18,0x00,0x18,0x1f,0x0a,0x1f,0x0d,0x1f,0x16,0x13,0x04,0x19,0x0a,0x15,0x0b,0x18,0x0e,0x11,0x11,0x0e,0x14,0x08,0x14,0x04,0x0e,0x04,0x01,0x02,0x04,0x04,0x04,0x01,
		0x01,0x06,0x18,0x1f,0x11,0x1f,0x1f,0x17,0x15,0x1d,0x15,0x15,0x1f,0x1c,0x04,0x1f,0x1d,0x15,0x17,0x1f,0x15,0x17,0x10,0x10,0x1f,0x1f,0x15,0x1f,0x1d,0x15,0x1f,0x0a,0x01,0x0a,0x04,0x0a,0x11,0x0a,0x0a,0x0a,0x11,
		0x0a,0x04,0x08,0x13,0x0c,0x0e,0x15,0x0d,0x0f,0x14,0x0f,0x1f,0x15,0x0a,0x0e,0x11,0x0a,0x1f,0x11,0x0e,0x1f,0x15,0x11,0x1f,0x14,0x10,0x0e,0x11,0x16,0x1f,0x04,0x1f,0x11,0x1f,0x11,0x11,0x1f,0x10,0x1f,0x04,0x1b,
		0x1f,0x01,0x01,0x1f,0x08,0x1f,0x1f,0x0e,0x1f,0x0e,0x11,0x0e,0x1f,0x14,0x08,0x0c,0x12,0x0d,0x1f,0x14,0x0b,0x09,0x15,0x12,0x10,0x1f,0x10,0x1e,0x01,0x1e,0x1c,0x03,0x1c,0x1e,0x07,0x1e,0x1b,0x04,0x1b,0x18,0x07,
		0x18,0x13,0x15,0x19,0x1f,0x11,0x18,0x06,0x01,0x11,0x1f,0x08,0x10,0x08,0x01,0x01,0x01,0x10,0x08,0x06,0x09,0x07,0x1f,0x09,0x06,0x06,0x09,0x09,0x06,0x09,0x1f,0x06,0x0b,0x05,0x04,0x1f,0x14,0x05,0x0b,0x06,0x1f,
		0x04,0x03,0x17,0x01,0x16,0x1f,0x02,0x05,0x1f,0x0f,0x0c,0x0f,0x07,0x08,0x07,0x06,0x09,0x06,0x0f,0x0a,0x04,0x04,0x0a,0x0f,0x0f,0x04,0x05,0x0a,0x04,0x0f,0x04,0x0e,0x01,0x0e,0x0c,0x03,0x0c,0x0e,0x03,0x0e,0x09,
		0x06,0x09,0x0d,0x03,0x0e,0x0b,0x0f,0x0d,0x04,0x1f,0x11,0x1f,0x11,0x1f,0x04,0x06,0x04,0x0c};
	const char warningScreen[] PROGMEM = {0x0e,0x07,0x00,0x35,0x1c,0x00,0xd8,0xd1,0xc9,0xd9,0xd1,0xc9,0xd9,0xd1,0xc9,0xd8,0xd1,0xc9,0x35,0x1c,0x00,0x10,0x08,0x00,0x35,0x1c,0x00,0x60,0x36,0x00,0xe1,0xd8,0xc9,0xe2,
		0xd9,0xc9,0xe2,0xd9,0xc9,0xe1,0xd8,0xc9,0x60,0x36,0x00,0x36,0x1d,0x00,0x4a,0x27,0x00,0x74,0x49,0x00,0x86,0x5c,0x03,0x8a,0x61,0x09,0xe6,0xdd,0xca,0xe5,0xdc,0xc9,0x75,0x49,0x00,0x4c,0x29,0x00,0x4f,0x2a,0x00,
		0x78,0x4d,0x00,0x8a,0x61,0x09,0xe6,0xde,0xcc,0xe6,0xde,0xcc,0xe6,0xdd,0xcb,0x79,0x4e,0x00,0x51,0x2b,0x00,0x4f,0x2a,0x00,0x78,0x4d,0x00,0x8a,0x61,0x09,0xe6,0xde,0xcc,0xe6,0xde,0xcc,0x8b,0x62,0x0b,0x79,0x4e,
		0x00,0x51,0x2b,0x00,0x4a,0x27,0x00,0x74,0x49,0x00,0x86,0x5c,0x03,0x8b,0x62,0x0b,0x8b,0x62,0x0b,0x87,0x5e,0x04,0x75,0x49,0x00,0x4c,0x29,0x00,0x35,0x1c,0x00,0x60,0x36,0x00,0x75,0x49,0x00,0xe2,0xd9,0xc9,0xe2,
		0xd9,0xc9,0x75,0x49,0x00,0x62,0x38,0x00,0x37,0x1d,0x00,0x10,0x08,0x00,0x36,0x1d,0x00,0x4c,0x29,0x00,0xda,0xd2,0xc9,0xda,0xd2,0xc9,0x4c,0x29,0x00,0x37,0x1d,0x00,0x11,0x08,0x00};
	const char errorScreen[] PROGMEM = {0x11,0x00,0x00,0x3f,0x00,0x00,0x59,0x00,0x00,0x5f,0x00,0x00,0x5f,0x00,0x00,0x59,0x00,0x00,0x40,0x00,0x00,0x13,0x00,0x00,0x3f,0x00,0x00,0x72,0x00,0x00,0x86,0x12,0x12,0xe6,
		0xcd,0xcd,0xe6,0xcd,0xcd,0x86,0x12,0x12,0x72,0x00,0x00,0x41,0x00,0x00,0x59,0x00,0x00,0x86,0x12,0x12,0x95,0x2b,0x2b,0xe9,0xd3,0xd3,0xe9,0xd3,0xd3,0x95,0x2b,0x2b,0x86,0x12,0x12,0x5b,0x00,0x00,0x5f,0x00,0x00,
		0x8a,0x16,0x16,0x98,0x31,0x31,0xe9,0xd4,0xd4,0xe9,0xd4,0xd4,0x98,0x32,0x32,0x8b,0x18,0x18,0x62,0x00,0x00,0x5f,0x00,0x00,0x8a,0x16,0x16,0x98,0x31,0x31,0xe9,0xd4,0xd4,0xe9,0xd4,0xd4,0x98,0x32,0x32,0x8b,0x18,
		0x18,0x62,0x00,0x00,0x59,0x00,0x00,0x86,0x12,0x12,0x95,0x2b,0x2b,0x98,0x32,0x32,0x98,0x32,0x32,0x96,0x2c,0x2c,0x86,0x12,0x12,0x5b,0x00,0x00,0x40,0x00,0x00,0x72,0x00,0x00,0x86,0x12,0x12,0xe6,0xce,0xce,0xe6,
		0xce,0xce,0x86,0x12,0x12,0x74,0x00,0x00,0x42,0x00,0x00,0x13,0x00,0x00,0x41,0x00,0x00,0x5b,0x00,0x00,0xdd,0xc9,0xc9,0xdd,0xc9,0xc9,0x5b,0x00,0x00,0x42,0x00,0x00,0x15,0x00,0x00};

	
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////  Impl  //////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	void init() {
      pinMode(DISPLAY_OUTPUT_PIN, OUTPUT);
      digitalWrite(DISPLAY_OUTPUT_PIN, HIGH);
	  
	  for(int i=0; i<DISPLAY_NUM_LEDS*3; i++) pixels[i] = 0;
	}

	uint32_t colors(char index) {
	  switch(index) {
		case 0: return 0;
		case 1: return 330274;
		case 2: return 4720674;
		case 3: return 20768;
		case 4: return 8134928;
		case 5: return 2827551;
		case 6: return 10263971;
		case 7: return 16770775;
		case 8: return 16711710;
		case 9: return 16740864;
		case 10: return 16776969;
		case 11: return 54564;
		case 12: return 688127;
		case 13: return 5062761;
		case 14: return 16728440;
		case 15: return 16755579;
		default: return 0;
	  }
	}
	
	void dimAt(int x, int y) {
      uint8_t ledIndex = (((DISPLAY_WIDTH-1) - x)*DISPLAY_HEIGHT + y)*3;
	  
      uint32_t r = pixels[ledIndex+1];
      uint32_t g = pixels[ledIndex+0];
      uint32_t b = pixels[ledIndex+2];
	  
      pixels[ledIndex+1] = r/6;
      pixels[ledIndex+0] = g/6;
      pixels[ledIndex+2] = b/6;
	}
	
	void lightAt(int x, int y) {
      uint8_t ledIndex = (((DISPLAY_WIDTH-1) - x)*DISPLAY_HEIGHT + y)*3;
	  
      uint32_t r = pixels[ledIndex+1];
      uint32_t g = pixels[ledIndex+0];
      uint32_t b = pixels[ledIndex+2];
	  
      pixels[ledIndex+1] = 220 + (r/8);
      pixels[ledIndex+0] = 220 + (g/8);
      pixels[ledIndex+2] = 220 + (b/8);
	}

	void drawLoadingScreen() {
	  // randomly pick a sample pixelcon from flash memory
      char randomPixelconId[] = "0000000000000000000000000000000000000000000000000000000000000000";
      if(storage::getNumStaticPixelcon() > 0) {
        int index = random(0, storage::getNumStaticPixelcon());
        storage::getStaticPixelconId(index, randomPixelconId);
	  }
	  drawPixelcon(randomPixelconId, 0, 0);
	
      //draw the PixelCon 'P'
      dimAt(1,0); dimAt(2,0); dimAt(3,0);
      dimAt(0,1); dimAt(0,2); dimAt(0,3); dimAt(0,4); dimAt(0,5);
      dimAt(4,1); dimAt(4,2); dimAt(4,3);
      dimAt(2,4); dimAt(3,4); dimAt(2,5);
      dimAt(2,2); dimAt(1,6);
      lightAt(1,1); lightAt(1,2); lightAt(1,3); lightAt(1,4); lightAt(1,5);
      lightAt(2,1); lightAt(3,1); lightAt(3,2); lightAt(3,3); lightAt(2,3);
	}

	void drawErrorScreen() {
	  for(int x=0; x<DISPLAY_WIDTH; x++) {
		for(int y=0; y<DISPLAY_HEIGHT; y++) {
		  int i = (y*DISPLAY_WIDTH + x)*3;
		  setColor(x, y, pgm_read_byte_near(errorScreen+i+0), pgm_read_byte_near(errorScreen+i+1), pgm_read_byte_near(errorScreen+i+2));
		}
	  }
	}

	void drawWarningScreen() {
	  for(int x=0; x<DISPLAY_WIDTH; x++) {
		for(int y=0; y<DISPLAY_HEIGHT; y++) {
		  int i = (y*DISPLAY_WIDTH + x)*3;
		  setColor(x, y, pgm_read_byte_near(warningScreen+i+0), pgm_read_byte_near(warningScreen+i+1), pgm_read_byte_near(warningScreen+i+2));
		}
	  }
	}

	void drawPixelcon(const char* id, int xOffset, int yOffset) {
	  for(int x=0; x<DISPLAY_WIDTH; x++) {
		for(int y=0; y<DISPLAY_HEIGHT; y++) {
		  uint8_t colorIndex = toVal(id[y*DISPLAY_WIDTH + x]);
		  setColor(x + xOffset, y + yOffset, colors(colorIndex));
		}
	  }
	}

	void drawBlankScreen() {
	  for(int x=0; x<DISPLAY_WIDTH; x++) {
		for(int y=0; y<DISPLAY_HEIGHT; y++) {
		  int i = (y*DISPLAY_WIDTH + x)*3;
		  setColor(x, y, 0,0,0);
		}
	  }
	}

	void drawText(const char* text, int xOffset, int yOffset) {
	  setColor(xOffset-1, yOffset-1, colors(5));
	  setColor(xOffset-1, yOffset+0, colors(5));
	  setColor(xOffset-1, yOffset+1, colors(5));
	  setColor(xOffset-1, yOffset+2, colors(5));
	  setColor(xOffset-1, yOffset+3, colors(5));
	  setColor(xOffset-1, yOffset+4, colors(5));
	  setColor(xOffset-1, yOffset+5, colors(5));
		
	  int x=0;
	  int t=0;
	  while(text[t]) {
		int chIndex = text[t];
		if(chIndex<32 || chIndex>126) chIndex = 32;
		chIndex = chIndex-32;

		char fontSegmentsAtIndex = pgm_read_byte_near(fontSegments + chIndex);
		char fontSegmentsAtIndex1 = pgm_read_byte_near(fontSegments + chIndex + 1);
		
		int chStart = fontSegmentsAtIndex + chIndex;
		int chWidth = (fontSegmentsAtIndex1 - fontSegmentsAtIndex) + 1;
		for(int w=0; w<chWidth; w++) {
		  int chData = pgm_read_byte_near(fontData + chStart + w);

		  setColor(xOffset+x+w, yOffset-1, colors(5));
		  setColor(xOffset+x+w, yOffset+0, (chData&0x10)?colors(7):colors(5));
		  setColor(xOffset+x+w, yOffset+1, (chData&0x08)?colors(7):colors(5));
		  setColor(xOffset+x+w, yOffset+2, (chData&0x04)?colors(7):colors(5));
		  setColor(xOffset+x+w, yOffset+3, (chData&0x02)?colors(7):colors(5));
		  setColor(xOffset+x+w, yOffset+4, (chData&0x01)?colors(7):colors(5));
		  setColor(xOffset+x+w, yOffset+5, colors(5));
		}

		x += chWidth;
		setColor(xOffset+x, yOffset-1, colors(5));
		setColor(xOffset+x, yOffset+0, colors(5));
		setColor(xOffset+x, yOffset+1, colors(5));
		setColor(xOffset+x, yOffset+2, colors(5));
		setColor(xOffset+x, yOffset+3, colors(5));
		setColor(xOffset+x, yOffset+4, colors(5));
		setColor(xOffset+x, yOffset+5, colors(5));

		x++;
		t++;
	  }
	}

	void setColor(int x, int y, uint32_t color) {
	  uint8_t r = (color >> 16) & 0x000000ff;
	  uint8_t g = (color >> 8) & 0x000000ff;
	  uint8_t b = (color >> 0) & 0x000000ff;
	  setColor(x, y, r, g, b);
	}

	void setColor(int x, int y, int r, int g, int b) {
	  if(x>=0 && x<DISPLAY_WIDTH && y>=0 && y<DISPLAY_HEIGHT) {
		uint8_t ledIndex = (((DISPLAY_WIDTH-1)-x)*DISPLAY_HEIGHT + y)*3;
		
	    pixels[ledIndex+0] = g;
	    pixels[ledIndex+1] = r;
	    pixels[ledIndex+2] = b;
	  }
	}

	void flush() {
	  uint8_t pixels_br[DISPLAY_NUM_LEDS*3];
	  for(int i=0; i<DISPLAY_NUM_LEDS*3; i++) {
		  uint32_t byte = pixels[i];
		  pixels_br[i] = (byte * (storage::getBright() / 2)) / 255;
	  }
	  
	  noInterrupts();
	  espShow(pixels_br, DISPLAY_NUM_LEDS*3);
	  interrupts();
	}
	
	
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////  From Adafruit_NeoPixel  ////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	static uint32_t _getCycleCount(void) __attribute__((always_inline));
	static inline uint32_t _getCycleCount(void) {
	  uint32_t ccount;
	  __asm__ __volatile__("rsr %0,ccount":"=a" (ccount));
	  return ccount;
	}

	void ICACHE_RAM_ATTR espShow(uint8_t *pixels, uint32_t numBytes) {
	  uint8_t pin = DISPLAY_OUTPUT_PIN; 
	  uint8_t *p, *end, pix, mask;
	  uint32_t t, time0, time1, period, c, startTime, pinMask;

	  pinMask   = _BV(pin);
	  p         =  pixels;
	  end       =  p + numBytes;
	  pix       = *p++;
	  mask      = 0x80;
	  startTime = 0;

	  time0  = (F_CPU / 2500000); // 0.4us;
	  time1  = (F_CPU / 1250000); // 0.8us
	  period = (F_CPU /  800000); // 1.25us per bit;

	  for(t = time0;; t = time0) {
		if(pix & mask) t = time1;                             // Bit high duration
		while(((c = _getCycleCount()) - startTime) < period); // Wait for bit start
		GPIO_REG_WRITE(GPIO_OUT_W1TC_ADDRESS, pinMask);       // Set high

		startTime = c;                                        // Save start time
		while(((c = _getCycleCount()) - startTime) < t);      // Wait high duration
		GPIO_REG_WRITE(GPIO_OUT_W1TS_ADDRESS, pinMask);       // Set low

		if(!(mask >>= 1)) {                                   // Next bit/byte
		  if(p >= end) break;
		  pix  = *p++;
		  mask = 0x80;
		}
	  }
	  while((_getCycleCount() - startTime) < period); // Wait for last bit
	}

	
}

#endif /* DISPLAY_H */
