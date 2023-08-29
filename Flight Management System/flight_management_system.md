# Flight Management System
This is a system that helps hotel owners and managers to manage the various operations in a hotel.

## Function Requirement

- Passenger should be able to:
  - Book flights
  - Search flights between airports
  - View flight details (flight number, departure city, arrival city, departure time, arrival time, flight status, and available seats)
  - View booking
  - Cancel booking

- Staff should be able to:
  - Set flight status
  - Modify flight details (change start and end city)
  - View flight information

## Non-Functional Requirement
- Scalable
- Testable
- Modular

## Diagrams

### Use-case Diagram
```mermaid
flowchart LR

Passenger --> PassengerUseCase

subgraph PassengerUseCase
SearchFlights
BookFlight
CancelFlight
ViewBooking
end

subgraph StaffUseCase
UpdateFlightStatus
ModifyFlightDetails
ViewFlightInformation
end

Staff --> StaffUseCase
```

### Class Diagram
```mermaid
classDiagram
    class Flight {
        -flightId: string
        -flightName: string
        -arrivalCity: string
        -destinationCity: string
        -arrivalTime: string
        -departureTime: string
        -status: FlightStatus
        -capacity: int
        -availableSeats: int
        +Flight(flightId: string, flightName: string, arrivalCity: string, destinationCity: string, arrivalTime: string, departureTime: string, status: FlightStatus, capacity: int)
        +setFlightStatus(status: FlightStatus): void
        +getAvailableSeats(): int
        +getTotalSeats(): int
        +acquireSeat(): bool
        +releaseSeat(): bool
        +getFlightId(): string
        +getFlightName(): string
        +getArrivalCity(): string
        +setArrivalCity(arrivalCity: string): void
        +getDestinationCity(): string
        +setDestinationCity(destinationCity: string): void
        +getArrivalTime(): string
        +setArrivalTime(arrivalTime: string): void
        +getdepartureTime(): string
        +setdepartureTime(departureTime: string): void
    }

    class Passenger {
        -name: string
        -emailId: string
        -bookingIds: unordered_set<string>
        +Passenger(name: string, emailId: string)
        +getName(): string
        +getBookingIds(): unordered_set<string>
        +viewBookings(): void
        +addBookingId(bookingId: string): void
        +removeBookingId(bookingId: string): void
    }

    class Booking {
        -bookingId: string
        -flight: Flight*
        -passenger: Passenger*
        -status: BookingStatus
        +Booking(bookingId: string, flight: Flight*, passenger: Passenger*, status: BookingStatus)
        +getBookingId(): string
        +getFlight(): Flight*
        +getPassenger(): Passenger*
        +getStatus(): BookingStatus
        +setBookingStatus(status: BookingStatus): void
        +cancelBooking(): void
        +ViewBooking(): void
    }

    class ITicketPriceAdvisor {
        +calculatePrice(flight: Flight*): double
    }

    class TicketPriceAdvisor {
        +calculatePrice(flight: Flight*): double
    }

    class IPayment {
        +pay(amount: double): void
    }

    class CreditCard {
        +pay(amount: double): void
    }

    class Staff {
        -name: string
        -staffId: string
        +Staff(name: string, staffId: string)
    }

    class FlightManagementSystem {
        -flights: unordered_map<string, unordered_set<Flight*>>
        -distribution: uniform_int_distribution<int>
        -generator: default_random_engine
        -BOOKING_ID_LENGTH: const int
        +generateBookingId(): string
        +addFlight(flight: Flight*): void
        +removeFlight(flight: Flight*): void
        +searchFlight(arrivalCity: string, destinationCity: string): void
        +bookFlight(passenger: Passenger*, flight: Flight*): Booking*
        +cancelBooking(booking: Booking*): void
        +setBookingStatus(booking: Booking*, status: BookingStatus): void
        +viewFlightDetails(flight: Flight*): void
        +modifyFlightStatus(flight: Flight*, status: FlightStatus): void
        +modifyFlightArrivalCity(flight: Flight*, arrivalCity: string): void
        +modifyFlightDestinationCity(flight: Flight*, destinationCity: string): void
        +modifyFlightArrivalTime(flight: Flight*, arrivalTime: string): void
        +modifyFlightdepartureTime(flight: Flight*, departureTime: string): void
    }

    class BookingStatus{
      <<Enumeration>>  
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

    class FlightStatus{
      <<Enumeration>>
      PaymentPending,
      Confirmed,
      Waitlisted,
      Canceled  
    }

    Flight <-- ITicketPriceAdvisor
    TicketPriceAdvisor --|> ITicketPriceAdvisor
    Booking o-- Flight
    Booking *-- Passenger
    IPayment <|.. CreditCard
    FlightManagementSystem --> Flight
    FlightManagementSystem --> Passenger
    FlightManagementSystem --> Booking

```

## Explanation