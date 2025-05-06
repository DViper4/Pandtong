#include <vector>
#include <iostream>
#include <limits.h>
#include <algorithm>
#include <cmath>

namespace Pan
{
    // _____________Code exercise 1_____________
    // fibo recursion:
    unsigned int fibo(unsigned int x) {
        if (x == 0)
        throw;
        
        if (x == 1)
        return 1;
        if (x == 2)
        return 1;
        if (x == 3)
        return 2;
        
        return fibo(x-1) + fibo(x-2); 
    }
    
    // fibo template:
    template <int n>
    struct Fibonacci {
        static const int value = Fibonacci<n - 1>::value + Fibonacci<n - 2>::value;
    };
    
    template <>
    struct Fibonacci<0> {
        static const int value = 0;
    };
    
    template <>
    struct Fibonacci<1> {
        static const int value = 1;
    };


    // _____________Code exercise 2_____________
    // Code exercise 2 – Calculate daily prices
    void daily_prices(std::vector<double> prices) {
        double min = std::numeric_limits<double>::max(), max = 0, sum = 0, median;

        for (auto p : prices) {
            sum += p;
            if (min < p)
                min = p;
            if (max > p)
                max = p;
        }

        // to find the median, we can sort the lowest half of the elements, then
        // return the middle element.
        // alternatively, we could use quicksort in an iterative manner.
        std::nth_element(prices.begin(), 
            prices.begin() + prices.size() + 1, prices.end(), std::greater<double>{});
        if(prices.size() % 2 == 1)
            median = prices[prices.size()/2];
        else
            median = (prices[prices.size()/2 - 1] + prices[prices.size()/2]) / 2;

        // std::cout << fmt::format("max: {}, mix: {}, average: {}, mean: {}", 
        //         max, min, sum/prices.size(), median);
        std::cout << "max: " << max;
        std::cout << "min: " << min;
        std::cout << "mean: " << sum/prices.size();
        std::cout << "median: " << median;
    }



    // Code exercise 2 – Dynamic ticks
    double calculateTickPrice(double price) {
        double tick_size;
        if (price < 0.01)
            throw;

        if (price <= 0.5) {
            tick_size = 0.001;
        } else if (price <= 5) {
            tick_size = 0.01;
        } else if (price <= 100) {
           tick_size = 0.5;
        } else {
            tick_size = 1;
        }

        return tick_size;
    }

    enum Side : uint8_t {
        Buy = 0,
        Sell = 1
    };

    double calculateFinalPrice(Side side, double price, int ticks)
    {
        auto tick_size = calculateTickPrice(price);

        double new_price = price + (ticks * tick_size);

        if (side == Side::Sell)
            return std::ceil(new_price / tick_size) * tick_size;
        else
            return std::floor(new_price / tick_size) * tick_size;
    }

} // namespace name

int main () {
    std::cout << calculateFinalPrice(Pan::Side::Buy, 0.0461, -2) << std::endl;
    std::cout << calculateFinalPrice(Pan::Side::Sell, 0.0461, -2) << std::endl;

    std::cout << calculateFinalPrice(Pan::Side::Buy, 7.2, 2) << std::endl;
    std::cout << calculateFinalPrice(Pan::Side::Sell, 7.2, 2) << std::endl;

    return 0;
}