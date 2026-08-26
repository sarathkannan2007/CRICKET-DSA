#include<iostream>
#include<string>
#include<fstream>
#include<sstream>
using namespace std;
struct Player
{
    int playerID;
    string playerName;
    int age;
    int teamID;
    string role;
    int battingSkill;
    int bowlingSkill;
    int fieldingSkill;
    bool isSubstitute;
    bool isWicketkeeper;

    Player *next;

};
Player *head = nullptr;
Player* createPlayer()
{
    Player *newPlayer = new Player;
    newPlayer->playerID = 0;
    newPlayer->playerName = "";
    newPlayer->age = 0;
    newPlayer->teamID = 0;
    newPlayer->role = "";
    newPlayer->battingSkill = 0;
    newPlayer->bowlingSkill = 0;
    newPlayer->fieldingSkill = 0;
    newPlayer->isSubstitute = false;
    newPlayer->isWicketkeeper = false;
    newPlayer->next = nullptr;
    return newPlayer;
}
bool checkPlayerID(int id)
{
    Player *temp = head;
    while(temp != nullptr)
    {
        if(temp->playerID == id)
        {
            return true;
        }
        temp = temp->next;
    }
    return false;
}
Player *getPlayerByID(int id)
{
    Player *temp = head;
    while(temp != nullptr)
    {
        if(temp->playerID == id)
        {
            return temp;
        }
        temp = temp->next;
    }
    return nullptr;
}
int getNextID()
{
    int maxID = 0;
    Player *temp = head;
    while(temp != nullptr)
    {
        if(temp->playerID > maxID)
        {
            maxID = temp->playerID;
        }
        temp = temp->next;
    }
    return maxID + 1;
}
string trimString(string str)
{
    while(!str.empty() && (str.back() == '\r' || str.back() == '\n' || str.back() == ' '))
        str.pop_back();
    return str;
}
void readCSV()
{
    // Clear existing linked list before loading
    while(head != nullptr)
    {
        Player *del = head;
        head = head->next;
        delete del;
    }

    ifstream file("Player_details.csv");
    if(!file.is_open())
    {
        cout << "Error : Could not open Player_details.csv" << endl;
        return;
    }

    string line;
    getline(file, line); // Skip header row

    while(getline(file, line))
    {
        line = trimString(line);
        if(line.empty()) continue;

        stringstream ss(line);
        string token;
        Player *newPlayer = createPlayer();

        // playerID
        getline(ss, token, ',');
        token = trimString(token);
        if(token.empty()) continue;
        newPlayer->playerID = stoi(token);

        // Player_Name
        getline(ss, token, ',');
        newPlayer->playerName = trimString(token);

        // Age
        getline(ss, token, ',');
        token = trimString(token);
        newPlayer->age = token.empty() ? 0 : stoi(token);

        // Team_ID (can be empty)
        getline(ss, token, ',');
        token = trimString(token);
        newPlayer->teamID = token.empty() ? 0 : stoi(token);

        // Role
        getline(ss, token, ',');
        newPlayer->role = trimString(token);

        // Batting_Skill
        getline(ss, token, ',');
        token = trimString(token);
        newPlayer->battingSkill = token.empty() ? 0 : stoi(token);

        // Bowling_Skill
        getline(ss, token, ',');
        token = trimString(token);
        newPlayer->bowlingSkill = token.empty() ? 0 : stoi(token);

        // Fielding_Skill
        getline(ss, token, ',');
        token = trimString(token);
        newPlayer->fieldingSkill = token.empty() ? 0 : stoi(token);

        // Is_Substitute (can be empty)
        getline(ss, token, ',');
        token = trimString(token);
        newPlayer->isSubstitute = (token == "true");

        // Is_Wicketkeeper (can be empty - last field)
        getline(ss, token);
        token = trimString(token);
        newPlayer->isWicketkeeper = (token == "true");

        // Add to end of linked list
        if(head == nullptr)
        {
            head = newPlayer;
        }
        else
        {
            Player *temp = head;
            while(temp->next != nullptr)
            {
                temp = temp->next;
            }
            temp->next = newPlayer;
        }
    }
    file.close();
    cout << "Player data loaded from CSV successfully." << endl;
}
void writeCSV()
{
    ofstream file("Player_details.csv");
    if(!file.is_open())
    {
        cout << "Error : Could not open Player_details.csv for writing" << endl;
        return;
    }

    file << "playerID,Player_Name,Age,Team_ID,Role,Batting_Skill,Bowling_Skill,Fielding_Skill,Is_Substitute,Is_Wicketkeeper" << endl;

    Player *temp = head;
    while(temp != nullptr)
    {
        file << temp->playerID << ","
             << temp->playerName << ","
             << temp->age << ",";

        if(temp->teamID != 0)
            file << temp->teamID;
        file << ",";

        file << temp->role << ","
             << temp->battingSkill << ","
             << temp->bowlingSkill << ","
             << temp->fieldingSkill << ",";

        if(temp->isSubstitute)
            file << "true";
        file << ",";

        if(temp->isWicketkeeper)
            file << "true";

        file << endl;
        temp = temp->next;
    }
    file.close();
}
void displayPlayers()
{
    if(head == nullptr)
    {
        cout << "No Players To Display" << endl;
        return;
    }
    Player *temp = head;
    while(temp != nullptr)
    {   cout << "----------------------------------------" << endl;
        cout << "Player ID      : " << temp->playerID << endl;
        cout << "Player Name    : " << temp->playerName << endl;
        cout << "Age            : " << temp->age << endl;
        if(temp->teamID != 0)
            cout << "Team ID        : " << temp->teamID << endl;
        else
            cout << "Team ID        : None" << endl;
        cout << "Role           : " << temp->role << endl;
        cout << "Batting Skill  : " << temp->battingSkill << endl;
        cout << "Bowling Skill  : " << temp->bowlingSkill << endl;
        cout << "Fielding Skill : " << temp->fieldingSkill << endl;
        cout << "Substitute     : " << (temp->isSubstitute ? "Yes" : "No") << endl;
        cout << "Wicketkeeper   : " << (temp->isWicketkeeper ? "Yes" : "No") << endl;
        cout << "----------------------------------------" << endl;
        temp = temp->next;
    }
}
void searchPlayer()
{
    cout << "Enter Player ID to Search : ";
    int id;
    cin >> id;
    Player *temp = head;
    if(head == nullptr)
    {
        cout << "No Players To Search" << endl;
        return;
    }
    while(temp != nullptr)
    {
        if(temp->playerID == id)
        {
            cout << "----------------------------------------" << endl;
            cout << "Player ID      : " << temp->playerID << endl;
            cout << "Player Name    : " << temp->playerName << endl;
            cout << "Age            : " << temp->age << endl;
            if(temp->teamID != 0)
                cout << "Team ID        : " << temp->teamID << endl;
            else
                cout << "Team ID        : None" << endl;
            cout << "Role           : " << temp->role << endl;
            cout << "Batting Skill  : " << temp->battingSkill << endl;
            cout << "Bowling Skill  : " << temp->bowlingSkill << endl;
            cout << "Fielding Skill : " << temp->fieldingSkill << endl;
            cout << "Substitute     : " << (temp->isSubstitute ? "Yes" : "No") << endl;
            cout << "Wicketkeeper   : " << (temp->isWicketkeeper ? "Yes" : "No") << endl;
            cout << "----------------------------------------" << endl;
            return;
        }
        temp = temp->next;
    }
    cout << "Player with ID " << id << " not found." << endl;
}
void addPlayersToTeam()
{
    int teamID;
    cout << "Enter Team ID to add players to : ";
    cin >> teamID;

    int choice;
    do
    {
        cout << "\n1. Add Existing Player to Team" << endl;
        cout << "2. Add New Player to Team" << endl;
        cout << "0. Done Adding Players" << endl;
        cout << "Enter your choice : ";
        cin >> choice;

        switch(choice)
        {
            case 1:
            {
                // Display available players not assigned to any team
                cout << "\nAvailable Players (Not in any team) :" << endl;
                cout << "----------------------------------------" << endl;
                Player *temp = head;
                bool found = false;
                while(temp != nullptr)
                {
                    if(temp->teamID == 0)
                    {
                        cout << "ID: " << temp->playerID
                             << " | " << temp->playerName
                             << " | " << temp->role
                             << " | Bat: " << temp->battingSkill
                             << " Bowl: " << temp->bowlingSkill
                             << " Field: " << temp->fieldingSkill << endl;
                        found = true;
                    }
                    temp = temp->next;
                }
                cout << "----------------------------------------" << endl;
                if(!found)
                {
                    cout << "No available players without a team." << endl;
                    break;
                }

                int playerID;
                cout << "Enter Player ID to add : ";
                cin >> playerID;

                Player *player = getPlayerByID(playerID);
                if(player == nullptr)
                {
                    cout << "Player with ID " << playerID << " not found." << endl;
                    break;
                }
                if(player->teamID != 0)
                {
                    cout << "Player is already in Team " << player->teamID << "." << endl;
                    break;
                }

                int roleChoice;
                cout << "1. Main Player" << endl;
                cout << "2. Substitute Player" << endl;
                cout << "3. Wicketkeeper" << endl;
                cout << "Enter player type : ";
                cin >> roleChoice;

                player->teamID = teamID;
                if(roleChoice == 1)
                {
                    player->isSubstitute = false;
                    player->isWicketkeeper = false;
                }
                else if(roleChoice == 2)
                {
                    player->isSubstitute = true;
                    player->isWicketkeeper = false;
                }
                else if(roleChoice == 3)
                {
                    player->isSubstitute = false;
                    player->isWicketkeeper = true;
                }
                else
                {
                    cout << "Invalid choice. Setting as Main Player." << endl;
                    player->isSubstitute = false;
                    player->isWicketkeeper = false;
                }

                writeCSV();
                cout << player->playerName << " added to Team " << teamID << " successfully." << endl;
                break;
            }
            case 2:
            {
                Player *newPlayer = createPlayer();
                newPlayer->playerID = getNextID();
                newPlayer->teamID = teamID;

                cout << "Enter Player Name : ";
                cin.ignore();
                getline(cin, newPlayer->playerName);

                cout << "Enter Age : ";
                cin >> newPlayer->age;

                cout << "Enter Role (Batsman/Bowler/All-Rounder/Wicketkeeper-Batsman) : ";
                cin.ignore();
                getline(cin, newPlayer->role);

                cout << "Enter Batting Skill (0-100) : ";
                cin >> newPlayer->battingSkill;

                cout << "Enter Bowling Skill (0-100) : ";
                cin >> newPlayer->bowlingSkill;

                cout << "Enter Fielding Skill (0-100) : ";
                cin >> newPlayer->fieldingSkill;

                int roleChoice;
                cout << "1. Main Player" << endl;
                cout << "2. Substitute Player" << endl;
                cout << "3. Wicketkeeper" << endl;
                cout << "Enter player type : ";
                cin >> roleChoice;

                if(roleChoice == 1)
                {
                    newPlayer->isSubstitute = false;
                    newPlayer->isWicketkeeper = false;
                }
                else if(roleChoice == 2)
                {
                    newPlayer->isSubstitute = true;
                    newPlayer->isWicketkeeper = false;
                }
                else if(roleChoice == 3)
                {
                    newPlayer->isSubstitute = false;
                    newPlayer->isWicketkeeper = true;
                }
                else
                {
                    cout << "Invalid choice. Setting as Main Player." << endl;
                    newPlayer->isSubstitute = false;
                    newPlayer->isWicketkeeper = false;
                }

                // Add to end of linked list
                if(head == nullptr)
                {
                    head = newPlayer;
                }
                else
                {
                    Player *temp = head;
                    while(temp->next != nullptr)
                    {
                        temp = temp->next;
                    }
                    temp->next = newPlayer;
                }

                writeCSV();
                cout << newPlayer->playerName << " (ID: " << newPlayer->playerID << ") added to Team " << teamID << " successfully." << endl;
                break;
            }
            case 0:
                cout << "Done adding players to Team " << teamID << "." << endl;
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    }while(choice != 0);
}
void deletePlayer()
{
    int id;
    cout << "Enter Player ID to Delete : ";
    cin >> id;

    if(head == nullptr)
    {
        cout << "No Players To Delete" << endl;
        return;
    }
    if(head->playerID == id)
    {
        Player *del = head;
        head = head->next;
        delete del;
        writeCSV();
        cout << "Player Deleted Successfully" << endl;
        return;
    }

    Player *prev = head;
    Player *curr = head->next;
    while(curr != nullptr)
    {
        if(curr->playerID == id)
        {
            prev->next = curr->next;
            delete curr;
            writeCSV();
            cout << "Player Deleted Successfully" << endl;
            return;
        }
        prev = curr;
        curr = curr->next;
    }
    cout << "Player with ID " << id << " not found." << endl;
}
void removePlayerFromTeam()
{
    int id;
    cout << "Enter Player ID to Remove from Team : ";
    cin >> id;

    Player *player = getPlayerByID(id);
    if(player == nullptr)
    {
        cout << "Player with ID " << id << " not found." << endl;
        return;
    }
    if(player->teamID == 0)
    {
        cout << "Player is not assigned to any team." << endl;
        return;
    }

    cout << "Removing " << player->playerName << " from Team " << player->teamID << "..." << endl;
    player->teamID = 0;
    player->isSubstitute = false;
    player->isWicketkeeper = false;
    writeCSV();
    cout << "Player removed from team successfully." << endl;
}
int main()
{
    readCSV();

    int choice;
    do
    {
        cout << "\n1. Display All Players" << endl;
        cout << "2. Search Player" << endl;
        cout << "3. Add Players to Team" << endl;
        cout << "4. Delete Player" << endl;
        cout << "5. Remove Player from Team" << endl;
        cout << "0. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch(choice)
        {
            case 1:
                displayPlayers();
                break;
            case 2:
                searchPlayer();
                break;
            case 3:
                addPlayersToTeam();
                break;
            case 4:
                deletePlayer();
                break;
            case 5:
                removePlayerFromTeam();
                break;
            case 0:
                cout << "Exiting..." << endl;
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    } while(choice != 0);
}