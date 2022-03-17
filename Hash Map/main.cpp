/*
Credits to Nihal for the 'first.txt' and 'last.txt' files.
*/

#include <bits/stdc++.h>
#include <string>

using namespace std;

struct Student {
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

//function that adds student to student list
void add(Node*& head, Student* student) {
    Node* newNode = new Node(student);
    Node* current = head;
    if (current == NULL) {
        head = newNode;
    }
    while (current->getNext() != NULL) {
        current = current->getNext();
    } 
    current->setNext(newNode);
}

//function that prints all students stored in the studentlist
void print(Node* head) {
    if (head != NULL) {
        while(head != NULL) {
            cout 
            << head->getStudent()->first << " "
            << head->getStudent()->last << ", "
            << head->getStudent()->id << ", "
            << head->getStudent()->GPA;

            head = head->getNext();
        }
    }
}

//function that deletes a student
void del(Node**& table, int id, int size) {
    for (int i = 0; i < size; i++) {
        Node* head = table[i];

        if (head != NULL) {
            if (head->getStudent()->id == id) {
                Node* temp = head;
                head = head->getNext();
                temp->~Node();
            }
            else {
                Node* previous = head;
                Node* current = head;

                while (current->getNext() != NULL) {
                    current = current->getNext();
                    if (current->getStudent()->id == id) {
                        previous->setNext(current->getNext());
                        current->~Node();
                        return;
                    }
                    previous = current;
                }
            }
        }
    }
}

int hashF(Student* student, int size) {
    return student->id % size;
}

void generate(Node**& table, int num, int& id, int size) {
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

        if (strcmp(input, "ADD") == 0) {
            cout << "How many students would you like to add?" << endl;
            int num; cin >> num;

            generate(table, num, id, size);
        }

        if (strcmp(input, "PRINT") == 0) {
            for (int i = 0; i < size; i++) {
                print(table[i]);
            }
        }

        if (strcmp(input, "DELETE") == 0) {
            cout << "What is the id of the student you want to delete?" << endl;
            int id; cin >> id;
        
            del(table, id, size);
        }

        if (strcmp(input, "QUIT") == 0) {
            stillPlaying = false;
        }
    }
}