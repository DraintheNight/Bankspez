#pragma once

#include <string>
#include <vector>
#include <map>
#include <memory>
#include <stdexcept>
#include <iostream>
#include "bank_account.h"
class Account;
class Bank_Owner;
class Bank;

class Customer : public std::enable_shared_from_this<Customer> {
unsigned id;
std::string name;
std::map<unsigned, std::shared_ptr<Account>> accounts;
static unsigned next_id;
public:
Customer(std::string name): name(name){
    if(name.empty())
        throw std::runtime_error("Name darf nicht leer sein!");
    id=next_id;
    next_id++;
}
void add_account(std::shared_ptr<Account> acc);
unsigned create_account(std::string acc_name,int dispo, int balance,
Account_Type = Account_Type::STANDARD, int fee = 0);
int total_balance() const; 
const std::string& get_name() const;
unsigned get_id() const;
const std::map<unsigned, std::shared_ptr<Account>>& get_accounts() const;
bool share_account(unsigned aid, std::shared_ptr<Customer> new_owner);
bool transfer(int amount,unsigned source_id, std::shared_ptr<Customer> target,unsigned target_id);
void remove_account_from_map(unsigned id);
friend std::ostream& operator<<(std::ostream& o, const Customer& c);
};


