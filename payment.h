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

    void InsertionSort(PaymentNode** head_ref);
    void SortedInsert(PaymentNode** head_ref, PaymentNode* newNode);

    int GetListSize(PaymentNode* head);
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
        
        try
        {
            id = stoi(last1->PaymentID);
        }
        catch(const std::exception& e)
        {
            // std::cerr << e.what() << '\n';
            cout << "Error converting string to int, please enter whole numbers\n";
            return;
        }
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

//admin view all
void PaymentList::ViewAllPayments(PaymentNode*pHead, string role)
{
    PaymentNode* curr = pHead;
    int count = 0, page = 1;
    int size = GetListSize(pHead);
    string selection;

    cout << "\n*========================================Tickets========================================*\n\n";
    cout    << left << setw(5) << "ID" << left << setw(10) << "User" << left << setw(15) << "First Name" << left << setw(15) << "Start Station" << left
            << setw(15) << "End Station" << endl;
    while (curr != NULL){
        cout << left << setw(5) << curr->PaymentID << left << setw(10) << curr-> Username << left << setw(15) <<  curr-> FirstName << left << setw(15) << curr->StartName << left
            << setw(15) << curr-> EndName << endl;

        count++;
        curr = curr->next;
    }
    cout << "\n*=======================================================================================*\n\n";
    cout << "Enter the Payment ID of the ticket to view the details. Enter 'BACK' to return to menu.\nEnter 'SORT' to sort list by first name.\n";
    cout << "Selection >> ";
    cin >> selection;
    if (selection == "BACK"){ return DisplayAdminMenu(pHead); }
    if (selection == "SORT"){ 
        InsertionSort(&pHead);
        return ViewAllPayments(pHead, role); 
        }
    
    try
    {
        int id = stoi(selection);
        if (id >= 1 && id <= count){
            return ViewPaymentDetails(pHead, role, selection);
        }
    }
    catch(const std::exception& e)
    {
        // std::cerr << e.what() << '\n';
        cout << "Error converting string to int, please enter whole numbers\n";
        return ViewAllPayments(pHead, role);
    }
    
    cout << "***ID Out of Bounds or invalid input!***" << endl;
    return ViewAllPayments(pHead, role);
}

void PaymentList::ViewPayments(PaymentNode*pHead, string role, string searchBy, string searchValue)
{
    PaymentNode* curr = pHead;
    int count = 0, page = 1;
    int size = GetListSize(pHead);
    string selection;

    cout << "\n*========================================Tickets ["<< searchBy << " : " << searchValue <<"]========================================*\n\n";
    cout    << left << setw(5) << "ID" << left << setw(10) << "User" << left << setw(15) << "First Name" << left << setw(15) << "Start Station" << left
            << setw(15) << "End Station" << endl;
    while (curr != NULL){
        if(searchBy == "username" && curr->Username == searchValue){
            cout << left << setw(5) << curr->PaymentID << left << setw(10) << curr-> Username << left << setw(15) <<  curr-> FirstName << left << setw(15) << curr->StartName << left
            << setw(15) << curr-> EndName << endl;
        }
        if(searchBy == "firstName" && curr->FirstName == searchValue){
            cout << left << setw(5) << curr->PaymentID << left << setw(10) << curr-> Username << left << setw(15) <<  curr-> FirstName << left << setw(15) << curr->StartName << left
            << setw(15) << curr-> EndName << endl;
        }
        if(searchBy == "lastName" && curr->LastName == searchValue){
            cout << left << setw(5) << curr->PaymentID << left << setw(10) << curr-> Username << left << setw(15) <<  curr-> FirstName << left << setw(15) << curr->StartName << left
            << setw(15) << curr-> EndName << endl;
        }
        if(searchBy == "startStation" && curr->StartName == searchValue){
            cout << left << setw(5) << curr->PaymentID << left << setw(10) << curr-> Username << left << setw(15) <<  curr-> FirstName << left << setw(15) << curr->StartName << left
            << setw(15) << curr-> EndName << endl;
        }
        if(searchBy == "endStation" && curr->EndName == searchValue){
            cout << left << setw(5) << curr->PaymentID << left << setw(10) << curr-> Username << left << setw(15) <<  curr-> FirstName << left << setw(15) << curr->StartName << left
            << setw(15) << curr-> EndName << endl;
        }
        
        count++;
        curr = curr->next;
    }
    cout << "\n*=======================================================================================*\n\n";
    cout << "Enter the Payment ID of the ticket to view the details.\nEnter 'BACK' to return to menu.\nEnter 'SORT' to sort list by first name.\n";
    cout << "Selection >> ";
    cin >> selection;
    if (selection == "BACK"){ return DisplayAdminMenu(pHead); }
    if (selection == "SORT"){
        InsertionSort(&pHead);
        return DisplayAdminMenu(pHead); 
    }
    try
    {
        int id = stoi(selection);
        if (id >= 1 && id <= count){
            return ViewPaymentDetails(pHead, role, selection);
        }
    }
    catch(const std::exception& e)
    {
        // std::cerr << e.what() << '\n';
        cout << "Error converting string to int, please enter whole numbers\n";
        return ViewAllPayments(pHead, role);
    }
    cout << "***ID Out of Bounds or invalid input!***" << endl;
    return ViewAllPayments(pHead, role);
}

void PaymentList::ViewPaymentsMember(PaymentNode*pHead, string searchValue)
{
    PaymentNode* curr = pHead;
    int count = 0, page = 1;
    int size = GetListSize(pHead);
    string selection;

    cout << "\n*========================================Tickets [User : " << searchValue <<"]========================================*\n\n";
    cout    << left << setw(5) << "ID" << left << setw(10) << "User" << left << setw(15) << "Start Station" << left
            << setw(15) << "End Station" << endl;
    while (curr != NULL){
        if(curr->Username == searchValue){
            cout << left << setw(5) << curr->PaymentID << left << setw(10) << curr-> Username << left << setw(15) << curr->StartName << left
            << setw(15) << curr-> EndName << endl;
        }
        
        count++;
        curr = curr->next;
    }
    cout << "\n*=======================================================================================*\n\n";
    cout << "Enter the Payment ID of the ticket to view the details.\nEnter 'BACK' to return to menu.\n";
    cout << "Selection >> ";
    cin >> selection;
    if (selection == "BACK"){ return DisplayMemberMenu(pHead, searchValue); }
    
    try
    {
        int id = stoi(selection);
        if (id >= 1 && id <= count){
            return ViewPaymentDetails(pHead, searchValue, selection);
        }
    }
    catch(const std::exception& e)
    {
        // std::cerr << e.what() << '\n';
        cout << "Error converting string to int, please enter whole numbers\n";
        return ViewPaymentsMember(pHead, searchValue);
    }
    cout << "***Out of Bounds or invalid input!***" << endl;
    return ViewPaymentsMember(pHead, searchValue);
}

void PaymentList::DisplayMemberMenu(PaymentNode* pHead, string usr)
{
    int selection;
    cout<<"\nWelcome back, "<< usr <<". What do you want to do today?" << endl;
    cout<<"========== Please enter the corresponding option number ==========" << endl;
    cout<<"1. Start New Purchase\n2. View Transaction History\n3. Exit system\n";
    cout<<"==================================================================" <<endl;
    cout<<"Selection >> ";
    cin >> selection;
    //If selection is outside the range of optioons
    if (selection <= 0 || selection > 4) { 
        cout<<"\nInvalid option, please select again. \n";
        return DisplayMemberMenu(pHead, usr);
    }
    if (selection == 1) { return StartPurchaseMenu(pHead, usr);}
    if (selection == 2) { 
        ViewPaymentsMember(pHead, usr);
    }
    if (selection == 3){    
        cout << "Thank you, have a good day.";
        EXIT_SUCCESS;
        return;
    }
}

int PaymentList::GetListSize(PaymentNode* pHead)
{
    int count=0;
    PaymentNode* curr = pHead;
    while (curr != NULL){
        count++;
        curr = curr->next;
    }
    return count;
}

void PaymentList::DeletePayment(PaymentNode** pHead, string id)
{
    // Store head node
    PaymentNode* temp = *pHead;
    PaymentNode* prev = NULL;
     
    // If head node itself holds
    // the id to be deleted
    if (temp != NULL && temp->PaymentID == id)
    {
        *pHead = temp->next; // Changed head
        delete temp;            // free old head
        return;
    }
 
    // Else Search for the id to be deleted,
    // keep track of the previous node as we
    // need to change 'prev->next' */
      else
    {
    while (temp != NULL && temp->PaymentID != id)
    {
        prev = temp;
        temp = temp->next;
    }
 
    // If id was not present in linked list
    if (temp == NULL)
        return;
 
    // Unlink the node from linked list
    prev->next = temp->next;
 
    // Free memory
    delete temp;
    }
}

void PaymentList::EditPaymentDetails(PaymentNode** head, string targetID, string newStartID, string newStartName, string newEndID, string newEndName, int newDuration, string newDeparture, double newCost, string dt)
{
    // Node* curr = new Node;
    PaymentNode* last = *head;

    while (last->PaymentID != targetID)
        last = last->next;

    last->StartID = newStartID;
    last->StartName = newStartName;
    last->EndID = newEndID;
    last->EndName = newEndName;
    last->Duration = newDuration;
    last->DepartureTime = newDeparture;
    last->Amount = newCost;
    last->TransactionDate = dt;
}

void PaymentList::SortedInsert(struct PaymentNode** head_ref, struct PaymentNode* newNode)
{
    PaymentNode* current;
 
    // if list is empty
    if (*head_ref == NULL)
        *head_ref = newNode;
 
    // if the node is to be inserted at the beginning
    // of the doubly linked list
    else if ((*head_ref)->FirstName >= newNode->FirstName) {
        newNode->next = *head_ref;
        newNode->next->prev = newNode;
        *head_ref = newNode;
    }
 
    else {
        current = *head_ref;
 
        // locate the node after which the new node
        // is to be inserted
        while (current->next != NULL &&
               current->next->FirstName < newNode->FirstName)
            current = current->next;
 
        /*Make the appropriate links */
 
        newNode->next = current->next;
 
        // if the new node is not inserted
        // at the end of the list
        if (current->next != NULL)
            newNode->next->prev = newNode;
 
        current->next = newNode;
        newNode->prev = current;
    }
}
 
// function to sort a doubly linked list using insertion sort
void PaymentList::InsertionSort(struct PaymentNode** head_ref)
{
    // Initialize 'sorted' - a sorted doubly linked list
     PaymentNode* sorted = NULL;
 
    // Traverse the given doubly linked list and
    // insert every node to 'sorted'
     PaymentNode* current = *head_ref;
    while (current != NULL) {
 
        // Store next for next iteration
         PaymentNode* next = current->next;
 
        // removing all the links so as to create 'current'
        // as a new node for insertion
        current->prev = current->next = NULL;
 
        // insert current in 'sorted' doubly linked list
        SortedInsert(&sorted, current);
 
        // Update current
        current = next;
    }
 
    // Update head_ref to point to sorted doubly linked list
    *head_ref = sorted;
}