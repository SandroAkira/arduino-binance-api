#include <BinanceApi.h>

/*******************************************************************
 *  An example of getting ticker info from binance.com             *
 *                                                                 *
 *  Based on Brian Lough's CoinMarketCap library example           *
 *******************************************************************/


#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>

//------- Install From Library Manager -------
#include <ArduinoJson.h>


//------- Replace the following! ------
char ssid[] = "SSID";       // your network SSID (name)
char password[] = "PASSWORD";  // your network key


WiFiClientSecure client;
BinanceApi api(client);

// Binance's limit is "no more than 10 per minute"
// Make sure to factor in if you are requesting more than one coin.
unsigned long api_mtbs = 60000; //mean time between api requests
unsigned long api_due_time = 0;

void setup() {

  Serial.begin(115200);

  // Set WiFi to station mode and disconnect from an AP if it was Previously
  // connected
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  delay(100);

  // Attempt to connect to Wifi network:
  Serial.print("Connecting Wifi: ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  IPAddress ip = WiFi.localIP();
  Serial.println(ip);
}

void printTickerData(String ticker) {
  Serial.println("---------------------------------");
  Serial.println("Getting ticker data for " + ticker);


  // Ticker unfortunately is not the symbol for some reason.
  // Go to Binance.com and select the coin you would like to check
  // The ticker name makes up the last part of the URL
  // e.g: http://coinmarketcap.com/currencies/bitcoin/ , "bitcoin" is the ticker value

  // Currency is optional, so you can pass only ticker if you want.
  // Check out the currency drop down on Binance.com to get available values
  BNBTickerResponse response = api.GetTickerInfo(ticker);
  if (response.error == "") {
    Serial.println("---------------------------------");
    Serial.println("Getting ticker data for " + ticker);
    Serial.println("---------------------------------");
    Serial.print("PriceChange: ");
    Serial.println(priceChange);
    Serial.print("weightedAvgPrice: ");
    Serial.println(weightedAvgPrice);
    Serial.print("prevClosePrice: ");
    Serial.println(prevClosePrice);
    Serial.print("lastPrice: ");
    Serial.println(lastPrice);
    Serial.print("lastQty: ");
    Serial.println(lastQty);
    Serial.print("bidPrice: ");
    Serial.println(bidPrice);
    Serial.print("bidQty: ");
    Serial.println(bidQty);
    Serial.print("askPrice: ");
    Serial.println(askPrice);
    Serial.print("askQty: ");
    Serial.println(askQty);
    Serial.print("openPrice: ");
    Serial.println(openPrice);
    Serial.print("highPrice: ");
    Serial.println(highPrice);
    Serial.print("lowPrice: ");
    Serial.println(lowPrice);
    Serial.print("volume: ");
    Serial.println(volume);
    Serial.print("quoteVolume: ");
    Serial.println(quoteVolume);
    Serial.print("openTime: ");
    Serial.println(openTime);
    Serial.print("closeTime: ");
    Serial.println(closeTime);
    Serial.print("firstId: ");
    Serial.println(firstId);
    Serial.print("lastId: ");
    Serial.println(lastId);
    Serial.print("count: ");
    Serial.println(count);

  } else {
    Serial.print("Error getting data: ");
    Serial.println(response.error);
  }
  Serial.println("---------------------------------");
}

void loop() {
  unsigned long timeNow = millis();
  if ((timeNow > api_due_time))  {
    printTickerData("BTCUSDT");
    printTickerData("ADABTC");
    printTickerData("EOSBTC");
    api_due_time = timeNow + api_mtbs;
  }
}
