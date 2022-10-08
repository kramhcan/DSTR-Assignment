#include <iostream>
#include <string>

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
        double PreviousStationCost;
        //Next station
        string NextStationID;
        string NextStationName;
        int NextStationDistance;
        double NextStationCost;
        Node* next;
};

//Linked List
class Station {
    Node* head;
    public:
        // void AddStation(Node** head, string newID, string newName, int previousID, string previousName, 
        //                 double previousDistance, double previousCost, string nextID, 
        //                 string nextName, double nextDistance, double nextCost, string position);
        void AddStationFront(Node** head, string newID, string newName, string previousID, string previousName, int previousDistance, double previousCost, string nextID, string nextName, int nextDistance, double nextCost);
        // void AddStationBack(Node** head, string newID, string newName, int previousID, string previousName, double previousDistance, double previousCost, string nextID, string nextName, double nextDistance, double nextCost);
        void ViewAllStations(Node* head);
};

void Station::AddStationFront(Node** head, string newID, string newName, string previousID, string previousName, int previousDistance, double previousCost, string nextID, string nextName, int nextDistance, double nextCost)
{
	Node* newNode = new Node;
	Node* last = *head;

	newNode->StationID = newID;
	newNode->StationName = newName;
	newNode->PreviousStationID = previousID;
	newNode->PreviousStationName = previousName;
	newNode->PreviousStationDistance = previousDistance;
	newNode->PreviousStationCost = previousCost;
	newNode->NextStationID = nextID;
	newNode->NextStationName = nextName;
	newNode->NextStationDistance = nextDistance;
    newNode->NextStationCost = nextCost;
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

void Station::ViewAllStations(Node* head)
{
    Node* curr = head;
    string choice;
    bool IsValid = true;
    
    while(curr!= NULL){
        cout<< "Station ID : " << curr->StationID<< " || Station Name : " << curr -> StationName << " || Previous Station ID : " << curr -> PreviousStationID << " || Previous Station Name : " << curr -> PreviousStationName << endl;
        curr = curr->next;
    }
}

int main()
{
    Node* head = NULL;
    Station station;
    station.AddStationFront(&head, "SS01", "Titiwangsa", "N/A", "N/A", 0, 0, "SS02", "PTWC", 3, 0.4);
    station.AddStationFront(&head, "SS02", "PTWC", "SS01", "Titiwangsa", 3, 0.4, "SS03", "PTWC", 8, 0.8);

    station.ViewAllStations(head);
    return 0;
}

