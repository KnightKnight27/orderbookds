//
// Created by Kartik Bhatia on 06/01/24.
//
#include <cstdint>

#ifndef ORDERBOOKDS_ORDER_H
#define ORDERBOOKDS_ORDER_H

enum class OrderType{BUY, SELL};

struct Order {
    Order () {};
    Order(uint64_t id, uint64_t price, uint64_t quantity,OrderType orderType) :
            orderId{id}, price{price}, quantity{quantity},type{orderType} {};
    OrderType type;
    uint64_t quantity;
    uint64_t orderId;
    uint64_t price;  // floats doubles end up with precision issues better to have
    // in the form x/(10^a)
};


#endif //ORDERBOOKDS_ORDER_H
