#include <iostream>
#include <string>
#include <iomanip>

using namespace std;

//Linked List node -- stations
class Node {
    public:
        string StationID;
        string StationName;
        //Previous station
        string PreviousStationID;
        string PreviousStationName;
        int PreviousStationDistance;
        // double PreviousStationCost;
        //Next station
        string NextStationID;
        string NextStationName;
        int NextStationDistance;
        // double NextStationCost;

        //Linked list pointer
        Node* next;
};

//Linked List
class Station {
    Node* head;
    public:
        // void AddStation(Node** head, string newID, string newName, int previousID, string previousName, 
        //                 double previousDistance, double previousCost, string nextID, 
        //                 string nextName, double nextDistance, double nextCost, string position);
        void AddStationFront(Node** head, string newID, string newName, string previousID, string previousName, int previousDistance, string nextID, string nextName, int nextDistance);
        // void AddStationBack(Node** head, string newID, string newName, int previousID, string previousName, double previousDistance, double previousCost, string nextID, string nextName, double nextDistance, double nextCost);
        void ViewAllStations(Node* head);
        double CalculatePriceByDistance(Node* head, string direction);
        int CalculateTimeByDistance(Node* head, string direction);

        int DisplaySelectionOfPositionsReturnCount(Node* head);
};


class Queue {
    public:
        string* username;
        string* password;
        string* role;

        int capacity, front, rear;
        // int * count;

        Queue(int size)
        {
            username = new string[size];
            password = new string[size];
            role = new string[size];

            front = rear = 0;
            capacity = size;
            // count = new int;
        }
        void Enqueue(string username, string password, string role);
        string LoginUser(string name, string password);
};

#pragma region LinkedList
void Station::AddStationFront(Node** head, string newID, string newName, string previousID, string previousName, int previousDistance, string nextID, string nextName, int nextDistance)
{
	Node* newNode = new Node;
	Node* last = *head;

	newNode->StationID = newID;
	newNode->StationName = newName;
	newNode->PreviousStationID = previousID;
	newNode->PreviousStationName = previousName;
	newNode->PreviousStationDistance = previousDistance;
	// newNode->PreviousStationCost = previousCost;
	newNode->NextStationID = nextID;
	newNode->NextStationName = nextName;
	newNode->NextStationDistance = nextDistance;
    // newNode->NextStationCost = nextCost;
	newNode->next = nullptr;
	if (*head == NULL)
	{
		*head = newNode;
		return;
	}
	while (last->next != NULL)
		last = last->next;
	last->next = newNode;
	return;
}

double Station::CalculatePriceByDistance(Node* head, string direction)
{
    double price = 0.0;
    if (direction == "Forward") {
        // if (head->NextStationDistance == 0) { return 0; }
        price =  head->NextStationDistance * 0.1;
    } else if (direction == "Backward") {
        // if (head->PreviousStationDistance == 0) { return 0; }
        price =  head->PreviousStationDistance * 0.1;
    }
    return price;
}

int Station::CalculateTimeByDistance(Node* head, string direction)
{
    int time = 0;
    if (direction == "Forward") {
        // if (head->NextStationDistance == 0) { return 0; }
        time =  head->NextStationDistance - 1 ;
    } else if (direction == "Backward") {
        // if (head->PreviousStationDistance == 0) { return 0; }
        time =  head->PreviousStationDistance - 1;
    }
    return time;
}

//Displays summary of all stations
void Station::ViewAllStations(Node* head)
{
    Node* curr = head;
    string choice;
    bool IsValid = true;
    
    cout<<"KUALA LUMPUR LIGHT RAIL TRANSIT (LRT) - 'TITIWANGSA -> CHAN SOW LIN' STATION ROUTE \n";

    //Forward linked list traversal
    while(curr!= NULL){
        double price = 0.0;
        price = CalculatePriceByDistance(curr, "Forward");
        cout << "\n==============================\n\n";
        cout << "Station ID : " << curr->StationID <<endl;
        cout << "Station Name : " << curr->StationName <<endl;
        cout << "\n==============================" << endl;

        if (curr->NextStationDistance != 0) {
            cout << "\t\t|" << endl;
            cout << "\t\t| " << curr->NextStationDistance << " KM" << endl;
            cout << "\t\t|" << " RM " << CalculatePriceByDistance(curr, "Forward") << endl;
            cout << "\t\t| " << CalculateTimeByDistance(curr, "Forward") << " minutes\n\t\t|" << endl;
            cout << "\t\tV";
        }

        curr = curr->next;
    }
}

int Station::DisplaySelectionOfPositionsReturnCount(Node* head)
{
    Node* curr = head;
    int count = 0;

    cout << "\n*======================Select Position======================*\n\n";
    while (curr != NULL){
        cout << count << "--->> " <<  endl;
        cout << "     Station ID : " << curr->StationID << " || Station Name : " << curr->StationName <<endl;

        count++;

        if (curr->NextStationDistance == 0){
            cout << count << "--->> " <<  endl;
        }

        curr = curr->next;
    }
    cout << "\n*===========================================================*\n\n";

    return count;
}

#pragma endregion

#pragma region Queue
    void Queue::Enqueue(string usr, string pwd, string rl)
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

    string Queue::LoginUser(string usr, string pwd)
    {
        for (int i = front; i <= rear; i++)
        {
            if (usr == username[i] && pwd == password[i]) {
                return "Yes";
            }
        }
        return "No";
    }

#pragma endregion
int main()
{
    Node* head = NULL;
    Station station;
    station.AddStationFront(&head, "SS01", "Titiwangsa", "N/A", "N/A", 0, "SS02", "PTWC", 4);
    station.AddStationFront(&head, "SS02", "PTWC", "SS01", "Titiwangsa", 4, "SS03", "Sultan Ismail", 8);
    station.AddStationFront(&head, "SS03", "Sultan Ismail", "SS02", "PTWC", 8, "SS04", "Majlis Jamek", 8);
    station.AddStationFront(&head, "SS04", "Majlis Jamek", "SS03", "Sultan Ismail", 8, "SS05", "Plaza Rakyat", 6);
    station.AddStationFront(&head, "SS05", "Plaza Rakyat", "SS04", "Majlis Jamek", 6, "SS06", "Hang Tuah", 10);
    station.AddStationFront(&head, "SS06", "Hang Tuah", "SS05", "Plaza Rakyat", 10, "SS07", "Pudu", 5);
    station.AddStationFront(&head, "SS07", "Pudu", "SS06", "Hang Tuah", 5, "SS08", "Chan Sow Lin", 5);
    station.AddStationFront(&head, "SS08", "Chan Sow Lin", "SS07", "Pudu", 5, "N/A", "N/A", 0);

    // // station.ViewAllStations(head);
    // int test = station.DisplaySelectionOfPositionsReturnCount(head);
    

    Queue q(5);
    q.Enqueue("usr0", "1234", "admin");
    q.Enqueue("usr1", "1234", "admin");
    q.Enqueue("usr2", "1234", "admin");

    string usr, pwd;
    cout << "Username : ";
    cin >> usr;
    cout << "Password : ";
    cin >> pwd;

    cout << q.LoginUser(usr, pwd);


    return 0;
}

