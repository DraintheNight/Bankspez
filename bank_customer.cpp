
#include "bank_account.h"
#include "bank_customer.h"
#include "bank_owner.h"
#include <string>
#include <vector>
#include <map>
#include <memory>
#include <stdexcept>
#include <iostream>
unsigned Customer::next_id = 0;


unsigned Customer::create_account(std::string acc_name, int dispo, int balance, Account_Type type, int fee) {
    std::shared_ptr<Account> new_acc;
    if(type==Account_Type::STANDARD)
       new_acc = std::make_shared<Standard_Account>(acc_name, dispo, balance, shared_from_this());
    else {
         new_acc = std::make_shared<Special_Account>(acc_name, dispo, balance, shared_from_this(), fee);
    }
    unsigned this_id = new_acc->get_id();
    accounts[this_id] = new_acc;
    return this_id;
}
int Customer::total_balance() const{
        int sum = 0;
        std::for_each(accounts.begin(), accounts.end(), [&sum](const auto& entry){
            sum+= entry.second->get_balance();
        });
        return sum;
}
unsigned Customer::get_id() const{
    return this->id;
}
const std::string& Customer::get_name() const{
    return name;
}
const std::map<unsigned, std::shared_ptr<Account>>& Customer::get_accounts() const {
    return accounts;
}
bool Customer::share_account(unsigned aid, std::shared_ptr<Customer> new_owner) {
    auto it = accounts.find(aid);
    if(it == accounts.end()) {
        return false;
    }
    if (it->second->share_account(new_owner)) {
        new_owner->accounts[aid] = it->second; 
        return true;
    }
    return false; 
}
void Customer::remove_account_from_map(unsigned id){
    accounts.erase(id);

}
bool Customer::transfer(int amount, unsigned source_id, std::shared_ptr<Customer> target, unsigned target_id){
    if(amount <= 0)
        return false;
    if(source_id == target_id) {
        throw std::runtime_error("IDs sind identisch!");
    }

    auto it_source = accounts.find(source_id);
    if(it_source == accounts.end()) {
        return false;
    }
    auto it_target = target->accounts.find(target_id);
    if(it_target == target->accounts.end()) {
        return false;
    }
    
    std::shared_ptr<Account> source_acc = it_source->second;
    std::shared_ptr<Account> target_acc = it_target->second;
    try {
    source_acc->withdraw(amount);
    target_acc->deposit(amount);
    return true;
    }
    catch (const std::runtime_error&){
        return false;
    }
}

std::ostream& operator<<(std::ostream& o, const Customer& p) {
  
    o << "[" << p.get_name() << ", {";
    bool first = true;
    for (const auto& [id, acc_ptr] : p.get_accounts()) {
        if (!first) {
            o << ", ";
        }
        if (acc_ptr) {
            o << "[" << acc_ptr->get_name() << ", " << acc_ptr->owner_count() << "]";
        }
        first = false;
    }
    o << "}, " << p.total_balance() << "]";

    return o;
}
void Customer::add_account(std::shared_ptr<Account> acc) {
    if (acc) {
        accounts[acc->get_id()] = acc;
    }
}
