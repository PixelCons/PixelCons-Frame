#ifndef ETHEREUM_H
#define ETHEREUM_H

#include <WiFiClientSecure.h>
#include "utils.h"
#include "storage.h"

#define ETHEREUM_HTTPS_PORT 443
	
namespace eth
{
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////  Interface  //////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	int creatorTotal(const char* creator);
	int tokenOfCreatorByIndex(const char* creator, uint32_t index, char* retToken);
		
	int collectionTotal(const char* collection);
	int tokenOfCollectionByIndex(const char* collection, uint32_t index, char* retToken);
	
	int balanceOf(const char* owner);
	int tokenOfOwnerByIndex(const char* owner, uint32_t index, char* retToken); 
	
	int totalSupply();
	int tokenByIndex(uint32_t index, char* retToken);

	/* Helper Functions */
	int sendJSONRPC(String json, char* result, uint32_t len);

	
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////  Impl  //////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	int creatorTotal(const char* creator) {
	  String json = FS("{\"jsonrpc\":\"2.0\",\"id\":7,\"method\":\"eth_call\",\"params\":[{\"to\":\"0x5536B6aAdd29eAf0DB112Bb28046A5FaD3761bD4\",\"data\":\"0x08702682000000000000000000000000") + String(creator) + FS("\"},\"latest\"]}");

	  char hex[64];
	  int res = sendJSONRPC(json, hex, 64);
	  if(res < 0) return res;
	  return convertFromHex(hex, 64);
	}

	int tokenOfCreatorByIndex(const char* creator, uint32_t index, char* retToken) {
	  char hexIndex[65];
	  String json = FS("{\"jsonrpc\":\"2.0\",\"id\":7,\"method\":\"eth_call\",\"params\":[{\"to\":\"0x5536B6aAdd29eAf0DB112Bb28046A5FaD3761bD4\",\"data\":\"0x4fc09275000000000000000000000000") + String(creator) + String(convertToHex(index, hexIndex, 64)) + FS("\"},\"latest\"]}");

	  return sendJSONRPC(json, retToken, 64);
	}  

	int collectionTotal(const char* collection) {
	  String json = FS("{\"jsonrpc\":\"2.0\",\"id\":4,\"method\":\"eth_call\",\"params\":[{\"to\":\"0x5536B6aAdd29eAf0DB112Bb28046A5FaD3761bD4\",\"data\":\"0x26a50862000000000000000000000000") + String(collection) + FS("\"},\"latest\"]}");

	  char hex[64];
	  int res = sendJSONRPC(json, hex, 64);
	  if(res < 0) return res;
	  return convertFromHex(hex, 64);
	}

	int tokenOfCollectionByIndex(const char* collection, uint32_t index, char* retToken) {
	  char hexIndex[65];
	  String json = FS("{\"jsonrpc\":\"2.0\",\"id\":4,\"method\":\"eth_call\",\"params\":[{\"to\":\"0x5536B6aAdd29eAf0DB112Bb28046A5FaD3761bD4\",\"data\":\"0x4aeabcb6000000000000000000000000") + String(collection) + String(convertToHex(index, hexIndex, 64)) + FS("\"},\"latest\"]}");

	  return sendJSONRPC(json, retToken, 64);
	}  

	int balanceOf(const char* owner) {
	  String json = FS("{\"jsonrpc\":\"2.0\",\"id\":4,\"method\":\"eth_call\",\"params\":[{\"to\":\"0x5536B6aAdd29eAf0DB112Bb28046A5FaD3761bD4\",\"data\":\"0x70a08231000000000000000000000000") + String(owner) + FS("\"},\"latest\"]}");

	  char hex[64];
	  int res = sendJSONRPC(json, hex, 64);
	  if(res < 0) return res;
	  return convertFromHex(hex, 64);
	}

	int tokenOfOwnerByIndex(const char* owner, uint32_t index, char* retToken) {
	  char hexIndex[65];
	  String json = FS("{\"jsonrpc\":\"2.0\",\"id\":4,\"method\":\"eth_call\",\"params\":[{\"to\":\"0x5536B6aAdd29eAf0DB112Bb28046A5FaD3761bD4\",\"data\":\"0x2f745c59000000000000000000000000") + String(owner) + String(convertToHex(index, hexIndex, 64)) + FS("\"},\"latest\"]}");

	  return sendJSONRPC(json, retToken, 64);
	}  

	int totalSupply() {
	  String json = FS("{\"jsonrpc\":\"2.0\",\"id\":4,\"method\":\"eth_call\",\"params\":[{\"to\":\"0x5536B6aAdd29eAf0DB112Bb28046A5FaD3761bD4\",\"data\":\"0x18160ddd\"},\"latest\"]}");

	  char hex[64];
	  int res = sendJSONRPC(json, hex, 64);
	  if(res < 0) return res;
	  return convertFromHex(hex, 64);
	  
	}

	int tokenByIndex(uint32_t index, char* retToken) {
	  char hexIndex[65];
	  String json = FS("{\"jsonrpc\":\"2.0\",\"id\":4,\"method\":\"eth_call\",\"params\":[{\"to\":\"0x5536B6aAdd29eAf0DB112Bb28046A5FaD3761bD4\",\"data\":\"0x4f6ccce7") + String(convertToHex(index, hexIndex, 64)) + FS("\"},\"latest\"]}");

	  return sendJSONRPC(json, retToken, 64);
	} 

	int sendJSONRPC(String json, char* result, uint32_t len) {
	  WiFiClientSecure client;
	  client.setInsecure();
	  client.setTimeout(3000);
	  
	  const char* rpcClient = storage::getRPCClient();
	  char rpcClientHost[256];
	  char rpcClientHostPath[256];
	  int i=0,j=0;
	  for(; rpcClient[i] != 0 && rpcClient[i] != '/'; i++) rpcClientHost[i] = rpcClient[i];
	  for(; rpcClient[i+j] != 0; j++) rpcClientHostPath[j] = rpcClient[i+j];
	  rpcClientHost[i] = rpcClientHostPath[j] = 0;
	  
	  if (!client.connect(rpcClientHost, ETHEREUM_HTTPS_PORT)) {
		Serial.println(FS("Failed to connect to JSON-RPC client"));
		return -1;
	  }

	  client.print(FS("POST ") + String(rpcClientHostPath) + FS(" HTTP/1.1\r\n") +
			  FS("Host: ") + rpcClientHost + FS("\r\n") +
			  FS("Connection: close\r\n") +
			  FS("Content-Type: application/json\r\n") +
			  FS("Content-Length: ") + json.length() + FS("\r\n") +
			  FS("\r\n") + json + FS("\r\n"));
	  while(client.connected()) {
		String line = client.readStringUntil('\n');
		if (line == "\r") {
		  break;
		}
	  }
	  
	  String line = client.readStringUntil('}');
	  client.stop();
	  
	  int index = line.indexOf(FS("\"result\""));
	  if(index == -1 || line.length() != (index + len + 13)) {
		Serial.println(FS("JSON-RPC responded in error"));
		return -2;
	  }
	  
	  for(int i=0; i<len; i++) result[i] = line.charAt(index+12+i);
	  return 0;
	}
	
	
}

#endif /* ETHEREUM_H */
