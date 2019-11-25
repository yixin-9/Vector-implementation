// Description : Implementing a Vector class in namespace CS52 that has similar behavior to std::vector.

#include <iostream>
#include <exception>
#include <vector>

namespace CS52 {
    class Vector {
       
        public :
        // Constructors
        Vector(); // default constructor
        Vector(int s, int iVal); // overloaded constructor
        Vector(const Vector &b); // copy constructor
        
        // Destructor
        ~Vector();
       
        // Get or set element at location i in Vector .
        int& at(int i) const throw (std::out_of_range);
       
        // Returns a reference to the last element in the Vector
        int& back() const throw (std::out_of_range);
       
        // Returns the allocated storage for the Vector .
        int capacity() const;
        
        // Erases the elements of the Vector but does not change capacity .
        void clear();
       
        // Returns pointer to the first element in the Vector .
        int* data() const;
       
        // If Vector is empty return true , else false .
        bool empty() const;
       
        // Returns a reference to the first element in a vector .
        int& front() const throw (std::out_of_range);
       
        // Deletes the element at the end of the vector .
        void pop_back();
       
        // Add an element to the end of the vector .
        void push_back(int element);
       
        // Returns the number of elements in the vector .
        int size() const;
       
        // Implementing an integer by selection sort
        void sort();
        
        // Overloaded operators
        int& operator[] (int i); // [] array syntax
        Vector & operator =(const Vector &b); // copy assignment
        
        // Overloaded stream insertion operator
        friend std::ostream & operator <<(std::ostream &stream, Vector& iVector);
        
        private :
        // helper to copy Vector to new Vector
        void copy_data();
        
        int iSize = 0;
        int iCapacity = 0;
        int * iData = nullptr;
  
    };
}

void swap(int *x, int *y);


int main (){
    // default constructor
    CS52::Vector v;
    v.push_back(10); v.push_back(88);
    // print out the contents of v
    std::cout << "v = " << v << "\n";
    // overloaded constructor
    CS52::Vector v1(2,5);
    std::cout<< "v1 = " << v1 << "\n";
   /// copy constructor
    CS52::Vector v2(v1);
    std::cout<< "v2 = " << v2 << "\n";
    v1.push_back(10); v1.push_back(2);
    v1.push_back(99); v1.push_back(-5);
    // assign values to vector v1
    v1[0]=25; v1[1]=1;
    // access the 11th element which is out-of-bounds
    try {
        std::cout<< v1.at(10) << " " << v1.at(1) << "\n\n";
    }
    catch (std::exception e){
        std::cout<< e.what() << "\n";
    }
    // sort vector v1 and print
    v1.sort();
    std::cout<< "v1.sort()= " << v1;
    
    return 0;
}

CS52::Vector::Vector(){ //default constructor, initialize the iSize, iCapacity and iData
    iSize=0;
    iCapacity=0;
    iData=nullptr;
}

CS52::Vector::Vector(int s,int iVal){  //overloaded constructor, allocate memory and initialize iData
    
    if (s==0) { //if s equal 0, do nothing
        ;
    }
    else{
    iData=new int[s]; //else allocate new memory
    for (int i=0; i<s; i++) {
        iData[i]=iVal;  //initialize iData
        iCapacity++;   //increase iCapacity
        }
    }
    iSize=s;
}

CS52::Vector::Vector(const Vector &b){  //copy constructor, duplicate b to new vector
    iSize=b.iSize;
    iData= new int[iSize];  //allocate memory
    for (int i=0; i<iSize; i++) {
        iData[i]=b.iData[i];  //assign b to iData
    }
}

CS52::Vector::~Vector(){  //destructor, delete iData if iData does not equal to Null
    if (iData!=nullptr) {
        delete [] iData;
        iData=nullptr;
    }
}

int& CS52::Vector::at(int i) const throw (std::out_of_range) {  // Set element at location i in Vector
    if (i>=iSize) {  //if i greater or equal to iSize, print out-of-bounds and throw
        std::cout<<"out-of-bounds ";
        throw std::out_of_range("at");
    }
    else
    return iData[i];  //else return the vector
}

int& CS52::Vector::back()const throw(std::out_of_range){
    try{
        return iData[iSize-1];  //return the last element of the vector
    }
    catch(std::exception e){
        throw e;
    }
}

int CS52::Vector::capacity() const{
    return iCapacity;  //return capacity
}

void CS52::Vector::clear(){
    iSize=0; //clear the Vector, size equals to 0
}

int* CS52::Vector::data() const{
    return iData;  //return pointer to the first element in the vector .
}

bool CS52::Vector::empty() const{
    if (iSize==0) {  //if vector is empty return true
        return 1;
    }
    else
        return 0;
}

int& CS52::Vector::front()const throw(std::out_of_range){
    try{
        return iData[0];  //return the first element of the vector
    }
    catch(std::exception e){
        throw e;
    }
}

void CS52::Vector::pop_back(){
    iSize=iSize-1; //remove the last element
}

void CS52::Vector::push_back(int element){
    if (iSize+1>iCapacity) { //if the iSize+1 is greater than the iCapacity
        if (iCapacity==0) {  //if iCapacity=0, assign iCapacity to 1
            iCapacity=1;
        }
        iCapacity=iCapacity*2;
        int* tmp= new int[iCapacity];  //allocate memory
        for (int i=0; i<iSize; i++) { //assign iData to temporary memory
            tmp[i]=iData[i];
        }
        delete [] iData;  //delete memory
        iData=tmp;  //assign back to iData
    }
    iData[iSize]= element;  //add element to the end of the vector
    iSize++;  //iSize increase 1
}

int CS52::Vector::size() const{
    return iSize;  //return the size of the vector
}

void CS52::Vector::sort(){ //selection sort
    for (int i=0; i<iSize-1; i++) {
        int minIndex= i;
        for (int j=i+1; j<iSize; j++) {
            if (iData[j]<iData[minIndex]) {  //if iData[j] is greater than the previous iData
                minIndex=j;  //assign j to minIndex
            }
        }
        swap(&iData[minIndex], &iData[i]);  //swap to arrange the vector in ascending order
    }
}

void swap(int *x, int *y)
{
    int temp = *x;
    *x = *y;
    *y = temp;
}


int& CS52::Vector::operator[](int i){  //overloaded operator // array syntax
    return iData[i];
}

CS52::Vector & CS52::Vector::operator=(const CS52::Vector &b){  //copy assignment
    if (this == &b)
    {
        return *this;
    }
    delete[] this->iData;  //delete memory
    iSize= b.iSize;
    this->iData = new int[iCapacity];  //allocate new memory
    for(int i=0; i<iCapacity; i++)
    {
        this->iData[i] = b.iData[i];
    }
    return *this;
}

//friend operator, overloaded stream insertion operator
std::ostream & CS52::operator<<(std::ostream& stream, CS52::Vector& iVector){
    for (int i = 0; i<iVector.size(); i++)
    {
        stream << iVector.at(i)<<" ";
    }
    return stream;
}

void CS52::Vector::Vector::copy_data(){
    int *a=iData;  //store the original data in pointer a
    iData= new int[iCapacity*2];  //allocate memory
    
    for (int i=0; i<iCapacity; i++) {  //initialize the new memory with pointer a
        iData[i]=a[i];
    }
    iCapacity=iCapacity*2;  //capacity become twice larger
    delete [] a;  //delete a
}
