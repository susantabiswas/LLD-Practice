#include <iostream>
#include <vector>
#include <chrono>
#include <ctime>
using namespace std;

//////// Base Entities
class PaymentAdvisor {
public:
    virtual double calculateCharge(chrono::duration<double> duration) = 0;
};

class Vehicle {
private:
    string registrationNumber;
    string color;
    string vehicleType;
protected:
    chrono::time_point<chrono::system_clock> parkingStartTime;
    chrono::time_point<chrono::system_clock> parkingEndTime;
    PaymentAdvisor* paymentAdvisor;
public:
    Vehicle(string registration, string color, string vehicleType, PaymentAdvisor* paymentAdvisor):
        registrationNumber(registration), color(color), vehicleType(vehicleType), paymentAdvisor(paymentAdvisor) {};
    
    string getRegistrationNumber() { return registrationNumber; }

    string getColor() { return color; }
    
    string getVehicleType() { return vehicleType; }
    
    void park() { 
        this->parkingStartTime = chrono::system_clock::now(); 
        time_t start = chrono::system_clock::to_time_t(parkingStartTime);
        cout << "Car parked at: " << ctime(&start);
    }
    
    void unpark() { this->parkingEndTime = chrono::system_clock::now(); }
    
    chrono::time_point<chrono::system_clock> getParkingStartTime() { return parkingStartTime; }
    
    chrono::time_point<chrono::system_clock> getParkingEndTime() { return parkingEndTime; }
    
    chrono::duration<double> getParkingDuration() { return parkingEndTime - parkingStartTime; }
    
    double calculateCharge() { return this->paymentAdvisor->calculateCharge(this->getParkingDuration()); }
};

class ParkingTicket {
private:
    Vehicle* vehicle;
    // <floor, slotNumber>
    pair<int, int> parkedLocation = {-1, -1};
public:
    ParkingTicket(Vehicle* vehicle, pair<int, int> location): 
        vehicle(vehicle), parkedLocation(location) { }

    pair<int, int> getParkedLocation() { return parkedLocation; }

    Vehicle* getVehicle() { return vehicle; }
};

class PaymentMode {
public:
    virtual void pay(double amount) = 0;
};

//////////////////// Implementations
#pragma region Vehicles
class Car: public Vehicle {
public:
    Car(string registrationNumber, string color, PaymentAdvisor* paymentAdvisor):
        Vehicle(registrationNumber, color, "Car", paymentAdvisor) { }
};

class Bike: public Vehicle {
public:
    Bike(string registrationNumber, string color, PaymentAdvisor* paymentAdvisor):
        Vehicle(registrationNumber, color, "Bike", paymentAdvisor) { }
};

class Wheelchair: public Vehicle {
public:
    Wheelchair(string registrationNumber, string color, PaymentAdvisor* paymentAdvisor):
        Vehicle(registrationNumber, color, "Wheelchair", paymentAdvisor) { }
};
#pragma endregion

#pragma region Payment Advisors
class CarPaymentAdvisor: public PaymentAdvisor {
public:
    double calculateCharge(chrono::duration<double> duration) {
        return duration.count() * 2;
    }
};

class BikePaymentAdvisor: public PaymentAdvisor {
public:
    double calculateCharge(chrono::duration<double> duration) {
        return duration.count() * 1;
    }
};

class WheelchairPaymentAdvisor: public PaymentAdvisor {
public:
    double calculateCharge(chrono::duration<double> duration) {
        return 0;
    }   
};
#pragma endregion

#pragma region Payment Modes
class CreditCard: public PaymentMode {
public:
    void pay(double amount) {
        cout << "Paid " << amount << " using Credit Card" << endl;
    }
};

class DebitCard: public PaymentMode {
public:
    void pay(double amount) {
        cout << "Paid " << amount << " using Debit Card" << endl;
    }
};
#pragma endregion

/////////////////// Parking Lot 

class ParkingLot {
private:
    int floors;
    int slotsPerFloor;
    int freeSlots;
    vector<vector<ParkingTicket*>> multiLevelParking;
public:
    ParkingLot(int floors, int slotsPerFloor) { 
        this->floors = floors;
        this->slotsPerFloor = slotsPerFloor;
        multiLevelParking.resize(floors, vector<ParkingTicket*>(slotsPerFloor, nullptr));
        freeSlots = floors * slotsPerFloor;
    }

    pair<int, int> findFreeSlot() {
        for(int floor = 0; floor < floors; floor++) {
            for(int slot = 0; slot < slotsPerFloor; slot++) {
                if(multiLevelParking[floor][slot] == nullptr)
                    return {floor, slot};
            }
        }

        return {-1, -1};
    }

    ParkingTicket* park(Vehicle* vehicle) {
        if(freeSlots == 0) {
            cout << "No free slots available" << endl;
            return nullptr;
        }

        auto [floor, slot] = findFreeSlot();

        if(floor == -1 || slot == -1) {
            cout << "No free slots available" << endl;
            return nullptr;
        }

        multiLevelParking[floor][slot] = new ParkingTicket(vehicle, make_pair(floor, slot));
        vehicle->park();
        --freeSlots;
        cout << "Vehicle " << vehicle->getRegistrationNumber() << " parked at floor: " << floor << ", slotNumber: " << slot << endl;

        return multiLevelParking[floor][slot];
    }

    bool unpark(ParkingTicket* parkingTicket) {
        if(parkingTicket == nullptr) {
            cout << "Invalid Parking Ticket" << endl;
            return false;
        }

        auto [floor, slot] = parkingTicket->getParkedLocation();
        if(floor == -1 || slot == -1) {
            cout << "Cannot unpark! Invalid Parking Ticket" << endl;
            return false;
        }

        multiLevelParking[floor][slot] = nullptr;
        parkingTicket->getVehicle()->unpark();
        ++freeSlots;
        cout << "Vehicle " << parkingTicket->getVehicle()->getRegistrationNumber() << " unparked from floor: " << floor << ", slotNumber: " << slot << endl;

        return false;
    }

    double calculateParkingCharge(ParkingTicket* parkingTicket) {
        return parkingTicket->getVehicle()->calculateCharge();
    }

    int freeSlotsAvailable() {
        return freeSlots;
    }

    void generateBill(ParkingTicket* ticket) {
        if(ticket == nullptr) {
            cout << "Invalid ticket!";
            return;
        }
        time_t start = chrono::system_clock::to_time_t(ticket->getVehicle()->getParkingStartTime());
        time_t end = chrono::system_clock::to_time_t(ticket->getVehicle()->getParkingEndTime());

        cout << "**************** Parking Bill ****************\n";
        cout << "Bill for vehicle: " << ticket->getVehicle()->getRegistrationNumber() << endl;
        cout << "Parking Start:"<<ctime(&start)<<"Parking End:"<<ctime(&end);
        cout << "Parking Duration: " << ticket->getVehicle()->getParkingDuration().count() << 
            " secs, Hours: " << chrono::duration_cast<chrono::hours>(ticket->getVehicle()->getParkingDuration()).count()<<endl;
        cout << "Parking Charge: " << ticket->getVehicle()->calculateCharge() << endl;
    }
};

//////////////////////////

int main() {
    ParkingLot parkingLot(2, 2);
    
    // Payment mode
    CreditCard creditCard;
    DebitCard debitCard;

    // Vehicles
    Car car("KA-01-HH-1234", "White", new CarPaymentAdvisor());
    Car car2("KA-01-HH-9999", "Red", new CarPaymentAdvisor());
    Bike bike("KA-01-HH-7777", "Black", new BikePaymentAdvisor());
    Wheelchair wheelchair("", "Black", new WheelchairPaymentAdvisor());

    // Parking
    ParkingTicket* carTicket = parkingLot.park(&car);
    ParkingTicket* car2Ticket = parkingLot.park(&car2);

    cout << "Car Ticket: RegistrationNumber: "<<carTicket->getVehicle()->getRegistrationNumber() << " floor: " << carTicket->getParkedLocation().first << ", slotNumber: " << carTicket->getParkedLocation().second << endl;
    cout << "Car Ticket: RegistrationNumber: "<<car2Ticket->getVehicle()->getRegistrationNumber() << " floor: " << carTicket->getParkedLocation().first << ", slotNumber: " << carTicket->getParkedLocation().second << endl;
    cout << "Available Spots: " << parkingLot.freeSlotsAvailable() << endl;

    ParkingTicket* bikeTicket = parkingLot.park(&bike);
    cout << "Bike Ticket: RegistrationNumber: "<<car2Ticket->getVehicle()->getRegistrationNumber() << " floor: " << carTicket->getParkedLocation().first << ", slotNumber: " << carTicket->getParkedLocation().second << endl;
    
    cout << "Available Spots: " << parkingLot.freeSlotsAvailable() << endl;

    parkingLot.unpark(carTicket);
    cout << "Available Spots: " << parkingLot.freeSlotsAvailable() << endl;

    parkingLot.generateBill(carTicket);
    cout << "Paid Car Charge: " << endl;
    creditCard.pay(parkingLot.calculateParkingCharge(carTicket));

    return 0;
}