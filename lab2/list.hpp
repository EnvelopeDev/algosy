#pragma once
#include <iostream>
#include <stdexcept> //for calling exceptions

template<typename T>
class List
{
private:
    //structure of a node of the list
    struct Node
    {
        T value;
        Node* next;
        Node* prev;
    };
    Node* head; //pointer to the head of the list
    std::size_t sz; //size of the list (amount of nodes)
    void freeList(); //deleting of allocated memory
public:
    List(); //default constructor
    List(const T* arr, size_t size); //constructor with parameters (array of values, size of array)
    ~List(); //destructor
    void push_back(T value); //adding a new node to the end of the list
    void print(); //printing the list to the terminal
    List* substractLists(const List& B, const List& C, const List& D); //function that subtracts sets from the set A
    char* toDynChar(); //converting the list to array (only for List<char>)
};

template<typename T>
List<T>::List(){
    //initialize empty list
    head=nullptr;
    sz=0;
}

template<typename T>
List<T>::~List(){
    freeList();
}

template<typename T>
List<T>::List(const T* arr, size_t size){
    //initialize an empty list
    sz=0;
    head=nullptr;
    //adding values from an array
    for(int i=0;i<size;i++){
        this->push_back(arr[i]);
    }
}

template<typename T>
void List<T>::freeList(){
    //if list isn`t empty deleting it
    if(head!=nullptr){
        Node* curr = head;
        Node* temp; //temporary variable to store an address of the node to delete it
        while(curr!=nullptr){
            temp = curr;
            curr=curr->next;
            delete temp;
        }
    }
}

template<typename T>
void List<T>::push_back(T value){
    Node* newNode = new Node; //allocating memory for a new node
    newNode->prev=nullptr;
    newNode->next=nullptr;
    newNode->value=value;
    sz++; //increase size of the list
    //setting the head if the list is empty
    if(head==nullptr){
        head = newNode;
        return;
    }
    Node* curr = head;
    //going through the list until the end
    while(curr->next!=nullptr){
        curr=curr->next;
    }
    //adding the new node to the end of a list
    curr->next = newNode;
    newNode->prev=curr;
}

template<typename T>
void List<T>::print(){
    //exiting from the func if the list is empty
    if(head==nullptr){
        return;
    }
    Node* curr = head;
    //going through the list until the end, printing the values of the nodes
    while(curr!=nullptr)
    {
        std::cout << curr->value << ' ';
        curr = curr->next;
    }
    std::cout << '\n';
}

template<typename T>
List<T>* List<T>::substractLists(const List& B, const List& C, const List& D){
    Node* curr = this->head; //current node of the main set
    Node* currSubSet=nullptr; //current node of the subsets
    bool flag=true; //flag to check if an element of the main set is not contained in the subsets
    List<T>* res = new List<T>(); //allocating memory for the result list
    //going through the main set until the end
    while(curr!=nullptr){
        flag=true;
        //comparing element of the main set with the elements of the subsets
        currSubSet = B.head;
        while(currSubSet!=nullptr && flag){
            if(currSubSet->value==curr->value){
                flag=false;
            }
            currSubSet = currSubSet->next;
        }

        currSubSet = C.head;
        while(currSubSet!=nullptr && flag){
            if(currSubSet->value==curr->value){
                flag=false;
            }
            currSubSet = currSubSet->next;
        }

        currSubSet = D.head;
        while(currSubSet!=nullptr && flag){
            if(currSubSet->value==curr->value){
                flag=false;
            }
            currSubSet = currSubSet->next;
        }
        if(flag){
            res->push_back(curr->value);
        }
        curr = curr->next;
    }
    return res;
}

template<>
char* List<char>::toDynChar() {
    char* result = new char[sz+1]; //allocating memory for the result array
    Node* curr = head;
    int i=0;
    
    //going through the list until the end, converting values from list to array
    while(curr != nullptr){
        result[i++] = curr->value;
        curr = curr->next;
    }
    result[i] = '\0';
    
    return result;
}