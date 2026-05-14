bool Bank_Owner::transfer_bank(Bank_Owner& target){
            if (!this->bank)
                return false;
    target->bank = std::move(this->bank);
    return true;
}
const map<unsigned, shared_ptr<Customer>>& Bank_Owner::get_customers() const
    if(!this->bank)
        throw std::runtime_error("keine customers");
    return customers;
}
void Bank_owner::create_customer(std::string name,string acc_name,int dispo, int balance,
Account_Type type, int fee ){
    if(!this->bank)
        throw std::runtime_error("keine customers");
    bank->create_customer(name, acc_name, dispo, balance, type, fee );
}
