#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_ROOMS 10

// Structure to store room information
struct Room {
    int roomNumber;
    int isOccupied;  // 0 = vacant, 1 = occupied
    char guestName[50];
    int nights;
};

// Function prototypes
void displayMenu();
void checkIn(struct Room rooms[], int *totalGuests);
void checkOut(struct Room rooms[], int *totalGuests);
void displayRooms(struct Room rooms[]);
void initializeRooms(struct Room rooms[]);

int main() {
    struct Room rooms[MAX_ROOMS];
    int choice;
    int totalGuests = 0;

    // Initialize all rooms as vacant
    initializeRooms(rooms);

    printf("========================================\n");
    printf("   WELCOME TO SUNNY HOTEL MANAGEMENT   \n");
    printf("========================================\n\n");

    while(1) {
        displayMenu();
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar(); // Clear newline from buffer

        switch(choice) {
            case 1:
                checkIn(rooms, &totalGuests);
                break;
            case 2:
                checkOut(rooms, &totalGuests);
                break;
            case 3:
                displayRooms(rooms);
                break;
            case 4:
                printf("\nThank you for using Sunny Hotel Management System!\n");
                printf("Goodbye!\n");
                exit(0);
            default:
                printf("\nInvalid choice! Please try again.\n\n");
        }
    }

    return 0;
}

// Initialize all rooms as vacant
void initializeRooms(struct Room rooms[]) {
    int i;
    for(i = 0; i < MAX_ROOMS; i++) {
        rooms[i].roomNumber = 101 + i;  // Rooms numbered 101-110
        rooms[i].isOccupied = 0;
        strcpy(rooms[i].guestName, "");
        rooms[i].nights = 0;
    }
}

// Display main menu
void displayMenu() {
    printf("\n========================================\n");
    printf("           MAIN MENU\n");
    printf("========================================\n");
    printf("1. Check-in\n");
    printf("2. Check-out\n");
    printf("3. Display All Rooms\n");
    printf("4. Exit\n");
    printf("========================================\n");
}

// Check-in function
void checkIn(struct Room rooms[], int *totalGuests) {
    int roomChoice, nights, i;
    char guestName[50];

    printf("\n--- CHECK-IN ---\n");

    // Display available rooms
    printf("\nAvailable Rooms:\n");
    int hasVacant = 0;
    for(i = 0; i < MAX_ROOMS; i++) {
        if(rooms[i].isOccupied == 0) {
            printf("Room %d\n", rooms[i].roomNumber);
            hasVacant = 1;
        }
    }

    if(!hasVacant) {
        printf("Sorry! All rooms are occupied.\n");
        return;
    }

    printf("\nEnter room number to book: ");
    scanf("%d", &roomChoice);
    getchar(); // Clear newline

    // Find the room
    int roomIndex = -1;
    for(i = 0; i < MAX_ROOMS; i++) {
        if(rooms[i].roomNumber == roomChoice) {
            roomIndex = i;
            break;
        }
    }

    if(roomIndex == -1) {
        printf("Invalid room number!\n");
        return;
    }

    if(rooms[roomIndex].isOccupied == 1) {
        printf("Sorry! This room is already occupied.\n");
        return;
    }

    // Get guest details
    printf("Enter guest name: ");
    fgets(guestName, 50, stdin);
    guestName[strcspn(guestName, "\n")] = 0; // Remove newline

    printf("Enter number of nights: ");
    scanf("%d", &nights);

    // Update room information
    strcpy(rooms[roomIndex].guestName, guestName);
    rooms[roomIndex].nights = nights;
    rooms[roomIndex].isOccupied = 1;
    (*totalGuests)++;

    printf("\n*** CHECK-IN SUCCESSFUL ***\n");
    printf("Room %d has been assigned to %s for %d night(s).\n",
           roomChoice, guestName, nights);
}

// Check-out function
void checkOut(struct Room rooms[], int *totalGuests) {
    int roomChoice, i;
    float billAmount;
    const float pricePerNight = 100.0;

    printf("\n--- CHECK-OUT ---\n");

    // Display occupied rooms
    printf("\nOccupied Rooms:\n");
    int hasOccupied = 0;
    for(i = 0; i < MAX_ROOMS; i++) {
        if(rooms[i].isOccupied == 1) {
            printf("Room %d - Guest: %s\n", rooms[i].roomNumber, rooms[i].guestName);
            hasOccupied = 1;
        }
    }

    if(!hasOccupied) {
        printf("No rooms are currently occupied.\n");
        return;
    }

    printf("\nEnter room number to check-out: ");
    scanf("%d", &roomChoice);

    // Find the room
    int roomIndex = -1;
    for(i = 0; i < MAX_ROOMS; i++) {
        if(rooms[i].roomNumber == roomChoice) {
            roomIndex = i;
            break;
        }
    }

    if(roomIndex == -1) {
        printf("Invalid room number!\n");
        return;
    }

    if(rooms[roomIndex].isOccupied == 0) {
        printf("This room is already vacant!\n");
        return;
    }

    // Calculate bill
    billAmount = rooms[roomIndex].nights * pricePerNight;

    printf("\n*** CHECK-OUT SUMMARY ***\n");
    printf("Guest Name: %s\n", rooms[roomIndex].guestName);
    printf("Room Number: %d\n", rooms[roomIndex].roomNumber);
    printf("Nights Stayed: %d\n", rooms[roomIndex].nights);
    printf("Total Bill: $%.2f\n", billAmount);

    // Clear room information
    strcpy(rooms[roomIndex].guestName, "");
    rooms[roomIndex].nights = 0;
    rooms[roomIndex].isOccupied = 0;
    (*totalGuests)--;

    printf("\n*** CHECK-OUT SUCCESSFUL ***\n");
    printf("Thank you for staying with us!\n");
}

// Display all rooms and their status
void displayRooms(struct Room rooms[]) {
    int i;

    printf("\n========================================\n");
    printf("         ROOM STATUS\n");
    printf("========================================\n");
    printf("Room No.\tStatus\t\tGuest Name\n");
    printf("========================================\n");

    for(i = 0; i < MAX_ROOMS; i++) {
        printf("%d\t\t", rooms[i].roomNumber);
        if(rooms[i].isOccupied == 1) {
            printf("Occupied\t%s\n", rooms[i].guestName);
        } else {
            printf("Vacant\t\t--\n");
        }
    }
    printf("========================================\n");
}
