#ifndef RENDERING_H
#define RENDERING_H

#include "utils.h"
#include "storage.h"
#include "display.h"
#include "ethereum.h"

#define SHOW_IP_DURATION 180
#define ANIMATION_FRAME_DURATION 20
#define RENDER_30FPS_CONSTANT_NOWIFI 510
#define RENDER_30FPS_CONSTANT_WIFI 825
#define RENDER_FRAMES_TO_FETCH 30
	
namespace rendering
{
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////  Interface  //////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	void init();
	void process(bool wifiConnected);
	void refreshPixelconSources();
	void skipToNextPixelcon();
	void showIPAddress();
	void setWiFiRenderMode(bool wifiRenderMode);

	/* Helper Functions */
	void pixelconSourcesRefresh();
	int fetchNextPixelcon(bool wifiConnected);
	void randomizeAnimationDir();

	
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////  Data  //////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	int isWiFiRenderMode = false;
	int showIPAddressCounter = 0;
	int steady30FPSCounter = 0;
	int pixelconTotalAtSource[20];
	int pixelconSourceTotal = 0;
	int pixelconDurationTime = 0;
	int pixelconClock = 0;
	int pixelconSourceRefreshEvery = 30;
	int pixelconSourceRefreshCounter = 0;
	char loadedPixelconId[] = "0000000000000000000000000000000000000000000000000000000000000000";
	int loadedPixelconIndex = 0;
	int pixelconAnimationDir = 0;
	
	
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////  Impl  //////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	void init() {
	  pixelconDurationTime = storage::getDuration()*30;
	  pixelconClock = pixelconDurationTime;
	  pixelconSourceRefreshCounter = pixelconSourceRefreshEvery;
	}
	
	void process(bool wifiConnected) {
	  pixelconDurationTime = storage::getDuration()*30;
	  int steady30FPSValue = RENDER_30FPS_CONSTANT_NOWIFI;
	  int cyclesRequiredToFetch = 0;
	  if(wifiConnected) {
		steady30FPSValue = RENDER_30FPS_CONSTANT_WIFI;
		cyclesRequiredToFetch += RENDER_FRAMES_TO_FETCH;
		if(pixelconSourceRefreshCounter+1 >= pixelconSourceRefreshEvery) cyclesRequiredToFetch += storage::getNumPixelconSources()*RENDER_FRAMES_TO_FETCH;
		isWiFiRenderMode = true;
	  }
	  
	  if(++steady30FPSCounter >= steady30FPSValue) {
		steady30FPSCounter = 0;
		if(showIPAddressCounter > 0) {
		  showIPAddressCounter--;

		  // show ip address
		  if(loadedPixelconIndex > -1) display::drawPixelcon(loadedPixelconId, 0, 0);
		  else display::drawWarningScreen(); 
		  if(wifiConnected) display::drawText(WiFi.localIP().toString().c_str(), 10 - (70-(showIPAddressCounter*70)/SHOW_IP_DURATION), 3);
		  else display::drawText("Not Conneted", 10 - (70-(showIPAddressCounter*70)/SHOW_IP_DURATION), 3);
		} else {

		  // regular draw pixelcon routine
		  pixelconClock++;
		  if(pixelconClock >= (pixelconDurationTime - cyclesRequiredToFetch)) {
			pixelconClock = 0;
			randomizeAnimationDir();
	  
			// refresh pixelcon sources
			if(wifiConnected) {
			  pixelconSourceRefreshCounter++;
			  if(pixelconSourceRefreshCounter >= pixelconSourceRefreshEvery) {
				pixelconSourceRefreshCounter = 0;
				pixelconSourcesRefresh();
			  }
			}
	  
			// fetch and draw next pixelcon
			fetchNextPixelcon(wifiConnected);
			Serial.print(FS("Loaded Pixelcon: "));
			Serial.println(loadedPixelconId);
		  }

		  // determine animation offsets
		  int x = 0;
		  int y = 0;
		  if(pixelconClock < ANIMATION_FRAME_DURATION) {
			int a = ANIMATION_FRAME_DURATION-pixelconClock;
			a = (a*a*a*8)/(ANIMATION_FRAME_DURATION*ANIMATION_FRAME_DURATION*ANIMATION_FRAME_DURATION);
			if(pixelconAnimationDir == 0) x = -a;
			else if(pixelconAnimationDir == 1) x = a;
			else y = -a;
		  }

		  // draw pixelcon
		  if(loadedPixelconIndex > -1) display::drawPixelcon(loadedPixelconId, x, y);
		  else display::drawWarningScreen(); 
		}
		display::flush();
	  }
	}

	void pixelconSourcesRefresh() {
	  Serial.println(FS("Refreshing PixelCon sources from WiFi..."));
	  pixelconSourceTotal = 0;
	  int numSources = storage::getNumPixelconSources();
	  for(int i=0; i<numSources; i++) {
		int total = 0;
		int sourceType = storage::getPixelconSourceType(i);
		if(sourceType == 1) total = eth::creatorTotal(storage::getPixelconSourceId(i));
		if(sourceType == 2) total = eth::collectionTotal(storage::getPixelconSourceId(i));
		if(sourceType == 3) total = eth::balanceOf(storage::getPixelconSourceId(i));
		if(sourceType == 4) total = eth::totalSupply();
		if(total < 0) total = 0;
		
		pixelconSourceTotal += total;
		pixelconTotalAtSource[i] = pixelconSourceTotal;
	  }
	}

	void refreshPixelconSources() {
	  pixelconClock = pixelconDurationTime;
	  pixelconSourceRefreshCounter = pixelconSourceRefreshEvery;
	}

	void skipToNextPixelcon() {
	  pixelconClock = pixelconDurationTime;
	}

	int fetchNextPixelcon(bool wifiConnected) {
	  if(isWiFiRenderMode && !storage::getIsStaticMode()) {
		if(wifiConnected && pixelconSourceTotal > 0) {
		  
		  // randomly load a pixelcon from wifi
		  Serial.println(FS("Fetching PixelCon from WiFi..."));
		  int index = random(0, pixelconSourceTotal);
		  if(index == loadedPixelconIndex) index = (index + 1) % pixelconSourceTotal;
		  loadedPixelconIndex = index;
		  int sourceIndex = 0; 
		  int numSources = storage::getNumPixelconSources();
		  while(sourceIndex < numSources) {
			if(index < pixelconTotalAtSource[sourceIndex]) break;
			else sourceIndex++;
		  }
		  int sourceType = storage::getPixelconSourceType(sourceIndex);
		  if(sourceIndex > 0) index -= pixelconTotalAtSource[sourceIndex-1];
		  int fetchRes = 0;
		  if(sourceType == 1) fetchRes = eth::tokenOfCreatorByIndex(storage::getPixelconSourceId(sourceIndex), index, loadedPixelconId);
		  if(sourceType == 2) fetchRes = eth::tokenOfCollectionByIndex(storage::getPixelconSourceId(sourceIndex), index, loadedPixelconId);
		  if(sourceType == 3) fetchRes = eth::tokenOfOwnerByIndex(storage::getPixelconSourceId(sourceIndex), index, loadedPixelconId);
		  if(sourceType == 4) fetchRes = eth::tokenByIndex(index, loadedPixelconId);
		  if(fetchRes < 0) {
			if(fetchRes == -1) {

			  // load the no pixelcon/bad rpc-client error screen
			  loadedPixelconIndex = -1;
			  Serial.println(FS("Error: RPC-Client is down?"));
			  memset(loadedPixelconId, 0, 64);
			} else {
			  
			  // make sure we are up to date on the sources
			  Serial.println(FS("Assuming source totals need refreshed"));
			  refreshPixelconSources();
			}
		  }
		} else if(wifiConnected) {
		  
		  // load the no pixelcon/bad rpc-client error screen
		  loadedPixelconIndex = -1;
		  Serial.println(FS("Error: Source list has no valid PixelCons"));
		  memset(loadedPixelconId, 0, 64);
		} else {

		  // load the no wifi error screen
		  loadedPixelconIndex = -1;
		  Serial.println(FS("Error: WiFi is not connected"));
		  memset(loadedPixelconId, 0, 64);
		}
	  } else {
		if(storage::getNumStaticPixelcon() > 0) {

		  // randomly load a sample pixelcon from flash memory
		  int index = random(0, storage::getNumStaticPixelcon());
		  if(index == loadedPixelconIndex) index = (index + 1) % storage::getNumStaticPixelcon();
		  loadedPixelconIndex = index;
		  storage::getStaticPixelconId(index, loadedPixelconId);
		} else {
		  
		  // load the no static pixelcon screen
		  loadedPixelconIndex = -1;
		  Serial.println(FS("Error: No static pixelcons to fetch from"));
		  memset(loadedPixelconId, 0, 64);
		}
	  }

	  loadedPixelconId[65] = 0;
	  return 0;
	}

	void setWiFiRenderMode(bool wifiRenderMode) {
	  isWiFiRenderMode = wifiRenderMode;
	}

	void showIPAddress() {
	  if(showIPAddressCounter == 0) showIPAddressCounter = SHOW_IP_DURATION;
	}

	void randomizeAnimationDir() {
	  int old = pixelconAnimationDir;
	  while(pixelconAnimationDir == old) pixelconAnimationDir = random(0, 3);
	}
	
	
}

#endif /* RENDERING_H */
