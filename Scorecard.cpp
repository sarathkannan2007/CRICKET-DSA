#include<iostream>
#include<string>
#include "score.cpp"
using namespace std;
void showTeamScore(struct node *head, string teamName, int teamScore, int wickets)
{
    cout << "\n--------------------------------------\n";
    cout << "        " << teamName << " SCORECARD\n";
    cout << "-----------------------------------------\n";
    cout << "TOTAL : " << teamScore << "-" << wickets << "\n\n";
    cout << "Player            Runs   Wickets\n";
    cout << "----------------------------------------\n";
    temp = head;
    while (temp != NULL)
    {
        cout << temp->playername;
        int nameLen = temp->playername.length();
        for (int i = nameLen; i < 18; i++)
            cout << " ";
        cout << temp->score;
        if (temp->wicket)
            cout << "     OUT";
        cout << endl;
        temp = temp->next;
    }
    cout << "----------------------------------------\n";
}
