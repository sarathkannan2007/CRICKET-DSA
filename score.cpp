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

struct node *hteam1 = NULL;
struct node *tteam1 = NULL;

struct node *hteam2 = NULL;
struct node *tteam2 = NULL;

struct node *temp = NULL;

struct node *alloc()
{
    struct node *nnode = (struct node *)malloc(sizeof(struct node));
    return nnode;
}

void addTeam1(string pnn,int pn,string tm)
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

void addTeam2(string pnn,int pn,string tm)
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

struct node *getPlayer(struct node *head,int position)
{
    temp = head;

    int count = 0;

    while(temp != NULL)
    {
        if(count == position)
            return temp;

        count++;
        temp = temp->next;
    }

    return NULL;
}

struct node *getPlayerByID(struct node *head,int id)
{
    temp = head;

    while(temp != NULL)
    {
        if(temp->playernum == id)
            return temp;

        temp = temp->next;
    }

    return NULL;
}

void displayTeam1()
{
    cout << "\n========== TEAM 1 ==========\n";

    temp = hteam1;

    while(temp != NULL)
    {
        cout << temp->playernum
             << "  "
             << temp->playername
             << "  Score: "
             << temp->score
             << "  Wickets: "
             << temp->wicket
             << endl;

        temp = temp->next;
    }
}

void displayTeam2()
{
    cout << "\n========== TEAM 2 ==========\n";

    temp = hteam2;

    while(temp != NULL)
    {
        cout << temp->playernum
             << "  "
             << temp->playername
             << "  Score: "
             << temp->score
             << "  Wickets: "
             << temp->wicket
             << endl;

        temp = temp->next;
    }
}

void delTeam1()
{
    while(hteam1 != NULL)
    {
        temp = hteam1;
        hteam1 = hteam1->next;
        free(temp);
    }

    tteam1 = NULL;
}

void delTeam2()
{
    while(hteam2 != NULL)
    {
        temp = hteam2;
        hteam2 = hteam2->next;
        free(temp);
    }

    tteam2 = NULL;
}