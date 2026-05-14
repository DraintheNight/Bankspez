#ifndef ACCOUNT_H
#define ACCOUNT_H


#include <string>
#include <vector>
#include <map>
#include <memory>
#include <stdexcept>
#include <iostream>


class Customer;



class Account : public std::enable_shared_from_this<Account> {
private:
    unsigned id;
    std::string name;
    int dispo;
    static unsigned next_id;
    int balance; 
    std::map<unsigned, std::weak_ptr<Customer> owners;

public:
  
   Account(std::string name, int dispo, int balance, std::shared_ptr<Customer> owner) 
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

    
    virtual ~Account() = default;

    
    virtual int withdraw(int x);
    int deposit(int x);
    
    unsigned get_id() const;
    unsigned owner_count() const;
    
    bool share_account(std::shared_ptr<Customer> new_owner);
    bool remove_owner(unsigned id);

    
    virtual std::string additional_output() const = 0;

    friend std::ostream& operator<<(std::ostream& o, const Account& p);
    unsigned get_id();
    int get_balance();
    bool remove_owner(unsigned id);

};


std::ostream& operator<<(std::ostream& o, const Account& p);

#endif
class Standard_Account : public Account {
public:
    
    using Account::Account;

    
    std::string additional_output() const override{
        std::cout << "Standard"
    };
};
class Special_Account : public Account {
    int fee;
public:
    Special_Account(string name, int dispo, int balance, shared_ptr<Customer> owner,int fee): name{name}, dispo{dispo}, balance{balance}, fee{fee} {
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
    if (fee<= 0) {
        throw std::runtime_error("fee muss größer 0 sein");
    }
    this->id = next_id++;

    owners[owner->get_id()] = owner;
}
std::string additional_output() const override{
        std::cout << "Special"
    };
int withdraw(int x);



    };


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