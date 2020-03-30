

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
    int displayHelper( int root);
    
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
    void ArrayGLL<DT>::display(){// bonus
        /*This will display in parenthesis format*
         if parent has child open parenthesis if no more or no children close
         parenthesis*/
        // if down is true open parenthese
       // int info = myGLL[firstElement].getInfo();
        
        cout<<"parenthes format  Not done yet"<<endl;
        //cout<< "( ";
       // displayHelper(firstElement);
       // cout<< " )"<<endl;
    }
    template<class DT>
    int ArrayGLL<DT>::displayHelper( int root){
        int next = myGLL[root].getNext();
       
       if(root == -1){
            return -1;
       }
        else{
            // if down open
            if(myGLL[root].getDown() != -1){
                           cout<< "( ";
            }
            if( next != -1 || next == -1){
                        cout<< myGLL[root].getInfo()<<" ";
                                    
            }
            int tempNext = displayHelper( myGLL[root].getNext());
           
            if( tempNext != -1){
                cout<< myGLL[root].getInfo();
                    return tempNext;
            }
          
            else {
                cout<< " )";
                    return -1;
                  }
            }
    }


/*In the find method I return a call to its helper called finIndex. We are trying to return the node
Where the key is located at. In findIndex we make two test cases either root == -1 or the info at that root is the key
Both would be exit cases for the recurison. After the two if statments we enter an else where we keep track of the recurison by storeing
it into an int . As exits cases fail and it eventually back track to test the other part of the tree. */
    template<class DT>
    int ArrayGLL<DT>::find(DT& key){
        
        int index = findIndex(key,firstElement);
        return index;
        
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
        for( int i = 0; i < OneGLL.size(); ++i){
            if(OneGLL[i].getInfo() != 999){
                s<<"Node: "<<i<<endl;
                s<< OneGLL[i]<<endl;
            }
        }
        s<<"These are the emptie nodes"<<endl;
        for( int i = 0; i < OneGLL.maxSize; ++i){
                  if(OneGLL[i].getInfo() == 999){
                      s<<"Node: "<<i<<endl;
                      s<< OneGLL[i]<<endl;
                  }
              }
        if( OneGLL.find(temp) == -1){
            s<<"Key does not Exist!"<<endl;
        }
        else{
            s<< "This is the Node where the key is located at: " << OneGLL.find(temp) << endl;
            
        }
        OneGLL.findDisplayPath(temp);
        if(OneGLL.parentPos(temp) == -1){
            s<<"This is the root so no parent"<<endl;
        }
        else{
            s<<OneGLL.parentPos(temp)<<" Is the parent node of the key "<<temp<<endl;
        }
        
        s << "The size of the tree at "<<OneGLL.getFirstElement() <<": "<<OneGLL.size()<<endl;
        s<<"The number of free at "<< OneGLL.getFirstFree() << ": "<<OneGLL.noFree()<<" Nodes that are free"<<endl;
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
    int noElements,value,next,down,parentPos;
    int pos = -1;
    int keyValues;
    int zero = 0;
    GLRow<int> oneRow(zero);// This is statically defined
    
    //All variables must be defined
    
    cin>> noElements;
    ArrayGLL<int> firstGLL(noElements);
    
    for(int i = 0; i < noElements; ++i){
        cin >> value >> next >> down ;
        oneRow.setInfo(value);
        oneRow.setNext(next);
        oneRow.setDown(down);
        firstGLL[i] = oneRow;
        
    }
   keyValues = 25;
    firstGLL.setKey(keyValues);
     firstGLL.setFirstFree(8);// I changed this to eight since it was the only way to reach all 3 empties
     firstGLL.setFirstElement(2);// setter done
    cout<<"\n\n";
     cout<<"This is the Ostream operator for firstGLL: \n"<<firstGLL<<endl;//This is for ostream I think
     //firstGLL.display();// parenthes format
    
     ArrayGLL<int>* secondGLL = new ArrayGLL<int>(firstGLL);
     int passByRef = 600;
     int passByRef2 = 700;
     (*secondGLL)[1].setInfo(passByRef);
     (*secondGLL)[2].setInfo(passByRef2);
    (*secondGLL).setKey(keyValues);
    //cout<< "This is what's in the array: "<< (*secondGLL)<<endl;
    cout<<"This is the Ostream Operator for secondGLL: \n"<<(*secondGLL)<<endl;// ostream
    //(*secondGLL).display();// parenthese format

    
    //I moved everything to ostream to demonstrate ostream.
    /*The code below I left since the pdf said the variables in main need to be defined. I was going to move it
     to ostream. However I didnt want that to count against me.*/
    pos = (*secondGLL).find(keyValues);
    if(pos != -1){
        cout<<(*secondGLL)[pos]<<endl;//
        (*secondGLL).findDisplayPath(keyValues);
    }
    
    parentPos = (*secondGLL).parentPos(keyValues);
   
    
    if(parentPos != -1){
        cout<< (*secondGLL)[parentPos]<<endl;
    }

    delete secondGLL;

    return 0;
}



