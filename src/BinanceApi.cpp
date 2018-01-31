#include "BinanceApi.h"

BinanceApi::BinanceApi(Client &client)	{
  this->client = &client;
}

String BinanceApi::SendGetToBinance(String command) {
  String body="";
  body.reserve(700);
  bool finishedHeaders = false;
  bool currentLineIsBlank = true;
  bool post = false;
  char lastchar;
	long now;
	bool avail;

	if (client->connect(Binance_HOST, Port)) {
		// Serial.println(".... connected to server");
		String a="";
		char c;
		int ch_count=0;
		client->println("GET " + command + " HTTP/1.1");
    client->println("Host: " Binance_HOST);
		client->println(F("User-Agent: arduino/1.0.0"));
		client->println();
		now=millis();
		avail=false;
		while (millis()-now<1500) {
			while (client->available()) {
				char c = client->read();
				//Serial.write(c);

        if(!finishedHeaders){
          if (currentLineIsBlank && c == '\n') {
            finishedHeaders = true;
          }
        } else {
          if (c == '{' and lastchar == '\n') {
            post = true;
          }
          if (post and c == '\n') {
            post = false;
          }
          if (post) {
            body=body+c;
            ch_count++;
          }
        }

        if (c == '\n') {
          currentLineIsBlank = true;
        } else if (c != '\r') {
          currentLineIsBlank = false;
        }

        lastchar = c;

				avail=true;
			}
			if (avail) {
        body="["+body+"]";
				Serial.println("Body:");
				Serial.println(body);
				Serial.println("END");
				break;
			}
		}
	}

  return body;
}

BNBTickerResponse BinanceApi::GetTickerInfo(String coinId) {
  // https://api.Binance.com/api/v1/ticker/24hr?symbol=BTCUSDT
  coinId.toUpperCase();
  String command="/api/v1/ticker/24hr?symbol=" + coinId ;

  Serial.println(command);
  String response = SendGetToBinance(command);
  BNBTickerResponse responseObject = BNBTickerResponse();
  DynamicJsonBuffer jsonBuffer;
	JsonArray& root = jsonBuffer.parseArray(response);
  if (root.success()) {
    responseObject.symbol = root[0]["symbol"].as<String>();
    responseObject.priceChange = root[0]["priceChange"].as<double>();
    responseObject.priceChangePercent = root[0]["priceChangePercent"].as<double>();
    responseObject.weightedAvgPrice = root[0]["weightedAvgPrice"].as<double>();
    responseObject.prevClosePrice = root[0]["prevClosePrice"].as<double>();
    responseObject.lastPrice = root[0]["lastPrice"].as<double>();
    responseObject.lastQty = root[0]["lastQty"].as<double>();
    responseObject.bidPrice = root[0]["bidPrice"].as<double>();
    responseObject.bidQty = root[0]["bidQty"].as<double>();
    responseObject.askPrice = root[0]["askPrice"].as<double>();
    responseObject.askQty = root[0]["askQty"].as<double>();
    responseObject.openPrice = root[0]["openPrice"].as<double>();
    responseObject.highPrice = root[0]["highPrice"].as<double>();
    responseObject.lowPrice = root[0]["lowPrice"].as<double>();

    responseObject.volume = root[0]["volume"].as<double>();
    responseObject.quoteVolume = root[0]["quoteVolume"].as<double>();
    responseObject.openTime = root[0]["openTime"].as<double>();
    responseObject.closeTime = root[0]["closeTime"].as<double>();

    responseObject.firstId = root[0]["firstId"].as<double>();
    responseObject.lastId = root[0]["lastId"].as<double>();
    responseObject.count = root[0]["count"].as<double>();
  } else {
    JsonObject& rootObject = jsonBuffer.parseObject(response);
    if (rootObject.containsKey("error")) {
       responseObject.error = rootObject["error"].as<String>();
    } else {
      responseObject.error = "Failed to parse JSON";
    }

    return responseObject;
  }
}
