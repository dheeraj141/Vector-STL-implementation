//
//  main.cpp
//  ImplementingVector
//
//  Created by Dheeraj Kumar Ramchandani on 10/11/19.
//  Copyright © 2019 Dheeraj Kumar Ramchandani. All rights reserved.
//

#include <iostream>
using namespace std;
template <typename T>
class vector1
{
    int sz;                                 // the size
    T *elem;                                // pointer to the elements
    int space;                              // reserved space used for push back
   
public:
    
    vector1() : sz{0}, elem{ nullptr}, space{0}{}
    
    //  make every single argument constructor as explicit because they are implicit by defualt and can cause a lot of issue
    
    explicit vector1(int x): sz{x}, elem{new T[x]}
    {
        space = sz;
        for(int i = 0; i<x; i++)
        elem[i] = 0.0;
    }
    
    //  constructor for the initializer list
    
    vector1 ( initializer_list<double> lst) : sz{static_cast<int>(lst.size())},elem{ new T[sz]}
    {
        copy(lst.begin(), lst.end(), elem);
    }
    
    // copy constructor use such as vector v1 = v2
    
    vector1 ( const vector1 &A): sz{A.sz}, elem{new T[A.sz]}
    {
        copy(A.elem, A.elem+sz, elem);
    }
    
    // copy assignment operator  for uses such as v1 = v2;
    
    vector1& operator= (const vector1 &a)
    {
        if ( this == &a) return *this;            // self assignment v=v no work needed
        if ( a.sz <=space )
        {
            for(int i = 0; i<a.sz; i++)
                elem[i] = a.elem[i];
            sz =  a.sz;
            return *this;
        }
        T *p = new T[a.sz];
        copy(a.elem, a.elem+ a.sz, p);
        delete [] elem;                             // deallocate old space
        elem = p;
        space  = sz = a.sz;
        return *this;                               // returns a reference to the object
        
        
    }
    
    // operator for accessing the elements using the  subscript operator []
    
    T& operator[](int n) { return elem[n];}
    const T& operator[](int n) const{ return elem[n];}
    
    int size() const { return sz;}
    
    // destructor
    
    ~vector1()
    { delete[]elem;}
    
    // now implementing the size changes of the vector
    
    void reserve( int newalloc)
    {
        // never decrease the space
        if( newalloc <= space )
            return ;
        
        T *p =  new double[ newalloc];
        // we are not initializing the elements in the reserved space
        copy( elem, elem+ sz, p);
        delete [] elem;
        elem = p;
        space =  newalloc;
    }
    
    // so for a vector v.capacity() - v.size() this many elements can be pushed back
    
    int capacity() const { return space;}
    
    // implementing the resize operation four cases are there
    // new size greater than space
    // new size greater than sz but less than space
    // new size equal to sz
    // new size less than sz all the cases are handled
    
    
    void resize (int newsize)
    {
        reserve( newsize);
        // initializing the new elements
        
        for( int i = sz; i<newsize; i++)
            elem[i] = 0.0;
        
        
    }
    // push back method
    
    void push_back( const T &d )
    {
        if ( space == 0)
            reserve(8);
        else if( space  == sz)
            reserve( 2*space);      // get more space
        elem[sz] = d;
        sz++;                       // add d at the end and increase sz
        
    }
    
};
template <typename T>
void display_vector( vector1<T> &a)
{
    int i, size;
    size = a.size();
   for(i=0; i<size; i++)
       cout<<a[i]<<" ";
    cout<<endl;
}
template <typename T>
void f( const vector1<T> &a, vector1<T> &b)
{
    b[1] = 2.0;
}
 


int main(int argc, const char * argv[]) {
    //vector1  v(1000);
    // constructor initializer list called
    vector1<int> v{1,2,3};
    
    // defualt constructor called
    vector1<int> v1(4);
    
    // copy constructor called
    vector1<int> v2 =  v1;
    // copy assignment called they are doing deep copy which means they are copying the values not the addresses. If the copy assignment or copy constructor is not implemented in you code they by default shallow copy will happen and then both v2 and v will point to the same objects and various disaster can occur such as deleting the memory twice.
    
    v2 = v;
    
    // here deault constructor is called which is made explicit but if you haven't made your constructor explicit  then
    vector1<int> v3(10);
    
    
    // here it will show error becuase the constructor is explicit but if that was not the case then it would have created a vector of 10 doubles initialized to 0.0. can uncomment to check
   // v1 = 10;
    
    display_vector(v);
    display_vector(v1);
    display_vector(v1);
    v[1] = 5;
    display_vector(v);
    f( v, v1);
    
    
    cout<<" size of the vector v is"<<sizeof(v)<<endl;
    return 0;
}
