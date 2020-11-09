// AllDigitisUnique.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <map>
using namespace std;

bool AllDigitsUnique(unsigned int value);

int main()
{

    std::string number;
    std::cout << "Enter a number: ";
    std::getline(std::cin, number);

    unsigned int uiInput = atoi(number.c_str());

    if (AllDigitsUnique(uiInput))
    {
        cout << "All Digits Unique";
    }
    else
    {
        cout << "All Digits NOT Unique";
    }

    cin.get();
  
}

bool AllDigitsUnique(unsigned int value)
{
    if (value == 0) return false; // false, since there are no digits

    // convert to string
    std::string tmp = std::to_string(value);

    std::map<char, int> dict;
    for (auto c : tmp)
    {
        // Look for match
        auto kvp = dict.find(c);
        if (kvp != dict.end()) // found a match
        {
            // Update count
            return false;
        }
        else {
            // Add key
            dict.insert({ c, 1 });
        }
    }


    return true;
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
