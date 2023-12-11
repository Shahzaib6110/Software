#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

class Account {
private:
    int accountNumber;
    std::string accountHolder;
    std::string password;
    double balance;

public:
    Account(int number, const std::string& holder, const std::string& pwd, double initialBalance)
        : accountNumber(number), accountHolder(holder), password(pwd), balance(initialBalance) {}

    int getAccountNumber() const {
        return accountNumber;
    }

    const std::string& getAccountHolder() const {
        return accountHolder;
    }

    double getBalance() const {
        return balance;
    }

    bool validatePassword(const std::string& pwd) const {
        return password == pwd;
    }

    void changePassword(const std::string& newPwd) {
        password = newPwd;
        std::cout << "Password changed successfully." << std::endl;
    }

    void deposit(double amount) {
        balance += amount;
        std::cout << "Deposit successful. New balance: " << balance << std::endl;
    }

    void withdraw(double amount) {
        if (balance >= amount) {
            balance -= amount;
            std::cout << "Withdrawal successful. New balance: " << balance << std::endl;
        } else {
            std::cout << "Insufficient funds for withdrawal." << std::endl;
        }
    }

    void displayAccountInfo() const {
        std::cout << "Account Number: " << accountNumber << ", Holder: "
                  << accountHolder << ", Balance: " << balance << std::endl;
    }
};

class Bank {
private:
    std::vector<Account> accounts;

public:
    void addAccount(const Account& account) {
        accounts.push_back(account);
    }

    Account* findAccount(int accountNumber) {
        for (auto& account : accounts) {
            if (account.getAccountNumber() == accountNumber) {
                return &account;
            }
        }
        return nullptr;
    }

    Account* authenticateUser(int accountNumber, const std::string& password) {
        Account* account = findAccount(accountNumber);
        if (account && account->validatePassword(password)) {
            return account;
        }
        return nullptr;
    }
};

// Function to generate a random account number (for demonstration purposes)
int generateAccountNumber() {
    srand(static_cast<unsigned>(time(nullptr)));
    return rand() % 9000 + 1000; // Generates a 4-digit account number
}

int main() {
    Bank bank;

    // Create and add an initial account (for demonstration purposes)
    Account initialAccount(generateAccountNumber(), "John Doe", "pass123", 1000.0);
    bank.addAccount(initialAccount);

    // User interaction loop
    while (true) {
        std::cout << "\n1. Open a new account\n2. Login\n3. Exit\n";
        int choice;
        std::cin >> choice;

        switch (choice) {
            case 1: {
                // Open a new account
                std::string holder, password;
                double initialBalance;

				start:
                std::cout << "Enter your name: ";
                std::cin.ignore(); // Ignore newline from previous input
                std::getline(std::cin, holder);
                if ( (holder >= "a" && holder <= "z") || (holder >= "A" && holder <= "Z"))
			{
                std::cout << "Set a password: ";
                std::cin >> password;
				
				ib:
                std::cout << "Enter initial balance: ";
                if (!(std::cin >> initialBalance)) 
				{
        	    std::cin.clear();  // Clear the error flag
        	    while (std::cin.get() != '\n') ;  // Discard invalid input
        	    std::cout << "Invalid input. Please enter a valid integer.\n";
        	    goto ib;
        		}
        	
                // Generate a new account number
                int newAccountNumber = generateAccountNumber();

                // Create and add the new account to the bank
                Account newAccount(newAccountNumber, holder, password, initialBalance);
                bank.addAccount(newAccount);

                std::cout << "Account opened successfully. Your account number is: " << newAccountNumber << std::endl;
                break;
            }
            else{
            	std::cout << "Enter Character only..." << std::endl << std::endl;
            	goto start;
			}
        }

            case 2: {
                // Login
                int accountNumber;
                std::string password;

                std::cout << "Enter your account number: ";
                std::cin >> accountNumber;

                std::cout << "Enter your password: ";
                std::cin >> password;

                Account* loggedInAccount = bank.authenticateUser(accountNumber, password);

                if (loggedInAccount) {
                    std::cout << "Login successful. Welcome, " << loggedInAccount->getAccountHolder() << "!" << std::endl;

                    // User-specific operations
                    while (true) {
                        std::cout << "\n1. Deposit\n2. Withdraw\n3. View Account Info\n4. Change Password\n5. Logout\n";
                        int userChoice;
                        std::cin >> userChoice;

                        switch (userChoice) {
                            case 1: {
                                // Deposit
                                double depositAmount;
                                std::cout << "Enter deposit amount: ";
                                std::cin >> depositAmount;
                                loggedInAccount->deposit(depositAmount);
                                break;
                            }

                            case 2: {
                                // Withdraw
                                double withdrawAmount;
                                std::cout << "Enter withdrawal amount: ";
                                std::cin >> withdrawAmount;
                                loggedInAccount->withdraw(withdrawAmount);
                                break;
                            }

                            case 3:
                                // View Account Info
                                loggedInAccount->displayAccountInfo();
                                break;

                            case 4: {
                                // Change Password
                                std::string newPassword;
                                std::cout << "Enter new password: ";
                                std::cin >> newPassword;
                                loggedInAccount->changePassword(newPassword);
                                break;
                            }

                            case 5:
                                // Logout
                                std::cout << "Logout successful. Goodbye, " << loggedInAccount->getAccountHolder() << "!"
                                          << std::endl;
                                break;
                        }

                        if (userChoice == 5) {
                            break; // Break out of the user-specific operations loop when logging out
                        }
                    }
                } else {
                    std::cout << "Invalid account number or password. Login failed." << std::endl;
                }

                break;
            }

            case 3:
                // Exit
                std::cout << "Exiting program. Goodbye!" << std::endl;
                return 0;

            default:
                std::cout << "Invalid choice. Please enter a valid option." << std::endl;
        }
    }

    return 0;
}