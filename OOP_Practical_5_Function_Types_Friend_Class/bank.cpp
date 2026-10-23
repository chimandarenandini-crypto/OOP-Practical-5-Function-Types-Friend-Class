#include <iostream>
#include <string>
using namespace std;
 
// Class that represents a real-life bank account
class BankAccount {
private:
    int accNo;
    string name;
    double balance;
    static int totalAccounts;      // static data member (shared by all objects)
 
public:
    // Constructor: parameter names are same as data members,
    // so we use the 'this' pointer to tell them apart
    BankAccount(int accNo, string name, double balance) {
        this->accNo = accNo;
        this->name = name;
        this->balance = balance;
        totalAccounts++;           // one more account created
    }
 
    // Returns *this so that calls can be chained (this pointer)
    BankAccount& deposit(double amount) {
        this->balance = this->balance + amount;
        return *this;
    }
 
    BankAccount& withdraw(double amount) {
        if (amount <= balance)
            balance = balance - amount;
        else
            cout << "Insufficient balance for " << name << endl;
        return *this;
    }
 
    // Inline function (declared here, defined below with 'inline')
    inline double calculateInterest(double rate);
 
    // Static member function: works without any object
    static int getTotalAccounts() {
        return totalAccounts;
    }
 
    void display() {
        cout << "Acc No: " << accNo << " | Name: " << name
             << " | Balance: " << balance << endl;
        cout << "Address of this object (this pointer): " << this << endl;
    }
 
    // Friend class: Auditor can access private members of BankAccount
    friend class Auditor;
};
 
// Definition of static data member (must be done outside the class)
int BankAccount::totalAccounts = 0;
 
// Inline function definition
inline double BankAccount::calculateInterest(double rate) {
    return (balance * rate) / 100;
}
 
// Auditor is a friend of BankAccount
class Auditor {
public:
    void audit(BankAccount &acc) {
        cout << "[Auditor] Checking account of " << acc.name << endl;
        cout << "[Auditor] Private balance = " << acc.balance << endl;
        if (acc.balance < 1000)
            cout << "[Auditor] Warning: Low balance!" << endl;
        else
            cout << "[Auditor] Balance is fine." << endl;
    }
};
 
int main() {
    cout << "Accounts at start: " << BankAccount::getTotalAccounts() << endl;
 
    BankAccount a1(101, "Rahul", 5000);
    BankAccount a2(102, "Sneha", 800);
 
    cout << "\n--- Account Details ---" << endl;
    a1.display();
    a2.display();
 
    cout << "\n--- Function chaining using this pointer ---" << endl;
    a1.deposit(2000).withdraw(1500);
    a1.display();
 
    cout << "\n--- Inline function ---" << endl;
    cout << "Interest on Rahul's account at 5%: " << a1.calculateInterest(5) << endl;
 
    cout << "\n--- Friend class ---" << endl;
    Auditor aud;
    aud.audit(a1);
    aud.audit(a2);
 
    cout << "\n--- Static member function ---" << endl;
    cout << "Total accounts created: " << BankAccount::getTotalAccounts() << endl;
 
    return 0;
}

