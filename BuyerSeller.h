#ifndef _BUYERSELLER_H
#define _BUYERSELLER_H
#define _CRT_SECURE_NO_WARNINGS
#include "Buyer.h"
#include "Seller.h"

class BuyerSeller :public Seller, public Buyer
{
public:
    BuyerSeller(const string& username, const string&  password, const string& fname, const string&  lname, Address& address);
	BuyerSeller(const Buyer& otherbuyer, const Seller& otherseller);
    BuyerSeller(const BuyerSeller& other);
    BuyerSeller(const BuyerSeller&& other);
    //virtual ~BuyerSeller();
    const BuyerSeller& operator=(const BuyerSeller& other);
    friend ostream& operator<<(ostream& out, BuyerSeller& bs);
    virtual Account* clone() const override;
    virtual const char *getType() const;
};

#endif // !_BUYERSELLER_H
