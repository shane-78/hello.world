#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_BOOKS 100
#define MAX_BORROWERS 50
#define MAX_NAME_LENGTH 50
#define MAX_TITLE_LENGTH 100

struct Book {
    int id;
    char title[MAX_TITLE_LENGTH];
    int isAvailable;
};

struct Borrower {
    int id;
    char name[MAX_NAME_LENGTH];
    int borrowedBookId;
    time_t dueDate;
};

struct Book library[MAX_BOOKS];
struct Borrower borrowers[MAX_BORROWERS];

int bookCount = 0;
int borrowerCount = 0;

void addBook() {
    if (bookCount >= MAX_BOOKS) 
    {
        printf("Library is full. Cannot add more books.\n");
        return;
    }

    struct Book newBook;
    newBook.id = bookCount + 1;
    printf("Enter book title: ");
    scanf(" %[^\n]s", newBook.title);
    newBook.isAvailable = 1;

    library[bookCount] = newBook;
    bookCount++;
    printf("Book added successfully.\n");
}

void displayBooks() {
    printf("\nLibrary Books:\n");
    printf("ID   Title\n");
    printf("--------------\n");
    for (int i = 0; i < bookCount; i++)
    {
        printf("%-4d %s\n", library[i].id, library[i].title);
    }
}

void lendBook() {
    if (bookCount == 0 || borrowerCount == 0)
    {
        printf("No books or borrowers available for lending.\n");
        return;
    }

    int borrowerId, bookId;
    printf("Enter borrower ID: ");
    scanf("%d", &borrowerId);

    printf("Enter book ID: ");
    scanf("%d", &bookId);

    if (borrowerId < 1 || borrowerId > borrowerCount || bookId < 1 || bookId > bookCount) 
    {
        printf("Invalid borrower or book ID.\n");
        return;
    }

    struct Borrower* borrower = &borrowers[borrowerId - 1];
    struct Book* book = &library[bookId - 1];

    if (!book->isAvailable) {
        printf("Book is already lent.\n");
        return;
    }

    borrower->borrowedBookId = book->id;

    time_t currentTime;
    time(&currentTime);
    borrower->dueDate = currentTime + 7 * 24 * 3600;

    book->isAvailable = 0;
    printf("Book lent successfully.\n");
}

void returnBook() 
{
    if (bookCount == 0 || borrowerCount == 0)
    {
        printf("No books or borrowers available for returning.\n");
        return;
    }

    int borrowerId;
    printf("Enter borrower ID: ");
    scanf("%d", &borrowerId);

    if (borrowerId < 1 || borrowerId > borrowerCount)
    {
        printf("Invalid borrower ID.\n");
        return;
    }

    struct Borrower* borrower = &borrowers[borrowerId - 1];

    if (borrower->borrowedBookId == -1) {
        printf("This borrower has not borrowed any books.\n");
        return;
    }

    struct Book* book = &library[borrower->borrowedBookId - 1];
    time_t currentTime;
    time(&currentTime);

    if (currentTime > borrower->dueDate) {
        int daysOverdue = (int)((currentTime - borrower->dueDate) / (24 * 3600));
        printf("Book is overdue by %d days. Please collect a fine.\n", daysOverdue);
    }

    borrower->borrowedBookId = -1;
    book->isAvailable = 1;
    printf("Book returned successfully.\n");
}

// Function to add a borrower
void addBorrower() {
    if (borrowerCount >= MAX_BORROWERS) {
        printf("Borrower limit reached. Cannot add more borrowers.\n");
        return;
    }

    struct Borrower newBorrower;
    newBorrower.id = borrowerCount + 1;
    printf("Enter borrower name: ");
    scanf(" %[^\n]s", newBorrower.name);
    newBorrower.borrowedBookId = -1; 
    time(&newBorrower.dueDate); 

    borrowers[borrowerCount] = newBorrower;
    borrowerCount++;
    printf("Borrower added successfully.\n");
}

void displayBorrowers() {
    printf("\nBorrowers:\n");
    printf("ID   Name\n");
    printf("--------------\n");
    for (int i = 0; i < borrowerCount; i++) {
        printf("%-4d %s\n", borrowers[i].id, borrowers[i].name);
    }
}

int main() {
    int choice;

    do {
        printf("\nLibrary Management System\n");
        printf("1. Add Book\n");
        printf("2. Display Books\n");
        printf("3. Lend Book\n");
        printf("4. Return Book\n");
        printf("5. Add Borrower\n");
        printf("6. Display Borrowers\n");
        printf("0. Quit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addBook();
                break;
            case 2:
                displayBooks();
                break;
            case 3:
                lendBook();
                break;
            case 4:
                returnBook();
                break;
            case 5:
                addBorrower();
                break;
            case 6:
                displayBorrowers();
                break;
            case 0:
                printf("Goodbye!\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 0);

    return 0;
}
