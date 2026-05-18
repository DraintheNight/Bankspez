#pragma once

#include <string>
#include <vector>
#include <map>
#include <memory>
#include <stdexcept>
#include <iostream>


enum class Account_Type{ STANDARD, SPECIAL };
class Customer;

class Customer;
class Bank_owner;
class Bank;

class Account : public std::enable_shared_from_this<Account> {
private:
    unsigned id;
    std::string name;
    int dispo;
    static unsigned next_id;
    int balance; 
    std::map<unsigned, std::weak_ptr<Customer>> owners;

public:
  
   Account(std::string name, int dispo, int balance, std::shared_ptr<Customer> owner);
    

    
    virtual ~Account() = default;

    
    virtual int withdraw(int x);
    int deposit(int x);
    
    unsigned get_id() const;
    unsigned owner_count() const;
    int get_dispo() const; 
    
    bool share_account(std::shared_ptr<Customer> new_owner);
    bool remove_owner(unsigned id);

    
    virtual std::string additional_output() const = 0;

    friend std::ostream& operator<<(std::ostream& o, const Account& p);
    
    int get_balance() const ;
    std::string get_name() const ;


};



class Standard_Account : public Account {
public:
    
    using Account::Account;

    
    std::string additional_output() const override{
        return "Standard";
    };
};
class Special_Account : public Account {
    int fee;
public:
    Special_Account(std::string name, int dispo, int balance, std::shared_ptr<Customer> owner, int fee)
        : Account(name, dispo, balance, owner), fee{fee} 
    {
       
        if (fee <= 0) {
            throw std::runtime_error("fee muss groesser 0 sein");
        }
    }
std::string additional_output() const override{
        return "Special, " + std::to_string(fee);
    };
int withdraw(int x) override;



    };

std::ostream& operator<<(std::ostream& o, const Account_Type& type);