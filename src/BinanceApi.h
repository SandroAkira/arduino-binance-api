/*
Copyright (c) 2017 Brian Lough. All right reserved.

This library is free software; you can redistribute it and/or
modify it under the terms of the GNU Lesser General Public
License as published by the Free Software Foundation; either
version 2.1 of the License, or (at your option) any later version.

This library is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public
License along with this library; if not, write to the Free Software
Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA
*/


#ifndef BinanceApi_h
#define BinanceApi_h

#include <Arduino.h>
#include <ArduinoJson.h>
#include <Client.h>

#define Binance_HOST "api.binance.com"

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


class BinanceApi
{
  public:
    BinanceApi (Client &client);
    String SendGetToBinance(String command);
    BNBTickerResponse GetTickerInfo(String coinId);
    int Port = 443;

  private:
    Client *client;
};

#endif
