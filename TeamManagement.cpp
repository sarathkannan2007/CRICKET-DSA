#include <iostream>
#include <string>
using namespace std;
struct Team
{
    int TeamID;
    string TeamName;
    string captain;
    string coach;
    string city;
    int matchesPlayed;
    int matchesWon;
    int matchedLost;
    int points;

    Team *next;

};
Team *head = nullptr;
Team* createTeam()
{
    Team *newTeam = new Team;
    newTeam->TeamID = 0;
    newTeam->TeamName = "";
    newTeam->captain = "";
    newTeam->coach = "";
    newTeam->city = "";
    newTeam->matchesPlayed = 0;
    newTeam->matchesWon = 0;
    newTeam->matchedLost = 0;       
    newTeam->points = 0;
    newTeam->next = nullptr;
    return newTeam;
}
bool checkID(int id)
{
    Team *temp = head;
    while(temp != nullptr)
    {
        if(temp->TeamID == id)
        {
            return true;
        }
        temp = temp->next;
    }
    return false;
}
Team *getTeamByID(int id)
{
    Team *temp = head;
    while(temp != nullptr)
    {
        if(temp->TeamID == id)
        {
            return temp;
        }
        temp = temp->next;
    }
    return nullptr;
}

void addTeam()
{
    Team *newTeam = createTeam();
    cout << "Enter Team ID: ";  
    cin>>newTeam->TeamID;
    while(checkID(newTeam->TeamID))
    {
        cout << "Team ID already exists. Please enter a unique Team ID." << endl;
        cin>>newTeam->TeamID;
    }  
    cout << "Enter Team Name: ";
    cin.ignore();
    getline(cin, newTeam->TeamName);
    cout << "Enter Captain Name : ";
    getline(cin, newTeam->captain);
    cout << "Enter Coach Name : ";
    getline(cin, newTeam->coach);
    cout << "Enter City : ";
    getline(cin, newTeam->city);
    do
    {
        cout << "Enter Matches Played : ";
        cin >> newTeam->matchesPlayed;      
        cout << "Enter Matches Won : ";
        cin >> newTeam->matchesWon;
        cout << "Enter Matches Lost : ";
        cin >> newTeam->matchedLost;
        if(newTeam->matchesWon + newTeam->matchedLost > newTeam->matchesPlayed)
        {
            cout << "Error : Inavlid Match Played Statistics" << endl;
        }
    }while(newTeam->matchesWon + newTeam->matchedLost > newTeam->matchesPlayed);
    newTeam->points = (newTeam->matchesWon * 2) ;
    if (head == nullptr)
    {
           head = newTeam;
     }
    else
    {
    Team *temp = head;
    while(temp->next != nullptr)
    {
        temp = temp->next;
    }
    temp->next = newTeam;
    }
    cout << "Team added successfully "<< endl;  
}
void displayTeams()
{
    if( head == nullptr )
    {
        cout<< "No Teams TO Display" << endl;
        return;
    }
    Team *temp= head;
    while(temp != nullptr )
    {   cout << "----------------------------------------" << endl;
        cout << "Team ID : " << temp->TeamID << endl;
        cout << "Team Name : " << temp->TeamName << endl;
        cout << "Captain Name : " << temp->captain << endl;
        cout << "Coach Name : " << temp->coach << endl;
        cout << "City : " << temp->city << endl;
        cout << "Matches Played : " << temp->matchesPlayed << endl;
        cout << "Matches Won : " << temp->matchesWon << endl;
        cout << "Matches Lost : " << temp->matchedLost << endl;
        cout << "Points : " << temp->points<< endl;
        cout << "----------------------------------------" << endl;
        temp = temp->next;
    }
}
void searchTeam()
{
    cout << "Enter Team ID to Search : ";
    int id;
    cin >> id;
    Team *temp = head;
    if ( head == nullptr)
    {
        cout << "No Teams TO Search" << endl;
        return;
    }
    while(temp != nullptr)
    {
        if(temp->TeamID == id)
        {
            cout << "----------------------------------------" << endl;
            cout << "Team ID : " << temp->TeamID << endl;
            cout << "Team Name : " << temp->TeamName << endl;
            cout << "Captain Name : " << temp->captain << endl;
            cout << "Coach Name : " << temp->coach << endl;
            cout << "City : " << temp->city << endl;
            cout << "Matches Played : " << temp->matchesPlayed << endl;
            cout << "Matches Won : " << temp->matchesWon << endl;
            cout << "Matches Lost : " << temp->matchedLost << endl;
            cout << "Points : " << temp->points<< endl;
            cout << "----------------------------------------" << endl;
            return;
        }
        temp = temp->next;
    }
    cout << "Team with ID " << id << " not found." << endl;
}
void updateTeam()
{
    int id;
    cout << "Enter Team ID to Update : ";
    cin >> id;
    Team *temp = head;
    if(head == nullptr )
    {
        cout << "No Team To Update" << endl;
        return;
    }
    while(temp != nullptr)
    {
        if(temp->TeamID == id)
        {
        cout << "Enter New Team Name : ";
        cin.ignore();
        getline(cin, temp->TeamName);
        cout << "Enter New Captain Name : ";
        getline(cin, temp->captain);
        cout << "Enter New Coach Name : ";
        getline(cin, temp->coach);
        cout << "Enter New City : ";
        getline(cin, temp->city);
        do
        {
            cout << "Enter Matches Played : ";
            cin >> temp->matchesPlayed;      
            cout << "Enter Matches Won : ";
            cin >> temp->matchesWon;
            cout << "Enter Matches Lost : ";
            cin >> temp->matchedLost;
            if(temp->matchesWon + temp->matchedLost > temp->matchesPlayed)
            {
                cout << "Error : Inavlid Match Played Statistics" << endl;
            }
        }while(temp->matchesWon + temp->matchedLost > temp->matchesPlayed);
        temp->points = (temp->matchesWon * 2) ;
        cout << "Team Updated Successfully" << endl;
        return;
        }
        temp = temp->next;
    }
    cout << "Team with ID " << id << " not found." << endl;
}
void deleteTeam()
{
    int id;
    cout << "Enter Team ID to Delete : ";
    cin >> id;

    if (head == nullptr)
    {
        cout << "No Team To Delete" << endl;
        return;
    }
    if( head->TeamID == id )
    {
        Team *del = head;
        head  = head->next;
        delete del;
        cout << "Team Deleted Successfully" << endl;
        return;
    }

        Team *prev = head;
        Team *curr = head->next;
        while(curr != nullptr)
        {
            if(curr->TeamID == id)
            {
                prev->next = curr->next;
                delete curr;
                cout << "Team Deleted Successfully" << endl;
                return;
            }
            prev = curr;
            curr = curr->next;
        }
     cout << "Team with ID " << id << " not found." << endl;   
    
}
int main()
{
    int choice;
    do
    {
        cout << "1. Add Team" << endl;
        cout << "2. Display Teams" << endl;
        cout << "3. Search Team" << endl;
        cout << "4. Update Team" << endl;
        cout << "5. Delete Team" << endl;
        cout << "0. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice)
        {
            case 1:
                addTeam();
                break;
            case 2:
                displayTeams();
                break;
            case 3:
                searchTeam();
                break;
            case 4:
                updateTeam();
                break;
            case 5:
                deleteTeam();
                break;
            case 0:
                cout << "Exiting..." << endl;
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    } while (choice != 0);
    
}
