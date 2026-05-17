#include "bank_account.h"
#include "bank_customer.h"


#include <string>
#include <vector>
#include <map>
#include <memory>
#include <stdexcept>
#include <iostream>
int Account::withdraw(int x){
if (x <= 0 || (balance - x) < -dispo) {
 throw std::runtime_error("Withdrawal nich möglich");}
balance -= x;
return balance;
}
int Account::deposit(int x){
    if (x <= 0)
        throw std::runtime_error("Deposit nicht möglich!");
    balance += x;
    return balance;

}
unsigned Account::get_id() const{
    return id;

}
unsigned Account::owner_count() const{
    unsigned cnt = 0;
    std::for_each(owners.begin(), owners.end(), [&cnt](const std::pair<unsigned, std::weak_ptr<Customer>>& entry) {
         if(entry.second.lock())
            cnt++;

});
return cnt;
}
bool Account::share_account(std::shared_ptr<Customer> new_owner){
    if(!new_owner)  
        return false;
    unsigned new_id = new_owner->get_id();
    if (owners.find(new_id) != owners.end()) {
        return false;
    }
    owners[new_id] = new_owner;
    new_owner->add_account(shared_from_this());
    return true;

}
int Account::get_balance(){
    return balance;
}
unsigned Account::get_id(){
    return id;
}
bool Account::remove_owner(unsigned id) {
    
    if (owners.size() <= 1) {
        return false; 
    }

    auto it = owners.find(id);
    if (it == owners.end()) {
        return false; 
    }

    std::shared_ptr<Customer> customer_ptr = it->second.lock();
    if (customer_ptr) {
        customer_ptr->remove_account_from_map(this->get_id());
    }
    owners.erase(it); 

    return true;
}
int Special_Account::withdraw(int x) {


    if (x <= 0) {
        throw std::runtime_error("Withdrawal nicht möglich");
    }
    return Account::withdraw(x + fee);
}
unsigned Account::next_id = 0;

   Account::Account(std::string name, int dispo, int balance, std::shared_ptr<Customer> owner)
    : name{name}, dispo{dispo}, balance{balance} {
    
    if (name.empty()) {
        throw std::runtime_error("Name darf nicht leer sein!");
    }
    if (dispo <= 0 || dispo >= 10000) {
        throw std::runtime_error("Dispo muss > 0 und < 10000 sein!");
    }
    if (balance <= -dispo) {
        throw std::runtime_error("Startbalance muss groesser als -dispo sein!");
    }
    if (!owner) {
        throw std::runtime_error("Ein Konto braucht mindestens einen Besitzer!");
    }

    this->id = next_id++;

    owners[owner->get_id()] = owner;
}
int Account::get_dispo() const{
    return dispo;
}
std::ostream& operator<<(std::ostream& o, const Account& p) {

    o << "[" << p.name << ", " 
      << p.additional_output() << ", " 
      << p.balance << ", " 
      << p.dispo << ", {";

    bool first = true;
    for (const auto& pair : p.owners) {
   
        if (auto s_ptr = pair.second.lock()) { 
            if (!first) {
                o << ", ";
            }

            o << "[" << s_ptr->get_name() << ", " << s_ptr->total_balance() << "]";
            first = false;
        }
    }

    o << "}, " << p.owner_count() << "]";

    return o;
}
std::string Account::get_name(){
    return name;
}