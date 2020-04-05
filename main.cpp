

#include <iostream>
using namespace std;

template<class DT>
class GLRow;
template<class DT>
ostream& operator <<(ostream& s, GLRow<DT>& oneGLRow);

template<class DT>
class ArrayGLL;
template<class DT>
ostream& operator <<(ostream& s, ArrayGLL<DT>& OneGLL);

//Start of GLROW class
/* In class GLRow it will contain the infromation on each element such that it acts like an row
  which countains info,next, and down. Also in this class we make a shallow copy and deep copy as well
    Delete info. We also print out the row when index is called.*/
template<class DT>
class GLRow{
    friend ostream& operator << <DT>(ostream& s, GLRow<DT>& oneGLRow);
protected:
    DT* _Info;
    int _Next;
    int _Down;
    
public:
    GLRow();
    GLRow(DT& newInfo);
    GLRow(GLRow<DT>& anotherOne);//copy construtor
    GLRow<DT> operator = (GLRow& anotherOne);// make a deep copy
    int getNext();//This will get the next node if in same row
    int getDown();//This will go down the tree
    DT& getInfo();
    void setNext(int n);
    void setDown(int d);
    void setInfo(DT& x);
  
    ~GLRow();//destructor
    
};
    template<class DT>
    GLRow<DT>::GLRow(){
        _Info = NULL;
        _Next = -1;// -1 becauce 0 points to a spot in the array
        _Down = -1;
    }
    template<class DT>
    GLRow<DT>::GLRow(DT& newInfo){
        _Info = new DT(newInfo);
        _Next = -1;
        _Down = -1;
    }
    template<class DT>
    GLRow<DT>::GLRow(GLRow<DT>& copyGLRow){
        _Info =  new DT (copyGLRow.getInfo());
        _Next = copyGLRow._Next;
        _Down = copyGLRow._Down;
    }
    template<class DT>
    GLRow<DT> GLRow<DT>::operator =(GLRow& anotherOne){
        _Info = new DT (anotherOne.getInfo());
        _Next = anotherOne._Next;
        _Down = anotherOne._Down;
        return (*this);
    }
    template<class DT>
    int GLRow<DT>::getNext(){
        return _Next;
    }
    template<class DT>
    int GLRow<DT>::getDown(){
        return _Down;
    }
    template<class DT>
    DT& GLRow<DT>::getInfo(){
        return *_Info;
    }
    template<class DT>
    void GLRow<DT>::setNext(int n){
        _Next = n;
    }
    template<class DT>
    void GLRow<DT>::setDown(int d){
        _Down = d;
    }
    template<class DT>
    void GLRow<DT>::setInfo(DT& x){
        _Info = new DT(x);
    }
    template <class DT>
    ostream& operator <<  (ostream& s,  GLRow<DT>& oneGLRow) {
        s<<"Down: " <<oneGLRow.getDown()<<endl;
        s<<"next: "<< oneGLRow.getNext()<<endl;
        s<<"info: " <<oneGLRow.getInfo()<<endl;
        return s;
    }
    template <class DT>
    GLRow<DT>::~GLRow() {
        if(_Info != NULL){
            delete _Info;
        }
   }

//end of GLROW class

// start of ArrayGLL
/*In class ArrayGLL we will perform operation on an array that are similar to a linked list
 each element in the array myGLL has an info, next, and down where next and down act as pointers
to the next Index.**/
template<class DT>
class ArrayGLL{//Array generalized linked list
  friend ostream& operator << <DT>(ostream& s, ArrayGLL<DT>& OneGLL);
protected:
    GLRow<DT>* myGLL;// array created also be the address of the arry
    int maxSize;// max size of array
    int firstElement;//first Node?
    int firstFree;//Frist Free Node?
    DT* keyValue;// I made this generic variable to take in the key value from main so I can print The methods in ostream
  
public:
    ArrayGLL();//default
    ArrayGLL(int size);//non-empty
    ArrayGLL (ArrayGLL<DT>& anotherOne);//copy construtor
    ArrayGLL<DT>& operator =(ArrayGLL<DT>& anotherOne);
    
    void display();// bonus we need to display in parenthesis format
    void displayHelper( int root);
    
    int find(DT& key);/* return  the index position where you find the element key; return false if not found, use recursive search**/
    int findIndex(DT& key, int root);
    
    void findDisplayPath(DT& Key);
    bool print(DT& key, int root);
    
    int noFree();
    
    int  size();
    int sizeHelper(int root);
    
    int parentPos(DT& Key);//bonus
    int findParentPositionIndex(DT& key, int root,int parentPos);
    
    GLRow<DT>&  operator [] (int pos);// This will return the value that is in
    //this postion
    int getFirstFree();
    void setFirstFree(int pos);
    
    int getFirstElement();
    void setFirstElement(int pos);
    
    DT& getKey();
    void setKey(DT& x);
    void insertAChild(DT& parent, DT& child);
    int insertHelper(DT& parent, DT& child, int root);
    
    void removeANode(DT& node);
    
    ~ArrayGLL();//destructor
};
    template<class DT>
    ArrayGLL<DT>::ArrayGLL(){//default constructor
        keyValue = NULL;
        myGLL = NULL;
        firstElement = 0;
        firstFree = 0;
    }
    template<class DT>
    ArrayGLL<DT>::ArrayGLL(int size){// non default
        keyValue = new DT();
        
        myGLL = new GLRow<DT> [size];
        maxSize = size;
        firstElement = 0;
       
        for(int i = 0; i < maxSize;++i){
            if(i == maxSize -1){
                myGLL[i].setNext(-1);
            }
            myGLL[i].setNext(i + 1);
            
        }
        firstFree = 0;
    }
    template<class DT>
    ArrayGLL<DT>::ArrayGLL (ArrayGLL<DT>& anotherOne){
        keyValue =  new DT ();
        maxSize = anotherOne.maxSize;
        myGLL = new GLRow<DT>[maxSize];
        for( int i = 0; i < maxSize; ++i){
              myGLL[i] = anotherOne.myGLL[i];
        }
        firstElement = anotherOne.firstElement;
        firstFree = anotherOne.firstFree;
    }

    template<class DT>
    ArrayGLL<DT>& ArrayGLL<DT>::operator =(ArrayGLL<DT>& anotherOne){
        keyValue =  new DT ();
        maxSize = anotherOne.maxSize;
        myGLL = new GLRow<DT>[maxSize];// Maybe over write this
        for( int i = 0; i < maxSize; ++i){
            myGLL[i] = anotherOne.myGLL[i];
        }
        firstElement = anotherOne.firstElement;
        firstFree = anotherOne.firstFree;
        return (*this);
    }

    template<class DT>
    void ArrayGLL<DT>::insertAChild(DT& parent, DT& child){
    
        int parentIndex = find(parent);
        
        if(parentIndex == -1){
            return;
        }
        int newFirstFree = firstFree;
        //myGLL[firstFree].setNext(-1);
        firstFree += 1;
               
        //myGLL[firstFree].setNext(child + 1);
        myGLL[newFirstFree].setInfo(child);
        int tempDown = myGLL[parentIndex].getDown();
        myGLL[parentIndex].setDown(newFirstFree);
        myGLL[newFirstFree].setNext(tempDown);
        myGLL[newFirstFree].setDown(-1);
  
        cout<<"insertion"<<endl;
    }

template<class DT>
void ArrayGLL<DT>::removeANode(DT& node){
    int index = find(node);
    if(index == -1){
        return ;
    }
    if(myGLL[index].getDown() == -1){
        int tempNext = myGLL[index].getNext();
    
        if(tempNext == -1){
            int invalid = 999;
            myGLL[index].setInfo(invalid);
            myGLL[index].setNext(-1);
            myGLL[index].setDown(-1);
            
        }
    }
    
    int replaceIndex = index;
    while(myGLL[index].getDown() != -1){
        index = myGLL[index].getDown();
    }
    myGLL[replaceIndex] = myGLL[index];
    
    int invalid = 999;
    myGLL[index].setInfo(invalid);
    myGLL[index].setNext(-1);
    myGLL[index].setDown(-1);
    
    cout<< "Element removed"<<endl;
    return;
    
    
}



template<class DT>
void ArrayGLL<DT>::display(){
    
   
    displayHelper(firstElement);
   
}


    template<class DT>
    void ArrayGLL<DT>::displayHelper( int root){
        //first two if's check for an exit
        if(root == -1){
                return ;
        }
        if(myGLL[root].getInfo() == -1){
            return ;
        }
        
        cout<< myGLL[root].getInfo();
        if((myGLL[root].getDown() != -1) && (myGLL[root].getNext() != -1)){
            int tempDown = myGLL[root].getDown();
            int tempNext =  myGLL[root].getNext();
            cout<<" (";
            displayHelper(tempDown);
            cout<< ") ";
            displayHelper(tempNext);
            
        }
        else if (myGLL[root].getDown() != -1){
            root = myGLL[root].getDown();
            cout<< " (";
            displayHelper(root);
            cout<< ")";
        }
        else if(myGLL[root].getNext() != -1){
            root = myGLL[root].getNext();
            cout<<" ";
            displayHelper(root);
        }
        return;
    }


/*In the find method I return a call to its helper called finIndex. We are trying to return the node
Where the key is located at. In findIndex we make two test cases either root == -1 or the info at that root is the key
Both would be exit cases for the recurison. After the two if statments we enter an else where we keep track of the recurison by storeing
it into an int . As exits cases fail and it eventually back track to test the other part of the tree. */
    template<class DT>
    int ArrayGLL<DT>::find(DT& key){
        return findIndex(key,firstElement);
    }
    template<class DT>
    int ArrayGLL<DT>::findIndex(DT& key, int root){
   
        if(root == -1){
                   return -1;
               }
               if(myGLL[root].getInfo() == key){
                       return root;
               }
               else{
                   int tempNext = findIndex(key, myGLL[root].getNext());
                   int tempDown = findIndex(key, myGLL[root].getDown());
                   if( tempNext != -1){
                       return tempNext;
                   }
                   if(tempDown != -1){
                       return tempDown;
                   }
                   else {
                       return -1;
                   }
               }

        
    }


/*For Find display path I also have a helper method . My helperMethod is named print. This method is similar to
  findIndex except I need to print the path. By doing this the main thing is to print when it goes down the most straight path.
  So we have our exit cases and instread of ints we use bools . The bool for down will print if true since it makes sense that you
 wouldnt want to print everything in next. */
    template<class DT>
    void ArrayGLL<DT>::findDisplayPath(DT& key){
       /*We will travel through the tree and print values we encounter
        if value is print all values**/
        cout<<"This is the path from the key "<< endl;
        print(key, firstElement);
    }

    template<class DT>
    bool ArrayGLL<DT>::print(DT& key, int root){
        
        if(root == -1){
              return false;
        }
     if(myGLL[root].getInfo() == key){
          return true;
     }
    else{
            bool tempNext = print(key, myGLL[root].getNext());
            bool tempDown = print(key, myGLL[root].getDown());
        if(tempNext){
             return true;
        }
        if(tempDown){
                cout<<"Node: "<<root<<" "<<"Info: "<<myGLL[root].getInfo()<<", ";
                cout<<endl;
                return true;
        }
        else {
            return false;
        }
        }
        
    }
    
/*noFree will find the number of empty nodes in the tree by going following the getnext*/
    template<class DT>
    int ArrayGLL<DT>:: noFree(){
        /*return number of free locations need to use the _Next or Next(my nameing)
         and get the free locations*
         The free location should relate to 999*/
        int counter = 1;
        int index = myGLL[firstFree].getNext();
       while(index != -1){
            ++counter ;
            index = myGLL[index].getNext();
        }
       return counter;
    }

/*In size method we use a helper and in the helper we have an exit case for root == -1*/
    template<class DT>
    int ArrayGLL<DT>::size(){
       
       return sizeHelper(getFirstElement());
       
    }
    template<class DT>
    int ArrayGLL<DT>::sizeHelper(int root){
        if(root == -1){
              return 0;
        }
       return 1 + sizeHelper( myGLL[root].getNext()) + sizeHelper(myGLL[root].getDown());
    }
/*In parent pos I made a helper to and passed in 3 variables. key, root, and parent. parent will be pushed when it recurisve next*/
    template<class DT>
    int ArrayGLL<DT>::parentPos(DT& key){
        int index = firstElement;
        return findParentPositionIndex(key,index, -1);
    }

    template<class DT>
    int ArrayGLL<DT>::findParentPositionIndex(DT& key, int root, int parent){
    if(root == -1){
        return -1;
    }
  
    if (myGLL[root].getInfo() == key) {
          return parent;
    }
    else{
            int tempNext = findParentPositionIndex(key, myGLL[root].getNext(), parent);
            int tempDown = findParentPositionIndex(key, myGLL[root].getDown(), root);
         
           if( tempNext != -1){
               return tempNext;
            }
           if(tempDown != -1){
              
               return tempDown;
            }
            else {
                return -1;
            }
    }
}

    template<class DT>
    GLRow<DT>& ArrayGLL<DT>:: operator[](int pos){
       
        return myGLL[pos];
    }

    template<class DT>
    int ArrayGLL<DT>::getFirstFree(){
        return firstFree;
    }
    template<class DT>
    int ArrayGLL<DT>::getFirstElement(){
        return firstElement;
    }
    template<class DT>
    void ArrayGLL<DT>::setFirstFree(int pos){
        firstFree = pos;
    }
    template<class DT>
    void ArrayGLL<DT>::setFirstElement(int pos){
        firstElement = pos;
    }
 
    template<class DT>
    DT& ArrayGLL<DT>::getKey(){
        return *keyValue;
    }
    template<class DT>
    void ArrayGLL<DT>::setKey(DT& x){
        keyValue = new DT(x);
    }

    template <class DT>
    ostream& operator <<  (ostream& s, ArrayGLL<DT>& OneGLL) {
        DT temp = OneGLL.getKey();
        s<<"These are the non-empty Nodes and where they can point to"<<endl;
        for(int i = 0; i < 8; ++i){
            s<<"Node: "<< i<<endl;
            s<< OneGLL[i]<<endl;
        }
       
             return s;
    }

    template <class DT>
    ArrayGLL<DT>::~ArrayGLL() {
        if(myGLL != NULL){
            delete[] myGLL;
        }
    }
//end of arrayGLL

int main() {
    
    cout<<"Hello"<<endl;
    ArrayGLL<int>* firstGLL;
    int noElements, count;
    char command;
    int value, pos;
    cin>> noElements;
   firstGLL = new ArrayGLL<int>(noElements);
    
    while(cin>>command){
       // cin>>command;
        switch(command){
            case 'I':{
                cin>> pos>>value;
                ++count;
                if(pos == -1){
                    (*firstGLL)[0].setInfo(value);
                    (*firstGLL)[0].setNext(-1);
                    firstGLL->setFirstElement(0);
                    firstGLL->setFirstFree(1);
                    (*firstGLL)[firstGLL->getFirstFree()].setNext(2);
                    
                }
                else{
                    firstGLL->insertAChild(pos, value);
                }
                //(*firstGLL).insert(pos,value);
                break;
            }
                
            case 'D':{
              //  cout<<(*firstGLL)<<endl;
                (*firstGLL).display();
                break;
            }
                
            case 'F':{
                cin >> value;
                cout<<"find"<<endl;
                int valueFound;
               valueFound = (*firstGLL).find(value);
                for(int i = 0; i < count; ++i){
                    if((*firstGLL)[i].getInfo() == (*firstGLL)[valueFound].getInfo()){
                        cout<<"The element "<<(*firstGLL)[i].getInfo()<< " is found at index: "<< i<<endl;
                        break;
                    }
                }
                    break;
            }
            case 'P':{
                cin>> value;
                int parent = (*firstGLL).parentPos(value);
                cout<<"The parent of "<<value<< " is: "<< (*firstGLL)[parent].getInfo()<<endl;
                
                    break;
            }
            case 'R':{
                cin >>  value;
                firstGLL->removeANode(value);
                break;
            }
    
            default: cout<<"Invalid command"<<endl;
            break;
        }
    }
   

    delete firstGLL;

    return 0;
}

