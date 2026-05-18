#include "bank_account.h"
#include "bank_owner.h"
#include <string>
#include <vector>
#include <map>
#include <memory>
#include <stdexcept>
#include <iostream>
bool Bank_Owner::transfer_bank(Bank_Owner& target){

            if (!this->bank)
                return false;
            if(target.bank)
                return false;
    target.bank = std::move(this->bank);
    return true;
}
const std::map<unsigned, std::shared_ptr<Customer>>& Bank_Owner::get_customers() const{
    if(!this->bank)
        throw std::runtime_error("keine customers");
    return bank->get_customers();
}
void Bank_Owner::create_customer(std::string name, std::string acc_name,int dispo, int balance,
Account_Type type, int fee ){
    if(!this->bank)
        throw std::runtime_error("keine customers");
    bank->create_customer(name, acc_name, dispo, balance, type, fee );
}
bool Bank_Owner::create_bank(std::string name){
    if(bank)    
        return false;
    this->bank = std::make_unique<Bank>(name);
    return true;
}

 std::ostream& operator<<(std::ostream& o, const Bank_Owner & bo){
  o << "[";
    if(!bo.bank){
        o << bo.name << "]";
    
    return o;
    }
     o << bo.name << ", " << *bo.bank << "]";
    return o;

 };
