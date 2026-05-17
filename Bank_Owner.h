#pragma once
#include <string>
#include <vector>
#include <map>
#include <memory>
#include <stdexcept>
#include <iostream>
#include "bank_account.h"
#include "bank.h"
#include "bank_customer.h"
#include "bank_owner.h"
class Bank;
class Customer;
class Account;

class Bank_Owner{
private:
std::string name;
std::unique_ptr<Bank> bank;
public:

Bank_Owner(std::string name) : name{name}{
    if(name.empty())
        throw std::runtime_error("name darf nicht leer sein!");
}
bool create_bank(std::string name);
bool transfer_bank(Bank_Owner& target); 
const std::map<unsigned, std::shared_ptr<Customer>>& get_customers() const;
void create_customer(std::string name, std::string acc_name,int dispo, int balance,
Account_Type type = Account_Type::STANDARD, int fee = 0);
};
