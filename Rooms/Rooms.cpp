// Rooms.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <map>

class Room;

class Door
{
    Room* roomIn = nullptr;

public:
    Door()
    {        
    }

    void SetRoom(Room* room)
    {
        roomIn = room;
    }
    Room* GetRoom()
    {
        return roomIn;
    }

};

class Room
{


    // Room name
    std::string name;
    // Doors...use map, in case we need to add more doors
    std::map<std::string, Door *> dict;
public:
    const std::string North = "North";
    const std::string South = "South";
    const std::string East = "East";
    const std::string West = "West";

    Room(std::string roomName)
    {
        // Set Name
        name = roomName;

        // Init doors
        dict.insert({ (std::string)"North", new Door() });
        dict.insert({ (std::string)"South", new Door() });
        dict.insert({ (std::string)"East", new Door() });
        dict.insert({ (std::string)"West", new Door() });
    }
    ~Room()
    {
        // Clean up memory
        auto kvp = dict.find("North");
        if (kvp != dict.end()) delete kvp->second; 
        
        kvp = dict.find("South");
        if (kvp != dict.end()) delete kvp->second;        
        
        kvp = dict.find("East");
        if (kvp != dict.end()) delete kvp->second;

        kvp = dict.find("West");
        if (kvp != dict.end()) delete kvp->second;
    }
   
    bool ConnectRoomThroughDoor(std::string DoorName, Room* room)
    {
        // Get Door
        auto kvp = dict.find(DoorName);
        if (kvp != dict.end()) return false;

        kvp->second->SetRoom(room);
    }

    bool PathExistsTo(const char* endingRoomName)
    {
        for (auto kvp : dict)
        {
            Room* room = kvp.second->GetRoom();
            if (room != nullptr)
            {
                // compare names
                if (strcmp(room->name.c_str(), endingRoomName) == 0)
                {
                    return true;
                }
            }
        }
        return false;
    }
    
};

int main()
{
    std::cout << "Hello World!\n";

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
