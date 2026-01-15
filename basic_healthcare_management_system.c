#include <stdio.h>
#include <string.h>
#include <ctype.h>

// MEDICINE STRUCT DEFINITION
typedef struct{
    char med_name[50];
    int quantity;
    float price;
}Medicine;

// PATIENT STRUCT DEFINITION
typedef struct {
    char name[50];
    int id;
    int age;
    char gender;
    int category;
    int stay_days;
    char diagnosis[100];
    Medicine meds[20];
    int med_count;
    float total_bill;
} Patient;

/*HELPER FUNCTIONS*/
// clear input buffer funcion
void clear_input_buffer() {
    int c;
    while((c = getchar()) !='\n' && c != EOF);
}


// name validation function
int validate_name(char *name) {
    int length = strlen(name);

    //name must be atleast 2 characters long
    if (length < 2) {
        return 0;
    }

    // loop through each character
    for(int i=0; i<length; i++){

        // if character is a letter and valid, move on
        if(isalpha((unsigned char)name[i])) {
            continue;
        }

        // allow spaces in names
        if(name[i] == ' ') {
            continue;
        }

        // if neither a letter nor space, invalid
        return 0;
    }

    // if all characters are valid
    return 1;
}


// remove trailing newline from fgets
void remove_newline(char *str) {
    str[strcspn(str, "\n")] = '\0';
}


// GLOBAL CONSTANTS
const float CONSULTATION_FEE = 1000.0f;
const float WARD_FEE = 1200.0f;


// CALCULATE BILL FUNCTION
void calculate_bill(Patient *p) {
    //start with consulation fee
    p->total_bill = CONSULTATION_FEE;

    //add ward fees if admitted
    if(p->category == 1) {
        p->total_bill += (p->stay_days * WARD_FEE);
    }

    //add all medicine costs
    for(int i=0; i<p->med_count; i++){
        p->total_bill += (p->meds[i].quantity * p->meds[i].price);
    }
}

// SAVE PATIENT DATA TO "patients.txt"
void save_patient(Patient *p) {
    // open file in append mode
    FILE *fp = fopen("patients.txt", "a");
    if(!fp) {
        perror("Error opening file");
        return;
    }

    // patient section
    fprintf(fp, "\n--------PATIENTS--------\n");
    fprintf(fp, "Name: %s\n", p->name);
    fprintf(fp, "Patient ID: %d\n", p->id);
    fprintf(fp, "Age: %d\n", p->age);
    fprintf(fp, "Gender: %c\n", p->gender);

    fprintf(fp, "Category: %s\n", p->category == 1 ? "In-patient" : "Out-patient");
    if(p->category == 1) {
        fprintf(fp, "Stay days: %d\n", p->stay_days);
    }

    fprintf(fp, "Diagnosis: %s\n", p->diagnosis);

    fprintf(fp, "---Prescriptions---\n");
    for(int i=0; i<p->med_count; i++) {
        fprintf(fp, "%d. Medicine: %s | Qty: %d | Price: %.2f\n",
            i+1,
            p->meds[i].med_name,
            p->meds[i].quantity,
            p->meds[i].price
        );
    }

    fprintf(fp, "Total Bill: %.2f\n", p->total_bill);

    // end of patient section
    fprintf(fp, "--------PATIENT END---------\n");


    // close file
    fclose(fp);
    printf("Patient saved successfully!\n");

}


// INPUT PATIENT DETAILS
void input_patient(Patient *p) {

    //input name
    do {
        printf("Enter patient's name: ");
        fgets(p->name, sizeof(p->name), stdin);
        remove_newline(p->name);

        if(!validate_name(p->name)) {
            printf("Invalid name. Only letter an spaces are allowed.\n");
        }

    } while(!validate_name(p->name));

    //input ID
    printf("ENter patient ID: ");
    scanf("%d", &p->id);
    clear_input_buffer();

    //input age
    printf("Enter age: ");
    scanf("%d", &p->age);
    clear_input_buffer();

    //input gender
    do {
        printf("Enter gender (M or F): ");
        scanf("%c", &p->gender);
        clear_input_buffer();

    } while(p->gender != 'M' && p->gender != 'F' &&
            p->gender != 'm' && p->gender != 'f');

    //input category
    do {
        printf("Enter category (1 = in-patient, 2= out-patient): ");
        scanf("%d", &p->category);
        clear_input_buffer();

    } while(p->category != 1 && p->category != 2);

    //inout stay days
    //if category is in-patient, input no of days
    if(p->category == 1) {
        printf("Enter number of stay days: ");
        scanf("%d", &p->stay_days);
        clear_input_buffer();
    }

    //input diagnosis
    printf("ENter diagnosis: ");
    fgets(p->diagnosis, sizeof(p->diagnosis), stdin);
    remove_newline(p->diagnosis);

    // input medicines
    do {
        printf("Enter number of medicines (0-20): ");
        scanf("%d", &p->med_count);
        clear_input_buffer();

    } while(p->med_count < 0 || p->med_count > 20);

    for( int i=0; i<p->med_count; i++) {
        printf("\nMedicine %d name: ", i +1 );
        fgets(p->meds[i].med_name, sizeof(p->meds[i].med_name), stdin);
        remove_newline(p->meds[i].med_name);

        printf("Quantity: ");
        scanf("%d", &p->meds[i].quantity);
        clear_input_buffer();

        printf("Price per unit: ");
        scanf("%f", &p->meds[i].price);
        clear_input_buffer();
    }


}

//VIEW ALL PATIENTS FUCNTION
void view_all_patients() {
    FILE *fp = fopen("patients.txt", "r");
    if(!fp) {
        printf("No patients found. File does not exist.\n");
        return;
    }

    //line buffer
    char line[256];

    printf("\n------- ALL PATIENTS -------\n");

    while (fgets(line, sizeof(line), fp)) {
        printf("%s", line);
    }

    printf("\n------- END OF LIST -------\n");

    fclose(fp);
}


//SEARCH PATIENT ID FUNCTION
void search_ID() {
    int search_id;
    printf("Enter patient ID to search: ");
    scanf("%d", &search_id);
    clear_input_buffer();

    FILE *fp = fopen("patients.txt", "r");
    if(!fp) {
        printf("No patients found.\n");
        return;
    }

    char line[256];

    //inside patient section (1 = inside patient section, 0=not inside)
    int in_section = 0;

    //was the patient found(1 = yes, 0 = no)
    int found = 0;

    while(fgets(line, sizeof(line), fp)) {

        //start of patient section
        if (strncmp(line, "--------PATIENTS--------", 24) == 0) {
            in_section = 1;
        }

        if (in_section) {

            //check for patient ID
            int id;
            if (sscanf(line, "Patient ID: %d", &id) == 1) {
                if(id == search_id){
                    found = 1;
                } else{
                    //skip section (wrong patient)
                    in_section = 0;
                }

            }

            //print if correct patient
            if (found) {
                printf("%s", line);
            }

            //end of patient section
            if(strncmp(line, "--------PATIENT END---------", 28) == 0) {

            //done printning patient
                if (found) break;

                //reset for next patient
                in_section = 0;
            }
        }
    }

    if(!found) {
        printf("Patient with ID %d not ofound!\n", search_id);
    }

    //close file
    fclose(fp);
}


//VIEW PATIENTS BY CATEGORY FUNCTION
void view_by_category() {
    int choice;
    printf("View patients by category:\n");
    printf("1. In-patient\n");
    printf("2. Out-patient\n");
    printf("Enter choice: ");
    scanf("%d", &choice);
    clear_input_buffer();

    char target[20];
    if (choice == 1) {
        strcpy(target, "In-patient");
    } else if (choice == 2) {
        strcpy(target, "Out-patient");
    } else {
        printf("Invalid choice.\n");
        return;
    }

    FILE *fp = fopen("patients.txt", "r");
    if (!fp) {
        printf("No patients found.\n");
        return;
    }

    char line[256];
    int in_section = 0;
    int match = 0;

    printf("\n--- %s Patients ---\n", target);

    while (fgets(line, sizeof(line), fp)) {

        //stat of patient section
        if (strncmp(line, "--------PATIENTS--------", 24) == 0) {
            in_section = 1;
            match = 0;
            continue;
        }

        if (in_section) {

            //find catgeory
            char category[30];
            if (sscanf(line, "Category: %29[^\n]", category) == 1) {
                if (strcmp(category, target) == 0) {
                    match = 1;
                }
            }

            //print only matching patients
            if (match) {
                printf("%s", line);
            }

            //End of patient section
            if (strncmp(line, "--------PATIENT END---------", 28) == 0) {
                in_section = 0;
                match = 0;
            }
        }
    }

    fclose(fp);
}


//MAIN FUNCTION
int main() {
    int choice;
    Patient p;

    do {
        printf("\n----------HOSPITAL MANAGEMENT SYSTEM----------\n");
        printf("1. Add new patient.\n");
        printf("2. View all patients.\n");
        printf("3. Search patient by ID.\n");
        printf("4. View patient by category.\n");
        printf("5. Exit.\n");

        printf("Enter your choice: ");

        scanf("%d", &choice);
        clear_input_buffer();

        switch(choice) {
            case 1:
                input_patient(&p);      //get dtails
                calculate_bill(&p);     // compute bill
                save_patient(&p);       //save to file
                break;

            case 2:
                view_all_patients();    //view all patients
                break;

            case 3:
                search_ID();
                break;

            case 4:
                view_by_category();
                break;

            case 5:
                printf("Exiting the system. Goodbye!\n");
                break;

            default:
                printf("Invalid choice. TRy again!\n");
        }

    } while (choice != 5);

    return 0;
}
