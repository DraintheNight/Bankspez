unsigned Customer::next_id = 0;

unsigned Customer::create_account(string acc_name, int dispo, int balance, Account_Type type, int fee) {
    std::shared_ptr<Account> new_acc;
    if(type==Account_Type::STANDARD)
       new_acc = std::make_shared<Standard_Account>{acc_name, dispo, balance, shared_from_this()};
    else {
         new_acc = std::make_shared<Special_Account>{acc_name, dispo, balance, shared_from_this(), fee};
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
const string& Customer::get_name() const{
    return name;
}
const map<unsigned,shared_ptr<Account>>& Customer::get_accounts() const {
    return accounts;
}
bool Customer::share_account(unsigned aid,shared_ptr<Customer> new_owner {
    auto it = accounts.find(aid);
    if(it == accounts.end())
        return false;
   if (found_account->share_account(new_owner)) {
        new_owner->accounts[aid] = found_account; 
        return true;
    }
    return false; 

}
bool Customer::transfer(int amount,unsigned source_id,shared_ptr<Customer> target,unsigned target_id){
    if(source_id == target_id)
        throw std::runtime_error("ID's gleich");
    auto it = accounts.find(source_id);
    if(it_source==accounts.end())
        return false;
    auto it1 = target->accounts.find(target_id);
    if(it_target==target->accounts.end())
        return false;
    shared_ptr<Account> source_acc = it_source->second;
    shared_ptr<Account> target_acc = it_target->second;
    source_acc->withdraw(amount);
    target_acc->deposit(amount);
    return true;
    }
void Customer::remove_account_from_map(unsigned aid) {
    accounts.erase(aid);
}

std::ostream& operator<<(std::ostream& o, const Customer& p) {
  
    o << "[" << p.getName() << ", {";
    bool first = true;
    for (const auto& [id, acc_ptr] : p.getAccounts()) {
        if (!first) {
            o << ", ";
        }
        if (acc_ptr) {
            o << "[" << acc_ptr->getName() << ", " << acc_ptr->owner_count() << "]";
        }
        first = false;
    }
    o << "}, " << p.total_balance() << "]";

    return o;
}
   
