#include <iostream>
#include <string>
#include <iomanip>
#include <sstream>
#include <algorithm>
#include <ctime>
#include <chrono>

using namespace std;

class PaymentNode {
    public:
        string PaymentID;
        string Username;
        string FirstName;
        string LastName;
        string UserIC;//*
        string StartID;
        string StartName;
        string EndID;
        string EndName;
        int Duration;
        double Amount;
        string TransactionDate;
        string DepartureTime;//*



        PaymentNode * next;
        PaymentNode * prev;
};

class PaymentList {
    PaymentNode * Head;
    public:
    void AddPayment(PaymentNode** head, string usr, string fst, string lst, string ic, string startID, string startName,string endID, string endName, double amount, int duration, string date, string dpt);
    void ViewPaymentDetails(PaymentNode*head, string role, string id);
    void ViewPaymentDetails(PaymentNode*head, string role, string id, string usr);
    void ViewAllPayments(PaymentNode*head, string role);
    void ViewAllPayments(PaymentNode*head, string role, string id, string usr);
    void ViewPayments(PaymentNode*pHead, string role, string searchBy, string searchValue);
    void ViewPaymentsMember(PaymentNode*pHead, string searchValue);
    void DisplayAdminMenu(PaymentNode* hd);
    void DisplayMemberMenu(PaymentNode* hd, string usr);
    
    //Display start purchase menu -> Select Direction -> Select stations -> Display Ticket details
    //->Confirm purchase -> Add payment
    void StartPurchaseMenu(PaymentNode* hd, string usr);
    void SelectStations(PaymentNode* hd, string direction);
    void DisplayNewTicketDetails(PaymentNode* hd, string usr, string startStID, string endStID, string direction);

    void DeletePayment(PaymentNode** hd, string id);
    void EditPaymentAdmin(PaymentNode* hd, PaymentNode * curr);
    void EditPaymentDetails(PaymentNode** head, string targetID, string newStartID, string newStartName, string newEndID, string newEndName, int newDuration, string newDeparture, double newCost, string dt);

    int GetListSize(PaymentNode* head);
    PaymentNode* SortList(PaymentNode* pHead, string sortBy);
    string Minimum(string Member, PaymentNode* curr);
};

void PaymentList::AddPayment(PaymentNode** pHead, string usr, string fst, string lst, string ic, string startID, string startName,string endID, string endName, double amount, int duration, string date, string dpt)
{
    PaymentNode* newNode = new PaymentNode;
    PaymentNode* last = *pHead;
    PaymentNode* last1 = last;
    int id = 0;

    if (last1 != NULL)
    {
        while (last1->next != NULL)
            last1 = last1->next;
        id = stoi(last1->PaymentID);
    }    
    
    id++;
    stringstream ss;
    string idString;
    ss << id;
    ss >> idString;

    newNode->PaymentID = idString;
    newNode->Username = usr;
    newNode->FirstName = fst;
    newNode->LastName = lst;
    newNode->UserIC = ic;
    newNode->StartID = startID;
    newNode->StartName = startName;
    newNode->EndID = endID;
    newNode->EndName = endName;
    newNode->Duration = duration;
    newNode->Amount = amount;
    newNode->TransactionDate = date;
    newNode->DepartureTime = dpt;
    newNode->next = nullptr;

    if(*pHead == NULL)
    {
        *pHead = newNode;
        return;
    }
    
    while (last->next != NULL)
        last = last->next;

    last->next = newNode;
    newNode->prev = last;
    return; 
}

void PaymentList::ViewPaymentDetails(PaymentNode * pHead, string role, string id)
{
    //admin view
    PaymentNode *curr = pHead;
    int size = GetListSize(pHead);
    int page = 1, tId = 0;
    string input;

    while(curr->PaymentID != id)
        curr = curr->next;
    
    while(page)
    {
        cout << "\n========================Ticket["<<id<<"]========================\n";
        cout << left << setw(30)<< "Ticket ID : " << curr->PaymentID <<endl;
        cout << left << setw(30)<< "Username : " << curr->Username <<endl;
        cout << left << setw(30)<< "First Name : " << curr->FirstName <<endl;
        cout << left << setw(30)<< "Last Name : " << curr->LastName <<endl;
        cout << left << setw(30)<< "Identification Number : " << curr->UserIC <<endl;
        cout << left << setw(30)<< "Last Name : " << curr->LastName <<endl;
        cout << left << setw(30)<< "Start Station ID : " << curr->StartID <<endl;
        cout << left << setw(30)<< "Start Station Name : " << curr->StartName <<endl;
        cout << left << setw(30)<< "End Station ID : " << curr->EndID <<endl;
        cout << left << setw(30)<< "End Station Name : " << curr->EndName <<endl;
        cout << left << setw(30)<< "Estimated Travel Duration : " << curr->Duration <<" minutes" <<endl;
        cout << left << setw(30)<< "Departure Time: " << curr->DepartureTime <<endl;
        cout << left << setw(30)<< "Ticket Cost : " << "RM " << curr->Amount <<endl;
        cout << left << setw(30)<< "Time created : " << curr->TransactionDate << endl;
        cout << "============================================================\n" << endl;
        cout << "[1] Return To List\nEnter 'EDIT' to edit this purchase entry\nEnter 'DELETE' to delete this purchase history.\n";
        cout << "Selection >> ";
        cin >> input;
        if(input == "1"){
            break;
        }
        if(input == "DELETE"){
            cout<<"Are you sure? This action cannot be undone [Y/n]\nInput >> ";
            cin >> input;
            if (input =="Y" || input == "y")
                DeletePayment(&pHead, curr->PaymentID);
            break;
        }
        if(input == "EDIT"){
            return EditPaymentAdmin(pHead, curr);
        }
    }

    if (role == "admin"){ return ViewAllPayments(pHead, role);}
    
    //'role' here is username
    return ViewPaymentsMember(pHead, role);
}