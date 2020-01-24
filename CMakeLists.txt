cmake_minimum_required(VERSION 3.15)
project(ecommerce)

set(CMAKE_CXX_STANDARD 14)

add_executable(ecommerce main.cpp Buyer.cpp Buyer.h Seller.cpp Seller.h Item.cpp Item.h Feedback.cpp Feedback.h Address.cpp Address.h Date.cpp Date.h Order.cpp Order.h Manager.cpp Manager.h CUI.cpp CUI.h Account.cpp Account.h BuyerSeller.cpp BuyerSeller.h OFunctions.cpp OFunctions.h)