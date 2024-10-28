#include <stdlib.h>
#include <stdio.h>
#include <string.h>




//Name: Shaza Ghawanmeh
//Student ID: 260960872
//Major: Computer Science & Economics
//Mini Assignment 5: Dynamic Memory and File I/O


/*Ex. 1 — A University Personnel Information System
This program is a personnel information system for a university.
It allows the user to enter the information of a new person,
and then displays the information of all people in record.
The program uses dynamic memory allocation to store the information of each person.
The program also uses file I/O to write the records to a file.
*/


// Record / Node for the linked list.
// You MUST use the exact structure. No modification allowed.
typedef struct PersonalInfoRecord {
    char id[10];
    char ptype;
    char name[31];

    union {
        struct {
            char dept[31];
            int hireyear;
            char tenured;
        } prof;
        struct {
            char faculty[31];
            int admyear;
        } stud;
    } info;

    struct PersonalInfoRecord *next;
} PersonalInfoRecord;
//
// Use this in your code as
// PersonalInfoRecord pir; PersonalInfoRecord *pirp; etc ...
//

// Whatever other functions you need.


//function that will either update the linked list or add a new node to the linked list


typedef struct prev prev;

struct PersonalInfoRecord* addNode(PersonalInfoRecord **head, PersonalInfoRecord* pir) { //
    //fill in
    //add node in the correct position in the list according to id ascending
    PersonalInfoRecord* temp = *head;
    PersonalInfoRecord* prev = NULL;
    //make them atoi then compare integers
    while (temp != NULL && atoi(temp->id) < atoi(pir->id)) { //if the id of the node is less than the id of the new node
        prev = temp;
        temp = temp->next;
    }
    if (prev == NULL) { //if the new node is the first node in the list
        pir->next = *head;
        *head = pir;
    } else { //if the new node is not the first node in the list
        pir->next = temp;
        prev->next = pir;
    }
    return *head;
}




struct PersonalInfoRecord* updateList(PersonalInfoRecord** head, PersonalInfoRecord * pir) {
    PersonalInfoRecord* temp = *head;
    while (temp != NULL) {
        if (strcmp(temp->id, pir->id) == 0) //if the id of the node is the same as the id of the new node
        {
            //loop through both the node that is in our LL and the input record
            //if the input record has a value that is not null, then update the node with the new value
            //if the input record has a value that is null, then keep the value of the node
            //check if he is a student or a professor
            if (temp->ptype == 'S') {
                if (strcmp(pir->info.stud.faculty, "") != 0) {
                    strcpy(temp->info.stud.faculty, pir->info.stud.faculty);
                }
                if (pir->info.stud.admyear != 0) {
                    temp->info.stud.admyear = pir->info.stud.admyear;
                }
            } else if (temp->ptype == 'P') {
                if (strcmp(pir->info.prof.dept, "") != 0) {
                    strcpy(temp->info.prof.dept, pir->info.prof.dept);
                }
                if (pir->info.prof.hireyear != 0) {
                    temp->info.prof.hireyear = pir->info.prof.hireyear;
                }
                if (pir->info.prof.tenured != '\0') {
                    //strcpy((char *) temp->pir->info.prof.tenured, (const char *) pir->info.prof.tenured);
                    temp->info.prof.tenured = pir->info.prof.tenured;
                }
            }
            return *head;
        }
        temp =temp->next;
        //if the id of the node is not the same as the id of the new node, then add the new node to the end of the linked list

    }
    //call addNode function
    addNode(head, pir);
}



/*
//function that will find the node with the given id and delete it from the linked list
struct PersonalInfoRecord* deleteNode(PersonalInfoRecord** head, char* id) {
    PersonalInfoRecord*temp = *head;
    PersonalInfoRecord*prev = NULL;
    if (*head != NULL && strcmp((*head)->id, id) == 0) //if the head node is the node we want to delete
    {
        *head = (*head)->next;
        free(temp);
        return *head;
    }
    while (temp != NULL && strcmp(temp->id, id) != 0) //if the head node is not the node we want to delete
{
prev = temp;
temp = temp->next;
}
if (temp == NULL) //if the node is not in the linked list
{
return *head;
}
prev->next = temp->next;
free(temp);
}
*/

//function that will find the node with the given id and delete it from the linked list
struct PersonalInfoRecord* deleteNode(PersonalInfoRecord** head, char* id) {
    PersonalInfoRecord* temp = *head;
    PersonalInfoRecord* prev = NULL;
    while (temp != NULL && strcmp(temp->id, id) != 0) {
        prev = temp;
        temp = temp->next;
    }
    if (temp == NULL) {
        return *head;
    }
    if (prev == NULL) {
        *head = temp->next;
    } else {
        prev->next = temp->next;
    }
    free(temp);
    return *head;
}

//write the linked list to the file the user entered in the command line after the program name
//the file will be overwritten if it already exists
//if the file does not exist, then it will be created
//free the memory of the linked list after writing it to the file
//then terminate the program
//if it cannot open the file, then print an error message and terminate the program with code 3

void writeToFile(PersonalInfoRecord** head, char* filename) {
    FILE* fp = fopen(filename, "w");
    if (fp == NULL) {
        printf("Error: cannot open file %s\n", filename);
        exit(3);
    }
    PersonalInfoRecord* temp = *head;
    while (temp != NULL) {
        fprintf(fp, "%s,%c,%s", temp->id, temp->ptype, temp->name);
        if (temp->ptype == 'S') {
            fprintf(fp, ",%s,%d", temp->info.stud.faculty, temp->info.stud.admyear);
        } else if (temp->ptype == 'P') {
            fprintf(fp, " %s,%d,%c", temp->info.prof.dept, temp->info.prof.hireyear, temp->info.prof.tenured);
        }
        fprintf(fp, "\n");
        temp = temp->next;
    }
    fclose(fp);
    PersonalInfoRecord* temp2 = *head;
    while (temp2 != NULL) {
        PersonalInfoRecord* temp3 = temp2;
        temp2 = temp2->next;
        free(temp3);
    }
    exit(0);
}

//function that will print the linked list
void printList(PersonalInfoRecord* head) {
    PersonalInfoRecord* temp = head;
    while (temp != NULL) {
        printf("%s,%c,%s", temp->id, temp->ptype, temp->name);
        if (temp->ptype == 'S') {
            printf(",%s,%d", temp->info.stud.faculty, temp->info.stud.admyear);
        } else if (temp->ptype == 'P') {
            printf(",%s,%d,%c", temp->info.prof.dept, temp->info.prof.hireyear, temp->info.prof.tenured);
        }
        printf("\n");
        temp = temp->next;
    }
}

//char *strsep(char **pString, const char *string); //strsep function


// The main of your application
int main(int argc, char *argv[]) {
    char inputbuffer[100], *input; // to store each input line;

    // declare other variables as needed, etc.
    //PersonalInfoRecord *pir = malloc(sizeof(PersonalInfoRecord)); //pointer to a PersonalInfoRecord
    PersonalInfoRecord *head = NULL; //pointer to the head of the linked list
    FILE *fp = NULL; //pointer to the file

    // do not forget to check input arguments...
    //If the program is passed the correct number of arguments,✔️
    if (argc != 2) {
        fprintf(stderr, "Error, please pass the database filename as the argument.\n"
                        "Usage ./pimapp <dbfile>\n");
        return 1;
    }

    while (fgets(input = inputbuffer, 100, stdin) != NULL) // Get each input line.
    {
        if (strncmp(input, "END", 3) == 0) {
            //function that will write to function and then free the memory
            writeToFile(&head, argv[1]);
            break; // We are asked to terminate.
        }
        if (strncmp(input, "LIST", 4) == 0) {
            //function that will print the linked list
            printList(head);
            continue;
        }

        //This parses through the values and saves them into an array where we will then allocate the values to our struct
        char *fielddata;
        char *fields[10];
        char **p = fields;
        int i = 0;

        while ((fielddata = strsep(&input, ",\n")) != NULL) {
            p[i] = fielddata;
            i++;
        }
        if (strcmp(p[0], "I") == 0) {//if the first character is I
            if (strcmp(p[2], "P") == 0) {//if person is a Prof.
                PersonalInfoRecord *newProf = malloc(sizeof(PersonalInfoRecord));
                strcpy(newProf->id, p[1]);//copy the pid to the new prof's id
                newProf->ptype = *(p[2]);
                strcpy(newProf->name, p[3]);//copy the name to the new prof's name
                strcpy(newProf->info.prof.dept, p[4]);//copy the dept to the new prof's dept
                newProf->info.prof.hireyear = atoi(p[5]);
                newProf->info.prof.tenured = *(p[6]);
                newProf->next = NULL;
                head = updateList(&head, newProf); // why do we need to pass the address of head?


            } else {//if person is a Student
                PersonalInfoRecord *newStud = malloc(sizeof(PersonalInfoRecord));
                strcpy(newStud->id, p[1]);//copy the pid to the new student's id
                newStud->ptype = p[2][0];
                strcpy(newStud->name, p[3]);//copy the name to the new student's name
                strcpy(newStud->info.stud.faculty, p[4]);//copy the faculty to the new student's faculty
                newStud->info.stud.admyear = atoi(p[5]);
                newStud->next = NULL;
                head = updateList(&head, newStud);

            }

        }
        if (strcmp(p[0], "D") == 0) {
            //PersonalInfoRecord *person = malloc(sizeof(PersonalInfoRecord));
            //strcpy(person->id, p[1]);//copy the pid to the person's id
            head = deleteNode(&head, p[1]);
        }

    }

    return 0; // Appropriate return code from this program.

}
