#ifndef STORAGE_H
#define STORAGE_H

#include <EEPROM.h>
#include "utils.h"

#define STORAGE_MAX_STATIC_PIXELCON 100
#define STORAGE_MAX_SOURCES 10
#define STORAGE_INIT_FLAG 159
	
namespace storage
{
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////  Interface  //////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	void init();
	void commit();

	char getNumStaticPixelcon();
	void setNumStaticPixelcon(char num);

	void getStaticPixelconId(int index, char* pixelconId);
	uint8_t* getStaticPixelcon(int index);
	void setStaticPixelcon(int index, uint8_t* data);

	int getNumPixelconSources();

	char getPixelconSourceType(int index);
	void setPixelconSourceType(int index, char type);

	const char* getPixelconSourceId(int index);
	void setPixelconSourceId(int index, const char* id);

	bool getIsStaticMode();
	void setIsStaticMode(bool staticMode);
		
	char getBright();
	void setBright(char bright);
		
	int getDuration();
	void setDuration(int duration);
		
	const char* getRPCClient();
	void setRPCClient(const char* rpcClient);
	
	/* Helper Functions */
	void setDefaultStaticPixelconData(uint8_t* dataBuffer);
	
	
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////  Data  //////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	const char numDefaultStaticPixelcon = 84;
	const char defaultStaticPixelcon[] PROGMEM = 
	  "9a999999990990999909909999999999907777099400004999477499999aa9999a9999999949949994944949ee9999eee499994e99400499999aa99999999999"
	  "9a9999999999909990049099999999999499994999400499999aa999999999999a99999999499499949449499999999991777719901dd10994777749999aa999"
	  "9a9999999949949c9494494c99999999907777099022220999088099999aa9999a99944999994999944490999909909999999999999900999999aa9999999999"
	  "9a999999990990999909909999999999994774999474474994499449999999999a9999999999999997099709977997799999999999422499999aa99999999999"
	  "9a9999999999999999099099990990999999999999422499949aa949999999999a99999999999099900490999999999994999949994224999998899999988999"
	  "9a99999994099049990990999999999992eeee29992882999997e999999999999a9999999949949994944949c999999c927777299428824999477499999aa999"
	  "9a999999994994999494494999999999949999499942249999988999999889999a9999999909909999099099999999999999a499999909999999a49999999999"
	  "9a9999999949949994944949ee9999eeee99a4ee999909999999a499999999999a99999999099099990990999c9999999c944999994aa4999999999999999999"
	  "9a499499949999499909909999099099999999999990099999900999999aa9999a9999999449944999999999900990099999999999900999999009999999c999"
	  "9a9999999449944999044099990990999999999999422499949aa949999999998e8888888228822888022088880880888888888888e77e8882777728888ee888"
	  "9a4994999499994999999999920990299cc99cc99cc77cc99cc00cc99cc9acc9cc1cc1ccc1cccc1cc77cc77c97099079977997799990099999900999999aa999"
	  "cc1cc1ccc1cccc1ccc0cc0cc990990999c9999999c99999999900999999aa9993b1331333133331333033033330330333331333333b303333333133333333333"
	  "9a99999999999999944994499999999994000049903bb30994bbbb4999bbbb999a99999999999999977997099079977999999999990099099099009999999999"
	  "0d0000d00dd00de00dddddd00d0d0dd0117e71100d777dd0001edd1001ddddd100999900099999909949090499499f229909ffff0044ffff049940e0499ff400"
	  "00028000028880000027770004970700004977700002877000028777000d777711111110111fffe000010010fdf00e00ffffff200effeee00e2fffe00ee22000"
	  "03bbbb303b7bbbb3b3bbbb3bb70bb70bb30bb03b0bbbbbb000b33b00000bb0000dccccd0dc7ccccdcdccccdcc70cc70ccd0cc0dc0cccccc000cddc00000cc000"
	  "00088270008822000777666006eeeed0f72fe26ef7f76e6e067e26d000676d00ff4444fff467764f46b33b64673703766730037647b33b7efe7777efffffffff"
	  "ff4444fff467764f46dccd6467c70c7667c00c7647dccd7efe7777efffffffff00b3b300000b300000ee28000e8e88800ee88280028288200028820000022000"
	  "00000000070000700cd66dc006d77d600d622dd001688d1000d6d10000000000001282100128a811128a988228aaaaa88aaaaa822889a821118a821001282100"
	  "11112121212112921191112129a921111191121211212921211112111112111200110000019a100019a100001aa100101aa911a119aaaa91019aa91000111100"
	  "2119111219299291129aa92119aaaa9999aaaa91129aa9211929929121119112000008880008899900899aaa089aabbb089abccc89abccdd89abcd0089abcd00"
	  "0008800000878800000880000071160007100160070000600070060000066000000cc00000c7cc00000cc0000071160007100160070000600070060000066000"
	  "00000000000000000a0aa0900cabba80099999400aaaaa9000000000000000000000000000e777e00ee777ee088eee88008eee800008e8000000e00000000000"
	  "0000000000c777c00cc777cc066ccc66006ccc600006c6000000c000000000000000000000a777a00aa777aa099aaa99009aaa900009a9000000a00000000000"
	  "0000000000b777b00bb777bb033bbb33003bbb300003b3000000b0000000000000000000077777a00a100a900a400a900a747a900aa40a900aa77a9000000000"
	  "0128218101298221122898101828982112899921289aa98229aaaa92128888210d777d00677777607767767d767007076d6007070677707d000d776000006770"
	  "0000000000770000066700000776d990000d6999000444990002444400002442000000000e808e00e7e8e8e08e8888e008888e000088e000000e000000000000"
	  "000000000e807600e7e767608e877760088776000087600000060000000000000000000006707600666767607677776007777600007760000006000000000000"
	  "7600000067600000067600400067d090000d7d900000d92000499282000000287600000067600000067600400067d090000d7d900000d9d000499dcd000000dc"
	  "7600000067600000067600400067d090000d7d900000d940004994a40000004a7600000067600000067600400067d090000d7d900000d930004993b30000003b"
	  "0188881018e77e818e7887e887877878878778788e7887e818e77e81018888100000000000aaa900aa99949aa0aaa90a90aaa909099aa49000094000009aa400"
	  "0000000000822200082002800800008002800820002aa200000aa000000000000000000000c111000c1001c00c0000c001c00c10001aa100000aa00000000000"
	  "000001dd0992010d42a90d000079000000a49a790074444000a94a90004aa9409444444094444440a9999990412121206161616070707070767676706dddddd0"
	  "0000000000ddd6000d100d700d100d60811108e88101088221110222000000000000000000ddd6000d100d700d100d60b1110b7bb1010bb33111033300000000"
	  "00000000000000000866a66d01d76d10047dd642046dc642044664420000000000d000d0000d0d00dddddd99d7600844d6000c44d0006d44d0067d44dddddd44"
	  "0777776007bbb7d0073337d007bbb7d0077777d0078787d0077777d0067776d01ac128829cc967761ca128829cc1677628822882677667762882288267766776"
	  "00001000000001000000110000066600d6722270d0d777601ddd6660001d6610000000000777600007776dd0099940600aaa90d00aaa9d1009aa400000000000"
	  "00000000004994000097a900009aa9000099990009a7aa900009400000000000000000000cc7c7c00cc677c00cccccc00c7777c00c7777c00d6666d000000000"
	  "000000000887878008867780088888800877778008777780026666200000000000f6aa000fec9970feec977777e0077777700e777779ceef0799cef000aa6f00"
	  "6000000dd70000dd06700dd00067dd0000067000022d688020200808221002886000000dd70000dd06700dd00067dd0000067000011d6cc010100c0c111006cc"
	  "00ee00000efa9000eea7ee0089988ee0142888ef112288f701122fff0011444200ee00000efa9000eea7dd00299ccdd014dcccdf11ddccf7011ddfff00114442"
	  "00ee00000efa4000eea79900244aa990149aaa9f1199aaf701199fff0011444200ee00000efa9000eea73300299bb330143bbb3f1133bbf701133fff00114442";
	struct {
	  uint8_t initCheck;
	  uint8_t staticMode;
	  uint8_t numStaticPixelcons;
	  uint8_t staticPixelconData[STORAGE_MAX_STATIC_PIXELCON*32];
	  uint8_t sourceTypes[STORAGE_MAX_SOURCES];
	  uint8_t sourceIds[STORAGE_MAX_SOURCES][41];
	  uint8_t rpcClient[256];
	  uint8_t brightness;
	  uint32_t duration;
	} flashData;

	
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////  Impl  //////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	void init() {
	  EEPROM.begin(3968);
	  EEPROM.get(0, flashData);
	  EEPROM.end();

	  // initialize flash data if it hasn't been set yet
	  if(flashData.initCheck != STORAGE_INIT_FLAG) {
		flashData.initCheck = STORAGE_INIT_FLAG;
		flashData.staticMode = 0;
		flashData.numStaticPixelcons = numDefaultStaticPixelcon;
		setDefaultStaticPixelconData(flashData.staticPixelconData);
		for(int i=0; i<STORAGE_MAX_SOURCES; i++) {
		  flashData.sourceTypes[i] = 0;
		  flashData.sourceIds[i][0] = 0;
		}
		flashData.sourceTypes[0] = 1;
		memset((char*)flashData.sourceIds[0], 0, 41);
		strcpy((char*)flashData.sourceIds[0], "f88e77f202db096e75596b468eef7c16282156b1");
		memset((char*)flashData.rpcClient, 0, 256);
		strcpy((char*)flashData.rpcClient, "mainnet.infura.io/v3/07d72fe8b8b74534a05d2091e108e26e");
		flashData.brightness = 80;
		flashData.duration = 30;
		commit(); 
	  }
	}

	void commit() {
	  EEPROM.begin(3968);
	  EEPROM.put(0, flashData);
	  EEPROM.commit(); 
	  EEPROM.end();
	}
	
	void setDefaultStaticPixelconData(uint8_t* dataBuffer) {
	  for(int i=0; i<numDefaultStaticPixelcon*32; i++) {
		int defaultDataIndex = i*2;
		uint8_t upperValue = toVal(pgm_read_byte_near(defaultStaticPixelcon + defaultDataIndex));
		uint8_t lowerValue = toVal(pgm_read_byte_near(defaultStaticPixelcon + defaultDataIndex + 1));
		dataBuffer[i] = (upperValue << 4) + lowerValue;
	  }
	}

	char getNumStaticPixelcon() {
	  return flashData.numStaticPixelcons;
	}
	
	void setNumStaticPixelcon(char num) {
	  flashData.numStaticPixelcons = num;
	}

	void getStaticPixelconId(int index, char* pixelconId) {
	  for(int i=0; i<32; i++) {
		uint8_t value = flashData.staticPixelconData[32*index + i];
		int stringIndex = i*2;
		pixelconId[stringIndex+0] = toHex((value & 0xF0) >> 4);
		pixelconId[stringIndex+1] = toHex(value & 0x0F);
	  }
	}
	
	uint8_t* getStaticPixelcon(int index) {
	  return &(flashData.staticPixelconData[32*index]);
	}
	
	void setStaticPixelcon(int index, uint8_t* data) {
	  int startIndex = 32*index;
	  for(int i=0; i<32; i++) flashData.staticPixelconData[startIndex+i] = data[i];
	}

	int getNumPixelconSources() {
	  int count = 0;
	  while(count < STORAGE_MAX_SOURCES) {
		if(flashData.sourceTypes[count] > 0) count++;
		else break;
	  }
	  return count;
	}

	char getPixelconSourceType(int index) {
	  return flashData.sourceTypes[index];
	}
	
	void setPixelconSourceType(int index, char type) {
	  flashData.sourceTypes[index] = type;
	}

	const char* getPixelconSourceId(int index) {
	  return (char*)flashData.sourceIds[index];
	}
	
	void setPixelconSourceId(int index, const char* id) {
	  memset((char*)flashData.sourceIds[index], 0, 41);
	  strcpy((char*)flashData.sourceIds[index], id);
	}

	bool getIsStaticMode() {
	  return flashData.staticMode > 0;
	}
	
	void setIsStaticMode(bool staticMode) {
	  if(staticMode) flashData.staticMode = 1;
	  else flashData.staticMode = 0;
	}

	char getBright() {
	  return flashData.brightness;
	}
	
	void setBright(char bright) {
	  flashData.brightness = bright;
	}

	int getDuration() {
	  return flashData.duration;
	}
	
	void setDuration(int duration) {
	  flashData.duration = duration;
	}

	const char* getRPCClient() {
	  return (const char*)flashData.rpcClient;
	}
	
	void setRPCClient(const char* rpcClient) {
	  memset((char*)flashData.rpcClient, 0, 256);
	  strcpy((char*)flashData.rpcClient, rpcClient);
	}
	
	
}

#endif /* STORAGE_H */
