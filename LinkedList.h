// Name of Author: Vijay Ramakrishna
// ASU ID: 1202948495
// Homework Number: 4
// Description: This program prompts the user to enter a size and generates a hash table.
//              The hash table is then populated until the user enters a value to stop inserting. The program will then
//              ask how many commands the user wishes to enter, and will keep asking a user to enter the next choice
//              until the desired number of commands have been issued. This file is the LinkedList class file for the program.

#include <iostream> //to use cout
#include <iomanip> //to format output
#include <string> //to use strings
#include <stdlib.h> // to free nodes

using namespace std;

// struct Athlete represents some Athlete information
struct Athlete
{
    string key;
    string discipline;
    string gender;
    string team_or_ind;
    string event;
    string venue;
    string medal;
    string athlete;
    string country;
    struct Athlete * next;
};

// class LinkedList will contain a linked list of Athletes
class LinkedList
{
    private:
        struct Athlete * head;
        int index;

    public:
        LinkedList(int mIndex);
        bool insertAthlete(string mDiscipline, string mGender, string mTeam_or_ind, string mEvent, string mVenue, string mMedal, string mAthlete, string mCountry, string mKey);
        bool deleteAthlete(string deleteKey);
        bool searchAthlete(string findKey);
        void printList();
};

// Linked List
// Description: Constructor to initialize the linked list
LinkedList::LinkedList(int mIndex)
{
    head = NULL;
    index = mIndex;
}

// Insert Athlete
// Description: The Insert Athlete method adds a new country to the linked list, using
//              arguments specified by the user in the main program to populate the
//              structure's information. The new structure is always added to the head of the
//              Linked List, even in the case of a collision.
bool LinkedList::insertAthlete(string mDiscipline, string mGender, string mTeam_or_ind, string mEvent, string mVenue, string mMedal, string mAthlete, string mCountry, string mKey)
{
    // Create a new Athlete node
    struct Athlete * newAthlete = new Athlete;

    // Populate the new node with data passed into the method
    newAthlete->discipline = mDiscipline;
    newAthlete->gender = mGender;
    newAthlete->team_or_ind = mTeam_or_ind;
    newAthlete->event = mEvent;
    newAthlete->venue = mVenue;
    newAthlete->medal = mMedal;
    newAthlete->athlete = mAthlete;
    newAthlete->country = mCountry;
    newAthlete->key = mKey;

    // Add node to LinkedList
    struct Athlete * currentOnList = NULL; // Create pointer to nodes
    // If head is null, set the new node as the head and its next pointer to null, return true
    if (head == NULL)
    {
        head = newAthlete;
        head->next = NULL;
        return true;
    }
    // if head is not null, set the new node as the head, and its next pointer to the previous head, return true
    else
    {
        currentOnList = head;
        head = newAthlete;
        head->next = currentOnList;
        return true;
    }
    return false; // return false is new node could not be added
}

// Delete Athlete
// Description: The Delete Athlete method searches for an athlete specified
//              by the user in the main program by constructing a key. If an athlete matching the specified
//              key is found, the athlete will be removed from the linked list,
//              and the memory it was allocated will be freed. Will return false if the
//              country is not actually in the list.
bool LinkedList::deleteAthlete(string deleteKey)
{
    // Create variables to store keys and point at nodes
    string deleteAthlete = deleteKey;
    struct Athlete * currentOnList = NULL;
    struct Athlete * nextOnList = NULL;
    string saveHeadKey;
    string extractNextKey;

    if (head == NULL)
    {
        return false; //return false if the list is empty
    }

    // extract values for pointers and head's key
    currentOnList = head;
    nextOnList = head->next;
    saveHeadKey = head->key;

    if (head-> next == NULL) // if the only item on the list is the head
    {
        if (saveHeadKey == deleteAthlete) // if key is equal to the deletion key, delete the node and return true
        {
            free(head);
            head = NULL;
            return true;
        }
        else
        {
            return false; // if the one item is not the item being deleted, return false
        }
    }
    extractNextKey = nextOnList->key; // extract key for nextOnList's key
    while(currentOnList->next != NULL) // loop until currentOnList is the end of the list
    {
        if(saveHeadKey == deleteAthlete) // if head key is the deletion key, delete the head node, sets its next pointer node to the head and return true
        {
            free(head);
            head = nextOnList;
            return true;
        }
        else if (extractNextKey == deleteAthlete) // if extractNextKey is the deletion key, delete its, and
        {                                         //set the previous node's next pointer to its next pointer
            currentOnList->next = nextOnList->next;
            free(nextOnList);
            return true;
        }
        else // else
        {
            currentOnList = nextOnList; // set currentOnList to nextOnList
            if (currentOnList->next == NULL) // if currentOnList's next pointer is NULL, return false
            {
                return false;
            }
            nextOnList = currentOnList->next; //set nextOnList to currentOnList's next pointer
            extractNextKey = nextOnList->key; // set extractNextKey to nextOnList's key
        }
    }
    return false;
}

// Search Athlete
// Description: The Search Athlete method is, as its name implies, used to find
//              an athlete which has already been added to the
//              linked list, and informs the User what medal they have. It does this by searching
//              for an athlete node in the linked list matching a key generated by user-specifications.
//              Will return false if the athlete is not in the list.
bool LinkedList::searchAthlete(string findKey)
{
    // Create variables to hold keys and point to nodes
    string findAthlete = findKey;
    struct Athlete * currentOnList = NULL;
    string extractKey;

    if (head == NULL)
    {
        return false; // if list is empty return false
    }

    currentOnList = head; // set currentOnList pointer to head
    extractKey = head->key; // set extractKey to head's key

    while (currentOnList != NULL) // Check until the end of the list
    {
        // Print message and return true if the current key matches the search key
        if (findAthlete == extractKey)
        {
            cout << "The medal recipient " << currentOnList->athlete << " has the medal " << currentOnList->medal << endl;
            return true;

        }
        else // else
        {
            currentOnList = currentOnList->next; // set currentOnList to currentOnList's next pointer
            if (currentOnList == NULL)
            {
                return false; // return false if past the end of the list
            }
            extractKey = currentOnList->key; // set extractKey to current node's key
        }
    }
    return false;
}

// Print List
// Description: Used to print the contents of the linked list. Prints the list index, and list size, and then prints each athlete's
//              name, followed by relevant information specified by the user when inserting the
//              athlete, followed by a new line. When the list is empty, will output "The list is empty"
//              followed by a new line.
void LinkedList::printList()
{
    struct Athlete * currentPointer = NULL; // Create pointer
    int listCounter = 0; // Create list counter to count items on list and set it to 0

    if (head != NULL) // set pointer to head if it isn't NULL
    {
        currentPointer = head;
        currentPointer->next = head->next;
    }
    while (currentPointer != NULL) // Count items on list
    {
        currentPointer = currentPointer->next;
        listCounter++;
    }
    cout << "index: " << index << ", linked list size: " << listCounter << endl; // Print index number and size

	if (head != NULL) // If head is not NULL, set currentPointer to be equal to it
    {
        currentPointer = head;
        currentPointer->next = head->next;
    }
    if (currentPointer == NULL) // if currentPointer is NULL, print out empty list message
    {
        cout << "The list is empty \n";
    }
    else
    {
        cout << "\n";
        do // run loop at least once; print contents of node for currentPointer and set currentPointer to its next pointer
        {
            cout << "discipline: " << currentPointer->discipline << endl << "gender: " << currentPointer->gender << endl << "team_or_ind: " << currentPointer->team_or_ind << endl << "event: " << currentPointer->event << endl << "venue: " << currentPointer->venue << endl << "medal: " << currentPointer->medal << endl << "athlete: " << currentPointer->athlete << endl << "country: " << currentPointer->country << endl << endl;
            currentPointer = currentPointer->next;
        } while (currentPointer != NULL); // run loop until until currentPointer is NULL, meaning list has reached end
    }
}
