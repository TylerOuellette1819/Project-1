#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

struct Resource {
    int id;
    string name;
    string type;
    bool available;
};

struct Reservation {
    int reservationID;
    int studentID;
    int resourceID;
    string date;
    string startTime;
    string endTime;
};

vector<Resource> resources;
vector<Reservation> reservations;

int nextReservationID = 1001;

// Load resources from file
void loadResources() {
    ifstream file("resources.txt");

    if (!file) {
        cout << "Error: Could not open resources.txt\n";
        return;
    }

    string line;

    while (getline(file, line)) {
        stringstream ss(line);

        string id;
        string name;
        string type;
        string available;

        getline(ss, id, '|');
        getline(ss, name, '|');
        getline(ss, type, '|');
        getline(ss, available, '|');

        Resource resource;

        resource.id = stoi(id);
        resource.name = name;
        resource.type = type;
        resource.available = (available == "1");

        resources.push_back(resource);
    }

    file.close();

    cout << "Resources loaded successfully.\n";
}

// Display all resources
void displayResources() {
    cout << "\n===== ALL RESOURCES =====\n";

    if (resources.empty()) {
        cout << "No resources available.\n";
        return;
    }

    for (const Resource& resource : resources) {
        cout << "ID: " << resource.id
             << " | Name: " << resource.name
             << " | Type: " << resource.type
             << " | Availability: "
             << (resource.available ? "Available" : "Unavailable")
             << endl;
    }
}

// Display resource availability
void displayAvailability() {
    cout << "\n===== RESOURCE AVAILABILITY =====\n";

    for (const Resource& resource : resources) {
        cout << resource.id << " - "
             << resource.name << ": "
             << (resource.available ? "Available" : "Unavailable")
             << endl;
    }
}

// Find a resource
Resource* findResource(int resourceID) {
    for (Resource& resource : resources) {
        if (resource.id == resourceID) {
            return &resource;
        }
    }

    return nullptr;
}

// Check whether reservation conflicts
bool reservationConflict(
    int resourceID,
    string date,
    string startTime,
    string endTime
) {
    for (const Reservation& reservation : reservations) {

        if (reservation.resourceID == resourceID &&
            reservation.date == date) {

            // Basic time overlap check
            if (startTime < reservation.endTime &&
                endTime > reservation.startTime) {

                return true;
            }
        }
    }

    return false;
}

// Create reservation
void createReservation() {
    int studentID;
    int resourceID;
    string date;
    string startTime;
    string endTime;

    cout << "\n===== CREATE RESERVATION =====\n";

    cout << "Enter Student ID: ";
    cin >> studentID;

    cout << "Enter Resource ID: ";
    cin >> resourceID;

    Resource* resource = findResource(resourceID);

    // Validate resource
    if (resource == nullptr) {
        cout << "Error: Resource does not exist.\n";
        return;
    }

    // Validate availability
    if (!resource->available) {
        cout << "Error: Resource is unavailable.\n";
        return;
    }

    cout << "Enter date (YYYY-MM-DD): ";
    cin >> date;

    cout << "Enter start time (HH:MM): ";
    cin >> startTime;

    cout << "Enter end time (HH:MM): ";
    cin >> endTime;

    // Validate time
    if (startTime >= endTime) {
        cout << "Error: Start time must be before end time.\n";
        return;
    }

    // Check conflict
    if (reservationConflict(
            resourceID,
            date,
            startTime,
            endTime)) {

        cout << "Error: Resource is already reserved during this time.\n";
        return;
    }

    Reservation reservation;

    reservation.reservationID = nextReservationID++;
    reservation.studentID = studentID;
    reservation.resourceID = resourceID;
    reservation.date = date;
    reservation.startTime = startTime;
    reservation.endTime = endTime;

    reservations.push_back(reservation);

    cout << "\nReservation created successfully!\n";
    cout << "Reservation ID: "
         << reservation.reservationID << endl;
}

// Cancel reservation
void cancelReservation() {
    int reservationID;

    cout << "\n===== CANCEL RESERVATION =====\n";

    cout << "Enter Reservation ID: ";
    cin >> reservationID;

    for (size_t i = 0; i < reservations.size(); i++) {

        if (reservations[i].reservationID == reservationID) {

            reservations.erase(reservations.begin() + i);

            cout << "Reservation cancelled successfully.\n";
            return;
        }
    }

    cout << "Error: Reservation not found.\n";
}

// Display active reservations
void displayReservations() {
    cout << "\n===== ACTIVE RESERVATIONS =====\n";

    if (reservations.empty()) {
        cout << "No active reservations.\n";
        return;
    }

    for (const Reservation& reservation : reservations) {

        cout << "Reservation ID: "
             << reservation.reservationID << endl;

        cout << "Student ID: "
             << reservation.studentID << endl;

        cout << "Resource ID: "
             << reservation.resourceID << endl;

        cout << "Date: "
             << reservation.date << endl;

        cout << "Time: "
             << reservation.startTime
             << " - "
             << reservation.endTime << endl;

        cout << "-----------------------------\n";
    }
}

int main() {

    loadResources();

    int choice;

    do {

        cout << "\n====================================\n";
        cout << " CAMPUS RESOURCE RESERVATION SYSTEM\n";
        cout << "====================================\n";

        cout << "1. Display All Resources\n";
        cout << "2. Display Resource Availability\n";
        cout << "3. Create Reservation\n";
        cout << "4. Cancel Reservation\n";
        cout << "5. Display Active Reservations\n";
        cout << "0. Exit\n";

        cout << "\nEnter choice: ";
        cin >> choice;

        switch (choice) {

            case 1:
                displayResources();
                break;

            case 2:
                displayAvailability();
                break;

            case 3:
                createReservation();
                break;

            case 4:
                cancelReservation();
                break;

            case 5:
                displayReservations();
                break;

            case 0:
                cout << "Exiting program...\n";
                break;

            default:
                cout << "Invalid choice. Please try again.\n";
        }

    } while (choice != 0);

    return 0;
}