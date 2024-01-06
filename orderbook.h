//
// Created by Kartik Bhatia on 06/01/24.
//

#ifndef ORDERBOOKDS_ORDERBOOK_H
#define ORDERBOOKDS_ORDERBOOK_H

#include <cstddef>
#include <map>
#include "order.h"
#include "marketdepth.h"
#include "Message.h"

enum class BookType{
    ASK,BID
};

using order_map =  std::unordered_map<uint64_t,Order>;
using volume_map = std::unordered_map<BookType,std::map<uint64_t,uint64_t>>;
using order_book = std::unordered_map<BookType,MarketDepth>;
class OrderBook {
public:
    explicit OrderBook(size_t depth);
    order_book processMessage(const Message& message);
    order_book printOrderBook();
private:
    size_t m_Depth;
    order_map m_Orders;
    volume_map m_PriceVolume;
    void add(const Order& order);
    void cancel(uint64_t orderId);
    void modify(const Order& order);
    void trade(uint64_t buy_orderId,uint64_t sell_orderId,uint64_t price,uint64_t quantity);
};

#endif //ORDERBOOKDS_ORDERBOOK_H
