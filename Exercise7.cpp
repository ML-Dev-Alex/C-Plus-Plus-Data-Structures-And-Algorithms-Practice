// Given an array of time intervals (start, end) for classroom lectures (possibly overlapping),
// find the minimum number of rooms required.
// For example, given [(30, 75), (0, 50), (60, 150)], you should return 2
#include <iostream>
#include <cstdio>
using namespace std;
int example1[2] = {30, 75};
int example2[2] = {0, 50};
int example3[2] = {60, 150};


// We are going to use a list of lists to hold classrooms and lectures in those classrooms
// Lets start by declaring the core node structure for storing lectures in a classroom
struct Lecture{
    public:
        int values[2];
        struct Lecture* next; 
}; 

// Now lets create a Node structure to hold classrooms
struct Classroom{
    public: 
        struct Lecture* firstLecture; // Each classroom points to the first lecture in it
        struct Classroom* nextClassroom; // And to the next classroom, if there are any others
        int numberOfLectures;
}; 

struct Classroom* addClassroom(Lecture* currentLecture){
    struct Classroom *newClassroom = (struct Classroom*) malloc(sizeof (struct Classroom));
    newClassroom->firstLecture = currentLecture;
    newClassroom->numberOfLectures = 1;
    newClassroom->nextClassroom = NULL;
    return newClassroom;
}


int assignToClassroom(Lecture* currentLecture, Classroom* currentClassroom, int numberOfClassrooms=1){
    Lecture* classroomLecture = currentClassroom->firstLecture;
    if (currentClassroom->firstLecture == NULL) {  // If this is the first lecture on the first classroom, initialize them
            currentClassroom->firstLecture = currentLecture;
            currentClassroom->nextClassroom = NULL;
            currentClassroom->numberOfLectures = 1;
            return numberOfClassrooms;
    }
    for (int i = 0; i < currentClassroom->numberOfLectures; i++){
        // If the current class we are trying to assign to the current classroom overlaps a class already assigned to that classroom
        if(currentLecture->values[0] >= classroomLecture->values[0] && currentLecture->values[0] <= classroomLecture->values[1]
          || currentLecture->values[1] >= classroomLecture->values[0] && currentLecture->values[1] <= classroomLecture->values[1]) {
            if (currentClassroom->nextClassroom != NULL && currentClassroom->nextClassroom != 0){  // We try to look for other classrooms that can hold it    
                numberOfClassrooms++;
                numberOfClassrooms = assignToClassroom(currentLecture, currentClassroom->nextClassroom, numberOfClassrooms); 
            } else {              
                numberOfClassrooms ++;                  
                Classroom* newClassroom = addClassroom(currentLecture);   // If there are no classrooms that can hold it
                currentClassroom->nextClassroom = newClassroom;                                                 // We assign it to a new classroom
                return numberOfClassrooms;                                                    // And we can stop looking for overlaps
            }
        }else if (i != currentClassroom->numberOfLectures - 1) classroomLecture = currentLecture->next;         // Otherwise we keep checking if it overlaps other lectures
        
        // If current lecture does not overlap any other class we put it on this classroom
        if (i >= currentClassroom->numberOfLectures - 1){
            currentClassroom->numberOfLectures ++;
            classroomLecture->next = currentLecture;
            return numberOfClassrooms;
        }
    }
    return numberOfClassrooms;
};



int main(){
    freopen( "Exercise7Output.txt", "w", stdout);  // log output
    Lecture lecture1 = {{30, 75}, NULL};
    Lecture lecture2 = {{0, 50}, NULL};
    Lecture lecture3 = {{60, 150}, NULL};
    Classroom firstClassroom = {NULL, NULL, 0};
    cout << "Assigning lecture... " << "Number of classrooms required so far: " << assignToClassroom(&lecture1, &firstClassroom) << endl;
    cout << "Assigning lecture... " << "Number of classrooms required so far: " << assignToClassroom(&lecture2, &firstClassroom) << endl;
    cout << "Assigning lecture... " << "Number of classrooms required so far: " << assignToClassroom(&lecture3, &firstClassroom) << endl;
    return 0;
}