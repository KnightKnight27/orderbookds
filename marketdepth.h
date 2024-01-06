//
// Created by Kartik Bhatia on 06/01/24.
//

#ifndef ORDERBOOKDS_MARKETDEPTH_H
#define ORDERBOOKDS_MARKETDEPTH_H

struct MarketDepth {
    std::vector<std::tuple<uint64_t,uint64_t> > limitOrders;

    friend std::ostream& operator<<(std::ostream& os, const MarketDepth& depth);
};

#endif //ORDERBOOKDS_MARKETDEPTH_H
