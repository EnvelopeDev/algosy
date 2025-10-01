#include "listSet.hpp"

int ListSet::setCounter = 0;

ListSet::ListSet(){
    if(setCounter < 10) std::cout << "ListSet::ListSet() - default constructor" << std::endl;
    sz=0;
    head=nullptr;
    end=nullptr;
    setCounter++;
    if(setCounter < 10) std::cout << "Active ListSet instances: " << setCounter << std::endl;
}

ListSet::ListSet(const char* inpSet){
    if(setCounter < 10) std::cout << "ListSet::ListSet(const char* inpSet) - constructor from char array" << std::endl;
    if(!inpSet){
        sz=0;
        head=nullptr;
        setCounter++;
        if(setCounter < 10) std::cout << "Active ListSet instances: " << setCounter << std::endl;
        return;     
    }
    sz=0;
    head=nullptr;
    end=nullptr;
    for(int i=0;i<strlen(inpSet);i++){
        insert(inpSet[i]);
    }
    setCounter++;
    if(setCounter < 10) std::cout << "Active ListSet instances: " << setCounter << std::endl;
}

ListSet::ListSet(const ListSet& other){
    if(setCounter < 10) std::cout << "ListSet::ListSet(const ListSet& other) - copy constructor" << std::endl;
    sz=0;
    head=nullptr;
    end=nullptr;
    Node* curr = other.head;
    for(int i=0;i<other.sz;i++){
        insert(curr->value);
        curr = curr->next;
    }
    setCounter++;
    if(setCounter < 10) std::cout << "Active ListSet instances: " << setCounter << std::endl;
}

ListSet::~ListSet(){
    if(setCounter < 10) std::cout << "ListSet::~ListSet() - destructor" << std::endl;
    clear();
    setCounter--;
    if(setCounter < 10) std::cout << "Active ListSet instances: " << setCounter << std::endl;
}

ListSet& ListSet::operator=(const ListSet& other){
    if(setCounter < 10) std::cout << "ListSet::operator=(const ListSet& other) - copy assignment operator" << std::endl;
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
    if(setCounter < 10) std::cout << "ListSet::operator&(const ListSet& other) - intersection operator" << std::endl;
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
    if(setCounter < 10) std::cout << "ListSet::operator|(const ListSet& other) - union operator" << std::endl;
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
    if(setCounter < 10) std::cout << "ListSet::operator&=(const ListSet& other) - intersection assignment operator" << std::endl;
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
    if(setCounter < 10) std::cout << "ListSet::operator|=(const ListSet& other) - union assignment operator" << std::endl;
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
    if(setCounter < 10) std::cout << "ListSet::operator~() - complement operator" << std::endl;
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
    if(setCounter < 10) std::cout << "ListSet::operator==(const ListSet& other) - equality operator" << std::endl;
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
    if(setCounter < 10) std::cout << "ListSet::subtractSets(const ListSet& B, const ListSet& C, const ListSet& D) - subtract sets method" << std::endl;
    ListSet resSet = *this & ~(B | C | D);
    return resSet;
}

void ListSet::insert(char ch){
    if(setCounter < 10) std::cout << "ListSet::insert(char ch) - insert character: " << ch << std::endl;
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
    if(setCounter < 10) std::cout << "ListSet::remove(char ch) - remove character: " << ch << std::endl;
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
    if(setCounter < 10) std::cout << "ListSet::print() - print set contents" << std::endl;
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
    if(setCounter < 10) std::cout << "ListSet::contains(char ch) - check contains character: " << ch << std::endl;
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
    if(setCounter < 10) std::cout << "ListSet::toChar() - convert to char array" << std::endl;
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
    if(setCounter < 10) std::cout << "ListSet::toString() - convert to string" << std::endl;
    std::string res(toChar());
    return res;
}

std::size_t ListSet::getSize()const{
    if(setCounter < 10) std::cout << "ListSet::getSize() - get set size" << std::endl;
    return sz;
}

void ListSet::clear(){
    if(setCounter < 10) std::cout << "ListSet::clear() - clear set" << std::endl;
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