#IFNDEF Bank_H
#DEFINE BANK_H
class Bank{
std::string name;
map<unsigned, shared_ptr<Customer>> customers;
public:
Bank(std::string name): name{name}{
    if(name.empty())
    throw std::runtime_error("name darf nicht leer sein");
}
const map<unsigned, shared_ptr<Customer>>& get_customers() const;
void create_customer(string name,string acc_name,int dispo, int balance,
Account_Type = Account_Type::STANDARD, int fee = 0); 
friend std::ostream& operator<<(std::ostream& o, const Bank& p);
};
#ENDIF