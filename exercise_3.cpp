#include "exercise_3.hpp"

namespace Pan {
    int Exchange::_addBid(Qty qty, Price price) {
        std::vector<Price> price_levels_to_remove;
        for (auto &[curr_bid_price, orders] : _bids)
        {
            if (curr_bid_price < price || qty <= 0)
                break;

            while (orders.size())
            {
                auto &o = orders.back();
                if (qty < o.qty)
                {
                std::cout << "heyy" << std::endl;

                    _trade_info_for_order[o.id].total_qty += qty;
                    _trade_info_for_order[id].total_qty += qty;
                    _trade_info_for_order[o.id].total_weighted_price += (qty*curr_bid_price);
                    _trade_info_for_order[id].total_weighted_price += (qty*curr_bid_price);
                    
                    o.qty -= qty;
                    qty = 0;
                    break;
                }
                if (qty == o.qty)
                {
                std::cout << "heyy" << std::endl;

                    _trade_info_for_order[o.id].total_qty += o.qty;
                    _trade_info_for_order[id].total_qty += o.qty;
                    _trade_info_for_order[o.id].total_weighted_price += (o.qty*curr_bid_price);
                    _trade_info_for_order[id].total_weighted_price += (o.qty*curr_bid_price);
                    
                    orders.pop_back();
                    qty = 0;
                    break;
                }
                // qty > o.qty
                std::cout << "heyy" << std::endl;

                _trade_info_for_order[o.id].total_qty += o.qty;
                _trade_info_for_order[id].total_qty += o.qty;
                _trade_info_for_order[o.id].total_weighted_price += (o.qty*curr_bid_price);
                _trade_info_for_order[id].total_weighted_price += (o.qty*curr_bid_price);

                orders.pop_back();
                qty -= o.qty;
            }

            if (orders.size() == 0)
                price_levels_to_remove.push_back(curr_bid_price);
        }

        for (auto price : price_levels_to_remove)
            _bids.erase(price);

        if (qty)
        {
            _asks[price].emplace_front(id, price, qty, Side::ASK);
        }

        return id++; 
    }

    int Exchange::_addAsk(Qty qty, Price price) {
        std::vector<Price> price_levels_to_remove;
        for (auto &[curr_ask_price, orders] : _asks)
        {
            if (curr_ask_price < price || qty <= 0)
                break;

            while (orders.size())
            {
                auto &o = orders.back();
                if (qty < o.qty)
                {
                std::cout << "heyy" << std::endl;

                    _trade_info_for_order[o.id].total_qty += qty;
                    _trade_info_for_order[id].total_qty += qty;
                    _trade_info_for_order[o.id].total_weighted_price += (qty*curr_ask_price);
                    _trade_info_for_order[id].total_weighted_price += (qty*curr_ask_price);
                    
                    o.qty -= qty;
                    qty = 0;
                    break;
                }
                if (qty == o.qty)
                {
                std::cout << "heyy" << std::endl;

                    _trade_info_for_order[o.id].total_qty += o.qty;
                    _trade_info_for_order[id].total_qty += o.qty;
                    _trade_info_for_order[o.id].total_weighted_price += (o.qty*curr_ask_price);
                    _trade_info_for_order[id].total_weighted_price += (o.qty*curr_ask_price);
                    
                    orders.pop_back();
                    qty = 0;
                    break;
                }
                // qty > o.qty
                std::cout << "heyy" << std::endl;
                _trade_info_for_order[o.id].total_qty += o.qty;
                _trade_info_for_order[id].total_qty += o.qty;
                _trade_info_for_order[o.id].total_weighted_price += (o.qty*curr_ask_price);
                _trade_info_for_order[id].total_weighted_price += (o.qty*curr_ask_price);

                orders.pop_back();
                qty -= o.qty;
            }

            if (orders.size() == 0)
                price_levels_to_remove.push_back(curr_ask_price);
        }

        for (auto price : price_levels_to_remove)
            _asks.erase(price);

        if (qty)
        {
            _asks[price].emplace_front(id, price, qty, Side::ASK);
        }

        return id++; 
    }

    int Exchange::inputOrder(Side side, Qty qty, Price price) {
        if (id == std::numeric_limits<ID>::max())
            throw std::runtime_error("exhausted all id values");

        if (side == Side::BID)
            return _addBid(price, qty);
        else
            return _addAsk(price, qty);
    }

    int Exchange::queryOrderTrade(ID orderId, Price& averagePrice) {
        auto trade_info_for_order = _trade_info_for_order[orderId];
        if (trade_info_for_order.total_qty == 0)
            averagePrice = 0;
        else 
            averagePrice = trade_info_for_order.total_weighted_price / trade_info_for_order.total_qty;

        return trade_info_for_order.total_qty;
    }
}