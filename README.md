# arduino-binance-api
A wrapper around the [Binance.com](http://binance.com/) API for Arduino (supports ESP8266).
Forked from [CoinMarketCapApi](https://github.com/witnessmenow/arduino-coinmarketcap-api).

The Binance API can be used to look information on a wide range of crypto currency coins, included Bitcoin and Ethereum (check out the full list on their site).

## Usage

The simplest way to see how it works is the check out [the example that comes with the library](https://github.com/SandroAkira/arduino-binance-api/blob/master/examples/ESP8266/GetTickerInfo/GetTickerInfo.ino).

### GetTickerInfo:
A wrapper around the single ticker endpoint supporting the convert parameter (currency)

Code is as follows:
```
BNBTickerResponse response = api.GetTickerInfo(ticker);
```

Go to [Binance.com](http://binance.com/) and select the coin you would like to check, the ticker name makes up the last part of the URL. e.g: https://api.binance.com/api/v1/ticker/24hr?symbol=BTCUSDT , "BTCUSDT" is the ticker value for BTC to USD. Other examples: ADABTC, ETHBTC, EOSBTC, XLMBTC, ...

Check out the currency list on [Binance.com](https://www.binance.com/trade.html) to get available values

The return object has the following values:
```
struct BNBTickerResponse{
  String symbol;
  double priceChange;
  double priceChangePercent;
  double weightedAvgPrice;
  double prevClosePrice;
  double lastPrice;
  double lastQty;
  double bidPrice;
  double bidQty;
  double askPrice;
  double askQty;
  double openPrice;
  double highPrice;
  double lowPrice;

  double volume;
  double quoteVolume;
  double openTime;
  double closeTime;

  double firstId;
  double lastId;
  double count;

  String error;
};
```
