class Customer : public std::enable_shared_from_this{
unsigned id;
string name;
map<unsigned, shared_ptr<Account>> accounts;
static unsigned next_id;
public:
Customer(string name): name(name){
    if(name.empty())
        throw std::runtime_error("Name darf nicht leer sein!");
    id=next_id;
    next_id++;
}
unsigned create_account(string acc_name,int dispo, int balance,
Account_Type = Account_Type::STANDARD, int fee = 0);
int total_balance() const; 
const string& get_name() const;
unsigned get_id() const;
const map<unsigned,shared_ptr<Account>>& get_accounts() const;
bool share_account(unsigned aid,shared_ptr<Customer> new_owner;
bool transfer(int amount,unsigned source_id,shared_ptr<Customer> target,unsigned target_id);
void remove_account_internal(unsigned aid);
friend std::ostream& operator<<(std::ostream& o, const Customer& c);
};


