#!/usr/bin/python3
# -*- coding: iso-8859-1 -*
""" Python starter bot for the Crypto Trader games, from ex-Riddles.io """
__version__ = "1.0"

import sys
import numpy as np

class Bot:
    def __init__(self):
        self.botState = BotState()
        self.prices = []
        self.priceHistory = []
        self.profitable = 0
        self.buyingPrice = 0
        self.sellingPrice = 0
        self.firstBuy = 0
        self.prevRatio = 0
        self.toBuy = 0
        self.toSell = 0

    def run(self):
        while True:
            reading = input() ## BTC - Prix début - Prix Fin  - Volume
            if len(reading) == 0:
                continue
            self.parse(reading)


    def isWorthMore(self, current_closing_price):
        if self.sellingPrice > current_closing_price:
            return 1
        return 0


    def profitable_to_buy(self, affordable, owned, current_closing_price):
        
        if (owned == 0 and self.firstBuy == 0):
            self.firstBuy = 1
            self.toBuy = 1
            self.priceHistory.append(current_closing_price)
            return (self.toBuy)
        elif owned == 0 and self.firstBuy == 1:
            self.toBuy = -1
        else:
            self.toBuy = 0
        if (self.toBuy == -1):
            if affordable > 0:
                ## Vérifier si le prix était en train de chuter et qu'il commence à remonter
                if current_closing_price > self.prices[-2] and self.prices[-3] > self.prices[-2] and self.prices[-3] < self.prices[-4] and current_closing_price < self.sellingPrice and self.isWorthMore(current_closing_price) == 1:
                    if current_closing_price / self.prices[-2] > 1.01:
                        print("Ratio is ", current_closing_price / self.prices[-2], file=sys.stderr)
                        self.toBuy = 1
                        if current_closing_price / self.prices[-2] > self.prevRatio:
                            self.prevRatio = current_closing_price / self.prices[-2]
                            self.buyingPrice = current_closing_price
                            self.priceHistory.append(current_closing_price)
                            print("Buying with dip values = ", self.prices[-2], " [-2]| ", self.prices[-3], " [-3]| ", self.prices[-4], " [-4]| ", current_closing_price, "CCP ", self.sellingPrice, "SP", file=sys.stderr)
        return (self.toBuy)

    def profitable_to_sell(self, affordable, owned, current_closing_price):
       
        if owned == 0:
            self.toSell = 0
            return (self.toSell)
        if (len(self.priceHistory) > 2 and current_closing_price > self.priceHistory[-2]):
            self.profitable = 1
        if (self.profitable == 1 and len(self.priceHistory) > 2):
            if (self.priceHistory[-1] < self.priceHistory[-2]):
                self.toSell = 1
            else:
                self.toSell = 0
        if (self.toSell == 1):
            self.profitable = 0
            self.sellingPrice = current_closing_price
        return (self.toSell)



    def parse(self, info: str):
        tmp = info.split(" ")
        if tmp[0] == "settings":
            self.botState.update_settings(tmp[1], tmp[2])
        if tmp[0] == "update":
            if tmp[1] == "game":
                self.botState.update_game(tmp[2], tmp[3])
        if tmp[0] == "action":
            # This won't work every time, but it works sometimes!

            dollars = self.botState.stacks["USDT"] ## combien d'argent j'ai
            current_closing_price = self.botState.charts["USDT_BTC"].closes[-1] ## Le prix de fermeture le prix auquel j'achète
            self.priceHistory.append(current_closing_price) ## je le rajoute à l'historique
            
            # HERE THE BOT WILL START BUYING THINGS TO SEE IF THEY ARE AFFORDABLE
            affordable = dollars / current_closing_price ## 1000$    | 1 btc -> 15 000
            
    
            owned = self.botState.stacks["BTC"]

            self.prices.append(current_closing_price)   


            if (self.profitable_to_buy(affordable, owned, current_closing_price) == 1):
                print(f'buy USDT_BTC {affordable}', flush=True)
                # print("Buying USDT_BTC ", affordable, file=sys.stderr)
            elif (self.profitable_to_sell(affordable, owned, current_closing_price) == 1):
                print(f'sell USDT_BTC {owned}', flush=True)
                # print("Seeling USDT_BTC ", owned, file=sys.stderr)
            else:
                print("no_moves", flush=True)
            

            


class Candle:
    def __init__(self, format, intel):
        tmp = intel.split(",")
        for (i, key) in enumerate(format):
            value = tmp[i]
            if key == "pair":
                self.pair = value
            if key == "date":
                self.date = int(value)
            if key == "high":
                self.high = float(value)
            if key == "low":
                self.low = float(value)
            if key == "open":
                self.open = float(value)
            if key == "close":
                self.close = float(value)
            if key == "volume":
                self.volume = float(value)

    def __repr__(self):
        return str(self.pair) + str(self.date) + str(self.close) + str(self.volume)


class Chart:
    def __init__(self):
        self.dates = []
        self.opens = []
        self.highs = []
        self.lows = []
        self.closes = []
        self.volumes = []
        self.indicators = {}

    def add_candle(self, candle: Candle):
        self.dates.append(candle.date)
        self.opens.append(candle.open)
        self.highs.append(candle.high)
        self.lows.append(candle.low)
        self.closes.append(candle.close)
        self.volumes.append(candle.volume)


class BotState:
    def __init__(self):
        self.timeBank = 0
        self.maxTimeBank = 0
        self.timePerMove = 1
        self.candleInterval = 1
        self.candleFormat = []
        self.candlesTotal = 0
        self.candlesGiven = 0
        self.initialStack = 0
        self.transactionFee = 0.1
        self.date = 0
        self.stacks = dict()
        self.charts = dict()

    def update_chart(self, pair: str, new_candle_str: str):
        if not (pair in self.charts):
            self.charts[pair] = Chart()
        new_candle_obj = Candle(self.candleFormat, new_candle_str)
        self.charts[pair].add_candle(new_candle_obj)

    def update_stack(self, key: str, value: float):
        self.stacks[key] = value

    def update_settings(self, key: str, value: str):
        if key == "timebank":
            self.maxTimeBank = int(value)
            self.timeBank = int(value)
        if key == "time_per_move":
            self.timePerMove = int(value)
        if key == "candle_interval":
            self.candleInterval = int(value)
        if key == "candle_format":
            self.candleFormat = value.split(",")
        if key == "candles_total":
            self.candlesTotal = int(value)
        if key == "candles_given":
            self.candlesGiven = int(value)
        if key == "initial_stack":
            self.initialStack = int(value)
        if key == "transaction_fee_percent":
            self.transactionFee = float(value)

    def update_game(self, key: str, value: str):
        if key == "next_candles":
            new_candles = value.split(";")
            self.date = int(new_candles[0].split(",")[1])
            for candle_str in new_candles:
                candle_infos = candle_str.strip().split(",")
                self.update_chart(candle_infos[0], candle_str)
        if key == "stacks":
            new_stacks = value.split(",")
            for stack_str in new_stacks:
                stack_infos = stack_str.strip().split(":")
                self.update_stack(stack_infos[0], float(stack_infos[1]))


if __name__ == "__main__":
    mybot = Bot()
    mybot.run()