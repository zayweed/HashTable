#include <bits/stdc++.h>

using namespace std;

struct Student {
    char first[200];
    char last[200];
    char id[200];
    char GPA[200];

  public:
    Student(char* newFirst, char* newLast, char* newId, char* newGPA) {
        strcpy(first, newFirst);
        strcpy(last, newLast);
        strcpy(id, newId);
        strcpy(GPA, newGPA);
    }
};

class Node {
    Student* student;
    Node* next;

  public:
    Node(Student* newStudent) { //constructor
        student = newStudent;
        next = NULL;
    }

    Student* getStudent() { //getter for student
    return student;
    }

    void setStudent(Student* newStudent) { //setter for student
        student = newStudent;
    }

    Node* getNext() { //getter for next node
        return next;
    }

    void setNext(Node* inNext) { //setter for next node
        next = inNext;
    }

};

int main() {
    cout << "START" << endl;
}

//function that adds student to student list
void add() {
  
}

//function that prints all students stored in the studentlist
void print() {
  
}

//function that deletes a student
void del() {

}