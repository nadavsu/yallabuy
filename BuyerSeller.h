#ifndef _BUYERSELLER_H
#define _BUYERSELLER_H
#define _CRT_SECURE_NO_WARNINGS
#include "Buyer.h"
#include "Seller.h"
#include "Array.h"

class BuyerSeller : public Seller, public Buyer
{
public:
    BuyerSeller(ifstream& os);
    BuyerSeller(const string& username, const string&  password, const string& fname, const string&  lname, Address& address);
	BuyerSeller(const Buyer& otherbuyer, const Seller& otherseller);
    BuyerSeller(const BuyerSeller& other);
    BuyerSeller(const BuyerSeller&& other);
    //virtual ~BuyerSeller();
    const BuyerSeller& operator=(const BuyerSeller& other);
    friend ostream& operator<<(ostream& out, BuyerSeller& bs);
    friend ifstream& operator>>(ifstream& in, Seller& b);
    virtual Account* clone() const override;
    virtual const string getType() const;
    void toOs(ostream& out) const override;
};

#endif // !_BUYERSELLER_H
