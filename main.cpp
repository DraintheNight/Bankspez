
#include "bank_owner.h"
#include "bank_customer.h"
#include "bank_account.h"
#include "bank.h"
#include <iostream>

int main() {
    try {
        Bank_Owner owner("Anton");
        owner.create_bank("Meine Mac-Bank");
        
        std::cout << "Perfekt! Das Programm startet und die Bank steht!" << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Fehler: " << e.what() << std::endl;
    }
    return 0;
}