#include <iostream>
#include <unordered_map>
#include <mutex>
#include <vector>
#include <random>
#include <unordered_set>
using namespace std;

/////////////////////////// Base Entities
#pragma region Base Entities
enum class FlightStatus {
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
};

enum class BookingStatus {
    PaymentPending,
    Confirmed,
    Waitlisted,
    Canceled
};

class Flight {
private:
    string flightId;
    string flightName;
    string arrivalCity;
    string destinationCity;
    string arrivalTime;
    string departureTime;
    FlightStatus status;
    int capacity;
    int availableSeats;

    mutex flightMutex;
public:
    Flight(string flightId, string flightName, string arrivalCity, string destinationCity,
        string arrivalTime, string departureTime, FlightStatus status, int capacity) {
        this->flightId = flightId;
        this->flightName = flightName;
        this->arrivalCity = arrivalCity;
        this->destinationCity = destinationCity;
        this->arrivalTime = arrivalTime;
        this->departureTime = departureTime;
        this->status = status;
        this->capacity = capacity;
        this->availableSeats = capacity;
    }

    void setFlightStatus(FlightStatus status) { this->status = status; }

    int getAvailableSeats() { return availableSeats; }
    
    int getTotalSeats() { return capacity; }
    
    bool acquireSeat() {
        unique_lock<mutex> lock(flightMutex);
        if(getAvailableSeats() > 0) { 
            --availableSeats;
            cout << "Seat booked!" << endl;
            return true;
        }

        cout << "No seat available!" << endl;
        return false;
    }

    bool releaseSeat() {
        unique_lock<mutex> lock(flightMutex);
        if(getAvailableSeats() < getTotalSeats()) {
            ++availableSeats;
            cout << "Seat released!" << endl;
            return true;
        }

        cout << "No seat to release!" << endl;
        return false;
    }
    
    string getFlightId() { return flightId; }
    
    string getFlightName() { return flightName; }

    string getArrivalCity() { return arrivalCity; }

    void setArrivalCity(string arrivalCity) { this->arrivalCity = arrivalCity; }

    string getDestinationCity() { return destinationCity; }

    void setDestinationCity(string destinationCity) { this->destinationCity = destinationCity; }

    string getArrivalTime() { return arrivalTime; }

    void setArrivalTime(string arrivalTime) { this->arrivalTime = arrivalTime; }

    string getdepartureTime() { return departureTime; }

    void setdepartureTime(string departureTime) { this->departureTime = departureTime; }
};

class IPayment {
public:
    virtual void pay(double amount) = 0;    
};

// We can have more fields like phoneNumber, age, gender etc
class Passenger {
private:
    string name;
    string emailId;
    unordered_set<string> bookingIds;

public:
    Passenger(string name, string emailId):
        name(name), emailId(emailId) { }

    string getName() { return name; }

    unordered_set<string> getBookingIds() { return bookingIds; }

    void viewBookings() {
        cout << "************* Showing bookings for passenger: " << getName() << "***********" << endl;
        for(auto bookingId: getBookingIds()) {
            cout << bookingId << endl;
        }
    }

    void addBookingId(string bookingId) { bookingIds.insert(bookingId); }

    void removeBookingId(string bookingId) { bookingIds.erase(bookingId); }
};

class Staff {
private:
    string name;
    string staffId;

public:
    Staff(string name, string staffId): name(name), staffId(staffId) { }
};

class Booking {
private:
    string bookingId;
    Flight* flight;
    Passenger* passenger;
    BookingStatus status;

public:
    Booking(string bookingId, Flight* flight, Passenger* passenger, BookingStatus status):
        bookingId(bookingId), flight(flight), passenger(passenger), status(status) { }

    string getBookingId() { return bookingId; }

    Flight* getFlight() { return flight; }

    Passenger* getPassenger() { return passenger; }

    BookingStatus getStatus() { return status; }

    void setBookingStatus(BookingStatus status) { this->status = status; }

    void cancelBooking() { setBookingStatus(BookingStatus::Canceled); }

    void ViewBooking() {
        cout << "Booking details for Id: " << getBookingId() << endl;
        cout << "Passenger Name: "<< getPassenger()->getName() << endl;
        cout << "Booking Status: " << static_cast<std::underlying_type<BookingStatus>::type>(getStatus()) << endl;
        cout << "Flight Id: " << getFlight()->getFlightId() << 
            ", Flight Name:"<<getFlight()->getFlightName()<<endl;
    }
};

// Base class to handle price calculation logic
class ITicketPriceAdvisor {
public:
    virtual double calculatePrice(Flight* flight) = 0;
};

#pragma endregion

/////////////////////////////////////////

////////////////////////// Entity Implementations

#pragma region Entity Implementations

// dummy price logic implementation
class TicketPriceAdvisor: public ITicketPriceAdvisor {
public:
    double calculatePrice(Flight* flight) {
        return 1000;
    }
};

class CreditCard: public IPayment {
public:
    void pay(double amount) {
        cout << "Paid " << amount << " using Credit Card" << endl;
    }
};

#pragma endregion

////////////////////////////// Flight Management System
class FlightManagementSystem {
private:
    // <sourceCity_destinationCity, (Flights)>
    unordered_map<string, unordered_set<Flight*>> flights;

    uniform_int_distribution<int> distribution{0, 25};
    default_random_engine generator;
    const int BOOKING_ID_LENGTH = 10;
public:
    string generateBookingId() {
        string id;
        for(int i = 0; i < BOOKING_ID_LENGTH; i++)
            id += (char)('0' + distribution(generator));
        return id;
    }

    void addFlight(Flight* flight) {
        string journey = flight->getArrivalCity() + "_" + flight->getDestinationCity();
        flights[journey].insert(flight);
    }

    void removeFlight(Flight* flight) {
        string journey = flight->getArrivalCity() + "_" + flight->getDestinationCity();
        flights[journey].erase(flight);
    }

    void searchFlight(string arrivalCity, string destinationCity) {
        string journey = arrivalCity + "_" + destinationCity;
        
        cout << "Showing flights between " << arrivalCity << " and " << destinationCity << endl;
        for(auto flight: flights[journey]) {
            cout << "Flight Id: " << flight->getFlightId() << 
                ", DepartureTime: " << flight->getArrivalTime() << ", ArrivalTime: " <<flight->getdepartureTime()<< endl;
        }
    }

    Booking* bookFlight(Passenger* passenger, Flight* flight) {
        bool bookingSuccess = flight->acquireSeat();
        if(bookingSuccess) {
            string bookingId = generateBookingId();
            Booking* booking = new Booking(bookingId, flight, passenger, BookingStatus::PaymentPending);
            passenger->addBookingId(bookingId);
            cout << "Seat acquired successfully, please pay to confirm!" << endl;
            return booking;
        }
        else {
            cout << "Booking failed!" << endl;
            return nullptr;
        }
    }

    void cancelBooking(Booking* booking) {
        booking->cancelBooking();
        booking->getFlight()->releaseSeat();
        booking->getPassenger()->removeBookingId(booking->getBookingId());
        cout << "Booking canceled successfully for bookingId: " << booking->getBookingId() << endl;
    }

    void setBookingStatus(Booking* booking, BookingStatus status) { booking->setBookingStatus(status); }

    void viewFlightDetails(Flight* flight) {
        if(flight == nullptr) {
            cout << "Flight not found!" << endl;
            return;
        }
        cout << "Flight Id: " << flight->getFlightId() << 
                ", DepartureTime: " << flight->getArrivalTime() << ", ArrivalTime: " <<flight->getdepartureTime()<< endl;
    }

    void modifyFlightStatus(Flight* flight, FlightStatus status) { flight->setFlightStatus(status); }

    void modifyFlightArrivalCity(Flight* flight, string arrivalCity) { flight->setArrivalCity(arrivalCity); }

    void modifyFlightDestinationCity(Flight* flight, string destinationCity) { flight->setDestinationCity(destinationCity); }

    void modifyFlightArrivalTime(Flight* flight, string arrivalTime) { flight->setArrivalTime(arrivalTime); }

    void modifyFlightdepartureTime(Flight* flight, string departureTime) { flight->setdepartureTime(departureTime); }
};


////////////////////////// Main
int main() {
    FlightManagementSystem fms;
    CreditCard creditCardPayment;
    TicketPriceAdvisor priceAdvisor;

    Flight* flight = new Flight("1", "Airbus 320", "Delhi", "Mumbai", "10:00", "12:00", FlightStatus::OnTime, 100);
    fms.addFlight(flight);

    Flight* flight2 = new Flight("2", "Airbus 321 neo", "Mumbai", "Delhi", "10:00", "12:00", FlightStatus::OnTime, 100);
    fms.addFlight(flight2);

    Flight* flight3 = new Flight("3", "Boeing 737 Max", "Kolkata", "Mumbai", "10:00", "12:00", FlightStatus::OnTime, 100);
    fms.addFlight(flight3);

    Passenger* passenger1 = new Passenger("John Doe", "john@gmail.com");
    Passenger* passenger2 = new Passenger("Rahul", "rahul@gmail.com");

    fms.searchFlight("Delhi", "Mumbai");
    auto booking1 = fms.bookFlight(passenger1, flight);
    creditCardPayment.pay(priceAdvisor.calculatePrice(flight));
    fms.setBookingStatus(booking1, BookingStatus::Confirmed);
    booking1->ViewBooking();

    fms.bookFlight(passenger2, flight2);
    fms.bookFlight(passenger1, flight3);

    passenger1->viewBookings();

    fms.cancelBooking(booking1);

    passenger1->viewBookings();
    return 0;
}