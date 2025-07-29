#include<stdio.h>
#ifndef STUDENT_H
#define STUDENT_H


typedef struct student{
    int roll, admyr,course_code, duration;
    long int fee;
    char name[50], course[30],course_detail[100];
}stud;

typedef struct courseDetailS {
    int course_code, duration;
    long int fee;
    char course_name[20], course_detail[100];
}course;

void student_management_main();
FILE* create();
void write_record(FILE *file, stud *s);
void search(FILE *file);
void update(FILE *file, stud *s);
void delete_record(FILE *file);
void delete_all();
void displayS(FILE *file);
int count();
int generateRollNumber(char *course,int admyr);
int getCourseDetails(char *course_name, course *c);
int showRecordPreviewS(stud *record, int recordNum);
void print_inr(long int value);
void toTitleCase(char str[]);

#endif
