#include <iostream>
#include <stdlib.h>
#include <string>

using namespace std;

struct node
{
    int playernum;
    string playername;
    int score;
    int wicket;
    string team;
    struct node *next;
};

struct node *alloc()
{
    struct node *nnode = (struct node *)malloc(sizeof(struct node));
    return nnode;
}

struct node *hteam1 = NULL;
struct node *tteam1 = NULL;

struct node *hteam2 = NULL;
struct node *tteam2 = NULL;

struct node *temp = NULL;

void addTeam1(string pnn, int pn, string tm)
{
    struct node *newnode = alloc();

    newnode->playername = pnn;
    newnode->playernum = pn;
    newnode->score = 0;
    newnode->wicket = 0;
    newnode->team = tm;
    newnode->next = NULL;

    if(hteam1 == NULL)
    {
        hteam1 = newnode;
        tteam1 = newnode;
    }
    else
    {
        tteam1->next = newnode;
        tteam1 = newnode;
    }
}

void addTeam2(string pnn, int pn, string tm)
{
    struct node *newnode = alloc();

    newnode->playername = pnn;
    newnode->playernum = pn;
    newnode->score = 0;
    newnode->wicket = 0;
    newnode->team = tm;
    newnode->next = NULL;

    if(hteam2 == NULL)
    {
        hteam2 = newnode;
        tteam2 = newnode;
    }
    else
    {
        tteam2->next = newnode;
        tteam2 = newnode;
    }
}

void updateScore(struct node *head,int pn,int runs)
{
    temp = head;

    while(temp != NULL)
    {
        if(temp->playernum == pn)
        {
            temp->score += runs;
            return;
        }

        temp = temp->next;
    }
}

void updateWicket(struct node *head,int pn)
{
    temp = head;

    while(temp != NULL)
    {
        if(temp->playernum == pn)
        {
            temp->wicket++;
            return;
        }

        temp = temp->next;
    }
}

node* getPlayer(struct node *head,int pn)
{
    temp = head;

    while(temp != NULL)
    {
        if(temp->playernum == pn)
            return temp;

        temp = temp->next;
    }

    return NULL;
}

void displayTeam1()
{
    temp = hteam1;

    cout << "\n========== TEAM 1 ==========\n";

    while(temp != NULL)
    {
        cout << temp->playernum << "  "
             << temp->playername
             << "  Runs: " << temp->score
             << "  Wickets: " << temp->wicket
             << endl;

        temp = temp->next;
    }
}

void displayTeam2()
{
    temp = hteam2;

    cout << "\n========== TEAM 2 ==========\n";

    while(temp != NULL)
    {
        cout << temp->playernum << "  "
             << temp->playername
             << "  Runs: " << temp->score
             << "  Wickets: " << temp->wicket
             << endl;

        temp = temp->next;
    }
}

void delTeam1()
{
    if(hteam1 == NULL)
        return;

    if(hteam1 == tteam1)
    {
        free(hteam1);
        hteam1 = NULL;
        tteam1 = NULL;
        return;
    }

    temp = hteam1;

    while(temp->next != tteam1)
        temp = temp->next;

    free(tteam1);

    tteam1 = temp;
    tteam1->next = NULL;
}

void delTeam2()
{
    if(hteam2 == NULL)
        return;

    if(hteam2 == tteam2)
    {
        free(hteam2);
        hteam2 = NULL;
        tteam2 = NULL;
        return;
    }

    temp = hteam2;

    while(temp->next != tteam2)
        temp = temp->next;

    free(tteam2);

    tteam2 = temp;
    tteam2->next = NULL;
}