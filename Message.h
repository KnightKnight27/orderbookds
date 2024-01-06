//
// Created by Kartik Bhatia on 06/01/24.
//

#ifndef ORDERBOOKDS_MESSAGE_H
#define ORDERBOOKDS_MESSAGE_H

#include <cstdint>
#include "order.h"
#include <iostream>
enum class Tick{
    NEW,MOD,CXL,TRD
};
inline std::unordered_map<std::string,Tick> Tick_Map = {
        {"NEW", Tick::NEW},
        {"MOD", Tick::MOD},
        {"CXL",Tick::CXL},
        {"TRD",Tick::TRD}
};
inline std::unordered_map<std::string,OrderType> Type_Map = {
        {"BUY", OrderType::BUY},
        {"SELL",OrderType::SELL}
};
struct Message {
    Tick type;
    OrderType orderType;
    uint64_t order_id;
    uint64_t price;
    uint64_t quantity;
    uint64_t mod_price;
    uint64_t mod_quantity;
    uint64_t buy_orderId;
    uint64_t sell_orderId;
    uint64_t tradePrice;
    uint64_t tradeQuantity;
    Message() = default;
    explicit Message(const std::string& tick,uint64_t id,uint64_t mod_price,uint64_t mod_quantity):
        type(Tick_Map[tick]), order_id(id), mod_price(mod_price), mod_quantity(mod_quantity){};

    explicit Message(const std::string& tick,uint64_t id): type(Tick_Map[tick]),order_id(id){};
    explicit Message(const std::string& tick,uint64_t id, uint64_t price, uint64_t quantity,
                     const std::string& orderType)
            : type(Tick_Map[tick]), orderType(Type_Map[orderType]),order_id(id), price(price), quantity(quantity) {}

    explicit Message(const std::string& tick,uint64_t buyId,uint64_t sell_Id,uint64_t tPrice,uint64_t tQuantity) :
    type(Tick_Map[tick]),buy_orderId(buyId),sell_orderId(sell_Id),tradePrice(tPrice),tradeQuantity(tQuantity){}
};


#endif //ORDERBOOKDS_MESSAGE_H

