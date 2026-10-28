#include <iostream>
#include <string>
using namespace std;

const int MAX_CARS = 8;
class myCarStack {
private:
    string cars[MAX_CARS];
    int stackTop;

public:
    myCarStack() {
        stackTop = -1;
    }
    bool isEmpty() const {
        return stackTop == -1;
    }
    bool isFull() const {
        return stackTop == MAX_CARS - 1;
    }
    int count() const {
        return stackTop + 1;
    }
    bool push(string carNumber) {
        if (isFull()) {
            cout << "Parking lot is full! Cannot park more cars.\n";
            return false;
        }
        if (search(carNumber)) {
            cout << "This car is already parked.\n";
            return false;
        }
        cars[++stackTop] = carNumber;
        cout << "Car " << carNumber << " parked successfully.\n";
        return true;
    }
    string pop() {
        if (isEmpty()) {
            return "";
        }
        return cars[stackTop--];
    }
    string top() const {
        if (isEmpty()) {
            return "";
        }

        return cars[stackTop];
    }
    bool search(string carNumber) const {
        for (int i = 0; i <= stackTop; i++) {
            if (cars[i] == carNumber) {
                return true;
            }
        }
        return false;
    }
    void display() const {
        if (isEmpty()) {
            cout << "No cars are currently parked.\n";
            return;
        }
        cout << "\nCars currently parked (Top to Bottom):\n";
        for (int i = stackTop; i >= 0; i--) {
            cout << cars[i];

            if (i == stackTop) {
                cout << "  <-- Top (exit)";
            }
            cout << endl;
        }
    }
    bool removeCar(string carNumber) {
        if (!search(carNumber)) {
            cout << "Car " << carNumber << " was not found.\n";
            return false;
        }
        myCarStack temp;
        while (top() != carNumber) {
            temp.push(pop());
        }
        cout << "Car " << pop() << " removed from parking lot.\n";

        while (!temp.isEmpty()) {
            push(temp.pop());
        }
        cout << "Other cars have been restored to their positions.\n";
        return true;
    }
};
int main() {
    myCarStack parkingLot;
    int choice;
    string carNumber;

    do {
        cout << "\n===== PARKING LOT MANAGEMENT =====\n";
        cout << "1. Park a new car\n";
        cout << "2. Remove a car by car number\n";
        cout << "3. View currently parked cars\n";
        cout << "4. Show total cars parked\n";
        cout << "5. View car at the exit (top car)\n";
        cout << "6. Search for a car\n";
        cout << "7. Check if parking lot is full\n";
        cout << "8. Check if parking lot is empty\n";
        cout << "0. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            cout << "Enter car number/license plate: ";
            cin >> carNumber;
            parkingLot.push(carNumber);
            break;

        case 2:
            cout << "Enter car number to remove: ";
            cin >> carNumber;
            parkingLot.removeCar(carNumber);
            break;

        case 3:
            parkingLot.display();
            break;

        case 4:
            cout << "Total cars parked: "
                << parkingLot.count() << " / "
                << MAX_CARS << endl;
            break;

        case 5:
            if (!parkingLot.isEmpty()) {
                cout << "Car at the exit: "
                    << parkingLot.top() << endl;
            }
            else {
                cout << "Parking lot is empty.\n";
            }
            break;

        case 6:
            cout << "Enter car number to search: ";
            cin >> carNumber;

            if (parkingLot.search(carNumber)) {
                cout << "Car " << carNumber
                    << " is currently parked.\n";
            }
            else {
                cout << "Car " << carNumber
                    << " is not in the parking lot.\n";
            }
            break;

        case 7:
            cout << (parkingLot.isFull()
                ? "Parking lot is full.\n"
                : "Parking lot has available spaces.\n");
            break;

        case 8:
            cout << (parkingLot.isEmpty()
                ? "Parking lot is empty.\n"
                : "Parking lot is not empty.\n");
            break;

        case 0:
            cout << "Exiting Parking Lot Management System.\n";
            break;

        default:
            cout << "Invalid choice! Please try again.\n";
        }

    } while (choice != 0);

    return 0;
}
