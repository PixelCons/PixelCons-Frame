#ifndef UTILS_H
#define UTILS_H

#include <pgmspace.h>

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////  Macros  //////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#define FS(string_literal) (String(F(string_literal)))


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////  Interface  //////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
uint8_t toVal(uint8_t hex);
uint8_t toHex(uint8_t val);

uint8_t toB64(uint8_t val);
uint8_t fromB64(uint8_t b64);

void toBase64_256(char* base64, const uint8_t* data);
void fromBase64_256(uint8_t* data, const char* base64);

uint32_t convertFromHex(char* hex, uint32_t len);
char* convertToHex(uint32_t num, char* hex, uint32_t len);


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////  Impl  //////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
uint8_t toVal(uint8_t hex) {
	if(hex >= 48 && hex <= 57) return hex-48;
	if(hex >= 65 && hex <= 70) return (hex-65)+10;
	if(hex >= 97 && hex <= 102) return (hex-97)+10;
	return 0;
}

uint8_t toHex(uint8_t val) {
	if(val > 15) val = 15;
	if(val < 10) return 48+val;
	return 97+(val-10);
}

uint8_t toB64(uint8_t val) {
	if(val > 63) val = 63;
	if(val == 63) return 47;
	if(val == 62) return 43;
	if(val >= 52) return (val-52)+48;
	if(val >= 26) return (val-26)+97;
	return val+65;
}

uint8_t fromB64(uint8_t b64) {
	if(b64 == 47) return 63;
	if(b64 == 43) return 62;
	if(b64 >= 48 && b64 <= 57) return (b64-48)+52;
	if(b64 >= 97 && b64 <= 122) return (b64-97)+26;
	if(b64 >= 65 && b64 <= 90) return b64-65;
	return 0;
}

void toBase64_256(char* base64, const uint8_t* data) {
  int index = 0;
  for(int i=0; i<30; i+=3) {
	int bytes = (data[i]<<16) + (data[i+1]<<8) + (data[i+2]);
	
	base64[index++] = toB64((bytes>>18)&0x3F);
	base64[index++] = toB64((bytes>>12)&0x3F);
	base64[index++] = toB64((bytes>>6)&0x3F);
	base64[index++] = toB64(bytes&0x3F);
  }
  int bytes = (data[30]<<16) + (data[31]<<8);
  base64[index++] = toB64((bytes>>18)&0x3F);
  base64[index++] = toB64((bytes>>12)&0x3F);
  base64[index++] = toB64((bytes>>6)&0x3F);
  base64[index++] = '=';
  base64[index] = 0;
}

void fromBase64_256(uint8_t* data, const char* base64) {
  int index = 0;
  for(int i=0; i<40; i+=4) {
	int bytes = (fromB64(base64[i])<<18) + (fromB64(base64[i+1])<<12) + (fromB64(base64[i+2])<<6) + fromB64(base64[i+3]);
	data[index++] = (bytes>>16)&0xFF;
	data[index++] = (bytes>>8)&0xFF;
	data[index++] = bytes&0xFF;
  }
  int bytes = (fromB64(base64[40])<<18) + (fromB64(base64[41])<<12) + (fromB64(base64[42])<<6);
  data[index++] = (bytes>>16)&0xFF;
  data[index++] = (bytes>>8)&0xFF;
  data[index] = 0;
}

uint32_t convertFromHex(char* hex, uint32_t len) {
  uint32_t num = 0;
  for(int i=0; i<len; i++) num = (num<<4) + toVal(hex[i]);
  return num;
}

char* convertToHex(uint32_t num, char* hex, uint32_t len) {
  for(int i=len-1; i>=0; i--) {
	uint32_t mask = num & 0x0000000F;
	hex[i] = toHex(mask);
	num = num >> 4;
  }
  hex[len] = 0;
  return hex;
}


#endif /* UTILS_H */
