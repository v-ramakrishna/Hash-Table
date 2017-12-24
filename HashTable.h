// Name of Author: Vijay Ramakrishna
// ASU ID: 1202948495
// Homework Number: 4
// Description: This program prompts the user to enter a size and generates a hash table.
//              The hash table is then populated until the user enters a value to stop inserting. The program will then
//              ask how many commands the user wishes to enter, and will keep asking a user to enter the next choice
//              until the desired number of commands have been issued. This file is the HashTable class file for the program.

#include <iostream> //to use cout
#include <iomanip> //to format output
#include <string> //to use strings
#include "LinkedList.h" // to use LinkedLists

// class HashTable will contains an array of LinkedLists
class HashTable
{
private:
    LinkedList **hTable;
    int tableSize;

public:
    HashTable();
    bool hash_insert(string mNewEntry);
    bool hash_search(string mSearch);
    bool hash_delete(string mDelete);
    void hash_display();
    int hash_function(string mKey);
};

// Hash Table
// Description: Constructor to initialize a hash table
HashTable::HashTable()
{
    tableSize = -1;
    while(tableSize == -1)
    {
        // Prompt user for hash table size
        cout << "Creating Hash Table. Set Table Size (Must be a Positive Integer): ";
        cin >> tableSize;
        // Validate User Entry for hash table size
        if (cin.fail())
        {
            // if entry was invalid, clear and reset input stream, reset variables to go back through loop
            cout << "Not a Valid Table Size" <<endl;
            cin.clear();
            cin.ignore(20, '\n'); //Flush the buffer
            tableSize = -1;
        }
    }
    cin.ignore(20, '\n'); //Flush the buffer
    // Create hash table of size previously inputted by user
    hTable = new LinkedList* [tableSize];
    for (int index = 0; index < tableSize; index++)
    {
        hTable[index] = new LinkedList(index);
    }
    string newEntry;
    string insertEnd = "InsertionEnd";
    string endMarker = "\r";
    // run loop to initially populate hash table
    do
    {
        cout << "Add New Athlete (InsertionEnd to stop Inserting Athletes): "; // Ask user for new entry
        getline(cin, newEntry); // Get entry from user
        string newEntryProcessed = newEntry.substr((newEntry.size()-1), 1);
        if (newEntryProcessed.compare(endMarker) == 0)
        {
            newEntry.erase(newEntry.size()-1);
        }
        if (newEntry.compare(insertEnd) != 0)
        {
            bool inserted = hash_insert(newEntry); //call hash_insert on new entry
            if (inserted == false)
            {
                cout << "Bad Entry: " << newEntry << endl; //if entry could not be processed, let the user know
            }
        }
    } while(newEntry.compare(insertEnd) != 0); // end the loop when the user inputs InsertionEnd
}

// Hash Insert
// Description: The Hash Insert method parses important information provided by the User,
//              and stores these in strings, and generates a key from this data. The hash function is then called
//              using the key as a parameter input. The LinkedList corresponding with the index returned from this function
//              then calls the Insert Athlete method. The user is then informed if insertion was successful.
bool HashTable::hash_insert(string mNewEntry)
{
    // Validate New Entry
    int commaCounter = 0;
    // Count the number of commas in the entry
    for (int i = 0; i < mNewEntry.size(); i++)
    {
        if (mNewEntry.substr(i, 1) == ",")
        {
            commaCounter++;
        }
    }
    // If the number of commas is not 7, immediately end insertion and return false
    if(commaCounter != 7)
    {
        return false;
    }
    // Create and Initialize strings for new Athlete entry
    string mDiscipline = "";
    string mGender = "";
    string mTeam_or_ind = "";
    string mEvent = "";
    string mVenue = "";
    string mMedal = "";
    string mAthlete = "";
    string mCountry = "";
    string mKey = "";
    // Declare size_t variables to find commas
    size_t disciplineToken;
    size_t genderToken;
    size_t teamToken;
    size_t eventToken;
    size_t venueToken;
    size_t medalToken;
    size_t athleteToken;
    size_t countryToken;
    // Find commas in new entry
    disciplineToken = mNewEntry.find(",");
    genderToken = mNewEntry.find(",", disciplineToken+1, 1);
    teamToken = mNewEntry.find(",", genderToken+1, 1);
    eventToken = mNewEntry.find(",", teamToken+1, 1);
    venueToken = mNewEntry.find(",", eventToken+1, 1);
    medalToken = mNewEntry.find(",", venueToken+1, 1);
    athleteToken = mNewEntry.find(",", medalToken+1, 1);
    countryToken = mNewEntry.find(",", athleteToken+1, 1);
    // Assign previously declared strings values depending on comma positions
    mDiscipline = mNewEntry.substr(0, disciplineToken);
    mGender = mNewEntry.substr(disciplineToken + 1, genderToken - disciplineToken - 1);
    mTeam_or_ind = mNewEntry.substr(genderToken + 1, teamToken - genderToken - 1);
    mEvent = mNewEntry.substr(teamToken + 1, eventToken - teamToken - 1);
    mVenue = mNewEntry.substr(eventToken + 1, venueToken-eventToken-1);
    mMedal = mNewEntry.substr(venueToken+1, medalToken-venueToken-1);
    mAthlete = mNewEntry.substr(medalToken+1, athleteToken-medalToken-1);
    mCountry = mNewEntry.substr(athleteToken+1, countryToken-athleteToken-1);
    // Generate key by appending discipline, gender, event, and athlete
    mKey.append(mDiscipline);
    mKey.append(mGender);
    mKey.append(mEvent);
    mKey.append(mAthlete);
    // run hash function to determine which LinkedList to place the entry in
    int hashIndex = hash_function(mKey);
    // Add entry to correct LinkedList, and tell the user if it was successful or not
    bool added = hTable[hashIndex]->insertAthlete(mDiscipline, mGender, mTeam_or_ind, mEvent, mVenue, mMedal, mAthlete, mCountry, mKey);
    if (added == true)
    {
        cout << "The medal recipient " << mAthlete << " for " << mDiscipline << " with event " << mEvent << " inserted. " << endl;
    }
    else
    {
        cout << mAthlete << " for " << mDiscipline << " with event " << mEvent << " not inserted. " << endl;
    }
    return true;
}

// Hash Search
// Description: The Hash Search method parses important information on the key to search for provided by the User,
//              and stores these in strings, and generates a key from this data. The hash function is then called
//              using the key as a parameter input. The LinkedList corresponding with the index returned from this function
//              then calls the Search Athlete method. The user is then informed if the search was successful (in a successful search
//              the Athlete is found, and medal information is given to the User).
bool HashTable::hash_search(string mSearch)
{
    // Validate Search Entry
    int commaCounter = 0;
    // Count the number of commas in the search command
    for (int i = 0; i < mSearch.size(); i++)
    {
        if (mSearch.substr(i, 1) == ",")
        {
            commaCounter++;
        }
    }
    // If the number of commas is not 4, immediately end the search and return false
    if(commaCounter != 4)
    {
        return false;
    }
    // Create strings to hold data from commands
    string mDiscipline = "";
    string mGender = "";
    string mEvent = "";
    string mAthlete = "";
    //Create size_t variables to mark comma positions
    size_t hashToken;
    size_t disciplineToken;
    size_t genderToken;
    size_t eventToken;
    size_t athleteToken;
    // Find commas in search command
    hashToken = mSearch.find(",");
    disciplineToken = mSearch.find(",", hashToken+1, 1);
    genderToken = mSearch.find(",", disciplineToken+1, 1);
    eventToken = mSearch.find(",", genderToken+1, 1);
    athleteToken = mSearch.find(",", eventToken+1, 1);
    // Assign values to previously created strings, based on comma positions
    mDiscipline = mSearch.substr(hashToken+ 1, disciplineToken - hashToken - 1);
    mGender = mSearch.substr(disciplineToken + 1, genderToken - disciplineToken - 1);
    mEvent = mSearch.substr(genderToken + 1, eventToken - genderToken - 1);
    mAthlete = mSearch.substr(eventToken+1, athleteToken-eventToken-1);
    // Create string, key, and append all of the other string data to it
    string key;
    key.append(mDiscipline);
    key.append(mGender);
    key.append(mEvent);
    key.append(mAthlete);
    //Call hash function using the key, to determine which LinkedList to search
    int hashIndex = hash_function(key);
    // Call searchAthlete using correct LinkedList for key and tell the user if they are found or not (the message for their being found is in LinkedList.h
    // as the output message needs to access data that needs to be accessed by the LinkedList)
    bool found = hTable[hashIndex]->searchAthlete(key);
    if (found == false)
    {
        cout << mAthlete << " for " << mDiscipline << " with event " << mEvent << " not found. " << endl;
    }
    return true;
}

// Hash Delete
// Description: The Hash Delete method parses important information on the key to search for provided by the User,
//              and stores these in strings, and generates a key from this data. The hash function is then called
//              using the key as a parameter input. The LinkedList corresponding with the index returned from this function
//              then calls the Delete Athlete method. The user is then informed if deletion was successful (in a successful deletion
//              the Athlete is found and deleted).
bool HashTable::hash_delete(string mDelete)
{
    //Validate Delete Entry
    int commaCounter = 0;
    // Count the number of commas in the delete command
    for (int i = 0; i < mDelete.size(); i++)
    {
        if (mDelete.substr(i, 1) == ",")
        {
            commaCounter++;
        }
    }
    // If the number of commas is not 4, immediately end the search and return false
    if(commaCounter != 4)
    {
        return false;
    }
    // Create strings to hold data from commands
    string mDiscipline = "";
    string mGender = "";
    string mEvent = "";
    string mAthlete = "";
    //Create size_t variables to mark comma positions
    size_t hashToken;
    size_t disciplineToken;
    size_t genderToken;
    size_t eventToken;
    size_t athleteToken;
    // Find commas in delete command
    hashToken = mDelete.find(",");
    disciplineToken = mDelete.find(",", hashToken+1, 1);
    genderToken = mDelete.find(",", disciplineToken+1, 1);
    eventToken = mDelete.find(",", genderToken+1, 1);
    athleteToken = mDelete.find(",", eventToken+1, 1);
    // Assign values to previously created strings, based on comma positions
    mDiscipline = mDelete.substr(hashToken+ 1, disciplineToken - hashToken - 1);
    mGender = mDelete.substr(disciplineToken + 1, genderToken - disciplineToken - 1);
    mEvent = mDelete.substr(genderToken + 1, eventToken - genderToken - 1);
    mAthlete = mDelete.substr(eventToken+1, athleteToken-eventToken-1);
    // Create string, key, and append all of the other string data to it
    string key;
    key.append(mDiscipline);
    key.append(mGender);
    key.append(mEvent);
    key.append(mAthlete);
    //Call hash function using the key, to determine which LinkedList to search
    int hashIndex = hash_function(key);
    // Search appropriate LinkedList for key and call deleteAthlete on it; tell the user if they are found or not
    bool deleted = hTable[hashIndex]->deleteAthlete(key);
    if (deleted == true)
    {
        cout << "The medal recipient " << mAthlete << " for " << mDiscipline << " with event " << mEvent << " deleted. " << endl;
    }
    else
    {
        cout << mAthlete << " for " << mDiscipline << " with event " << mEvent << " not found. " << endl;
    }
    return true;
}

// Hash Display
// Description: The Hash Display method is used to print the contents of all LinkedLists in the Hash Table.
//              It does this by calling the Print List method for every LinkedList in the Hash Table.
void HashTable::hash_display()
{
    // Call printList for every LinkedList in the hash table
    for (int index = 0; index < tableSize; index++)
    {
        hTable[index]->printList();
    }
}

// Hash Function
// Description: The Hash Function method is used to determine which LinkedList to call a method on.
int HashTable::hash_function(string mKey)
{
    int sum = 0; // create and initialize sum to 0
    for (int i = 0; i< mKey.size(); i++) // run loop through all of mKey
    {
        sum = sum + (i/2)*(int)mKey[i]; // Add the integer value of each character multiplied by its position in the key divided by 2 to the sum
    }
    int hashOutput = sum % tableSize; // Find the modulo of the sum and tableSize
    return hashOutput; // return the remainder
}
