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

};
}
bool Account::share_account(shared_ptr<Customer> new_owner){
    if(!new_owner)    git 
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
int Special_Account::withdraw(int x){
    if(balance-(x+fee)>=-dispo&&x>0){
        balance-=(x+fee);
        return balance;}
    throw std::runtime_error("Withdrawal nicht möglich");
}
unsigned Account::next_id = 0;
