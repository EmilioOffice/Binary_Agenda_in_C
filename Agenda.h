#define AGENDA_FILENAME "agenda.bin"
#define MAX_NAME_LEN 15

/* Menu options */
#define MENU_ADD         1
#define MENU_SEARCH      2
#define MENU_PLACEHOLDER 3
#define MENU_EXIT        4

/* Structure to store a person's info */
typedef struct {
    char name[MAX_NAME_LEN];
    int age;
    int salary;
} Person;