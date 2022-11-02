#include <iostream>
#include <string>
#include <iomanip>
#include <sstream>
#include <algorithm>
#include <ctime>
#include <chrono>

using namespace std;

class Queue {
    public:
        string *username, *password, *firstName, *lastName, *role;
        int capacity, front, rear;

        Queue(int size)
        {
            username = new string[size];
            password = new string[size];
            firstName = new string[size];
            lastName = new string[size];
            role = new string[size];

            front = rear = 0;
            capacity = size;
            // count = new int;
        }
        void Enqueue(string username, string password, string firstName, string lastName, string role);
        void LoginUser(Node* hd, Station st);
        int ValidateLogin(string name, string password);
        void RegisterUser(Node* hd, Station st);
        bool CheckExistingUsername(string usr);
};

void Queue::Enqueue(string usr, string pwd, string fstName, string lstName, string rl)
{
    if(capacity == rear) 
    {
        printf("\nQueue is full\n");
        return;
    }
    else
    {
        username[rear] = usr;
        password[rear] = pwd;
        role[rear] = rl;
        rear++;
    }
    return;
}

int Queue::ValidateLogin(string usr, string pwd)
{
    for (int i = front; i <= rear; i++)
    {
        if (usr == username[i] && pwd == password[i]) {
            if (role[i] == "admin"){ return 1; }
            if (role[i] == "member"){ return 2; }
        }
    }
    return 0;
}

void Queue::RegisterUser(Node* hd, Station st)
{
    string usr, pwd, fstName, lstName;
    cout<<"\nWelcome!\nPlease enter your desired Username : ";
    cin >> usr ;
    if(CheckExistingUsername(usr) != true){
        cout << "\n****Username already taken!****\n";
        return RegisterUser(hd, st);
    }
    cout<<"Please enter your desired Password : ";
    cin >> pwd ;

    cout<<"Please enter your first name : ";
    cin >> fstName ;

    cout<<"Please enter your last name : ";
    cin >> lstName ;

    Enqueue(usr, pwd, fstName, lstName, "member");
    cout<<"New member created!\n";
    return LoginUser(hd, st);
}

bool Queue::CheckExistingUsername(string usr)
{
    for (int i = front; i <= rear; i++)
    {
        if(usr == username[i])
        { return false; }
    }
    return true;
}