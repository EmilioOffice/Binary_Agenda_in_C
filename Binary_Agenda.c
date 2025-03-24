#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

/* For cross-platform sleeping:
   - On Windows, use Sleep(milliseconds).
   - On Unix-like systems, use usleep(microseconds). */
#ifdef _WIN32
  #include <windows.h>  // Sleep
  #define SLEEP_MS(ms) Sleep(ms)
#else
  #include <unistd.h>   // usleep
  #define SLEEP_MS(ms) usleep((ms) * 1000)
#endif

#include "Agenda.h"

int  showMenu();
void handleAdd();
void handleSearch();
void handlePlaceholder();
void handleExit();

int  createPeople(Person *people, int *count);
int  writePeopleToFile(const Person *people, int count, const char *filename);
int  readPeopleFromFile(Person *people, int *count, const char *filename);
Person searchPerson(Person *people, int count);
void   updatePersonInfo(Person *people, int count);
void   removePerson(Person *people, int *count);
void   inputName(Person *person);
void   inputAge(Person *person);
void   inputSalary(Person *person);

void playCliGame();

int main(void) {
    int option = 0;
    do {
        option = showMenu();
        switch(option) {
            case MENU_ADD:
                handleAdd();
                break;
            case MENU_SEARCH:
                handleSearch();
                break;
            case MENU_PLACEHOLDER:
                handlePlaceholder();
                break;
            case MENU_EXIT:
                handleExit();
                break;
            default:
                printf("Invalid option. Please try again.\n");
                break;
        }
    } while(option != MENU_EXIT);

    return 0;
}

int showMenu() {
    int choice = 0;
    printf("\n==========================\n");
    printf(" Welcome to your Agenda!\n");
    printf("==========================\n");
    printf("1) Add Person(s)\n");
    printf("2) Search (and Remove)\n");
    printf("3) (Placeholder: CLI Game)\n");
    printf("4) Exit\n");
    printf("==========================\n");
    printf("Select an option: ");
    scanf("%d", &choice);
    return choice;
}

void handleAdd() {
    Person *people = NULL;
    int count = 0;

    people = (Person *)malloc(sizeof(Person) * 1000);
    if(!people) {
        printf("Memory allocation error.\n");
        return;
    }

    if(!readPeopleFromFile(people, &count, AGENDA_FILENAME)) {
        printf("\n==================================================================\n");
        printf("No existing records or file not found. A new file will be created.\n");
        printf("==================================================================\n");
    }

    if(createPeople(people, &count)) {
        if(!writePeopleToFile(people, count, AGENDA_FILENAME)) {
            printf("\n============================\n");
            printf("Error writing to file.\n");
            printf("=============================\n");
        }
    }

    free(people);
}

/* 
 * Handle the 'Search' functionality.
 * Includes options to affect a person after searching
 */
void handleSearch() {
    Person *people = NULL;
    int count = 0;
    int updateChoice = 0;
    int removeChoice = 0;

    people = (Person *)malloc(sizeof(Person) * 1000);
    if(!people) {
        printf("Memory allocation error.\n");
        return;
    }

    if(!readPeopleFromFile(people, &count, AGENDA_FILENAME)) {
        printf("No records found.\n");
        free(people);
        return;
    }

    Person found = searchPerson(people, count);

    if(found.age == 0 && found.salary == 0 && strcmp(found.name, "") == 0) {
        printf("No matching person found.\n");
    } else {
        printf("\n==================================================================\n");
        printf("Do you want to update this person's info? (1 = Yes, 2 = No): ");
        printf("\n==================================================================\n");
        scanf("%d", &updateChoice);
        if(updateChoice == 1) {
            updatePersonInfo(people, count);
            writePeopleToFile(people, count, AGENDA_FILENAME);
        }
    }

    printf("\n=================================================\n");
    printf("Do you want to remove someone? (1=Yes, 2=No): ");
    scanf("%d", &removeChoice);
    printf("=================================================\n");
    if(removeChoice == 1) {
        removePerson(people, &count);
        writePeopleToFile(people, count, AGENDA_FILENAME);
    }

    free(people);
}

/* 
 * Handle the Placeholder feature: 
 * It only runs the CLI-animated game
 */
void handlePlaceholder() {
    printf("\n==================================================================\n");
    printf("Placeholder Feature: CLI-Animated Game\n");
    printf("==================================================================\n");

    playCliGame();
}

void handleExit() {
    printf("\n===================================================\n");
    printf("Thank you for using the Agenda! Have a great day!\n");
    printf("===================================================\n");
}

int createPeople(Person *people, int *count) {
    int n = 0, i;
    int confirm = 0;

    printf("How many people do you want to add? ");
    scanf("%d", &n);

    for(i = 0; i < n; i++) {
        printf("\n=============================\n");
        printf("\nEnter details for Person %d:\n", i + 1);
        inputName(&people[*count]);
        inputAge(&people[*count]);
        inputSalary(&people[*count]);

        printf("\n===================\n");
        printf("Verify the data:\n");
        printf("===================\n");
        printf("Name: %s\nAge: %d\nSalary: %d\n", 
            people[*count].name, 
            people[*count].age, 
            people[*count].salary
        );
        printf("===================\n");

        printf("\n=================================\n");
        printf("Is this correct? (1 = Yes, 2 = No): ");
        printf("\n=================================\n");
        scanf("%d", &confirm);
        if(confirm == 1) {
            (*count)++;
        } else {
            printf("Data for this person not saved. Skipping.\n");
        }
    }
    return 1;
}

int writePeopleToFile(const Person *people, int count, const char *filename) {
    FILE *fp = fopen(filename, "wb");
    if(!fp) {
        perror("Error opening file for writing");
        return 0;
    }
    fwrite(people, sizeof(Person), count, fp);
    fclose(fp);

    printf("Successfully wrote %d record(s) to %s\n", count, filename);
    return 1;
}

int readPeopleFromFile(Person *people, int *count, const char *filename) {
    FILE *fp = fopen(filename, "rb");
    if(!fp) {
        return 0;
    }

    fseek(fp, 0, SEEK_END);
    long fileSize = ftell(fp);
    rewind(fp);

    int totalRecords = fileSize / sizeof(Person);
    if(totalRecords <= 0) {
        fclose(fp);
        return 0;
    }

    fread(people, sizeof(Person), totalRecords, fp);
    fclose(fp);

    *count = totalRecords;
    return 1;
}

Person searchPerson(Person *people, int count) {
    int option = 0;
    Person emptyPerson = {"", 0, 0};
    char searchName[20];
    int searchAge, searchSalary, confirm;

    printf("\n==============================================\n");
    printf("Search by:\n1) Name\n2) Age\n3) Salary\nSelect: ");
    scanf("%d", &option);
    printf("\n==============================================\n");

    switch(option) {
        case 1:
            printf("Enter the name: ");
            scanf("%s", searchName);
            for(int i = 0; i < count; i++) {
                if(strcmp(people[i].name, searchName) == 0) {
                    printf("Match found:\n");
                    printf("=========================\n");
                    printf("Name: %s\nAge: %d\nSalary: %d\n", 
                           people[i].name, people[i].age, people[i].salary);
                    printf("=========================\n");
                    printf("\n=========================================\n");
                    printf("Is this the correct person? (1=Yes, 2=No): ");
                    scanf("%d", &confirm);
                    printf("\n=========================================\n");
                    if(confirm == 1) {
                        printf("Search successful.\n");
                        return people[i];
                    }
                }
            }
            break;
        case 2:
            printf("Enter the age: ");
            scanf("%d", &searchAge);
            for(int i = 0; i < count; i++) {
                if(people[i].age == searchAge) {
                    printf("Match found:\n");
                    printf("=========================\n");
                    printf("Name: %s\nAge: %d\nSalary: %d\n", 
                           people[i].name, people[i].age, people[i].salary);
                    printf("=========================\n");
                    printf("\n=========================================\n");
                    printf("Is this the correct person? (1=Yes, 2=No): ");
                    scanf("%d", &confirm);
                    printf("\n=========================================\n");
                    if(confirm == 1) {
                        printf("Search successful.\n");
                        return people[i];
                    }
                }
            }
            break;
        case 3:
            printf("Enter the salary: ");
            scanf("%d", &searchSalary);
            for(int i = 0; i < count; i++) {
                if(people[i].salary == searchSalary) {
                    printf("Match found:\n");
                    printf("=========================\n");
                    printf("Name: %s\nAge: %d\nSalary: %d\n", 
                           people[i].name, people[i].age, people[i].salary);
                    printf("=========================\n");
                    printf("\n=========================================\n");
                    printf("Is this the correct person? (1=Yes, 2=No): ");
                    scanf("%d", &confirm);
                    printf("\n=========================================\n");
                    if(confirm == 1) {
                        printf("Search successful.\n");
                        return people[i];
                    }
                }
            }
            break;
        default:
            printf("\n\n============================\n");
            printf("Invalid search option.\n");
            printf("============================\n");
            break;
    }
    printf("\n\n============================\n");
    printf("No matching person found.\n");
    printf("============================\n");
    return emptyPerson;
}

void updatePersonInfo(Person *people, int count) {
    char name[MAX_NAME_LEN];
    int option, newAge, newSalary;
    int found = 0;

    printf("\n=======================================\n");
    printf("Enter the name of the person to update: ");
    scanf("%s", name);
    printf("\n=======================================\n");

    for(int i = 0; i < count; i++) {
        if(strcmp(people[i].name, name) == 0) {
            found = 1;
            printf("Person found:\n");
            printf("============================\n");
            printf("Name: %s\nAge: %d\nSalary: %d\n", 
                   people[i].name, people[i].age, people[i].salary);
            printf("============================\n");
            printf("What do you want to update?\n");
            printf("1) Age\n2) Salary\n3) Both\n4) Cancel\n");
            scanf("%d", &option);
            switch(option) {
                case 1:
                    printf("============================\n");
                    printf("Enter new age: ");
                    scanf("%d", &newAge);
                    printf("\n============================\n");
                    people[i].age = newAge;
                    break;
                case 2:
                    printf("============================\n");
                    printf("Enter new salary: ");
                    scanf("%d", &newSalary);
                    printf("\n============================\n");
                    people[i].salary = newSalary;
                    break;
                case 3:
                    printf("============================\n");
                    printf("Enter new age: ");
                    scanf("%d", &newAge);
                    printf("\n============================\n");
                    people[i].age = newAge;
                    printf("============================\n");
                    printf("Enter new salary: ");
                    scanf("%d", &newSalary);
                    printf("\n============================\n");
                    people[i].salary = newSalary;
                    break;
                case 4:
                    printf("No changes made.\n");
                    break;
                default:
                    printf("Invalid option.\n");
                    break;
            }
            printf("\n============================\n");
            printf("Updated info:\n");
            printf("Name: %s\nAge: %d\nSalary: %d\n", 
                   people[i].name, people[i].age, people[i].salary);
            printf("============================\n");
            break;
        }
    }
    if(!found) {
        printf("Person not found.\n");
    }
}

void removePerson(Person *people, int *count) {
    int idx = 0;
    if(*count == 0) {
        printf("No persons to remove.\n");
        return;
    }

    printf("\n==========================================\n");
    printf("Persons in the agenda:\n");
    for(int i = 0; i < *count; i++) {
        printf("[%d] Name: %s | Age: %d | Salary: %d\n", 
               i+1, people[i].name, people[i].age, people[i].salary);
    }

    printf("\nEnter the number of the person to remove: ");
    scanf("%d", &idx);

    if(idx >= 1 && idx <= *count) {
        for(int j = idx - 1; j < (*count - 1); j++) {
            people[j] = people[j + 1];
        }
        (*count)--;
        printf("\n==============================\n");
        printf("Person removed successfully.\n");
        printf("==============================\n");
    } else {
        printf("\n===================\n");
        printf("Invalid index.\n");
        printf("===================\n");
    }
}

void inputName(Person *person) {
    printf("\n===========================\n");
    printf("Enter name: ");
    scanf("%s", person->name);
    printf("\n===========================\n");
}

void inputAge(Person *person) {
    printf("\n===========================\n");
    printf("Enter age: ");
    scanf("%d", &person->age);
    printf("\n===========================\n");
}

void inputSalary(Person *person) {
    printf("\n===========================\n");
    printf("Enter salary: ");
    scanf("%d", &person->salary);
    printf("\n===========================\n");
}

/* 
 * CLI-Animated Game (Placeholder).
 *  - Displays a spinner animation
 *  - Rolls a dice
 *  - Waits for user input before returning
 */
void playCliGame() {
    printf("\n==========================================\n");
    printf("Welcome to the CLI Animated Game!\n");
    printf("==========================================\n");

    const char spinner[4] = {'|', '/', '-', '\\'};
    for(int i = 0; i < 20; i++) {
        printf("\rLoading game... %c", spinner[i % 4]);
        fflush(stdout);
        SLEEP_MS(200);
    }
    printf("\nGame Loaded!\n");

    srand((unsigned)time(NULL));
    int dice = (rand() % 6) + 1;
    printf("You rolled a %d!\n", dice);

    printf("\nPress Enter to continue...");
    int c;
    while((c = getchar()) != '\n' && c != EOF) {}
    getchar();

    printf("\nReturning to main menu...\n");
}
