#include <iostream>
#include <string>
using namespace std;

class Contact 
{
private:
    string* fullName;  
    string homePhone;
    string workPhone;
    string mobilePhone;
    string additionalInfo;

public:
   
    Contact(string name, string home, string work, string mobile, string info): fullName(new string(name)), homePhone(home), workPhone(work), mobilePhone(mobile), additionalInfo(info) {}

    ~Contact() 
    {
        delete fullName; 
    }

    string getFullName() const 
    {
        return *fullName;
    }

    void display() const 
    {
        cout << "Full Name: " << *fullName << endl;
        cout << "Home Phone: " << homePhone << endl;
        cout << "Work Phone: " << workPhone << endl;
        cout << "Mobile Phone: " << mobilePhone << endl;
        cout << "Additional Info: " << additionalInfo << endl;
    }

    void saveToFile() const
    {
        cout << *fullName << endl;
        cout << homePhone << endl;
        cout << workPhone << endl;
        cout << mobilePhone << endl;
        cout << additionalInfo << endl;
    }

    static Contact* loadFromFile() 
    {
        string name, home, work, mobile, info;
        cout << "Enter Full Name: ";
        getline(cin, name);
        cout << "Enter Home Phone: ";
        getline(cin, home);
        cout << "Enter Work Phone: ";
        getline(cin, work);
        cout << "Enter Mobile Phone: ";
        getline(cin, mobile);
        cout << "Enter Additional Info: ";
        getline(cin, info);
        return new Contact(name, home, work, mobile, info);
    }
};

class PhoneBook 
{
private:
    Contact* contacts[100]; 
    int contactCount;

public:
    
    PhoneBook() : contactCount(0) {}

    ~PhoneBook() 
    {
        for (int i = 0; i < contactCount; ++i) 
        {
            delete contacts[i];
        }
    }

    void addContact(Contact* contact) 
    {
        if (contactCount < 100) 
        {
            contacts[contactCount++] = contact;
        }
        else {
            cout << "Phonebook is full!" << endl;
        }
    }

    void removeContact(const string& name)
    {
        for (int i = 0; i < contactCount; ++i)
        {
            if (contacts[i]->getFullName() == name) 
            {
                delete contacts[i];
                for (int j = i; j < contactCount - 1; ++j) 
                {
                    contacts[j] = contacts[j + 1];
                }
                --contactCount;
                cout << "Contact deleted." << endl;
                return;
            }
        }
        cout << "Contact with this name not found." << endl;
    }

    void searchContact(const string& name) const 
    {
        for (int i = 0; i < contactCount; ++i) 
        {
            if (contacts[i]->getFullName() == name) 
            {
                contacts[i]->display();
                return;
            }
        }
        cout << "Contact with this name not found." << endl;
    }

    void displayAllContacts() const
    {
        if (contactCount == 0)
        {
            cout << "Phonebook is empty." << endl;
            return;
        }

        for (int i = 0; i < contactCount; ++i) 
        {
            contacts[i]->display();
            cout << endl;
        }
    }

    void saveToFile() const
    {
        if (contactCount == 0)
        {
            cout << "Phonebook is empty, nothing to save." << endl;
            return;
        }
        for (int i = 0; i < contactCount; ++i) 
        {
            contacts[i]->saveToFile();
        }
    }
};

int main()
{
    PhoneBook phoneBook;
    int choice; string name;

    do
    {
        cout << "\nPhonebook Menu\n";
        cout << "1. Add Contact\n";
        cout << "2. Remove Contact\n";
        cout << "3. Search Contact\n";
        cout << "4. Display All Contacts\n";
        cout << "5. Save to File (displayed on console)\n";
        cout << "6. Load from File (via console input)\n";
        cout << "0. Exit\n";
        cout << "Choose an option: ";
        cin >> choice;
        cin.ignore();  

        switch (choice) 
        {
        case 1:
            phoneBook.addContact(Contact::loadFromFile());
            break;

        case 2:
            cout << "Enter the Full Name of the contact to remove: ";
            getline(cin, name);
            phoneBook.removeContact(name);
            break;

        case 3:
            cout << "Enter the Full Name of the contact to search: ";
            getline(cin, name);
            phoneBook.searchContact(name);
            break;

        case 4:
            phoneBook.displayAllContacts();
            break;

        case 5:
            phoneBook.saveToFile();
            break;

        case 6:
            cout << "Loading contact from console input..." << endl;
            phoneBook.addContact(Contact::loadFromFile());
            break;

        case 0:
            cout << "Exiting program..." << endl;
            break;

        default:
            cout << "Invalid option. Please try again." << endl;
        }

    } 
    while (choice != 0);

    return 0;
}