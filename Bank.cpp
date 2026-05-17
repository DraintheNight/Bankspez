
#include "bank_account.h"
#include "bank_customer.h"
#include "bank.h"
#include <string>
#include <vector>
#include <map>
#include <memory>
#include <stdexcept>
#include <iostream>
const std::map<unsigned, std::shared_ptr<Customer>>& Bank::get_customers() const {
    return customers;
}
void Bank::create_customer(std::string name, std::string acc_name,int dispo, int balance,
Account_Type type, int fee) {
   std::shared_ptr<Customer> new_customer = std::make_shared<Customer>(name);
   new_customer->create_account(acc_name, dispo, balance, type, fee );
   customers[new_customer->get_id()] = new_customer;

}
std::ostream& operator<<(std::ostream& o, const Bank& p){
o << "[" << p.name << ", {";
bool first = true; 
        std::for_each(p.customers.begin(), p.customers.end(), [&](const auto& pair){
            if(!first){
                o << ",";
                o << *(pair.second);
        first = false;
    }
});
o << "}]";
return o; 
}
