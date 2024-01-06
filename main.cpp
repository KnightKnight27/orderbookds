#include <iostream>
#include "orderbook.h"
#include "Message.h"
std::ostream& operator<<(std::ostream& os, const MarketDepth& depth) {
    if(depth.limitOrders.empty()){
        os <<"  No Orders yet\n";
    }
    for (const auto& order : depth.limitOrders) {
        os << "  Price: " << std::get<0>(order) << ", Quantity: " << std::get<1>(order) << "\n";
    }
    return os;
}
int main() {
    std::cout <<"Orderbook Data structure\n\n";
    size_t depth = 3;
    OrderBook orderBook(depth);
    std::vector<const Message> ticks = {
            Message("NEW",1,100,10,"BUY"),
            Message("NEW",2,97,20,"BUY"),
            Message("NEW",3,100,30,"SELL"),
            Message("TRD",1,3,100,5),
            Message("NEW",4,100,50,"BUY"),
            Message("NEW",5,97,70,"BUY"),
            Message("NEW",6,101,140,"BUY"),
            Message("NEW",7,96,102,"BUY"),
            Message("CXL", 2),
            Message("CXL",7),
            Message("MOD",6,95,120),
            Message("CXL", 5),
            Message("NEW",8,190,50,"SELL"),
    };
    for (auto &message: ticks) {
        order_book limitOrderBook = orderBook.processMessage(message);
        auto& bid_side = limitOrderBook[BookType::BID];
        std::cout <<"_______________________________" <<"\n";
        std::cout <<"Bid Depth"<< "\n";
        std::cout << bid_side;
        std::cout <<"_______________________________" <<"\n";
        auto& ask_side = limitOrderBook[BookType::ASK];
        std::cout <<"Ask Depth" <<"\n";
        std::cout << ask_side;
        std::cout <<"_______________________________" <<"\n";
    }
    return 0;
}
