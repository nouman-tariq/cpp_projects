#include <iostream>
#include <fstream>
using namespace std;

class account_query
{
    private:
    char first_name[10];
    char last_name[10];
    char account_number[20];
    float account_bal;

    public:
    void read_data();
    void show_data();
    void write_rec();
    void read_rec();
    void search_rec();
    void edit_rec();
    void delete_rec();
};

void account_query::read_data()
{
    cout<<"Enter your first name- ";
    cin>>first_name;
    cout<<"Enter your last name- ";
    cin>>last_name;
    cout<<"Enter your account number- ";
    cin>>account_number;
    cout<<"Enter your account balance- ";
    cin>>account_bal;
}
void account_query::show_data()
{
    cout<<"Account number- "<<account_number<<endl;
    cout<<"First name- "<<first_name<<endl;
    cout<<"Last name- "<<last_name<<endl;
    cout<<"Current balance- "<<account_bal<<endl;
    cout<<"_______________________________"<<endl;
}
void account_query::write_rec()
{
    ofstream out_file;
    out_file.open("test_case.bin", ios::binary|ios::app);
    read_data();
    out_file.write(reinterpret_cast<char *>(this), sizeof(*this));
    out_file.close();
}
void account_query::read_rec()
{
    ifstream in_file;
    in_file.open("test_case.bin", ios::binary);
    if(!in_file)
    {
        cout<<"\nError in opening! File Not Found!!"<<endl;
        return;
    }
    while(!in_file.eof())
    {
        if(in_file.read(reinterpret_cast<char *>(this), sizeof(*this)))
        {
            show_data();
        }
    }
    in_file.close();
}
void account_query::search_rec()
{
    int n;
    ifstream infile;
    infile.open("test_case.bin", ios::binary);
    if (!infile)
    {
        cout<<"Error in opening the file!";
        return;
    }

    infile.seekg(0, ios::end);
    int total_records = infile.tellg()/sizeof(*this);
    cout<<"\nThere are "<<total_records<<"number of records";
    cout<<"\n Enter the record number to search: ";
    cin>>n;

    infile.seekg((n-1)*sizeof(*this));
    infile.read(reinterpret_cast<char *>(this), sizeof(*this));
    show_data();
    
}
void account_query::edit_rec()
{
    int n;
    fstream iofile;
    iofile.open("test_case.bin", ios::binary|ios::in);
    if(!iofile)
    {
        cout<<"\n Error in opening file!";
        return;
    }

    iofile.seekg(0, ios::end);
    int total_records = iofile.tellg()/sizeof(*this);
    cout<<"\nThere are "<<total_records<<"number of records";
    cout<<"\nEnter record number to edit: ";
    cin>>n;

    iofile.seekg((n-1)*sizeof(*this));
    iofile.read(reinterpret_cast<char *>(this), sizeof(*this));
    cout<<"Record "<<n<<" has following data:"<<endl;
    show_data();
    iofile.close();
    iofile.open("test_case.bin", ios::out|ios::in|ios::binary);
    iofile.seekp((n-1)*sizeof(*this));
    cout<<"\nEnter the data to modify "<<endl;
    read_data();
    iofile.write(reinterpret_cast<char *>(this), sizeof(*this));
}
void account_query::delete_rec()
{
    int n;
    ifstream infile;
    infile.open("test_case.bin", ios::binary);
    if(!infile)
    {
        cout<<"\nError loading the file- "<<endl;
        return;
    }
    infile.seekg(0, ios::end);
    int total_records = infile.tellg()/sizeof(*this);
    cout<<"\nTotal number of records "<<total_records<<endl;
    cout<<"Which record to delete ?";
    cin>>n;
    fstream tmpfile;
    tmpfile.open("tmpfile.bin", ios::binary|ios::out);
    infile.seekg(0);
    for (size_t i = 0; i < total_records; i++)
    {
        infile.read(reinterpret_cast<char *>(this), sizeof(*this));
        if (i==(n-1)))
        {
            continue;
        }
        tmpfile.write(reinterpret_cast<char *>(this), sizeof(*this));
    }
    infile.close();
    tmpfile.close();
    remove("test_case.bin");
    rename("tmpfile.bin", "test_case.bin");

}


int main()
{
    account_query A;
    int choice;
    cout<<"***Acount Information System***"<<endl;
    while(true)
    {
        cout<<"Select one option below ";
        cout<<"\n\t1-->Add record to file";
        cout<<"\n\t2-->Show record from file";
        cout<<"\n\t3-->Search Record from file";
        cout<<"\n\t4-->Update Record";
        cout<<"\n\t5-->Delete Record";
        cout<<"\n\t6-->Quit";
        cout<<"\nEnter your choice: ";
        cin>>choice;
        switch(choice)
        {
        case 1:
            A.write_rec();
            break;
        case 2:
            A.read_rec();
            break;
        case 3:
            A.search_rec();
            break;
        case 4:
            A.edit_rec();
            break;
        case 5:
            A.delete_rec();
            break;
        case 6:
            exit(0);
            break;
        default:
            cout<<"\nEnter corret choice";
            exit(0);
        }
    }
    system("pause");
    return 0;
}