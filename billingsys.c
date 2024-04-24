#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

#define MAX_USERNAME_LENGTH 20
#define MAX_PASSWORD_LENGTH 20
#define MAX_ITEMS 10
#define MAX_ITEM_NAME_LENGTH 50
#define MAX_ITEM_COUNT 100


struct Customer {
    char name[50];
    char address[100];
    char customer_id[10];
};


struct Item {
    char name[MAX_ITEM_NAME_LENGTH];
    double price;
    int quantity;
};


struct Transaction {
    struct Customer customer;
    struct Item items[MAX_ITEMS];
    int itemCount;
    double totalAmount;
    time_t dateTime;
};


int authenticate(char username[], char password[]);
void inputCustomerDetails(struct Customer *customer);
void displayMenu();
float getPrice(int choice);
void addToBill(struct Transaction *transaction, int choice, int quantity);

int main() {
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];

   
    printf("Welcome to the Billing System\n");
    printf("Enter your username: ");
    fgets(username, MAX_USERNAME_LENGTH, stdin);
    username[strcspn(username, "\n")] = 0; 

    printf("Enter your password: ");
    fgets(password, MAX_PASSWORD_LENGTH, stdin);
    password[strcspn(password, "\n")] = 0; 

    if (authenticate(username, password)) {
        printf("Login successful. Welcome, %s!\n", username);

        
        struct Customer customer;
        inputCustomerDetails(&customer);

        
        struct Transaction transaction;
        transaction.customer = customer;
        transaction.itemCount = 0;
        transaction.totalAmount = 0.0;
        transaction.dateTime = time(NULL);

        
        int choice, quantity;
        do {
            displayMenu();
            printf("Enter your choice (1-11): ");
            scanf("%d", &choice);

            if (choice >= 1 && choice <= 10) {
                printf("Enter the quantity: ");
                scanf("%d", &quantity);
                addToBill(&transaction, choice, quantity);
            } else if (choice != 11) {
                printf("\nInvalid choice. Please try again.\n");
            }
        } while (choice != 11);

        
        printf("\n\nCustomer Information:\n");
        printf("Name: %s\n", transaction.customer.name);
        printf("Address: %s\n", transaction.customer.address);
        printf("Customer ID: %s\n", transaction.customer.customer_id);
        printf("\nDate and Time of Purchase: %s", asctime(localtime(&transaction.dateTime)));
        printf("\n****************************************\n");
        printf("\nItems Purchased:\n");
        for (int i = 0; i < transaction.itemCount; i++) {
            printf("%d. %s - Quantity : %d\n", i + 1, transaction.items[i].name, transaction.items[i].quantity);
        }
        printf("\nTotal Amount: Rs%.2f\n", transaction.totalAmount);
    } else {
        printf("Invalid username or password. Please try again.\n");
    }

    return 0;
}


int authenticate(char username[], char password[]) {
    
    char correctUsername[] = "admin";
    char correctPassword[] = "admin123";

    
    if (strcmp(username, correctUsername) == 0 && strcmp(password, correctPassword) == 0) {
        return 1; 
    } else {
        return 0; 
    }
}


void inputCustomerDetails(struct Customer *customer) {
    printf("\nEnter customer name: ");
    fgets(customer->name, sizeof(customer->name), stdin);
    customer->name[strcspn(customer->name, "\n")] = 0; 

    printf("Enter customer address: ");
    fgets(customer->address, sizeof(customer->address), stdin);
    customer->address[strcspn(customer->address, "\n")] = 0; 

    printf("Enter customer ID: ");
    fgets(customer->customer_id, sizeof(customer->customer_id), stdin);
    customer->customer_id[strcspn(customer->customer_id, "\n")] = 0; 
}


void displayMenu() {
    printf("\n\n**************** MENU ****************\n");
    printf("1. Chocolates - Rs10\n");
    printf("2. Pens       - Rs15\n");
    printf("3. Pencils    - Rs20\n");
    printf("4. Soaps      - Rs34.08\n");
    printf("5. Maggie     - Rs22\n");
    printf("6. Chips      - Rs33.55\n");
    printf("7. Ice cream  - Rs50\n");
    printf("8. Juices     - Rs55\n");
    printf("9. Brush      - Rs11.18\n");
    printf("10. Cupcake   - Rs40.45 \n");
    printf("11. Exit\n");
}


float getPrice(int choice) {
    switch (choice) {
        case 1: return 10.0;
        case 2: return 15.0;
        case 3: return 20.0;
        case 4: return 34.08;
        case 5: return 22.0;
        case 6: return 33.55;
        case 7: return 50.0;
        case 8: return 55.0;
        case 9: return 11.18;
        case 10: return 40.45;
        default: return 0.0;
    }
}


void addToBill(struct Transaction *transaction, int choice, int quantity) {
    if (transaction->itemCount < MAX_ITEMS) {
        struct Item item;
        switch (choice) {
            case 1: strcpy(item.name, "Chocolates"); break;
            case 2: strcpy(item.name, "Pens"); break;
            case 3: strcpy(item.name, "Pencils"); break;
            case 4: strcpy(item.name, "Soaps"); break;
            case 5: strcpy(item.name, "Maggie"); break;
            case 6: strcpy(item.name, "Chips"); break;
            case 7: strcpy(item.name, "Ice cream"); break;
            case 8: strcpy(item.name, "Juices"); break;
            case 9: strcpy(item.name, "Brush"); break;
            case 10: strcpy(item.name, "Cupcake"); break;
            default: return;
        }
        item.price = getPrice(choice);
        item.quantity = quantity;

        transaction->items[transaction->itemCount++] = item;
        transaction->totalAmount += (item.price * quantity);

        printf("\n%s (Quantity: %d) added to the bill.\n", item.name, quantity);
    } else {
        printf("\nMaximum items reached. Cannot add more.\n");
    }
}
