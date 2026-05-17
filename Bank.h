
#pragma once
#include <string>
#include <vector>
#include <map>
#include <memory>
#include <stdexcept>
#include <iostream>
#include "bank_account.h"
class Customer;
class Bank{
std::string name;
std::map<unsigned, std::shared_ptr<Customer>> customers;
public:
Bank(std::string name): name{name}{
    if(name.empty())
    throw std::runtime_error("name darf nicht leer sein");
}
const std::map<unsigned, std::shared_ptr<Customer>>& get_customers() const;
void create_customer(std::string name,std::string acc_name,int dispo, int balance,
Account_Type = Account_Type::STANDARD, int fee = 0); 
friend std::ostream& operator<<(std::ostream& o, const Bank& p);
};
