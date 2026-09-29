#include <iostream>
#include <string>
using namespace std;

class ShoppingCart {
    int customerID;
    double amount;
    string items;
    char category;           // 'P' premium, 'R' regular
public:
    ShoppingCart(int id, double amt, string it, char cat) {
        customerID = id; amount = amt; items = it; category = cat;
    }
    void show() const {
        cout << "Customer " << customerID << " (" << category << "), " << items
             << ": Rs " << amount << endl;
    }
    friend class DiscountManager;    // DiscountManager may read AND change the privates
};

class DiscountManager {
    static constexpr double MIN_AMOUNT = 100.0;   // the bill never goes below this
public:
    double discountRate(const ShoppingCart &c) const {
        double rate = 0;
        if (c.amount >= 5000) rate = 0.15;
        else if (c.amount >= 2000) rate = 0.10;
        else if (c.amount >= 500) rate = 0.05;
        if (c.category == 'P') rate += 0.05;       // premium customers get 5% more
        return rate;
    }
    void apply(ShoppingCart &c) const {
        double rate = discountRate(c);
        double finalAmount = c.amount * (1 - rate);
        if (finalAmount < MIN_AMOUNT) finalAmount = MIN_AMOUNT;
        cout << "  discount " << rate * 100 << "%, final Rs " << finalAmount << endl;
        c.amount = finalAmount;                    // allowed: DiscountManager is a friend
    }
};

int main() {
    ShoppingCart carts[3] = {
        ShoppingCart(1, 6000, "Laptop bag", 'R'),
        ShoppingCart(2, 2500, "Shoes", 'P'),
        ShoppingCart(3, 104, "Pen set", 'P'),
    };
    DiscountManager dm;
    for (int i = 0; i < 3; i++) {
        carts[i].show();
        dm.apply(carts[i]);
    }
    return 0;
}
