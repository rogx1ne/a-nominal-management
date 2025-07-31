#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include "STUDENT.H"
#include "COURSE.H"

void displayM();

void main()
{
    char choice;
    do
    {
        clrscr();
        // system("CD");
        displayM();
        printf("\n\n\nWhich domain you want to manage now: \n\n 1>Student Management \n 2>Course Management \n\n 3>Exit \n\n\nEnter your choice: ");

        choice = getche();

        switch (choice)
        {
        case '1':
            // system("STUDENT");
            student_management_main();
            break;

        case '2':
            // system("COURSE");
            course_management_main();
            break;

        case '3':
            clrscr();
            printf("Thanks for using the service!\nPress enter...");
            getch();
            clrscr();
            return;
        }
    } while (choice != '3');
}

void displayM()
{

    printf("================================================================================"
           "%-80s"
           "%-80s"
           "%-80s"
           "%-80s"
           "%-80s"
           "================================================================================",
           " ", "Arcade Business College Management", " ","Presented by J");
}
