/*
Credits to Nihal for the 'first.txt' and 'last.txt' files.
*/

#include <bits/stdc++.h>

using namespace std;

struct Student { //student struct
    char first[100];
    char last[100];
    int id;
    float GPA;

  public:
    Student(char* newFirst, char* newLast, int newId, float newGPA) {
        strcpy(first, newFirst);
        strcpy(last, newLast);
        id = newId;
        GPA = newGPA;
    }
};

class Node { //node class
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

//function prototypes
void add(Node*& head, Student* student);
void print(Node* head);
void del(Node* &head, Node* current, Node* previous, int id);
int hashF(Student* student, int size);
void randomStudents(Node**& table, int num, int& id, int size);


int main() {
    cout << "START" << endl;

    int size = 100;
    Node** table = new Node*[size];
    for (int i = 0; i < size; i++) {
        table[i] = NULL;
    }
    int id = 0;

    bool stillPlaying = true;

    while (stillPlaying == true) {
        cout << "Would you like to 'ADD', 'PRINT', 'DELETE', or 'QUIT'" << endl;
        char input[100];
        cin >> input;

        if (strcmp(input, "ADD") == 0) { //add
            cout << "How many students would you like to add?" << endl;
            int num; cin >> num;

            randomStudents(table, num, id, size);
            cout << num << endl;
        }

        if (strcmp(input, "PRINT") == 0) { //print
            for (int i = 0; i < size; i++) {
                print(table[i]);
            }
        }

        if (strcmp(input, "DELETE") == 0) { //delete 
            cout << "What is the id of the student you want to delete?" << endl;
            int id; cin >> id;
        
            for (int i = 0; i < size; i++) {
                del(table[i], table[i], table[i], id);
            }
        }

        if (strcmp(input, "QUIT") == 0) {
            stillPlaying = false;
        }
    }
}

//function that adds student to end of current linked list
void add(Node*& head, Student* student) {
    Node* current = head;
    if(current == NULL) {
        head = new Node(student);
    } 
    else {
        while (current->getNext() != NULL) {
        current = current->getNext();
        }
        current->setNext(new Node(student));
    }
}

//function that prints all students stored in the table
void print(Node* head) {
    if (head != NULL) {
        while(head != NULL) {
            cout 
            << head->getStudent()->first << " "
            << head->getStudent()->last << ", "
            << head->getStudent()->id << ", "
            << head->getStudent()->GPA << endl;

            head = head->getNext();
        }
    }
}

//function that deletes a student
void del(Node* &head, Node* current, Node* previous, int id) {
    if (head == NULL) {
        return;
    } 

    else if (current == NULL) {
        return;
    } 

    else if (id == current->getStudent()->id) {
        if (id == head->getStudent()->id) {
            Node* temp = head;
            head = head->getNext();
            temp->~Node();
        } 
        else {
            previous->setNext(current->getNext());
            current->~Node();
        }
    } 

    else {
        del(head, current->getNext(), current, id);
    }
}

//hash function
int hashF(Student* student, int size) {
    return student->id % size;
}

//function that generates random students and adds them to the hash table
void randomStudents(Node**& table, int num, int& id, int size) {
    srand(time(NULL));
    for (int i = 0; i < num; i++) {
        int firstline = rand() % 20+1;
        int lastline = rand() % 20+1;

        fstream fin; 
        fstream lin;
        fin.open("first.txt");
        lin.open("last.txt");
        char* first = new char[100];
        char* last = new char[100];

        for (int j = 0; j < firstline; j++) {
            fin >> first;
        }
        for (int j = 0; j < lastline; j++) {
            lin >> last;
        }

        float GPA = float(rand()%501)/100;

        Student* student = new Student(first, last, id, GPA);
        id++;

        add(table[hashF(student, size)], student);
    }
}