#include<iostream>
#include<fstream>
#define MIN_BALANCE 500
using namespace std;

class Bank_Account
{
    public:
    string fname;
    string lname;
    static int prev_account_num;
    int account_number;
    int balance;

    friend ofstream &operator<<(ofstream &ofs,Bank_Account &b);
    friend ifstream &operator>>(ifstream &ifs,Bank_Account &b);
    
    void inputData()
    {
        cout<<"Please enter your first name:";
        cin>>fname;
        cout<<"enter your last name:";
        cin>>lname;
        cout<<"enter your initial balance:";
        cin>>balance;
    }

    void displayData()
    {
        cout<<"Account Number: "<<account_number<<endl;
        cout<<"Name: "<<fname<<" "<<lname<<endl;
        cout<<"Balance: "<<balance<<endl<<endl;
    }
    
    void NewBankAccount()
    {
        ofstream ofs("Bank.txt",ios::app);
        Bank_Account b;
        prev_account_num++;
        b.account_number=prev_account_num;
        b.inputData();
        ofs<<b;
        ofs.close();

        cout<<"\n\nCONGRATULATIONS New Bank account created\n\n";
        b.displayData();
    }

    void depositMoney(int number, int amount) {
        ifstream ifs("Bank.txt");
        ofstream ofs("Temp.txt");
        Bank_Account b;
        bool found = false;

        while (ifs >> b) {
            if (b.account_number == number) {
                b.balance += amount;
                found = true;
            }
            ofs << b;
        }
        ifs.close();
        ofs.close();

        if (!found) {
            cout << "Account not found!" << endl;
            remove("Temp.txt");
        }

        remove("Bank.txt");
        rename("Temp.txt", "Bank.txt");
    }

    void withdrawMoney(int number, int amount)
    {
        ifstream ifs("Bank.txt");
        ofstream ofs("Temp.txt");

        Bank_Account b;
        bool found=false;
        while (ifs >> b)
        {
            if (b.account_number == number)
            {
                if (b.balance-MIN_BALANCE >= amount)
                {
                    b.balance -= amount;
                }
                else
                {
                    cout << "Insufficient funds!" << endl;
                }
                found=true;
            }
            ofs << b;
        }

        ifs.close();
        ofs.close();

        if (found)
        {
            remove("Bank.txt");
            rename("temp.txt","Bank.txt");
        }
        else{
            cout<<"account not found\n";
            remove("temp.txt");
        }
    }

    void displayallaccounts()
    {
        ifstream ifs("Bank.txt");
        Bank_Account b;

        while(ifs>>b)
        {
            b.displayData();
        }
        ifs.close();
    }

    void EnquiryBalance(int number)
    {
        ifstream ifs("Bank.txt");
        Bank_Account b;
        while(ifs>>b)
        {
            if(b.account_number==number)
            {
                b.displayData();
            }
        }
        ifs.close();
    }
};
int Bank_Account::prev_account_num=0;

ofstream &operator<<(ofstream &ofs,Bank_Account &b)
{
    ofs<<b.account_number<<" "<<b.fname<<" "<<b.lname<<" "<<b.balance<<endl;
    return ofs;
}

ifstream &operator>>(ifstream &ifs,Bank_Account &b)
{
    ifs>>b.account_number>>b.fname>>b.lname>>b.balance;
    return ifs;
}

int main()
{
    Bank_Account b;
    int acc_num,amount;
    ifstream ifs("Bank.txt");
    while(ifs>>b)
    {
        Bank_Account::prev_account_num=b.account_number;
    }
    ifs.close();
    int choice;
    do{
        cout<<"\n\n\n***WELCOME TO DANDY BANK***\n\n\n";
        cout<<"What operation do you want to perform:\n\n";
        cout<<"1. Open an account\n";
        cout<<"2. Balance enquiry\n";
        cout<<"3. Deposit Money\n";
        cout<<"4. Withdraw Money\n";
        cout<<"5. Display all accounts\n";
        cout<<"6. Exit\n\n";
        cout<<"enter your choice: ";
        cin>>choice;

        switch (choice)
        {
            case 1:
            b.NewBankAccount();
            break;

            case 2:
            cout<<"enter account number:";
            cin>>acc_num;
            b.EnquiryBalance(acc_num);
            break;

            case 3:
            cout<<"enter account number:";
            cin>>acc_num;
            cout<<"enter amount to be deposited:";
            cin>>amount;
            
            b.depositMoney(acc_num,amount);
            break;

            case 4:
            cout<<"enter account number:";
            cin>>acc_num;
            cout<<"enter amount to be withdrawn:";
            cin>>amount;
            b.withdrawMoney(acc_num,amount);
            break;

            case 5:
            b.displayallaccounts();
            break;

            case 6:
            cout<<"\nThank you for visiting Dandy Bank\n";
            break;
            default:
            cout<<"Please enter the correct option.";
        }
    }while(choice!=6);
}