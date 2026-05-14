class Bank_Owner{
private:
std::string name;
unique_ptr<Bank> bank;
public:
Bank_Owner(std::string name) : name{name}{
    if(name.empty())
        throw std::runtime_error("name darf nicht leer sein!");
}
bool create_bank(string name);
bool transfer_bank(Bank_Owner& target); 
const map<unsigned, shared_ptr<Customer>>& get_customers() const;
void create_customer(string name,string acc_name,int dispo, int balance,
Account_Type type = Account_Type::STANDARD, int fee = 0);
};
