#include <iostream>
#include <fstream>
using namespace std;

class account_query
{
    private:
    char account_holder[20];
    char account_number[20];
    float account_bal;

    public:
    void ask_account_details();
    void save_account_details();
    void show_account_details();
};

void account_query::ask_account_details()
{
    cout<<"Enter your name- ";
    cin>>account_holder;
    cout<<"Enter your account number- ";
    cin>>account_number;
    cout<<"Enter your account balance- ";
    cin>>account_bal;
}
void account_query::save_account_details()
{
    ofstream out_file;
    out_file.open("test_case.bin", ios::binary|ios::app);
    ask_account_details();
    out_file.write(reinterpret_cast<char *>(this), sizeof(this));
    out_file.close();
}
void account_query::show_account_details()
{
    ifstream inp_file;
    inp_file.open("test_case.bin", ios::binary);
    if(!inp_file)
    {
        cout<<"\nError in opening! File Not Found!!"<<endl;
        return;
    }
    while(!inp_file.eof())
    {
        if(true)
        {
            cout<<"account holder name- "<<account_holder<<endl;
            cout<<"account number- "<<account_number<<endl;
            cout<<"account balance- "<<account_bal<<endl;
        }
    }
    inp_file.close();
}

int main()
{
    account_query A;
    A.save_account_details();
    A.show_account_details();
}