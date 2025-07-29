#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<string.h>
#include "COURSE.H"



void course_management_main() {
    FILE *file = NULL;
    courseC *c = NULL;
    char choice;
    
    


    do {
        clrscr();
        printf("\nARCADE BUSINESS COLLEGE");
        printf("\n=======================\n");
        printf("\nEnter the choice of operation you want to perform: \n\n 1>Create a course \n 2>Read course details \n 3>Update a course detail \n 4>Remove a course \n 5>Exit \n\nEnter your choice: ");
        choice=getch();
        fflush(stdin);
        
        c = malloc(sizeof(courseC));
          if (c == NULL) {
            clrscr();
            printf("\nMemory Allocation failure!\n\npress enter to exit...");
            getch();
            exit(1);
          }

        switch (choice) {
        
          case '1':
            if (file != NULL) fclose(file);
            file = createC();
            if (file != NULL) {
                write_course(file, c);
                
                fclose(file);
                file = NULL;
            }
            
          break;
          
          case '2':
          
            if (file != NULL) fclose(file);
            file = fopen("ABCDB/course.txt", "r");
            if (file == NULL) {
              clrscr();
              printf("\nError in opening the record file\n\npress enter to go back...");
              getch();
            }else if (file != NULL) {
                read_course(file, c);
                
                fclose(file);
                file = NULL;
            }
          break;
          
          case '3':
          updateCourse(file,c);
          break;
          
          case '4':
          removeCourse(file,c);
          break;
          
         case '5': 
            clrscr();
            printf("\nGoing Back...\n\npress enter...");
            getch();
            clrscr();
            if(c!=NULL) free(c);
            return;
        }
        
    } while (choice != 5);

    if (file != NULL) fclose(file);
    if(c!=NULL) free(c);
}

FILE* createC() {
    FILE *file;
    file = fopen("ABCDB/course.txt", "a");
    if (file == NULL) {
        clrscr();
        printf("\nError in opening the record file\n\npress enter to go back...");
        getch();
        return NULL;
    }
    return file;
}

void write_course(FILE *file, courseC *c) {
    int main_choice = 1, save_choice;
    char temp[10];
    int i;

    while (main_choice == 1) {
        clrscr();
        printf("\nENTER COURSE DETAILS");
        printf("\n=====================\n");

        // Course code entry
        do {
            printf("Enter the course code: ");
            scanf("%d", &c->course_code);
            fflush(stdin);
            if(c->course_code > 9999 || c->course_code < 1000 || readCode(c->course_code)){
              printf("\nTHe input has either been taken or is invalid!\n\nEnter again..\n");
            }
        } while (c->course_code > 9999 || c->course_code < 1000 || readCode(c->course_code));

        // Course name input
        do {
            printf("\nEnter the name of the course(in acronym): ");
            fgets(c->course_name, sizeof(c->course_name), stdin);
            c->course_name[strcspn(c->course_name, "\n")] = 0; // Remove newline
            for(i=0;c->course_name[i]!=NULL;i++)
              c->course_name[i]=toupper(c->course_name[i]);
            if (strlen(c->course_name) == 0)
                printf("\nCourse Name cannot be empty. Please try again.\n");
            if (readName(c->course_name))
              printf("\nThis course already exists!\n");
        } while (strlen(c->course_name) == 0 || readName(c->course_name));

        // Course detail input
        do {
            printf("\nEnter the detail of course(full name): ");
            fgets(c->course_detail, sizeof(c->course_detail), stdin);
            c->course_detail[strcspn(c->course_detail, "\n")] = 0; // Remove newline
            for(i=0;c->course_detail[i]!=NULL;i++)
              c->course_detail[i]=toupper(c->course_detail[i]);
            if (strlen(c->course_detail) == 0)
                printf("Course Detail cannot be empty. Please try again.\n");
        } while (strlen(c->course_detail) == 0);

        // Duration
        do {
            printf("\nEnter the duration of the course (in years): ");
            scanf("%d", &c->duration);
            fflush(stdin);
        } while (c->duration <= 0);

        // Fee
        do {
            printf("\nEnter the fee for the course: ");
            scanf("%ld",&c->fee);
            fflush(stdin);
	    if (c->fee<= 0)
                printf("Course fee cannot be empty.\n\nPlease try again.\n");
        } while (c->fee<= 0);
        
        
        clrscr();
        printf("\nCOURSE DETAILS");
        printf("\n===============\n");
        printf("\nCourse Code\t: %d \nCourse Name\t: %s \nCourse Detail\t: %s \nDuration\t: %d years\nFee\t\t: ",
            c->course_code, c->course_name, c->course_detail, c->duration);
        print_inrC(c->fee);

        printf("\n\nDo you wish to : \n1>Save it \n2>Re-enter it \n3>Cancel it\nEnter choice: ");
        fgets(temp, sizeof(temp), stdin);
        save_choice = atoi(temp);

        if (save_choice == 1) {
            if (file == NULL) {
                printf("\nFile error!\n\nPress enter to continue...");
                getch();
                return;
            }
            fprintf(file, "\nCourse Code\t: %d \nCourse Name\t: %s \nCourse Detail\t: %s \nDuration\t: %d years\nFee\t\t: %.ld.00\n",
                c->course_code, c->course_name, c->course_detail, c->duration, c->fee);
            fflush(file);

            clrscr();
            printf("\nRecorded successfully!\n");
            printf("\n\nDo you wish to continue? (press 1 for yes, any other key for no): ");
            fgets(temp, sizeof(temp), stdin);
            main_choice = atoi(temp);
            fclose(file);
            file=fopen("ABCDB/course.txt","a");
        } else if (save_choice == 2) {
            main_choice = 1;
        } else if (save_choice == 3) {
            clrscr();
            printf("Going back to main menu...\n\npress enter...");
            getch();
            break;
        } else {
            printf("Invalid choice...\nenter again (1-3): ");
            main_choice = 1;
        }
    }
}

// --- Print INR with Rupee Symbol (for Turbo C, use "Rs." prefix) ---
void print_inrC(long int value) {
    long int int_part;
    int decimal_part;
    char num_str[20];
    int len, i;

    int_part = (long int)value;
    decimal_part = (int)((value - int_part) * 100 + 0.5);

    sprintf(num_str, "%ld", int_part);
    len = strlen(num_str);

    printf("Rs ");
    if (len <= 3) {
        printf("%s", num_str);
    } else {
        i = 0;
        while (i < len - 3) {
            printf("%c", num_str[i]);
            i++;
            if ((len - i) % 2 == 1 && i < len - 3) {
                printf(",");
            }
        }
        printf(",%c%c%c", num_str[len - 3], num_str[len - 2], num_str[len - 1]);
    }
    printf(".%02d", decimal_part);
}

void read_course(FILE *file,courseC *c){
    int choice;
    char record_lines[5][101];
    char line[101];
    int found=0;
    int preview_choice;
    int i;
    
    rewind(file);
    
    do{ 
      clrscr();
      printf("\nCOURSE READ");
      printf("\n===========\n");
      printf("\nDo yo want to: \n 1>Read all the course \n 2>Read course one by one \n 3>Go Back \n\nEnter your choice: ");
      scanf("%d",&choice);
      fflush(stdin);
      
      switch(choice){
        case 1:
          displayC(file,c);
          return;
          
        
        case 2:
          do{
            while(fgets(line, sizeof(line), file)){
              if(strstr(line, "Course Code\t:")){
                found++;
                strcpy(record_lines[0], line);
                for(i = 1; i < 5; i++){
                  fgets(record_lines[i], sizeof(record_lines[i]), file);
                }

                // Corrected sscanf statements
                sscanf(record_lines[0], "Course Code\t: %d", &c->course_code);
                sscanf(record_lines[1], "Course Name\t: %s", c->course_name);
                sscanf(record_lines[2], "Course Detail\t: %[^\n]", c->course_detail);
                sscanf(record_lines[3], "Duration\t: %d", &c->duration);
                sscanf(record_lines[4], "Fee\t\t: %ld", &c->fee);
                
                
                clrscr();
                printf("\nRecord %d:", found);
                printf("\n----------\n");
                printf("\nCourse Code\t: %d", c->course_code);
                printf("\nCourse Name\t: %s", c->course_name);
                printf("\nCourse Detail\t: %s", c->course_detail);
                printf("\nDuration\t: %d years", c->duration);
                printf("\nFee\t\t: ");
                print_inrC(c->fee);
                printf("\n1. Next record");
                printf("\n2. Cancel");
                printf("\nEnter your choice (1-2): ");
                scanf("%d", &preview_choice);
                fflush(stdin);
                
                if(preview_choice == 2) {
                  printf("\nSearch cancelled. Press enter...");
                  getch();
                  return;
                }
              }
            }
            if(feof(file)){
              printf("\nReached end of the file!\n\nPress enter...");
              getch();
              return;
            }
          }while(preview_choice==1);
          
          if(!found){
            printf("\nNo records found!\nPress enter to go back...");
            getch();
          }
          return;
          
        
        case 3:
          return;
      }
    }while(choice!=3);
}

// --- showRecordPreviewC as before ---
void showRecordPreviewC(courseC *record) {
    
    clrscr();
    printf("\nRecord ");
    printf("\n----------\n");
    printf("\nCourse Code\t: %d", record->course_code);
    printf("\nCourse Name\t: %s", record->course_name);
    printf("\nCourse Detail\t: %s", record->course_detail);
    printf("\nDuration\t: %d years", record->duration);
    printf("\nFee\t\t: ");
    print_inrC(record->fee);
    
}

// --- MODIFIED DISPLAY FUNCTION: record-by-record pause ---
void displayC(FILE *file,courseC *c) {
    int i, found = 0, pause_count = 0;
    char line[200];
    int fee;
   
    clrscr();
    printf("\nDISPLAYING COURSES");
    printf("\n======================\n");

    printf("%-6s | %-4s | %-20s | %-4s | %-15s\n", 
           "Cousre Code", "Course Name", "Cousre Detail", "Duration", "Fee (INR)");
    printf("---------------------------------------------------------------------\n");

    rewind(file);
    
    

    while(fgets(line, sizeof(line), file)) {
        if(strstr(line, "Course Code\t:")) {
            found++;
            sscanf(line, "\nCourse Code\t: %d", &c->course_code);
            fgets(line, sizeof(line), file);
            sscanf(line, "\nCourse Name\t: %s",c->course_name);
            fgets(line, sizeof(line), file);
            sscanf(line, "\nCourse Detail\t: %[^\n]", c->course_detail);
            fgets(line, sizeof(line), file);
            sscanf(line, "\nDuration\t: %d", &c->duration);
            fgets(line, sizeof(line), file);
            sscanf(line, "\nFee\t\t: %ld", &c->fee);

            printf("%-6d | %-4s | %-20s | %-4d years | ", c->course_code, c->course_name, c->course_detail, c->duration);
            print_inrC(c->fee);
            printf("\n");

            pause_count++;
            if(pause_count % 3 == 0) {
                printf("\nPress any key to see more records...\n\n");
                getch();
                
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

int readCode(int code){
  int check; 
  char line[101];
  FILE *fp=fopen("ABCDB/course.txt","r");
  while(fgets(line, sizeof(line), fp)){
    if(strstr(line, "Course Code\t:")){
      sscanf(line, "\nCourse Code\t: %d",&check);
      if(check==code){
        fclose(fp);
        return 1;
      }
    }
 }
 fclose(fp);
 return 0;
}

int readName(char name[20]){
  char check[20]; 
  char line[101];
  FILE *fp=fopen("ABCDB/course.txt","r");
  while(fgets(line, sizeof(line), fp)){
    if(strstr(line, "Course Name\t:")){
      sscanf(line, "\nCourse Name\t: %s",check);
      if(strcmp(check,name)==0){
        fclose(fp);
        return 1;
      }
    }
 }
 fclose(fp);
 return 0;
}

// Add these function declarations at the top with other declarations


// Update function implementation
void updateCourse(FILE *file, courseC *c) {
    int choice, update_choice, found = 0, code_input;
    char name_input[20], confirm;
    FILE *temp;
    char line[101];
    long num;
    int i;
    int current_code;
    
    if(file != NULL) fclose(file);
    file = fopen("ABCDB/course.txt", "r");
    
    if(file == NULL) {
        clrscr();
        printf("\nError opening file!\nPress enter to continue...");
        getch();
        return;
    }
    
    do {
        clrscr();
        printf("\nUPDATE COURSE");
        printf("\n=============\n");
        printf("\nSearch course by:\n1. Course Code\n2. Course Name\n3. Go Back\n\nEnter choice: ");
        scanf("%d", &choice);
        fflush(stdin);
        
        switch(choice) {
            case 1:
                printf("\nEnter Course Code: ");
                scanf("%d", &code_input);
                found = searchCourse(file, c, 'C', &code_input);
                break;
                
            case 2:
                printf("\nEnter Course Name: ");
                gets(name_input);
                for(i=0; name_input[i]!='\0'; i++)
                    name_input[i] = toupper(name_input[i]);
                found = searchCourse(file, c, 'N', name_input);
                break;
                
            case 3:
                return;
                
            default:
                printf("\nInvalid choice!\nPress enter to continue...");
                getch();
                continue;
        }
        
        if(found) {
            showRecordPreviewC(c);
            printf("\n\nDo you want to update this record? (Y/N): ");
            confirm = toupper(getch());
            
            if(confirm == 'Y') {
                do {
                    clrscr();
                    printf("\nWhat do you want to update?");
                    printf("\n1. Course Name\n2. Course Detail\n3. Duration\n4. Fee\n5. Cancel\n\nEnter choice: ");
                    scanf("%d", &update_choice);
                    fflush(stdin);
                    
                    switch(update_choice) {
                        case 1:
                            do {
                                printf("\nEnter new Course Name: ");
                                gets(c->course_name);
                                for(i=0; c->course_name[i]!='\0'; i++)
                                    c->course_name[i] = toupper(c->course_name[i]);
                                if(strlen(c->course_name) == 0 || readName(c->course_name))
                                    printf("\nInvalid or duplicate name! Try again.\n");
                            } while(strlen(c->course_name) == 0 || readName(c->course_name));
                            break;
                            
                        case 2:
                            do {
                                printf("\nEnter new Course Detail: ");
                                gets(c->course_detail);
                                for(i=0; c->course_detail[i]!='\0'; i++)
                                    c->course_detail[i] = toupper(c->course_detail[i]);
                                if(strlen(c->course_detail) == 0)
                                    printf("\nDetail cannot be empty! Try again.\n");
                            } while(strlen(c->course_detail) == 0);
                            break;
                            
                        case 3:
                            do {
                                printf("\nEnter new Duration (in years): ");
                                scanf("%d", &c->duration);
                                if(c->duration <= 0)
                                    printf("\nInvalid duration! Try again.\n");
                            } while(c->duration <= 0);
                            break;
                            
                        case 4:
                            do {
                                printf("\nEnter new Fee: ");
                                scanf("%ld", &num);
                                if(num <= 0)
                                    printf("\nInvalid fee! Try again.\n");
                            } while(num <= 0);
                            c->fee = (float)num;
                            break;
                            
                        case 5:
                            return;
                            
                        default:
                            printf("\nInvalid choice!\nPress enter to continue...");
                            getch();
                            continue;
                    }
                    
                    showRecordPreviewC(c);
                    printf("\n\nDo you want to save these changes? (Y/N): ");
                    confirm = toupper(getch());
                    
                    if(confirm == 'Y') {
                        temp = fopen("temp.txt", "w");
                        rewind(file);
                        
                        while(fgets(line, sizeof(line), file)) {
                            if(strstr(line, "Course Code\t:")) {
                                sscanf(line, "Course Code\t: %d", &current_code);
                                if(current_code == c->course_code) {
                                    fprintf(temp, "Course Code\t: %d\nCourse Name\t: %s\nCourse Detail\t: %s\nDuration\t: %d years\nFee\t\t: %ld\n",
                                        c->course_code, c->course_name, c->course_detail, c->duration, c->fee);
                                    for(i=0; i<4; i++)
                                        fgets(line, sizeof(line), file);
                                } else {
                                    fprintf(temp, "%s", line);
                                }
                            } else {
                                fprintf(temp, "%s", line);
                            }
                        }
                        
                        fclose(file);
                        fclose(temp);
                        remove("ABCDB/course.txt");
                        rename("temp.txt", "ABCDB/course.txt");
                        
                        printf("\n\nRecord updated successfully!\nPress enter to continue...");
                        getch();
                        return;
                    }
                } while(update_choice != 5);
            }
        } else {
            printf("\nRecord not found!\nPress enter to continue...");
            getch();
        }
    } while(choice != 3);
}

// Remove function implementation
void removeCourse(FILE *file, courseC *c) {
    int choice, code_input, found = 0;
    char name_input[20], confirm;
    FILE *temp;
    char line[101];
    int i;
    int current_code;
    
    if(file != NULL) fclose(file);
    file = fopen("ABCDB/course.txt", "r");
    
    if(file == NULL) {
        clrscr();
        printf("\nError opening file!\nPress enter to continue...");
        getch();
        return;
    }
    
    do {
        clrscr();
        printf("\nREMOVE COURSE");
        printf("\n=============\n");
        printf("\n1. Remove Specific Course\n2. Remove All Courses\n3. Go Back\n\nEnter choice: ");
        scanf("%d", &choice);
        fflush(stdin);
        
        switch(choice) {
            case 1:
                printf("\nSearch course by:\n1. Course Code\n2. Course Name\nEnter choice: ");
                scanf("%d", &i);
                fflush(stdin);
                
                if(i == 1) {
                    printf("\nEnter Course Code: ");
                    scanf("%d", &code_input);
                    found = searchCourse(file, c, 'C', &code_input);
                } else if(i == 2) {
                    printf("\nEnter Course Name: ");
                    gets(name_input);
                    for(i=0; name_input[i]!='\0'; i++)
                        name_input[i] = toupper(name_input[i]);
                    found = searchCourse(file, c, 'N', name_input);
                }
                
                if(found) {
                    showRecordPreviewC(c);
                    printf("\n\nAre you sure you want to remove this course? (Y/N): ");
                    confirm = toupper(getch());
                    
                    if(confirm == 'Y') {
                        temp = fopen("temp.txt", "w");
                        rewind(file);
                        
                        while(fgets(line, sizeof(line), file)) {
                            if(strstr(line, "Course Code\t:")) {
                                sscanf(line, "Course Code\t: %d", &current_code);
                                if(current_code == c->course_code) {
                                    for(i=0; i<4; i++)
                                        fgets(line, sizeof(line), file);
                                } else {
                                    fprintf(temp, "%s", line);
                                }
                            } else {
                                fprintf(temp, "%s", line);
                            }
                        }
                        
                        fclose(file);
                        fclose(temp);
                        remove("ABCDB/course.txt");
                        rename("temp.txt", "ABCDB/course.txt");
                        
                        printf("\n\nRecord removed successfully!\nPress enter to continue...");
                        getch();
                        return;
                    }
                } else {
                    printf("\nRecord not found!\nPress enter to continue...");
                    getch();
                }
                break;
                
            case 2:
                printf("\nAre you sure you want to remove ALL courses? (Y/N): ");
                confirm = toupper(getch());
                
                if(confirm == 'Y') {
                    fclose(file);
                    remove("ABCDB/course.txt");
                    file = fopen("ABCDB/course.txt", "w");
                    fclose(file);
                    printf("\n\nAll courses removed successfully!\nPress enter to continue...");
                    getch();
                    return;
                }
                break;
                
            case 3:
                return;
                
            default:
                printf("\nInvalid choice!\nPress enter to continue...");
                getch();
        }
    } while(choice != 3);
}

// Helper function to search for a course
int searchCourse(FILE *file, courseC *c, char type, void* searchVal) {
    char line[101];
    char record_lines[5][101];
    int i;
    
    rewind(file);
    
    while(fgets(line, sizeof(line), file)) {
        if(strstr(line, "Course Code\t:")) {
            strcpy(record_lines[0], line);
            for(i = 1; i < 5; i++) {
                fgets(record_lines[i], sizeof(record_lines[i]), file);
            }
            
            sscanf(record_lines[0], "Course Code\t: %d", &c->course_code);
            sscanf(record_lines[1], "Course Name\t: %s", c->course_name);
            sscanf(record_lines[2], "Course Detail\t: %[^\n]", c->course_detail);
            sscanf(record_lines[3], "Duration\t: %d years", &c->duration);
            sscanf(record_lines[4], "Fee\t\t: %ld", &c->fee);
            
            if(type == 'C' && c->course_code == *(int*)searchVal) {
                return 1;
            } else if(type == 'N' && strcmp(c->course_name, (char*)searchVal) == 0) {
                return 1;
            }
        }
    }
    
    return 0;
}
