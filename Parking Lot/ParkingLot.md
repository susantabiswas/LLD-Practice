# Parking Lot

## Functional Requirement
- Park different vehicles - Cars, Bikes and Handicapped Vehicles
- Unpark the vehicles
- Check availability of parking spots on a specific floor
- Track parking time of each vehicle
- Calculate cost of parking for different vehicle types

## Non-Functional Requirement
- Scalable and extensible
- Easy to test and understand
- Efficient and quickly respond to user requests

## Use-Case Diagram
```mermaid
flowchart LR

subgraph UseCase
Park
Unpark
Pay
AvailableSpots
CalculateParkingCharge
CalculateParkingTime
end

subgraph Operator
Attendent-->Park
Attendent-->Unpark
Attendent-->AvailableSpots
Attendent-->CalculateParkingCharge
Attendent-->GenerateBill
Attendent-->CalculateParkingTime
end

subgraph Customer
Cx-->Park
Cx-->Unpark
Cx-->Pay
Cx-->GenerateBill
end
```

## Entities
- Vehicle
  - TwoWheeler, FourWheeler, Wheelchair
- PaymentAdvisor
  - CreditCard, DebitCard, UPI
- PaymentMode
- ParkingTicket
- ParkingLot
  

## Class Diagram
```mermaid
classDiagram
  direction TB
    Vehicle <|.. Car
    Vehicle <|.. Bike
    Vehicle <|.. Wheelchair
    
    PaymentAdvisor --* Vehicle
    PaymentAdvisor <|.. CarPaymentAdvisor
    PaymentAdvisor <|.. BikePaymentAdvisor
    PaymentAdvisor <|.. WheelchairPaymentAdvisor

    PaymentMode <|.. CreditCard
    PaymentMode <|.. DebitCard

    ParkingTicket --* ParkingLot

    ParkingTicket --* Vehicle

    class Vehicle{
      -string registrationNumber
      -string color
      -string vehicleType
      #PaymentAdvisor* paymentAdvisor
      #parkingStartTime(): time_point
      #parkingEndTime(): time_point
      +getRegistrationNumber(): string
      +getColor(): string
      +getVehicleType(): string
      +park(): void
      +unpark(): void
      +getParkingStartTime(): time_point<chrono::system_clock>
      +getParkingEndTime(): time_point<chrono::system_clock>
      +getParkingDuration(): duration<double>
      +calculateCharge(): double
    }

    class PaymentAdvisor{
      +calculateCharge(duration<double> duration): double
    }

    class ParkingTicket{
      -Vehicle* vehicle
      -pair<int, int> parkedLocation
      +getParkedLocation(): pair<int, int> 
      +getVehicle(): Vehicle*
    }

    class PaymentMode{
      +pay(double amount)*: void
    }

    class ParkingLot{
      -int floors
      -int slotsPerFloor
      -int freeSlots
      -vector<vector<ParkingTicket*>> multiLevelParking
      +findFreeSlot(): pair<int, int> 
      +park(Vehicle* vehicle): ParkingTicket* 
      +unpark(ParkingTicket* parkingTicket): bool 
      +calculateParkingCharge(ParkingTicket* parkingTicket): double 
      +freeSlotsAvailable(): int 
      +generateBill(ParkingTicket* ticket): void 
    }

    class CreditCard{
      +pay(double amount): void
    }

    class DebitCard{
      +pay(double amount): void
    }

    class CarPaymentAdvisor{
      +calculateCharge(chrono::duration<double> duration): double
    }

    class BikePaymentAdvisor{
      +calculateCharge(chrono::duration<double> duration): double
    }

    class WheelchairPaymentAdvisor{
      +calculateCharge(chrono::duration<double> duration): double
    }
```