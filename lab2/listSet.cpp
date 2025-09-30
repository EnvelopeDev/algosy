#include "listSet.hpp"

ListSet::ListSet(){
    sz=0;
    head=nullptr;
    end=nullptr;
}

ListSet::ListSet(const char* inpSet){
    if(!inpSet){
        sz=0;
        head=nullptr;
        return;     
    }
    sz=0;
    head=nullptr;
    end=nullptr;
    for(int i=0;i<strlen(inpSet);i++){
        insert(inpSet[i]);
    }
}

ListSet::ListSet(const ListSet& other){
    sz=0;
    head=nullptr;
    end=nullptr;
    Node* curr = other.head;
    for(int i=0;i<other.sz;i++){
        insert(curr->value);
        curr = curr->next;
    }
}

ListSet::~ListSet(){
    clear();
}

ListSet& ListSet::operator=(const ListSet& other){
    if(&other==this){
        return *this;
    }
    this->clear();
    Node* curr = other.head;
    for(int i=0;i<other.sz;i++){
        insert(curr->value);
        curr = curr->next;
    }
    return *this;
}

ListSet ListSet::operator&(const ListSet& other)const{
    ListSet res;
    bool flag;
    Node* currThis = this->head, *currOther = other.head;
    for(int i=0;i<this->sz;i++){
        flag = false;
        currOther=other.head;
        for(int j=0;j<other.sz && !flag;j++){
            if(currThis->value==currOther->value){
                flag = true;
            }
            currOther=currOther->next;
        }
        if(flag){
            res.insert(currThis->value);
        }
        currThis = currThis->next;
    }

    return res;
}

ListSet ListSet::operator|(const ListSet& other)const{
    ListSet res;
    res = *this;
    Node* curr = other.head;
    for(int i=0;i<other.sz;i++){
        res.insert(curr->value);
        curr=curr->next;
    }
    return res;
}

ListSet& ListSet::operator&=(const ListSet& other){
    if(&other==this){
        return *this;
    }
    
    bool flag;
    ListSet res;
    Node* currThis=head, *currOther = other.head;
    for(int i=0;i<this->sz;i++){
        flag = false;
        currOther=other.head;
        for(int j=0;j<other.sz && !flag;j++){
            if(currThis->value==currOther->value){
                flag = true;
            }
            currOther=currOther->next;
        }
        if(flag){
            res.insert(currThis->value);
        }
        currThis=currThis->next;
    }
    if(sz!=0){
        clear();
    }
    *this = res;
    return *this;
}

ListSet& ListSet::operator|=(const ListSet& other){
    if(&other==this){
        return *this;
    }
    Node* curr = other.head;
    for(int i=0;i<other.sz;i++){
        this->insert(curr->value);
        curr=curr->next;
    }

    return *this;
}

ListSet ListSet::operator~()const{
    ListSet res;
    bool flag;
    Node* curr = head;
    for(int i=0;i<UNIVERSUM_SIZE;i++){
        flag=true;
        curr=head;
        for(int j=0;j<sz&&flag;j++){
            if('A'+i==curr->value){
                flag=false;
            }
            curr=curr->next;
        }
        if(flag){
            res.insert('A'+i);
        }
    }
    return res;
}

bool ListSet::operator==(const ListSet& other)const{
    if(this->sz!=other.sz){
        return false;
    }
    bool flag;
    Node* currThis=this->head, *currOther = other.head;
    for(int i=0;i<this->sz;i++){
        flag = false;
        currOther = other.head;
        for(int j=0;j<other.sz && !flag;j++){
            if(currThis->value==currOther->value){
                flag = true;
            }
            currOther = currOther->next;
        }
        if(!flag){
            return false;
        }
        currThis = currThis->next;
    }
    return true;
}

ListSet ListSet::subtractSets(const ListSet& B, const ListSet& C, const ListSet& D)const{
    ListSet resSet = *this & ~(B | C | D);
    return resSet;
}

void ListSet::insert(char ch){
    if(sz==26){
        return;
    }
    if(sz==0){
        Node* newNode = new Node(ch);
        head = newNode;
        end=head;
        sz++;
        return;
    }
    bool flag=true;
    Node* curr = head;
    for(int i=0;i<sz && flag;i++){
        if(curr->value==ch){
            flag=false;
        }
        curr=curr->next;
    }
    if(flag){
        Node* newNode = new Node(ch);
        end->next=newNode;
        end = end->next;
        sz++;
    }
}

void ListSet::remove(char ch){
    if(sz==0){
        return;
    }
    if(head->value==ch){
        Node* temp = head;
        head = temp->next;
        if(sz==2){
            end=head;
        }
        delete temp;
        sz--;
        return;
    }
    Node* curr = head, *temp;
    bool flag = false;
    for(int i=0;i<sz-1 && !flag;i++){
        if(curr->next->value==ch){
            flag=true;
            temp = curr->next;
            if(end==temp){
                end=curr;
            }
            curr->next = temp->next;
            delete temp;
            sz--;
        }
        curr=curr->next;
    }
}

void ListSet::print()const{
    Node* curr = head;
    for(int i=0;i<sz;i++){
        std::cout << curr->value;
        if(i!=sz-1){
            std::cout << ", ";
        }
        curr=curr->next;
    }
}

bool ListSet::contains(char ch)const{
    Node* curr = head;
    for(int i=0;i<sz;i++){
        if(curr->value==ch){
            return true;
        }
        curr=curr->next;
    }
    return false;
}

char* ListSet::toChar()const{
    char* res = new char[sz+1];
    Node* curr = head;
    for(int i=0;i<sz;i++){
        res[i] = curr->value;
        curr=curr->next;
    }
    res[sz]='\0';
    return res;
}

std::string ListSet::toString()const{
    std::string res(toChar());
    return res;
}

std::size_t ListSet::getSize()const{
    return sz;
}

void ListSet::clear(){
    Node* curr = head; //setting current node to the head
    Node* temp = nullptr;
    //going through the entire list, deleting each node
    for(int i=0;i<sz;i++){
        temp = curr; //saving node to delete
        curr = curr->next;
        delete temp; //deleting node
    }
    sz=0;
    head=nullptr;
    end=nullptr;
}