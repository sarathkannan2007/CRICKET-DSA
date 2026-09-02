#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;

struct Player
{
    int jersey;
    char name[50];
    bool out;
};

int main()
{
    Player team[11];

    ifstream file("players.csv");

    string line;
    int i = 0;

    while(getline(file, line) && i < 11)
    {
        int j = 0;
        char jersey[10];
        char name[50];

        // Read jersey number
        while(line[j] != ',')
        {
            jersey[j] = line[j];
            j++;
        }

        jersey[j] = '\0';

        j++;

        // Read player name
        int k = 0;

        while(line[j] != '\0')
        {
            name[k] = line[j];
            k++;
            j++;
        }

        name[k] = '\0';

        team[i].jersey = atoi(jersey);

        strcpy(team[i].name, name);

        team[i].out = false;

        i++;
    }

    file.close();

    // Two batsmen currently batting
    Player *batsman1 = &team[0];
    Player *batsman2 = &team[1];

    int nextBatsman = 2;
    int choice;

    while(nextBatsman <= 10)
    {
        cout << "\nCurrent Batsmen\n";
        cout << "1. " << batsman1->name << endl;
        cout << "2. " << batsman2->name << endl;

        cout << "\nWho got out?\n";
        cout << "1. " << batsman1->name << endl;
        cout << "2. " << batsman2->name << endl;
        cout << "3. End Innings\n";

        cin >> choice;

        if(choice == 3)
            break;

        if(choice == 1)
        {
            batsman1->out = true;

            cout << batsman1->name << " is OUT\n";

            batsman1 = &team[nextBatsman];
            nextBatsman++;
        }
        else if(choice == 2)
        {
            batsman2->out = true;

            cout << batsman2->name << " is OUT\n";

            batsman2 = &team[nextBatsman];
            nextBatsman++;
        }
        else
        {
            cout << "Invalid Choice\n";
        }

        if(nextBatsman > 10)
        {
            cout << "\nNo more batsmen left.\n";
            break;
        }
    }

    cout << "\nCurrent Players at Crease\n";
    cout << "Striker     : " << batsman1->name << endl;
    cout << "Non-Striker : " << batsman2->name << endl;

    return 0;
}
