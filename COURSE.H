
#include<stdio.h>

#ifndef COURSE_H
#define COURSE_H


typedef struct courseDetail {
    int course_code, duration;
    long int fee;
    char course_name[20], course_detail[100];
}courseC;

void course_management_main();
FILE* createC();
void write_course(FILE *file,courseC *c);
void print_inrC(long int value);
void displayC(FILE *file,courseC *c);
void showRecordPreviewC(courseC *record);
void read_course(FILE *file,courseC *c);
int readCode(int code);
int readName(char[]);
void updateCourse(FILE *file, courseC *c);
void removeCourse(FILE *file, courseC *c);
int searchCourse(FILE *file, courseC *c, char type, void* searchVal);

#endif
