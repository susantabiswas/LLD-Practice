#include <iostream>
#include <unordered_map>
using namespace std;

/////////////////////////// Base Entities
#pragma region Base Entities
enum FlightStatus {
    OnTime,
    Canceled,
    Delayed,  
    Arrived,
    SecurityCheck,
    OutOfService,
    Ready,
    ReadyForBoarding,
    Boarding,
    Departed
}

class Flight {
private:
    string flightId;
    string flightName;
    string arrivalCity;
    string destinationCity;
    string arrivalTime;
    string destinationTime;
    FlightStatus status;
    int capacity;
    int availableSeats;

public:
    Flight(string flightId, string flightName, string arrivalCity, string destinationCity,
        string arrivalTime, string destinationTime, FlightStatus status, int capacity) {
        this->flightId = flightId;
        this->flightName = flightName;
        this->arrivalCity = arrivalCity;
        this->destinationCity = destinationCity;
        this->arrivalTime = arrivalTime;
        this->destinationTime = destinationTime;
        this->status = status;
        this->capacity = capacity;
        this->availableSeats = capacity;
    }

    void setFlightStatus(FlightStatus status) { this->status = status; }

    int getAvailableSeats() { return availableSeats; }
    
    int getTotalSeats() { return capacity; }
    
    bool bookSeat() {

    }
    
    string getFlightId() { return flightId; }
    
    string getFlightName() { return flightName; }

    string getArrivalCity() { return arrivalCity; }

    string setArrivalCity(string arrivalCity) { this->arrivalCity = arrivalCity; }

    string getDestinationCity() { return destinationCity; }

    string setDestinationCity(string destinationCity) { this->destinationCity = destinationCity; }

    string getArrivalTime() { return arrivalTime; }

    string setArrivalTime(string arrivalTime) { this->arrivalTime = arrivalTime; }

    string getDestinationTime() { return destinationTime; }

    string setDestinationTime(string destinationTime) { this->destinationTime = destinationTime; }
};

class Payment {

};

class Passenger {

};

class Staff {

};

class Booking {

};

class ITicketPriceAdvisor {

};

#pragma endregion

/////////////////////////////////////////

////////////////////////// Entity Implementations

#pragma region Entity Implementations
#pragma endregion

////////////////////////////////////////////////

////////////////////////// Main
int main() {
    return 0;
}