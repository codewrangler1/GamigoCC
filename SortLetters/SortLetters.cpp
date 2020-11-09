// SortLetters.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <map>
using namespace std;

std::string SortLetters(const char* input, const char* sortOrder);

int main()
{
    cout << "SortLetters\n";
    cout << "INPUT: 'trion world network'\n";
    cout << "SORTORDER: ' oinewkrtdl'\n";


    std::string result = SortLetters("trion world network", " oinewkrtdl");
    cout << result;

    cin.get();
}


// For simplicity, we will return the resultant string
std::string SortLetters(const char * input, const char * sortOrder)
{

    std::string result;

    // Check for null pointers
    if (input == NULL || sortOrder == NULL)
        return result;

    // Check for empty strings
    if (strlen(input) == 0 || strlen(sortOrder) == 0)
        return result;

    // Make local copies
    std::string sInput = input;
    std::string sSortOrder = sortOrder;

    // Get Count of all chars
    std::map<char, int> dict;
    for (auto c : sInput)
    {
        // Look for match
        auto kvp = dict.find(c);
        if (kvp != dict.end()) // found a match
        {
            // Get Value
            int value = kvp->second;

            // Update value
            kvp->second += 1;
        }
        else {
            // Add key
            dict.insert({ c, 1 });
        }
    }

    // Sort, based on sortOrder string
    // It is assumed that ALL characters in the input are also in the sortOrder
    for (auto c : sSortOrder)
    {
        auto kvp = dict.find(c);
        if (kvp != dict.end()) // found a match
        {
            // Add characters that match sortOrder character
            for (int x = 0; x < kvp->second; x++)
            {
                result += c;
            }
        }

    }

    // Returned "sorted" string
    return result;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
