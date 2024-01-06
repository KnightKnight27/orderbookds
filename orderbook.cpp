//
// Created by Kartik Bhatia on 06/01/24.
//

#include <cassert>
#include "orderbook.h"
std::unordered_map<OrderType,BookType> rel_map = {
        {OrderType::BUY,BookType::BID},
        {OrderType::SELL,BookType::ASK}
};
OrderBook::OrderBook(size_t depth) : m_Depth(depth){}

void OrderBook::add(const Order &order){
    auto& bookType = rel_map[order.type];
    assert(m_Orders.find(order.orderId) == m_Orders.end() && "order_id already exists!" );//invariant to check two new orders of same id.
    m_Orders[order.orderId] = order;
    m_PriceVolume[bookType][order.price] += order.quantity;
    printOrderBook();
}

void OrderBook::cancel(uint64_t orderId) {
    assert(m_Orders.find(orderId) != m_Orders.end() && "order_id not found!" );// invariant to check if Order exists
    auto& order = m_Orders[orderId];
    auto& bookType = rel_map[order.type];
    m_PriceVolume[bookType][order.price] -= order.quantity;
    if (m_PriceVolume[bookType][order.price] == 0){
        m_PriceVolume[bookType].erase(order.price);
    }
    m_Orders.erase(orderId);
}

void OrderBook::modify(const Order &order) {
    assert((m_Orders.find(order.orderId) != m_Orders.end()) && "order_id not found!" ); // invariant to check if order exists
    // modify is equivalent to cancelling prev order and adding new order
    cancel(order.orderId);
    add(order);
}

void OrderBook::trade(uint64_t buy_orderId, uint64_t sell_orderId, uint64_t price, uint64_t quantity) {
    assert((m_Orders.find(buy_orderId)!= m_Orders.end() && m_Orders.find(sell_orderId) != m_Orders.end())
                    && "buyerId/sellerId not valid");
    // verifying if orders are valid
    Order& buy_Order = m_Orders[buy_orderId];
    Order& sell_Order = m_Orders[sell_orderId];
    assert((sell_Order.price == price && buy_Order.price == price && sell_Order.quantity >= quantity && buy_Order.quantity >= quantity)
                && "trade not possible! invalid price/quantity");
    m_PriceVolume[BookType::BID][price] -= quantity;
    m_PriceVolume[BookType::ASK][price] -= quantity;
    buy_Order.quantity -= quantity;
    if(buy_Order.quantity == 0){
        cancel(buy_orderId);
    }
    sell_Order.quantity -= quantity;
    if(sell_Order.quantity == 0){
        cancel(sell_orderId);
    }
}

std::unordered_map<BookType,MarketDepth> OrderBook::printOrderBook() {
    std::unordered_map<BookType,MarketDepth> limitOrderBook;
    for(auto it = m_PriceVolume[BookType::ASK].begin();it != m_PriceVolume[BookType::ASK].end()
                            && limitOrderBook[BookType::ASK].limitOrders.size()<m_Depth;it++){
        limitOrderBook[BookType::ASK].limitOrders.emplace_back(*it);
    }
    for(auto it = m_PriceVolume[BookType::BID].rbegin();it != m_PriceVolume[BookType::BID].rend()
                            && limitOrderBook[BookType::BID].limitOrders.size()<m_Depth;it++){
        limitOrderBook[BookType::BID].limitOrders.emplace_back(*it);
    }
    return limitOrderBook;
}

order_book OrderBook::processMessage(const Message& message) {
    switch(message.type){
        case Tick::NEW:
            add(Order{message.order_id,message.price,message.quantity,message.orderType});
            std::cout <<"NEW processed successfully\n";
            break;
        case Tick::CXL:
            cancel(message.order_id);
            std::cout <<"CXL processed successfully\n";
            break;
        case Tick::MOD:
            modify(Order{message.order_id,message.mod_price,message.mod_quantity,message.orderType});
            std::cout <<"MOD processed successfully\n";
            break;
        case Tick::TRD:
            trade(message.buy_orderId,message.sell_orderId,message.tradePrice,message.tradeQuantity);
            std::cout <<"TRD processed successfully\n";
            break;
        default:
            std::cerr << "Unknown message type\n";
    }
    auto limitOrderBook = printOrderBook();
    return limitOrderBook;
}

