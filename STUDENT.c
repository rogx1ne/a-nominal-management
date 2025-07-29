#include<stdio.h>
#include<conio.h>
#include<string.h>
#include<stdlib.h>
#include<ctype.h>
#include<time.h>
#include "COURSE.H"
#include "STUDENT.H"









void student_management_main(){
    FILE *file;
    stud *s;
    int choice;

    do{
        clrscr();
        printf("\nSTUDENT RECORD MANAGEMENT");
        printf("\n=========================");
        printf("\nWhat task would you like to do: \n\n1>Write a record \n2>Search a record \n3>Update a record \n4>Delete a record \n5>Display all record \n6>Delete all records \n7>Exit \n\nEnter your choice (1-7): ");
        scanf("%d", &choice);

        s = malloc(sizeof(stud));
        if(s == NULL){
            clrscr();
            printf("\nMemory Allocation failed!\n\npress enter to exit...");
            getch();
            exit(1);
        }

        switch(choice){
            case 1:
                if(file != NULL) {
                    fclose(file);  // Close if already open
                }
                file = create();
                if(file != NULL) {
                    write_record(file, s);
                    fclose(file);
                    file = NULL;  // Reset file pointer
                }
                break;

            case 2:
                file = fopen("ABCDB/student.txt", "r");
                if(file != NULL){
                    search(file);
                    fclose(file);
                }
                else{
                    clrscr();
                    printf("\nNo records found or error opening file!\n\npress enter...");
                    getch();
                }
                break;

            case 3:
                file = fopen("ABCDB/student.txt", "r+");
                if(file != NULL){
                    update(file, s);
                    fclose(file);
                }
                else{
                    clrscr();
                    printf("\nNo records found or error opening file!\n\npress enter...");
                    getch();
                }
                break;

            case 4:
                file = fopen("ABCDB/student.txt", "r");
                if(file != NULL){
                    delete_record(file);
                    fclose(file);
                }
                else{
                    clrscr();
                    printf("\nNo records found or error opening file!\n\npress enter...");
                    getch();
                }
                break;

            case 5:
                file = fopen("ABCDB/student.txt", "r");
                if(file != NULL){
                    displayS(file);
                    fclose(file);
                }
                else{
                    clrscr();
                    printf("\nNo records found or error opening file!\n\npress enter...");
                    getch();
                }
                break;

            case 6:
                delete_all();
                break;

            case 7:
                clrscr();
                printf("\nGoing Back...\n\npress enter...");
                getch();
                free(s);
                clrscr();
                return;
                

            default:
                printf("\nInvalid choice! Please enter 1-7.\n\npress enter...");
                getch();
                break;
        }
        free(s);
    }while(choice != 7);

    if(file != NULL) {
        fclose(file);
    }
}

FILE* create(){
    FILE *file;
    file = fopen("ABCDB/student.txt", "a");
    if(file == NULL){
        clrscr();
        printf("\nError in opening the record file\n\npress enter to go back...");
        getch();
        return NULL;
    }
    return file;
}

void write_record(FILE *file, stud *s) {
    int main_choice, save_choice,i;
    char temp[10];
    
    course c;
    char line[200];
    FILE *course_file;
    
    do {
        clrscr();
        printf("\nENTER STUDENT DETAILS");
        printf("\n=====================\n");

        // Course selection
        do {
            printf("\nAvailable Courses:\n");
            // Display available courses from ABCDB/course.txt
            course_file = fopen("ABCDB/course.txt", "r");
            if(course_file != NULL) {
                
                while(fgets(line, sizeof(line), course_file)) {
                    if(strstr(line, "Course Name\t:")) {
                        printf("%s", line);
                    }
                }
                fclose(course_file);
            }
            
            printf("\nEnter course name: ");
            scanf("%s", s->course);
            for(i=0;s->course[i]!=NULL;i++)
              s->course[i]=toupper(s->course[i]);
            fflush(stdin);
            
            if(!getCourseDetails(s->course, &c)) {
                printf("\nPlease enter a valid course...\n");
                continue;
            }
            
            // Store course details in student record
            s->course_code = c.course_code;
            s->duration = c.duration;
            s->fee = c.fee;
            strcpy(s->course_detail, c.course_detail);
            break;
            
        } while(1);
        
        
        // Name input
        do {
            printf("\nEnter the name of the student: ");
            fgets(s->name, sizeof(s->name), stdin);
            s->name[strcspn(s->name, "\n")] = 0; // Remove newline
            if(strlen(s->name) == 0) {
                printf("Name cannot be empty. Please try again.\n");
            }else{
                toTitleCase(s->name);
            }
        } while(strlen(s->name) == 0);

        // Admission year input
        s->admyr=2025;

        clrscr();
        printf("\nSTUDENT DETAILS (PREVIEW)");
        printf("\n=========================\n");
        printf("\nCourse\t\t: %s \nName\t\t: %s \nCourse Code\t: %d \nCourse Detail\t: %s \nDuration\t: %d years \nAdm.Year\t: %d \nFee\t\t: ",
            s->course, s->name, s->course_code, s->course_detail, s->duration, s->admyr);
        print_inr(s->fee);

        printf("\n\nDo you wish to : \n1>Save it \n2>Re-enter it \n3>Cancel it\nEnter choice: ");
        do {
            fgets(temp, sizeof(temp), stdin);
            save_choice = atoi(temp);
            if(save_choice == 1) {
                fclose(file);
                s->roll = generateRollNumber(s->course,s->admyr);

                file = fopen("ABCDB/student.txt", "a");
                if(file == NULL) {
                  printf("\nError reopening file! Press enter to continue...");
                  getch();
                  return;
                }

                fprintf(file, "\nRoll\t\t: %d \nCourse\t\t: %s \nName\t\t: %s \nCourse Code\t: %d \nCourse Detail\t: %s \nDuration\t: %d years \nAdm.Year\t: %d \nFee\t\t: %ld.00\n",
            s->roll, s->course,s->name, s->course_code, s->course_detail, s->duration, s->admyr, s->fee);
        
                fflush(file);
                fclose(file);
                file = fopen("ABCDB/student.txt", "a");

                clrscr();
                printf("\nRecorded successfully!\n\n");
                printf("\nRoll\t\t: %d \nCourse\t\t: %s \nName\t\t: %s \nCourse Code\t: %d \nCourse Detail\t: %s \nDuration\t: %d years \nAdm.Year\t: %d \nFee\t\t: ",
            s->roll, s->course,s->name, s->course_code, s->course_detail, s->duration, s->admyr);
                print_inr(s->fee);
                printf("\n\nDo you wish to enter another record? (press 1 for yes, any other key for no): ");
                fgets(temp, sizeof(temp), stdin);
                main_choice = atoi(temp);
                if(main_choice != 1)
                    main_choice = 0;
                break;
            } else if(save_choice == 2) {
                main_choice = 1;
                break;
            } else if(save_choice == 3) {
                clrscr();
                printf("Going back to main menu...\n\npress enter...");
                getch();
                return;
            } else {
                printf("Invalid choice...\nenter again (1-3): ");
            }
        } while(save_choice < 1 || save_choice > 3);

    } while(main_choice == 1);
}

int count(){
    FILE *file;
    int count = 0;
    char line[200];

    file = fopen("ABCDB/student.txt", "r");
    if(file == NULL){
        return 0;
    }

    while(fgets(line, sizeof(line), file)){
        if(strstr(line, "Roll\t\t:")){
            count++;
        }
    }

    fclose(file);
    return count;
}

//roll no generation
int generateRollNumber(char *course, int admyr) {
    FILE *file, *backup_file;
    int highest_roll = 0;
    int current_roll = 0;
    char line[200];
    char temp_course[30] = {0};
    int temp_year = 0;
    int year_suffix = admyr % 100;
    int base_roll;
    int i;
    int found_roll = 0, found_course = 0, found_year = 0;
    int new_roll;
    char *trimmed = line;
    time_t now;
    struct tm *timeinfo;
    char timestamp[30];
    

    // Set base roll number based on course
    base_roll = (year_suffix % 100)*1000;

    // First check backup file
    backup_file = fopen("ABCDB/roll_backup.txt", "r");
    if(backup_file != NULL) {
        while(fgets(line, sizeof(line), backup_file)) {
            if(sscanf(line, "%d,%[^,],%d", &current_roll, temp_course, &temp_year) == 3) {
                if(temp_year == admyr && strcmp(temp_course, course) == 0) {
                    if(current_roll > highest_roll) {
                        highest_roll = current_roll;
                    }
                }
            }
        }
        fclose(backup_file);
    }

    // Then check student.txt with improved parsing
    file = fopen("ABCDB/student.txt", "r");
    if(file != NULL) {
        while (fgets(line, sizeof(line), file)) {
            // Remove leading/trailing whitespace
            
            while (*trimmed == ' ' || *trimmed == '\t') trimmed++;

            // Parse roll
            if (strncmp(trimmed, "Roll", 4) == 0) {
                sscanf(trimmed, "Roll%*[^0-9]%d", &current_roll);
                found_roll = 1;
            }
            // Parse course
            else if (strncmp(trimmed, "Course", 6) == 0 && strstr(trimmed, "Course Code") == NULL) {
                sscanf(trimmed, "Course%*[^:]:%s", temp_course);
                found_course = 1;
            }
            // Parse admission year
            else if (strncmp(trimmed, "Adm.Year", 8) == 0) {
                sscanf(trimmed, "Adm.Year%*[^0-9]%d", &temp_year);
                found_year = 1;
            }

            // If all fields found, check
            if (found_roll && found_course && found_year) {
                if (strcmp(temp_course, course) == 0 && temp_year == admyr) {
                    if (current_roll > highest_roll) highest_roll = current_roll;
                }
                // Reset for next record
                found_roll = found_course = found_year = 0;
                current_roll = temp_year = 0;
                temp_course[0] = '\0';
            }
        }
        fclose(file);
    }

    // Generate new roll number
    new_roll = (highest_roll > 0) ? highest_roll + 1 : base_roll + 1;

    // Add new roll to backup file with timestamp and username
    backup_file = fopen("ABCDB/roll_backup.txt", "a");
    if(backup_file != NULL) {
        // Get current time
        
        
        time(&now);
        timeinfo = gmtime(&now);
        
        // Format timestamp as YYYY-MM-DD HH:MM:SS
        strftime(timestamp, sizeof(timestamp), "%Y-%m-%d %H:%M:%S", timeinfo);

        // Write to backup file with timestamp and username
        fprintf(backup_file, "%d,%s,%d,%s,user\n", 
                new_roll,    // Roll number
                course,      // Course
                admyr,      // Admission year
                timestamp); // UTC timestamp

        fclose(backup_file);
    }

    return new_roll;
}



// --- NEW: Delete all function ---
void delete_all() {
    int confirm;
    clrscr();
    printf("\nDELETE ALL RECORDS");
    printf("\n===================");
    printf("\nAre you sure you want to delete all records? This action cannot be undone!");
    printf("\nPress 1 to confirm, any other key to cancel: ");
    scanf("%d", &confirm);
    fflush(stdin);
    if(confirm == 1) {
        remove("ABCDB/student.txt");
        clrscr();
        printf("\nAll records deleted successfully!\n\nPress enter...");
    } else {
    clrscr();
        printf("\nAction cancelled. Press enter...");
    }
    getch();
}

void search(FILE *file){
    int i, j, k, search_choice, roll_to_search, found = 0, course_option, continue_search;
    char name_to_search[50], course_to_search[30];
    char line[200];
    char record_lines[8][200]; // Fixed: Changed from 5 to 8 to match actual usage
    char temp_course[30];
    char temp_name[50];
    char temp_name_lower[50], search_name_lower[50];
    int current_roll, preview_choice, match;
    stud temp_record;
    char *trimmed;
    
    do {
        clrscr();
        printf("\nSEARCH STUDENT RECORD");
        printf("\n=====================\n");
        printf("Search by: \n1>Course \n2>Name \n3>Roll Number \nEnter choice: ");
        scanf("%d", &search_choice);
        fflush(stdin);

        rewind(file);
        found = 0;

        if(search_choice == 1){
            clrscr();
            printf("\nSEARCH STUDENT RECORD");
            printf("\n=====================\n");
            printf("\nSelect Course: \n1>BCA \n2>BBA \nEnter choice: ");
            scanf("%d", &course_option);
            fflush(stdin);

            if(course_option == 1)
                strcpy(course_to_search, "BCA");
            else if(course_option == 2)
                strcpy(course_to_search, "BBA");
            else {
                printf("\nInvalid choice!\nPress enter to continue...");
                getch();
                return;
            }
            
            clrscr();
            printf("\nSEARCH STUDENT RECORD");
            printf("\n=====================\n");

            printf("\nWhat would you like to do?");
            printf("\n1>Display all %s students \n2>Search specific student in %s by name \n3>Search specific student in %s by roll number", course_to_search, course_to_search, course_to_search);
            printf("\nEnter choice: ");
            scanf("%d", &course_option);
            fflush(stdin);

            // Get additional input for options 2 and 3
            if(course_option == 2) {
                printf("\nEnter name to search (partial name allowed): ");
                fgets(name_to_search, sizeof(name_to_search), stdin);
                name_to_search[strcspn(name_to_search, "\n")] = 0;
                
                strcpy(search_name_lower, name_to_search);
                strlwr(search_name_lower);
            }
            else if(course_option == 3) {
                printf("\nEnter roll number to search: ");
                scanf("%d", &roll_to_search);
                fflush(stdin);
            }

            while(fgets(line, sizeof(line), file)) {
                trimmed = line;
                while (*trimmed == ' ' || *trimmed == '\t') trimmed++;

                if(strncmp(trimmed, "Roll", 4) == 0) {
                    strcpy(record_lines[0], line);
                    match = 1;
                    
                    // Read next 7 lines
                    for(i = 1; i < 8; i++) {
                        if(!fgets(record_lines[i], sizeof(record_lines[i]), file)) {
                            match = 0;
                            break;
                        }
                    }

                    if(match) {
                        // Parse each field using strncmp
                        for(i = 0; i < 8; i++) {
                            trimmed = record_lines[i];
                            while (*trimmed == ' ' || *trimmed == '\t') trimmed++;

                            if(strncmp(trimmed, "Roll", 4) == 0) {
                                sscanf(trimmed, "Roll : %d", &temp_record.roll);
                            }
                            else if(strncmp(trimmed, "Course", 6) == 0 && !strstr(trimmed, "Code") && !strstr(trimmed, "Detail")) {
                                sscanf(trimmed, "Course : %s", temp_record.course);
                            }
                            else if(strncmp(trimmed, "Name", 4) == 0) {
                                sscanf(trimmed, "Name : %[^\n]", temp_record.name);
                            }
                            else if(strncmp(trimmed, "Course Code", 10) == 0) {
                                sscanf(trimmed, "Course Code : %d", &temp_record.course_code);
                            }
                            else if(strncmp(trimmed, "Course Detail", 12) == 0) {
                                sscanf(trimmed, "Course Detail : %[^\n]", temp_record.course_detail);
                            }
                            else if(strncmp(trimmed, "Duration", 8) == 0) {
                                sscanf(trimmed, "Duration : %d", &temp_record.duration);
                            }
                            else if(strncmp(trimmed, "Adm.Year", 8) == 0) {
                                sscanf(trimmed, "Adm.Year : %d", &temp_record.admyr);
                            }
                            else if(strncmp(trimmed, "Fee", 3) == 0) {
                                sscanf(trimmed, "Fee : %ld", &temp_record.fee);
                            }
                        }

                        // Process based on course_option
                        if(strcmp(temp_record.course, course_to_search) == 0) {
                            switch(course_option) {
                                case 1: // Display all
                                    found++;
                                    preview_choice = showRecordPreviewS(&temp_record, found);
                                    if(preview_choice == 1) {
                                        printf("\nRecord displayed above.\nPress enter to continue...");
                                        getch();
                                    } else if(preview_choice == 3) {
                                        return;
                                    }
                                    break;

                                case 2: // Search by name in course
                                    strcpy(temp_name_lower, temp_record.name);
                                    strlwr(temp_name_lower);
                                    if(strstr(temp_name_lower, search_name_lower) != NULL) {
                                        found++;
                                        preview_choice = showRecordPreviewS(&temp_record, found);
                                        if(preview_choice == 1) {
                                            printf("\nRecord displayed above.\nPress enter to continue...");
                                            getch();
                                        } else if(preview_choice == 3) {
                                            return;
                                        }
                                    }
                                    break;

                                case 3: // Search by roll in course
                                    if(temp_record.roll == roll_to_search) {
                                        found = 1;
                                        preview_choice = showRecordPreviewS(&temp_record, found);
                                        if(preview_choice == 1) {
                                            printf("\nRecord displayed above.\nPress enter to continue...");
                                            getch();
                                        }
                                        return;
                                    }
                                    break;
                                    
                                default:
                                    printf("\nInvalid choice!\nPress enter to continue...");
                                    getch();
                                    break;
                            }
                        }
                    }
                }
            }
        }
        else if(search_choice == 2) {
            clrscr();
            printf("\nSEARCH STUDENT RECORD");
            printf("\n=====================\n");
            printf("\nEnter name to search (partial name allowed): ");
            fgets(name_to_search, sizeof(name_to_search), stdin);
            name_to_search[strcspn(name_to_search, "\n")] = 0;

            strcpy(search_name_lower, name_to_search);
            strlwr(search_name_lower);

            while(fgets(line, sizeof(line), file)) {
                trimmed = line;
                while (*trimmed == ' ' || *trimmed == '\t') trimmed++;

                if(strncmp(trimmed, "Roll", 4) == 0) {
                    strcpy(record_lines[0], line);
                    match = 1;
                    
                    // Read next 7 lines
                    for(i = 1; i < 8; i++) {
                        if(!fgets(record_lines[i], sizeof(record_lines[i]), file)) {
                            match = 0;
                            break;
                        }
                    }

                    if(match) {
                        // Parse each field using strncmp
                        for(i = 0; i < 8; i++) {
                            trimmed = record_lines[i];
                            while (*trimmed == ' ' || *trimmed == '\t') trimmed++;

                            if(strncmp(trimmed, "Roll", 4) == 0) {
                                sscanf(trimmed, "Roll : %d", &temp_record.roll);
                            }
                            else if(strncmp(trimmed, "Course", 6) == 0 && !strstr(trimmed, "Code") && !strstr(trimmed, "Detail")) {
                                sscanf(trimmed, "Course : %s", temp_record.course);
                            }
                            else if(strncmp(trimmed, "Name", 4) == 0) {
                                sscanf(trimmed, "Name : %[^\n]", temp_record.name);
                            }
                            else if(strncmp(trimmed, "Course Code", 10) == 0) {
                                sscanf(trimmed, "Course Code : %d", &temp_record.course_code);
                            }
                            else if(strncmp(trimmed, "Course Detail", 12) == 0) {
                                sscanf(trimmed, "Course Detail : %[^\n]", temp_record.course_detail);
                            }
                            else if(strncmp(trimmed, "Duration", 8) == 0) {
                                sscanf(trimmed, "Duration : %d", &temp_record.duration);
                            }
                            else if(strncmp(trimmed, "Adm.Year", 8) == 0) {
                                sscanf(trimmed, "Adm.Year : %d", &temp_record.admyr);
                            }
                            else if(strncmp(trimmed, "Fee", 3) == 0) {
                                sscanf(trimmed, "Fee : %ld", &temp_record.fee);
                            }
                        }

                        // Convert name to lowercase for case-insensitive search
                        strcpy(temp_name_lower, temp_record.name);
                        strlwr(temp_name_lower);

                        if(strstr(temp_name_lower, search_name_lower) != NULL) {
                            found++;
                            preview_choice = showRecordPreviewS(&temp_record, found);
                            if(preview_choice == 1) {
                                printf("\nRecord displayed above.\nPress enter to continue...");
                                getch();
                            } else if(preview_choice == 3) {
                                return;
                            }
                        }
                    }
                }
            }
        }
        else if(search_choice == 3) {
            clrscr();
            printf("\nSEARCH STUDENT RECORD");
            printf("\n======================\n");
            printf("\nEnter roll number to search: ");
            scanf("%d", &roll_to_search);
            fflush(stdin);

            while(fgets(line, sizeof(line), file)) {
                trimmed = line;
                while (*trimmed == ' ' || *trimmed == '\t') trimmed++;

                if(strncmp(trimmed, "Roll", 4) == 0) {
                    strcpy(record_lines[0], line);
                    match = 1;
                    
                    // Read next 7 lines
                    for(i = 1; i < 8; i++) {
                        if(!fgets(record_lines[i], sizeof(record_lines[i]), file)) {
                            match = 0;
                            break;
                        }
                    }

                    if(match) {
                        // Parse each field using strncmp
                        for(i = 0; i < 8; i++) {
                            trimmed = record_lines[i];
                            while (*trimmed == ' ' || *trimmed == '\t') trimmed++;

                            if(strncmp(trimmed, "Roll", 4) == 0) {
                                sscanf(trimmed, "Roll : %d", &temp_record.roll);
                            }
                            else if(strncmp(trimmed, "Course", 6) == 0 && !strstr(trimmed, "Code") && !strstr(trimmed, "Detail")) {
                                sscanf(trimmed, "Course : %s", temp_record.course);
                            }
                            else if(strncmp(trimmed, "Name", 4) == 0) {
                                sscanf(trimmed, "Name : %[^\n]", temp_record.name);
                            }
                            else if(strncmp(trimmed, "Course Code", 10) == 0) {
                                sscanf(trimmed, "Course Code : %d", &temp_record.course_code);
                            }
                            else if(strncmp(trimmed, "Course Detail", 12) == 0) {
                                sscanf(trimmed, "Course Detail : %[^\n]", temp_record.course_detail);
                            }
                            else if(strncmp(trimmed, "Duration", 8) == 0) {
                                sscanf(trimmed, "Duration : %d", &temp_record.duration);
                            }
                            else if(strncmp(trimmed, "Adm.Year", 8) == 0) {
                                sscanf(trimmed, "Adm.Year : %d", &temp_record.admyr);
                            }
                            else if(strncmp(trimmed, "Fee", 3) == 0) {
                                sscanf(trimmed, "Fee : %ld", &temp_record.fee);
                            }
                        }

                        if(temp_record.roll == roll_to_search) {
                            found = 1;
                            preview_choice = showRecordPreviewS(&temp_record, found);
                            if(preview_choice == 1) {
                                printf("\nRecord displayed above.\nPress enter to continue...");
                                getch();
                                return;
                            }
                            
                        }
                    }
                }
            }
            if(!found) {
                printf("\nNo records found with Roll Number %d!\n", roll_to_search);
            }
        }
        else {
            printf("\nInvalid choice!\nPress enter to continue...");
            getch();
        }

        if(found == 0 && search_choice != 3){ // Added condition to avoid duplicate message for search_choice == 3
            printf("\nNo records found!\n");
        }

        printf("\nDo you want to search again? (1 for Yes, 0 for No): ");
        scanf("%d", &continue_search);
        fflush(stdin);

    } while(continue_search == 1);
}


// --- MODIFIED DISPLAY FUNCTION: record-by-record pause ---
void displayS(FILE *file) {
    int i, found = 0, pause_count = 0;
    char line[200];
    char temp_course[30], temp_name[50];
    int temp_roll, temp_year;
    long int temp_fee;
    char record_lines[8][200];        
    char *trimmed;  // Fixed: Don't initialize here
    int match;
    
    clrscr();
    printf("\nDISPLAY STUDENT RECORDS");
    printf("\n======================\n");
    printf("%-6s | %-4s | %-20s | %-4s | %-15s\n", 
           "Roll", "Course", "Name", "Year", "Fee (INR)");
    printf("---------------------------------------------------------------------\n");
    rewind(file);
    
    while(fgets(line, sizeof(line), file)) {
        trimmed = line;  // Fixed: Initialize trimmed for each line
        while (*trimmed == ' ' || *trimmed == '\t') trimmed++;
        
        if(strncmp(trimmed, "Roll", 4) == 0) {
            found++;
            strcpy(record_lines[0], line);
            match = 1;
            
            // Read next 7 lines
            for(i = 1; i < 8; i++) {
                if(!fgets(record_lines[i], sizeof(record_lines[i]), file)) {
                    printf("\nError reading file!");
                    return;
                }
            }
            
            if(match) {
                // Parse each field using strncmp
                for(i = 0; i < 8; i++) {
                    trimmed = record_lines[i];
                    while (*trimmed == ' ' || *trimmed == '\t') trimmed++;
                    
                    if(strncmp(trimmed, "Roll", 4) == 0) {
                        sscanf(trimmed, "Roll : %d", &temp_roll);
                    }
                    else if(strncmp(trimmed, "Course", 6) == 0 && !strstr(trimmed, "Code") && !strstr(trimmed, "Detail")) {
                        sscanf(trimmed, "Course : %s", temp_course);
                    }
                    else if(strncmp(trimmed, "Name", 4) == 0) {
                        sscanf(trimmed, "Name : %[^\n]", temp_name);
                    }
                    else if(strncmp(trimmed, "Adm.Year", 8) == 0) {
                        sscanf(trimmed, "Adm.Year : %d", &temp_year);
                    }
                    else if(strncmp(trimmed, "Fee", 3) == 0) {
                        sscanf(trimmed, "Fee : %ld", &temp_fee);
                    }
                }
                
                // Display the parsed record
                printf("%-6d | %-4s | %-20s | %-4d | ", temp_roll, temp_course, temp_name, temp_year);
                print_inr(temp_fee);
                printf("\n");
                
                pause_count++;
                if(pause_count % 3 == 0) {
                    printf("\nPress any key to see more records...\n\n");
                    getch();
                }
            }
        }
    }
    
    if(!found) {
        printf("\nNo records found!\n");
    } else {
        printf("\n---------------------------------------------------------------------");
        printf("\nTotal Records: %d\n", found);
    }
    printf("\nPress enter to continue...");
    getch();
}
// --- Print INR with Rupee Symbol (for Turbo C, use "Rs." prefix) ---
 void print_inr(long int value) {
    long int int_part;
    int decimal_part;
    char num_str[20];
    int len, i;
    
    // Split into integer and decimal parts
    int_part = (long int)value;
    decimal_part = (int)((value - int_part) * 100 + 0.5); // Added 0.5 for rounding
    
    // Convert integer part to string
    sprintf(num_str, "%ld", int_part);
    len = strlen(num_str);
    
    // Print Rs prefix
    printf("Rs ");
    
    if(len <= 3) {
        // Numbers less than 1000
        printf("%s", num_str);
    }
    else {
        // Print leftmost digits before first comma (1-2 digits)
        i = 0;
        while(i < len-3) {
            printf("%c", num_str[i]);
            i++;
            if((len-i) % 2 == 1 && i < len-3) {
                printf(",");
            }
        }
        // Print last 3 digits with comma
        printf(",%c%c%c", num_str[len-3], num_str[len-2], num_str[len-1]);
    }
    
    // Print decimal part
    printf(".%02d", decimal_part);
}

// --- showRecordPreviewS as before ---
int showRecordPreviewS(stud *record, int recordNum) {
    int choice;
    
    clrscr();
    printf("\nRecord %d:", recordNum);
    printf("\n----------\n");
    printf("\nRoll\t\t: %d", record->roll);
    printf("\nCourse\t\t: %s", record->course);
    printf("\nName\t\t: %s", record->name);
    printf("\nCourse Code\t: %d", record->course_code);
    printf("\nCourse Detail\t: %s", record->course_detail);
    printf("\nDuration\t: %d years", record->duration);
    
    printf("\nAdm.Year\t: %d", record->admyr);
    printf("\nFee\t\t: ");
    print_inr(record->fee);
    printf("\n\nOptions:");
    printf("\n1. Select this record");
    printf("\n2. Next record");
    printf("\n3. Cancel");
    printf("\nEnter your choice (1-3): ");
    scanf("%d", &choice);
    fflush(stdin);
    return choice;
}


void update(FILE *file, stud *s) {
    FILE *temp_file;
    int i, found = 0, course_option, roll_to_update, choice;
    int update_choice, continue_update = 1, preview_choice;
    int search_by, match, current_roll;
    char line[200];
    char temp_lines[8][200];  // Increased to 8 for additional course details
    char temp_course[30];
    char name_to_update[50];
    char current_course[30], current_name[50], current_course_detail[100];
    int current_admyr, current_course_code, current_duration;
    long int current_fee;
    char temp[10];
    course c;  // For course details
    char course_line[200];
    FILE *course_file;
    char *trimmed;

    do {
        clrscr();
        printf("\nUPDATE STUDENT RECORD");
        printf("\n=====================\n");
        printf("Search record to update by:\n1>Course + Roll\n2>Course + Name\n3>Cancel\nEnter choice: ");
        scanf("%d", &search_by);
        fflush(stdin);

        if(search_by == 3) {
            printf("\nUpdate cancelled. Press enter to return to main menu...");
            getch();
            return;
        }

        if(search_by != 1 && search_by != 2) {
            printf("\nInvalid choice! Press enter to try again...");
            getch();
            continue;
        }

        // Display available courses
        clrscr();
        printf("\nUPDATE STUDENT RECORD");
        printf("\n=====================\n");
        printf("\nAvailable Courses:\n");
        course_file = fopen("ABCDB/course.txt", "r");
        if(course_file != NULL) {
            
            while(fgets(course_line, sizeof(course_line), course_file)) {
                if(strstr(course_line, "Course Name\t:")) {
                    printf("%s", course_line);
                }
            }
            fclose(course_file);
        }

        printf("\nSelect Course: ");
        scanf("%s", temp_course);
        for(i=0;temp_course[i]!=NULL;i++)
              temp_course[i]=toupper(temp_course[i]);
        fflush(stdin);
        
        
        
        

        if(!getCourseDetails(temp_course, &c)) {
            printf("\nCourse not found! Press enter to try again...");
            getch();
            continue;
        }

        // Get search criteria
        if(search_by == 1) {
            printf("\nEnter roll number to update (0 to cancel): ");
            scanf("%d", &roll_to_update);
            fflush(stdin);
            
            if(roll_to_update == 0) {
                printf("\nUpdate cancelled. Press enter to return...");
                getch();
                return;
            }
        } else {
            printf("\nEnter full name to update: ");
            fgets(name_to_update, sizeof(name_to_update), stdin);
            toTitleCase(name_to_update);
            name_to_update[strcspn(name_to_update, "\n")] = 0;
            
            if(strlen(name_to_update) == 0) {
                printf("\nUpdate cancelled. Press enter to return...");
                getch();
                return;
            }
        }

        temp_file = fopen("ABCDB/temp.txt", "w");  // FIXED: Consistent path
        if(temp_file == NULL) {
            printf("\nError creating temporary file! Press enter to return...");
            getch();
            return;
        }

        rewind(file);
        found = 0;

        while(fgets(line, sizeof(line), file)) {
            trimmed = line;  // FIXED: Added spaces around =
            while(*trimmed == ' ' || *trimmed == '\t') trimmed++;  // FIXED: Added spaces
            
            if(strncmp(trimmed, "Roll", 4) == 0) {  // FIXED: Added spaces around ==
                strcpy(temp_lines[0], line);  // FIXED: Added space after comma
                match = 1;  // FIXED: Added spaces around =
                
                for(i = 1; i < 8; i++) {  // Read next 7 lines of student record
                    if(fgets(temp_lines[i], sizeof(temp_lines[i]), file) == NULL) {
                        fclose(temp_file);
                        remove("ABCDB/temp.txt");  // FIXED: Consistent path
                        match = 0;  // FIXED: Added spaces around =
                        printf("\nError reading file! Press enter to return...");
                        getch();
                        return;
                    }
                }
                
                if(match) {
                    // Parse each field using strncmp
                    for(i = 0; i < 8; i++) {
                        trimmed = temp_lines[i];  // FIXED: Changed from record_lines to temp_lines
                        while (*trimmed == ' ' || *trimmed == '\t') trimmed++;

                        if(strncmp(trimmed, "Roll", 4) == 0) {
                            sscanf(trimmed, "Roll : %d", &current_roll);
                        }
                        else if(strncmp(trimmed, "Course", 6) == 0 && !strstr(trimmed, "Code") && !strstr(trimmed, "Detail")) {
                            sscanf(trimmed, "Course : %s", current_course);
                        }
                        else if(strncmp(trimmed, "Name", 4) == 0) {
                            sscanf(trimmed, "Name : %[^\n]", current_name);
                        }
                        else if(strncmp(trimmed, "Course Code", 10) == 0) {
                            sscanf(trimmed, "Course Code : %d", &current_course_code);
                        }
                        else if(strncmp(trimmed, "Course Detail", 12) == 0) {
                            sscanf(trimmed, "Course Detail : %[^\n]", current_course_detail);
                        }
                        else if(strncmp(trimmed, "Duration", 8) == 0) {
                            sscanf(trimmed, "Duration : %d", &current_duration);
                        }
                        else if(strncmp(trimmed, "Adm.Year", 8) == 0) {
                            sscanf(trimmed, "Adm.Year : %d", &current_admyr);
                        }
                        else if(strncmp(trimmed, "Fee", 3) == 0) {
                            sscanf(trimmed, "Fee : %ld", &current_fee);
                        }
                    }

                    if((search_by == 1 && current_roll == roll_to_update && strcmp(current_course, temp_course) == 0) ||
                       (search_by == 2 && strcmp(current_course, temp_course) == 0 && stricmp(current_name, name_to_update) == 0)) {  // FIXED: Changed strcmpi to stricmp
                        
                        found++;
                        
                        // Store current values in student structure
                        s->roll = current_roll;
                        strcpy(s->course, current_course);
                        s->course_code = current_course_code;
                        strcpy(s->course_detail, current_course_detail);
                        s->duration = current_duration;
                        strcpy(s->name, current_name);
                        s->admyr = current_admyr;
                        s->fee = current_fee;

                        // Show record preview
                        preview_choice = showRecordPreviewS(s, found);

                        if(preview_choice == 1) {
                            printf("\nWhat do you want to update?");
                            printf("\n1>Course\n2>Name\n3>All details\n4>Cancel\nEnter choice: ");
                            scanf("%d", &update_choice);
                            fflush(stdin);

                            if(update_choice == 4) {
                                fclose(temp_file);
                                remove("ABCDB/temp.txt");  // FIXED: Consistent path
                                printf("\nUpdate cancelled. Press enter to return...");
                                getch();
                                return;
                            }

                            switch(update_choice) {
                                case 1: // Update Course
                                    clrscr();
                                    printf("\nUPDATE STUDENT RECORD");
                                    printf("\n=====================\n");
                                    printf("\nAvailable Courses:\n");
                                    course_file = fopen("ABCDB/course.txt", "r");
                                    if(course_file != NULL) {
                                        
                                        while(fgets(course_line, sizeof(course_line), course_file)) {
                                            if(strstr(course_line, "Course Name\t:")) {
                                                printf("%s", course_line);
                                            }
                                        }
                                        fclose(course_file);
                                    }
                                    
                                    printf("\nEnter new Course: ");
                                    scanf("%s", s->course);
                                    for(i=0;s->course[i]!=NULL;i++)
                                        s->course[i]=toupper(s->course[i]);
                                    fflush(stdin);
                                    
                                    if(getCourseDetails(s->course, &c)) {
                                        s->course_code = c.course_code;
                                        s->duration = c.duration;
                                        s->fee = c.fee;
                                        strcpy(s->course_detail, c.course_detail);
                                    } else {
                                        printf("\nCourse not found! No changes made.");
                                        getch();
                                        continue;
                                    }
                                    break;

                                case 2: // Update Name
                                    do {
                                        printf("\nEnter new Name: ");
                                        fgets(s->name, sizeof(s->name), stdin);
                                        toTitleCase(s->name);
                                        s->name[strcspn(s->name, "\n")] = 0;
                                        if(strlen(s->name) == 0)
                                            printf("Name cannot be empty. Please try again.\n");
                                    } while(strlen(s->name) == 0);
                                    break;

                                case 3: // Update All Details
                                    // Course
                                    printf("\nAvailable Courses:\n");
                                    course_file = fopen("ABCDB/course.txt", "r");
                                    if(course_file != NULL) {
                                        
                                        while(fgets(course_line, sizeof(course_line), course_file)) {
                                            if(strstr(course_line, "Course Name\t:")) {
                                                printf("%s", course_line);
                                            }
                                        }
                                        fclose(course_file);
                                    }
                                    
                                    printf("\nEnter new Course: ");
                                    scanf("%s", s->course);
                                    for(i=0;s->course[i]!=NULL;i++)
                                        s->course[i]=toupper(s->course[i]);
                                    fflush(stdin);
                                    
                                    if(getCourseDetails(s->course, &c)) {
                                        s->course_code = c.course_code;
                                        s->duration = c.duration;
                                        s->fee = c.fee;
                                        strcpy(s->course_detail, c.course_detail);
                                    } else {
                                        printf("\nCourse not found! No changes made.");
                                        getch();
                                        continue;
                                    }

                                    // Name
                                    do {
                                        printf("\nEnter new Name: ");
                                        fgets(s->name, sizeof(s->name), stdin);
                                        toTitleCase(s->name);
                                        s->name[strcspn(s->name, "\n")] = 0;
                                        if(strlen(s->name) == 0)
                                            printf("Name cannot be empty. Please try again.\n");
                                    } while(strlen(s->name) == 0);

                                    // Admission Year
                                    s->admyr = 2025;  // Fixed to 2025
                                    break;
                            }

                            // Write updated record
                            fprintf(temp_file, "\nRoll\t\t: %d", s->roll);
                            fprintf(temp_file, "\nCourse\t\t: %s", s->course);
                            fprintf(temp_file, "\nName\t\t: %s", s->name);
                            fprintf(temp_file, "\nCourse Code\t: %d", s->course_code);
                            fprintf(temp_file, "\nCourse Detail\t: %s", s->course_detail);
                            fprintf(temp_file, "\nDuration\t: %d", s->duration);
                            fprintf(temp_file, "\nAdm.Year\t: %d", s->admyr);
                            fprintf(temp_file, "\nFee\t\t: %ld", s->fee);
                            
                            found = -1; // Mark as updated
                            continue;
                        } else if(preview_choice == 3) {
                            fclose(temp_file);
                            remove("ABCDB/temp.txt");  // FIXED: Consistent path
                            printf("\nUpdate cancelled. Press enter to return...");
                            getch();
                            return;
                        }
                    }
                    
                    // Write unchanged record - FIXED: This should be outside the match condition
                    for(i = 0; i < 8; i++) {
                        fprintf(temp_file, "%s", temp_lines[i]);
                    }
                } else {
                    // If match failed, write the original line
                    fprintf(temp_file, "%s", line);
                }
            } else {
                fprintf(temp_file, "%s", line);
            }
        }

        fclose(temp_file);
        
        if(found == 0) {
            remove("ABCDB/temp.txt");  // FIXED: Consistent path
            if(search_by == 1)
                printf("\nNo record found with roll number %d in %s!", roll_to_update, temp_course);
            else
                printf("\nNo record found with name '%s' in %s!", name_to_update, temp_course);
        } else if(found > 0) {
            remove("ABCDB/temp.txt");  // FIXED: Consistent path
            printf("\nNo record was updated!");
        } else {
            fclose(file);
            remove("ABCDB/student.txt");
            rename("ABCDB/temp.txt", "ABCDB/student.txt");  // FIXED: Consistent path
            file = fopen("ABCDB/student.txt", "r+");
            printf("\nRecord updated successfully!");
        }

        printf("\nDo you want to update another record? (1-Yes, 0-No): ");
        scanf("%d", &continue_update);
        fflush(stdin);

    } while(continue_update == 1);
}




void delete_record(FILE *file) {
    FILE *temp_file;
    int i, delete_choice, roll_to_delete, found = 0;
    int course_option, confirm, continue_deleting = 1;
    int preview_choice, current_roll;
    char name_to_delete[50], course_to_delete[30];
    char line[200];
    char record_lines[8][200];  // Increased to 8 for additional course details
    char temp_course[30], temp_name[50], temp_course_detail[100];
    stud temp_record;  // Temporary structure to hold record for preview
    char temp_name_lower[50], name_to_delete_lower[50];
    course c;  // For course details
    FILE *course_file;
    char course_line[200];
    char *trimmed;
    int match;
    char coursedel[30];
    int current_record_roll = 0;
    char current_record_course[30] = "";
    char *trimmed_current;
    char current_record_lines[8][200];
    int j,k;

    do {
        clrscr();
        printf("\nDELETE STUDENT RECORD");
        printf("\n=====================\n");
        printf("Delete by: \n1>Course + Name \n2>Roll Number \n3>Delete All Records \n4>Cancel\nEnter choice: ");
        scanf("%d", &delete_choice);
        fflush(stdin);

        if(delete_choice == 4) {
            clrscr();
            printf("\nDeletion cancelled. Press enter to return to main menu...");
            getch();
            return;
        }

        if(delete_choice == 3) {
            clrscr();
            printf("\nDELETE ALL RECORDS");
            printf("\n==================\n");
            printf("Are you sure you want to delete all records?\nThis action cannot be undone!\n");
            printf("\nPress 1 to confirm, any other key to cancel: ");
            scanf("%d", &confirm);
            fflush(stdin);

            if(confirm == 1) {
                fclose(file);
                if(remove("ABCDB/student.txt") == 0) {
                    printf("\nAll records deleted successfully!");
                } else {
                    printf("\nError deleting records!");
                }
                printf("\n\nPress enter to continue...");
                getch();
                return;
            } else {
                printf("\nDeletion cancelled. Press enter to return...");
                getch();
                continue;
            }
        }

        if(delete_choice == 1) {
            clrscr();
            printf("\nDELETE STUDENT RECORD");
            printf("\n=====================\n");
            printf("\nAvailable Courses:\n");
            course_file = fopen("ABCDB/course.txt", "r");
            if(course_file != NULL) {
                
                while(fgets(course_line, sizeof(course_line), course_file)) {
                    if(strstr(course_line, "Course Name\t:")) {
                        printf("%s", course_line);
                    }
                }
                fclose(course_file);
            }

            printf("\nEnter Course: ");
            scanf("%s", course_to_delete);
            for(i=0;course_to_delete[i]!=NULL;i++)
              course_to_delete[i]=toupper(course_to_delete[i]);
            fflush(stdin);

            if(!getCourseDetails(course_to_delete, &c)) {
                printf("\nCourse not found! Press enter to try again...");
                getch();
                continue;
            }

            printf("\nEnter student name to delete from %s (enter full name): ", course_to_delete);
            fgets(name_to_delete, sizeof(name_to_delete), stdin);
            toTitleCase(name_to_delete);
            name_to_delete[strcspn(name_to_delete, "\n")] = 0;

            // Convert to lowercase for case-insensitive comparison
            strcpy(name_to_delete_lower, name_to_delete);
            for(i = 0; name_to_delete_lower[i]; i++) {
                name_to_delete_lower[i] = tolower(name_to_delete_lower[i]);
            }
        } else if(delete_choice == 2) {
            clrscr();
            printf("\nDELETE STUDENT RECORD");
            printf("\n=====================\n");
            printf("\nEnter roll number to delete (0 to cancel): ");
            scanf("%d", &roll_to_delete);
            fflush(stdin);

            if(roll_to_delete == 0) {
                printf("\nDeletion cancelled. Press enter to return...");
                getch();
                continue;
            }
        }

        // Preview matching records
        rewind(file);
        found = 0;

        while(fgets(line, sizeof(line), file)) {
            trimmed = line;
            while (*trimmed == ' ' || *trimmed == '\t') trimmed++;

            if(strstr(line, "Roll\t\t:")) {
                // Store all lines of the record
                strcpy(record_lines[0], line);
                
                if(strncmp(trimmed, "Roll", 4) == 0) {
                    strcpy(record_lines[0], line);
                    match = 1;
                
                    for(i = 1; i < 8; i++) {
                        if(!fgets(record_lines[i], sizeof(record_lines[i]), file)) {
                            printf("\nError reading file! Press enter to return...");
                            match = 0;  // FIXED: Added semicolon
                            getch();
                            return;
                        }
                    }

                    if(match) {
                        // Parse each field using strncmp
                        for(i = 0; i < 8; i++) {
                            trimmed = record_lines[i];
                            while (*trimmed == ' ' || *trimmed == '\t') trimmed++;

                            if(strncmp(trimmed, "Roll", 4) == 0) {
                                sscanf(trimmed, "Roll : %d", &temp_record.roll);
                            }
                            else if(strncmp(trimmed, "Course", 6) == 0 && !strstr(trimmed, "Code") && !strstr(trimmed, "Detail")) {
                                sscanf(trimmed, "Course : %s", temp_record.course);
                            }
                            else if(strncmp(trimmed, "Name", 4) == 0) {
                                sscanf(trimmed, "Name : %[^\n]", temp_record.name);
                            }
                            else if(strncmp(trimmed, "Course Code", 10) == 0) {
                                sscanf(trimmed, "Course Code : %d", &temp_record.course_code);
                            }
                            else if(strncmp(trimmed, "Course Detail", 12) == 0) {
                                sscanf(trimmed, "Course Detail : %[^\n]", temp_record.course_detail);
                            }
                            else if(strncmp(trimmed, "Duration", 8) == 0) {
                                sscanf(trimmed, "Duration : %d", &temp_record.duration);
                            }
                            else if(strncmp(trimmed, "Adm.Year", 8) == 0) {
                                sscanf(trimmed, "Adm.Year : %d", &temp_record.admyr);
                            }
                            else if(strncmp(trimmed, "Fee", 3) == 0) {
                                sscanf(trimmed, "Fee : %ld", &temp_record.fee);
                            }
                        }

                        // Create lowercase version of name for comparison
                        strcpy(temp_name_lower, temp_record.name);
                        for(i = 0; temp_name_lower[i]; i++) {
                            temp_name_lower[i] = tolower(temp_name_lower[i]);
                        }

                        if((delete_choice == 1 &&
                            strcmp(temp_record.course, course_to_delete) == 0 &&
                            strstr(temp_name_lower, name_to_delete_lower) != NULL) ||
                           (delete_choice == 2 && temp_record.roll == roll_to_delete)) {

                            found++;
                            
                            // Use the common preview function
                            preview_choice = showRecordPreviewS(&temp_record, found);

                            if(preview_choice == 1) {
                                printf("\nAre you sure you want to delete this record? (1-Yes, 0-No): ");
                                scanf("%d", &confirm);
                                strcpy(coursedel,temp_record.course);
                                fflush(stdin);

                                if(confirm) {
                                    temp_file = fopen("ABCDB/temp.txt", "w");  // FIXED: Consistent path
                                    if(temp_file == NULL) {
                                        printf("\nError creating temporary file! Press enter to return...");
                                        getch();
                                        return;
                                    }

                                    // Copy all records except the one to be deleted
rewind(file);
while(fgets(line, sizeof(line), file)) {
    if(strstr(line, "Roll\t\t:")) {
        // Read the current record's details to check if it should be deleted
        
        strcpy(current_record_lines[0], line);
        
        // Read the complete current record
        for(i = 1; i < 8; i++) {
            if(!fgets(current_record_lines[i], sizeof(current_record_lines[i]), file)) {
                break;
            }
        }
        
        // Parse the current record to get roll and course
        
        
        for(j = 0; j < 8; j++) {
            trimmed_current = current_record_lines[j];
            while (*trimmed_current == ' ' || *trimmed_current == '\t') trimmed_current++;
            
            if(strncmp(trimmed_current, "Roll", 4) == 0) {
                sscanf(trimmed_current, "Roll : %d", &current_record_roll);
            }
            else if(strncmp(trimmed_current, "Course", 6) == 0 && !strstr(trimmed_current, "Code") && !strstr(trimmed_current, "Detail")) {
                sscanf(trimmed_current, "Course : %s", current_record_course);
            }
        }
        
        // Check if this is the record to delete
        // Delete only if BOTH roll number AND course match the selected record
        if(current_record_roll == temp_record.roll && strcmp(current_record_course, coursedel) == 0) {
            // This is the record to delete - skip it (don't write to temp file)
            //printf("\nSkipping record: Roll %d, Course %s", current_record_roll, current_record_course);
        } else {
            // This is NOT the record to delete - copy it to temp file
            for(k = 0; k < 8; k++) {
                fprintf(temp_file, "%s", current_record_lines[k]);
            }
        }
    } else {
        // This line is not a record start, copy it as is
        fprintf(temp_file, "%s", line);
    }
}

                                    fclose(temp_file);
                                    fclose(file);
                                    remove("ABCDB/student.txt");
                                    rename("ABCDB/temp.txt", "ABCDB/student.txt");  // FIXED: Consistent path
                                    
                                    // Reopen the file
                                    file = fopen("ABCDB/student.txt", "r");
                                    if(file == NULL) {
                                        printf("\nError reopening file! Press enter to return...");
                                        getch();
                                        return;
                                    }

                                    printf("\nRecord deleted successfully!");
                                    found = -1; // Mark as deleted
                                    break;
                                }
                            } else if(preview_choice == 3) {
                                printf("\nDeletion cancelled. Press enter to return...");
                                getch();
                                return;
                            }
                        }
                    }
                }  // FIXED: Added missing closing brace
            }
        }

        if(found == 0) {
            if(delete_choice == 1)
                printf("\nNo record found with name '%s' in %s!", name_to_delete, course_to_delete);
            else
                printf("\nNo record found with roll number %d!", roll_to_delete);
        }
        
        clrscr();

        printf("\n\nDo you want to delete another record? (1-Yes, 0-No): ");
        scanf("%d", &continue_deleting);
        fflush(stdin);

    } while(continue_deleting == 1);
}

// function to check if course exists and get details
int getCourseDetails(char *course_name, course *c) {
    FILE *course_file;
    char line[200];
    int found = 0;
    char record_lines[5][200];
    int i;
    char temp_name[30];
    
    course_file = fopen("ABCDB/course.txt", "r");
    if(course_file == NULL) {
        printf("Error: Cannot open course.txt file\n");
        return 0;
    }
    
    while(fgets(line, sizeof(line), course_file)) {
        // Look for "Course Code" line first
        if(strstr(line, "Course Code\t:")) {
            found = 1;
            strcpy(record_lines[0], line);  // Course Code line
            for(i = 1; i < 5; i++) {
                if(!fgets(record_lines[i], sizeof(record_lines[i]), course_file)) {
                    found = 0;
                    break;
                }
            }
            
            if(found) {
                // Parse course name from the second line
                sscanf(record_lines[1], "Course Name\t: %s", temp_name);
                if(strcmp(temp_name, course_name) == 0) {
                    // Parse all fields correctly
                    sscanf(record_lines[0], "Course Code\t: %d", &c->course_code);
                    strcpy(c->course_name, temp_name);
                    sscanf(record_lines[2], "Course Detail\t: %[^\n]", c->course_detail);
                    sscanf(record_lines[3], "Duration\t: %d", &c->duration);
                    sscanf(record_lines[4], "Fee\t\t: %ld", &c->fee);
                    fclose(course_file);
                    return 1;
                }
            }
        }
    }
    
    fclose(course_file);
    return 0;
}

//function to convert the string into the title case
void toTitleCase(char str[]) {
    int i;
    int len = strlen(str);
    int capitalizeNext = 1; // Flag to capitalize the next alphabetic character
    
    for (i = 0; i < len; i++) {
        if (isalpha(str[i])) {
            if (capitalizeNext) {
                str[i] = toupper(str[i]);
                capitalizeNext = 0;
            } else {
                str[i] = tolower(str[i]);
            }
        } else {
            // Non-alphabetic character found, capitalize next alphabetic character
            capitalizeNext = 1;
        }
    }
}
