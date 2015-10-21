
#ifndef Q3_H_
#define Q3_H_

#include <stdbool.h>

#define MAX_LEN 256

// Player struct for each student
typedef struct {
    char name[MAX_LEN];
    char student_id[MAX_LEN];
    float grade;
} student;

student students[5];

#endif /* Q3_H_ */
