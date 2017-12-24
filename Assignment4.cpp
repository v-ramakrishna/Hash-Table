// Name of Author: Vijay Ramakrishna
// ASU ID: 1202948495
// Homework Number: 4
// Name of Author: Vijay Ramakrishna
// ASU ID: 1202948495
// Homework Number: 4
// Description: This program prompts the user to enter a size and generates a hash table.
//              The hash table is then populated until the user enters a value to stop inserting. The program will then
//              ask how many commands the user wishes to enter, and will keep asking a user to enter the next choice
//              until the desired number of commands have been issued. This file is the main driver file for the program.

// Hash Function
// The hash function is h(k) = ∑(ascii_value_of_character * numerical_position_of_character/2), where k is the Key

// Hash Analysis
// I had to try several different hash functions before ultimately deciding to use the one which I used. Initially, I tried just counting
// the number of the characters in the key, and finding the modulus for this value and the number of tables. This was not a good function
// because many of the keys are the same length, particularly where teams are concerned. For example, with the sample input file, all teams
// doing the same event will be put into the same Linked List. So, I tried using an ASCII-converter next, summing up the ASCII values of the
// key to determine where to place it. This had a similar issue to the previous function, as many of the keys are quite similar. So, I added the
// additional qualifier of multiplying the ASCII value by the character's position divided by 2. This caused sufficient diversity in the outputs for the
// hash function to be a useful hash function.
//
// The expected number of collisions, given a relatively equal distribution should be equal to the load factor for the hash table. In the case of the input
// data provided, there are a total of 43 entries distributed among 13 Linked Lists. This means, on average, each list should have 3.3 items, and on average,
// 2.3 collisions will take place. This is seen using the sample data, where most lists have 3 or 4 entries.

#include <iostream>
#include <string> //to use strings
#include "HashTable.h" // to use HashTables

using namespace std;

void printMenu();

// Main
// Description: Driver to initialize and populate hash table and run the program to issue commands
int main()
{
    string newCommand = "";
    int commandNumber;
    string processCommand;
    string commandPrefix;
    string insertCommand;
    string endMarker = "\r"; // Used to validate end character

    HashTable * table = new HashTable(); // Create and populate hash table
    commandNumber = -1;
    while(commandNumber == -1)
    {
        // Prompt user for number of commands to follow
        cout << "Set Number of Commands: ";
        cin >> commandNumber;
        // Validate User Entry for hash table size
        if (cin.fail())
        {
            // if entry was invalid, clear and reset input stream, reset variables to go back through loop
            cout << "Not a Valid Command Number" <<endl;
            cin.clear();
            cin.ignore(20, '\n'); // Flush the buffer
            commandNumber = -1;
        }
    }
    cin.ignore(20, '\n'); // Flush the buffer
    printMenu(); // Print Menu
    int i = 0;
    while(i < commandNumber) // Prompt user for commands until the user has entered as many commands
    {
        cout << endl << "Enter New Command: "; // Get User's Command
        getline(cin, newCommand);
        int saveLastPosition = newCommand.size()-1; // Get last character of newCommand
        if (saveLastPosition >= 0) // if newCommand contains a string
        {
            string analyzeCommand = newCommand.substr(saveLastPosition, 1); // Create and initialize analyzeCommand to the last character of newCommand
            if (analyzeCommand.compare(endMarker) == 0) // if the last character of newCommand is equal to "\r" due to data being pulled from a file created on Windows
            {
                newCommand.erase(newCommand.size()-1); // Remove last character from newCommand
            }
        }
        commandPrefix = newCommand.substr(0,1); // Get first letter of command
        if (commandPrefix == "h") // if first letter is h
        {
            processCommand = newCommand.substr (5,2);
            if (newCommand.substr(5, 6) == "insert") // if letters 6-12 are "insert"
            {
                insertCommand = newCommand.substr(12, newCommand.size()-11); //create insertCommand by removing hash_insert, from the command
                bool inserted = table->hash_insert(insertCommand); // insert new entry by calling hash_insert
                if (inserted == false)
                {
                    cout << "Bad Insertion Command" << endl; // if a bad entry (wrong number of commas) was input
                }
                newCommand = "";
                i++;

            }
            else if(newCommand.substr(5, 6) == "search") // if letters 6-12 are "search"
            {
                bool searched = table->hash_search(newCommand); // call hash_search, using the command as input
                if (searched == false)
                {
                    cout << "Bad Search Command" << endl; // if a bad entry (wrong number of commas) was input
                }
                newCommand = "";
                i++;
            }
            else if(newCommand.substr(5, 6) == "delete") // if letters 6-12 are "delete"
            {
                bool deleted = table->hash_delete(newCommand); // delete entry by calling hash_delete, using the command as input
                if (deleted == false)
                {
                    cout << "Bad Delete Command" << endl; // if a bad entry (wrong number of commas) was input
                }
                newCommand = "";
                i++;
            }
            else if(newCommand.substr(5, 7) == "display") // if letters 6-13 are "display"
            {
                table->hash_display(); // call hash_display
                newCommand = "";
                i++;
            }
            else
            {
                cout << "Invalid Command " << endl; // invalid command error message
                newCommand = "";
                i++;
            }
        }
        else if (commandPrefix == "?")
        {
            printMenu(); // Print the menu again if the user presses ?
            newCommand = "";
            i++;
        }
        else if (commandPrefix != "h" && commandPrefix != "?")
        {
            cout << "Invalid Command" << endl; // if the user has an input that does not begin with a "h", "Q" or "?", output error message
            newCommand = "";
            i++;
        }
    }
    return 0;
}

// Print Menu
// Description: Displays Command options to the User after the hash table is initially populated.
void printMenu()
{
    // Create strings for Menu
    int lineSize = 85; // approximate size of largest item, character-wise, on left side of menu
    string commands = "Commands";
    string action = "Action";
    string lines = "------";
    string insertText = "hash_insert,Discipline,Gender,Team_or_Independent,Event,Venue,Medal,Athlete,Country";
    string insertText2 = "Add an Athlete";
    string displayText = "hash_display";
    string displayText2 = "Display Hash Table";
    string searchText = "hash_search,Discipline,Gender,Event,Athlete";
    string searchText2 = "Search for an Athlete";
    string deleteText = "hash_delete,Discipline,Gender,Event,Athlete";
    string deleteText2 = "Delete an Athlete";
    string quitText = "q or quit";
    string quitText2 = "Quit";
    string questionText = "?";
    string questionText2 = "Display Help";
    // Print Menu
    cout <<commands << string(lineSize-commands.size(), ' ') <<action << endl;
    cout <<lines << string(lineSize-lines.size(), ' ') <<lines << endl;
    cout <<insertText << string(lineSize-insertText.size(), ' ') <<insertText2 << endl;
    cout <<displayText << string(lineSize-displayText.size(), ' ') <<displayText2 << endl;
    cout <<searchText << string(lineSize-searchText.size(), ' ') <<searchText2 << endl;
    cout <<deleteText << string(lineSize-deleteText.size(), ' ') <<deleteText2 << endl;
    cout <<quitText << string(lineSize-quitText.size(), ' ') <<quitText2 << endl;
    cout <<questionText << string(lineSize-questionText.size(), ' ') <<questionText2 << endl;
}
