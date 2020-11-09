// Elevator.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <map>
#include <thread>
#include <mutex>
#include <vector>
// Instructions:

// Design an elevator controller for a building of ten floors (including the ground floor).

// Your ElevatorController class should implement the interface in ElevatorControllerBase and be constructed with a reference to an ElevatorMotor object.

// Design your controller to achive the overall-most-efficient system. The definition of overall-most-efficient is up to you. (Wow, that's vague)

class ElevatorMotor
{
    mutable std::mutex _mtx;
public:
    enum class Direction {UP = 1, None = 0, Down = -1};


    // Set default values
    int currrentFloor = 1;
    Direction currentDirection = Direction::None;
    int totalFloors = 1;

    ElevatorMotor(int floors)
    {
        totalFloors = floors;
    }

    int getCurrentFloor()
    {
        std::lock_guard<std::mutex> l(_mtx);
        return currrentFloor;
    }

    Direction getCurrentDirection()
    {
        std::lock_guard<std::mutex> l(_mtx);
        return currentDirection;
    }

    void goToFloor(int floor) 
    {
        std::lock_guard<std::mutex> l(_mtx);

        if (floor < 1 || floor > totalFloors) return; // invalid parameter

        currrentFloor = floor;

        if (floor > currrentFloor) currentDirection = Direction::UP;
        else if (floor < floor) currentDirection = Direction::Down;
        else if (floor == currrentFloor) currentDirection = Direction::None;

    }

};

// The instructions say, "Your ElevatorController class should implement the 'interface' in ElevatorControllerBase". 
// However, the example uses an abstract class with pure virtual functions

// Not clear from the instructins, who is calling these notification functions
class ElevatorControllerBase
{

public:

    virtual void summonButtonPushed(int summoningFloor, ElevatorMotor::Direction direction) = 0;

    virtual void floorButtonPushed(int destinationFloor) = 0;

    virtual void reachedFloor(int floor) = 0;
};

class ElevatorController : ElevatorControllerBase
{

    ElevatorMotor * motor;
    std::vector<bool> selectedFloors;
    std::thread*  elevatorRunThread;
    bool running = false;

    mutable std::mutex _mtx;

public:

    ElevatorController(int floors)
    {
        motor = new ElevatorMotor(floors);

        spawnWorkerThread();
    }

    void spawnWorkerThread() {
        running = true;
        elevatorRunThread = new std::thread(&ElevatorController::elevatorRunMethod, this, this);
        elevatorRunThread->join();
    }

    
    void elevatorRunMethod(ElevatorController * self)    
    {
        while (running)
        {

            // Move to next floor, if any
            ElevatorMotor::Direction currentDirection = motor->currentDirection;
            if (motor->currentDirection == ElevatorMotor::Direction::UP)
            {
                int cfloor = motor->currrentFloor;
                cfloor += 1;

                // Look for next floor, if any
                while (cfloor <= (int)selectedFloors.size())
                {
                    if (selectedFloors.at(cfloor)) // if selected
                    {
                        motor->goToFloor(cfloor);
                        selectedFloors.at(cfloor) = false; // moved to floor, so reset until selected again
                        break; // done with loop for now
                    }
                    else
                    {
                        cfloor += 1;
                    }
                }
            }
            else if (motor->currentDirection == ElevatorMotor::Direction::Down)
            {
                int cfloor = motor->currrentFloor;
                cfloor -= 1;

                // Look for next floor, if any
                while (cfloor > 0)
                {
                    if (selectedFloors.at(cfloor)) // if selected
                    {
                        motor->goToFloor(cfloor);
                        selectedFloors.at(cfloor) = false; // moved to floor, so reset until selected again
                        break; // done with loop for now
                    }
                    else
                    {
                        cfloor -= 1;
                    }
                }
            }
            else if (motor->currentDirection == ElevatorMotor::Direction::None)
            {
                // nothing to do
            }





            // add a delay, to give time to other threads
            std::this_thread::sleep_for(std::chrono::seconds(1));

        }
    }
    

    // Inherited via ElevatorControllerBase
    virtual void summonButtonPushed(int summoningFloor, ElevatorMotor::Direction direction) override
    {

        std::lock_guard<std::mutex> l(_mtx);
        if (summoningFloor < 1 || summoningFloor > (int)selectedFloors.size()) return; // invalid parameter

        selectedFloors.at(summoningFloor - 1) = true;


    }
    virtual void floorButtonPushed(int destinationFloor) override
    {

    }
    virtual void reachedFloor(int floor) override
    {
    }

    ~ElevatorController()
    {
        if (motor != nullptr) delete motor;
        running = false;
    }
};

int main()
{
    std::cout << "Hello World!\n";

    ElevatorController * ctrl = new ElevatorController(10);

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
