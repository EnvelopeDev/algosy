#include "list.hpp"

void push_back(Node** head, char value){
    Node* newNode = new Node; //allocating memory for a new node
    newNode->next=nullptr;
    newNode->value=value;

    //setting the head if the list is empty
    if(head==nullptr){
        *head = newNode;
        return;
    }
    Node* curr = *head;
    //going through the list until the end
    while(curr->next!=nullptr){
        curr=curr->next;
    }
    //adding the new node to the end of a list
    curr->next = newNode;
}

void print(Node* head){
    Node* curr = head;
    while(curr!=nullptr){
        std::cout << curr->value << ' ';
        curr = curr->next;
    }
    std::cout << '\n';
}

Node* substructSetList(Node* A, Node* B, Node* C, Node* D){
    Node* curr = A; //current node of the main set
    Node* currSubSet=nullptr; //current node of the subsets
    bool flag=true; //flag to check if an element of the main set is not contained in the subsets
    Node* res = new Node; //allocating memory for the result list
    //going through the main set until the end
    while(curr!=nullptr){
        flag=true;
        //comparing element of the main set with the elements of the subsets
        currSubSet = B;
        while(currSubSet!=nullptr && flag){
            if(currSubSet->value==curr->value){
                flag=false;
            }
            currSubSet = currSubSet->next;
        }

        currSubSet = C;
        while(currSubSet!=nullptr && flag){
            if(currSubSet->value==curr->value){
                flag=false;
            }
            currSubSet = currSubSet->next;
        }

        currSubSet = D;
        while(currSubSet!=nullptr && flag){
            if(currSubSet->value==curr->value){
                flag=false;
            }
            currSubSet = currSubSet->next;
        }
        if(flag){
            push_back(&res, curr->value);
        }
        curr = curr->next;
    }
    return res;
}

int listSize(Node* head){
    int sz=0;
    Node* curr = head;
    while(curr!=nullptr){
        sz++;
        curr=curr->next;
    }
    return sz;
}

char* toChar(Node* head){
    int sz=listSize(head);
    Node* curr = head;
    char* res = new char[sz+1];
    res[sz] = '\0';
    for(int i=0;i<sz;i++){
        res[i]=curr->value;
        curr=curr->next;
    }
    return res;
}