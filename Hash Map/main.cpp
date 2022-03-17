/*
Zayeed Saffat
3/16/2022
This project uses a hash table and random student generator to efficiently store student data using a hash function. 
The commands are 'ADD', 'PRINT', 'DELETE', and 'QUIT'.
Credits to Nihal Parthasarathy for the 'first.txt' and 'last.txt' files.
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
int collisionCount(Node** table, int size);


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
    
            if (collisionCount(table, size) > 3) { //if are more than 3 collisions somewhere in the hash table
                //make a temporary array that is double the size
                size = size*2;

                Node** temp = new Node*[size];
                for (int i = 0; i < size; i++) {
                    temp[i] = NULL;
                }

                for (int i = 0; i < size/2; i++) { //rehash
                    Node* node = table[i];
                    while (node != NULL) {
                        add(temp[hashF(node->getStudent(), size)], node->getStudent());
                        node = node->getNext();
                    }
                }

                //replace the hash table with the temporary table
                table = new Node*[size];
                table = temp;
            }
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

        if (strcmp(input, "QUIT") == 0) { //quit
            stillPlaying = false;
        }
    }
}

//function that adds student to end of current linked list
void add(Node*& head, Student* student) {
    Node* current = head;
    if(current == NULL) { //sets new to head if head is null
        head = new Node(student);
    } 
    else { //adds new node to end of the linked list
        while (current->getNext() != NULL) {
        current = current->getNext();
        }
        current->setNext(new Node(student));
    }
}

//function that prints all students stored from one head
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

//function that deletes a student by id number
void del(Node* &head, Node* current, Node* previous, int id) {
    if (head == NULL) { //does nothing if head is null
        return;
    } 

    else if (current == NULL) { //does nothing if the current node is null
        return;
    } 

    else if (id == current->getStudent()->id) { //removes current node if target id is found
        if (id == head->getStudent()->id) {
            Node* temp = head;
            head = head->getNext();
        } 
        else {
            previous->setNext(current->getNext());
        }
    } 

    else {
        del(head, current->getNext(), current, id); //recursion
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
        //generates 2 random numbers from 0 to 19 for which line of the 'first.txt' and 'last.txt' to get the names from
        int firstline = rand() % 20+1;
        int lastline = rand() % 20+1;

        //file stuff
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

        float GPA = float(rand()%501)/100; //generates random float from 0.00 to 5.00 to use as gpa

        Student* student = new Student(first, last, id, GPA); //makes the student
        id++; //increments id

        add(table[hashF(student, size)], student); //adds student to table
    }
}

//function that returns the max number of collisions found in the table
int collisionCount(Node** table, int size) {
    int maximum = 0;
    for (int i = 0; i < size; i++) {
        Node* node = table[i];
        int current = 1;
        if (node != NULL) {
            while (node->getNext() != NULL) {
                node = node->getNext();
                current++;
            }
            maximum = max(maximum, current);
        }
    }

    return maximum;
}