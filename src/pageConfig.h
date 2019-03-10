#ifndef PAGE_CONFIG_H
#define PAGE_CONFIG_H

#include "utils.h"
#include "storage.h"
#include "display.h"
#include "network.h"
#include "rendering.h"

#include "pageConfig_html.h"
	
namespace pageConfig
{
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////  Interface  //////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	void setup();
	
	/* Helper Functions */
	void handleRoot();
	void handleGetData();
	void handleSetData();
	
	
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////  Impl  //////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	void setup() {
	  network::registerEndPoint(PSTR("/"), handleRoot);
	  network::registerEndPoint(PSTR("/getData"), handleGetData);
	  network::registerEndPoint(PSTR("/setData"), handleSetData);
	}

	
	void handleRoot() {
	  ESP8266WebServer* server = network::getWebServer();
	  Serial.println("handling root...");

	  int fileSize = strlen_P(CONFIG_html);
	  server->setContentLength(fileSize);
	  server->send(200, "text/html", "");
	  server->sendContent_P(CONFIG_html, fileSize);  
	  delay(500);
	}

	void handleGetData() {
	  ESP8266WebServer* server = network::getWebServer();
	  Serial.println(FS("handling getData..."));
	  
	  char buff[45];
	  String s = FS("{\"staticMode\":") + String(storage::getIsStaticMode()?F("true"):F("false")) + FS(",");
	  s += FS("\"staticPixelconData\":\"");
	  for(int i=0; i<storage::getNumStaticPixelcon(); i++) {
	  buff[0] = buff[44] = 0;
	  toBase64_256(buff, storage::getStaticPixelcon(i));
	  s += String(buff);
	  }
	  s += FS("\",");
	  s += FS("\"sources\":[");
	  for(int i=0; i<storage::getNumPixelconSources(); i++) {
	  s += FS("{\"type\":") + String(storage::getPixelconSourceType(i),DEC) + FS(",\"id\":\"0x") + String(storage::getPixelconSourceId(i)) + FS("\"}");
	  if(i+1<storage::getNumPixelconSources()) s += FS(",");
	  }
	  s += FS("],");
	  s += FS("\"rpcClient\":\"") + String(storage::getRPCClient()) + FS("\",");
	  s += FS("\"brightness\":") + String(storage::getBright(),DEC) + FS(",");
	  s += FS("\"duration\":") + String(storage::getDuration(),DEC) + FS("}");
	  server->send(200, "text/json", s);
	  delay(500);
	}
	 
	void handleSetData() {
	  ESP8266WebServer* server = network::getWebServer();
	  Serial.println("handling setData...");

	  if(server->hasArg("plain")) {
		String json = server->arg("plain");
		bool needToSkipToNextPixelcon = false;
		bool needToCommitStorage = false;
		bool needToRefreshPixelconSources = false;
	  
		int index;
		index = json.indexOf(FS("\"staticMode\":"));
		if(index > -1) {
		  bool staticMode = json.charAt(index+13) == 't' && json.charAt(index+14) == 'r' && json.charAt(index+16) == 'e';
		  
		  if(staticMode) Serial.println(FS("staticMode -> true"));
		  else Serial.println(FS("staticMode -> false"));
		  storage::setIsStaticMode(staticMode);
		  needToSkipToNextPixelcon = true;
		  needToCommitStorage = true;
		}
		index = json.indexOf(FS("\"staticPixelconData\":"));
		if(index > -1) {
		  char buff[45];
		  buff[44] = 0;
	  
		  index += 22;
		  int pixelconIndex = 0;
		  while(pixelconIndex < STORAGE_MAX_STATIC_PIXELCON) {
		  bool foundEnd = false;
		  for(int i=0; i<44; i++) {
			char ch = json.charAt(index++);
			if(ch == '"') {
			foundEnd = true;
			break;
			}
			buff[i] = ch;
		  }
		  if(foundEnd) break;
		  
		  uint8_t data[32];
		  fromBase64_256(data, buff);
		  storage::setStaticPixelcon(pixelconIndex, data);
	  
		  pixelconIndex++;
		  }
	  
		  Serial.println(FS("staticPixelData -> ") + String(pixelconIndex,DEC) + FS(" (qty)"));
		  storage::setNumStaticPixelcon(pixelconIndex);
		  needToSkipToNextPixelcon = true;
		  needToCommitStorage = true;
		}
		index = json.indexOf(FS("\"sources\":"));
		if(index > -1) {
		  int endIndex = json.indexOf("]", index);
	  
		  for(int i=0; i<STORAGE_MAX_SOURCES; i++) {
		  char sourceType = 0;
		  char sourceId[41];
		  memset(sourceId, 0, 41);
		  
		  int typeIndex = json.indexOf(FS("\"type\":"), index);
		  int idIndex = json.indexOf(FS("\"id\":"), index);
		  if(typeIndex > -1 && idIndex > -1 && typeIndex < endIndex && idIndex < endIndex) {
			char ch;
			ch = json.charAt(typeIndex+7);
			for(int i=0; ch!=','&&ch!='}'; i++) {
			sourceType = sourceType*10 + toVal(ch);
			ch = json.charAt(typeIndex+8+i);
			}
			ch = json.charAt(idIndex+6);
			for(int i=0; i<40 && ch!='"'; i++) {
			sourceId[i] = ch;
			ch = json.charAt(idIndex+7+i);
			}
			if(typeIndex > idIndex) index = typeIndex+1;
			else index = idIndex+1;
			
			Serial.println(FS("sourceType") + String(i,DEC) + FS(" -> ") + String(sourceType,DEC));
			Serial.println(FS("sourceId") + String(i,DEC) + FS(" -> ") + String(sourceId));
		  }
		  storage::setPixelconSourceType(i, sourceType);
		  storage::setPixelconSourceId(i, sourceId);
		  }
		  needToRefreshPixelconSources = true;
		  needToCommitStorage = true;
		}
		index = json.indexOf(FS("\"rpcClient\":"));
		if(index > -1) {
		  char rpcClient[256];
		  memset(rpcClient, 0, 256);
	  
		  char ch = json.charAt(index+13);
		  for(int i=0; i<255 && ch!='"'; i++) {
		  rpcClient[i] = ch;
		  ch = json.charAt(index+14+i);
		  }
	  
		  Serial.println(FS("rpcClient -> ") + String(rpcClient));
		  storage::setRPCClient(rpcClient);
		  needToRefreshPixelconSources = true;
		  needToCommitStorage = true;
		}
		index = json.indexOf(FS("\"brightness\":"));
		if(index > -1) {
		  int brightness = 0;
		  
		  char ch = json.charAt(index+13);
		  for(int i=0; ch!=','&&ch!='}'; i++) {
		  brightness = brightness*10 + toVal(ch);
		  ch = json.charAt(index+14+i);
		  }
	  
		  Serial.println(FS("brightness -> ") + String(brightness, DEC));
		  storage::setBright(brightness);
		  needToCommitStorage = true;
		}
		index = json.indexOf(FS("\"duration\":"));
		if(index > -1) {
		  int duration = 0;
		  
		  char ch = json.charAt(index+11);
		  for(int i=0; ch!=','&&ch!='}'; i++) {
			duration = duration*10 + toVal(ch);
			ch = json.charAt(index+12+i);
		  }
	  
		  Serial.println(FS("duration -> ") + String(duration, DEC));
		  storage::setDuration(duration);
		  needToSkipToNextPixelcon = true;
		  needToCommitStorage = true;
		}
	  
		if(needToSkipToNextPixelcon) rendering::skipToNextPixelcon();
		if(needToRefreshPixelconSources) rendering::refreshPixelconSources();
		if(needToCommitStorage) storage::commit();
		if(needToRefreshPixelconSources && !storage::getIsStaticMode()) {
		  display::drawLoadingScreen();
		  display::flush();
		}
		server->send(200, "text/plain", "SUCCESS");
	  } else {
		server->send(500, "text/plain", "ERROR");
	  }
	  delay(500);
	}

	
}

#endif /* PAGE_CONFIG_H */
