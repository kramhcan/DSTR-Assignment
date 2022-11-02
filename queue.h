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