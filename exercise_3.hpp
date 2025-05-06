#include <vector>
#include <iostream>
#include <map>
#include <unordered_map>
#include <list>

namespace Pan {

using Price = int;
using Qty = int;
using ID = int;

enum class Side : uint8_t
{
    BID = 0,
    ASK = 1
};
struct Order;
using Bids = std::map<Price, std::list<Order>, std::greater<Price>>;
using Asks = std::map<Price, std::list<Order>>;

struct TradeInfo;
using TradeInfoForOrder = std::unordered_map<ID, TradeInfo>;

struct Order
{
    Order(ID _id, Price _price, Qty _qty, Side _side) : id(_id), price(_price), qty(_qty), side(_side) {}

    ID id;
    Price price;
    Qty qty;
    Side side;
};

struct TradeInfo
{
    TradeInfo(Qty _total_qty = 0, Price _total_weighted_price = 0) : 
                                                    total_qty(_total_qty),
                                                    total_weighted_price(_total_weighted_price)
                                                    {}
        Qty total_qty;
        Price total_weighted_price;     // to calculate average price
};

class Exchange {
private:

    Bids _bids;
    Asks _asks;
    TradeInfoForOrder _trade_info_for_order; // lookup table for finding nodes to delete in O(1)

    ID _addBid(Qty qty, Price price);
    ID _addAsk(Qty qty, Price price);

    ID id;

public:
    Exchange() : id(1) {}

    ~Exchange(){}

    // InputOrder receives order, and return assigned order Id.
    // Parameters:
    // int side: 0 is buy, 1 is sell
    // int volume: order's quantity
    // int price: order's price
    // Return:
    // int: order Id
    int inputOrder(Side side, Qty qty, Price price);
    
    // QueryOrderTrade queries order's trade volume and average price.
    // Parameters:
    // int orderId: assigned order Id
    // int averagePrice: return order's average trade price
    // Return:
    // int: return order's trade volume
    int queryOrderTrade(ID orderId, Price& averagePrice);
};
}

int main()
{
    Pan::Exchange ex;
    std::vector<int> orders;
    orders.push_back(ex.inputOrder(Pan::Side(0), 1, 100));
    orders.push_back(ex.inputOrder(Pan::Side(0), 2, 101));
    orders.push_back(ex.inputOrder(Pan::Side(0), 3, 102));
    orders.push_back(ex.inputOrder(Pan::Side(1), 4, 100));
    orders.push_back(ex.inputOrder(Pan::Side(1), 5, 101));
    orders.push_back(ex.inputOrder(Pan::Side(1), 6, 102));
    for (auto& orderId : orders)
    {
        int averagePrice;
        int tradeVolume = ex.queryOrderTrade(orderId, averagePrice);
        std::cout << "orderId: " << orderId << " tradeVolume: " <<
        tradeVolume << " averagePrice: " << averagePrice << std::endl;
    }

    return 0;
}