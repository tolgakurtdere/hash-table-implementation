#ifndef __HASHTABLE__
#define __HASHTABLE__

#include "HashUtils.h"

// Do not modify the public interface of this class.
// Otherwise, your code will note compile!
template <class T>
class HashTable {
    struct Entry {
        std::string Key;             // the key of the entry
        T Value;   // the value of the entry
        bool Deleted;        // flag indicating whether this entry is deleted
        bool Active;         // flag indicating whether this item is currently used

        Entry() : Key(), Value(), Deleted(false), Active(false) {}
    };

    struct Bucket {
        Entry entries[3];
    };

    int _capacity; // INDICATES THE SIZE OF THE TABLE
    int _size; // INDICATES THE NUMBER OF ITEMS IN THE TABLE

    Bucket* _table; // HASH TABLE
    int s; //total successful number

    // You can define private methods and variables

public:
    // TODO: IMPLEMENT THESE FUNCTIONS.
    // CONSTRUCTORS, ASSIGNMENT OPERATOR, AND THE DESTRUCTOR
    HashTable();
    HashTable(const HashTable<T>& rhs);
    HashTable<T>& operator=(const HashTable<T>& rhs);
    ~HashTable();

    // TODO: IMPLEMENT THIS FUNCTION.
    // INSERT THE ENTRY IN THE HASH TABLE WITH THE GIVEN KEY & VALUE
    // IF THE GIVEN KEY ALREADY EXISTS, THE NEW VALUE OVERWRITES
    // THE ALREADY EXISTING ONE.
    // IF LOAD FACTOR OF THE TABLE IS BIGGER THAN 0.5,
    // RESIZE THE TABLE WITH THE NEXT PRIME NUMBER.
    void Insert(std::string key, const T& value);

    // TODO: IMPLEMENT THIS FUNCTION.
    // DELETE THE ENTRY WITH THE GIVEN KEY FROM THE TABLE
    // IF THE GIVEN KEY DOES NOT EXIST IN THE TABLE, JUST RETURN FROM THE FUNCTION
    // HINT: YOU SHOULD UPDATE ACTIVE & DELETED FIELDS OF THE DELETED ENTRY.
    void Delete(std::string key);

    // TODO: IMPLEMENT THIS FUNCTION.
    // IT SHOULD RETURN THE VALUE THAT CORRESPONDS TO THE GIVEN KEY.
    // IF THE KEY DOES NOT EXIST, THIS FUNCTION MUST RETURN T()
    T Get(std::string key) const;

    // TODO: IMPLEMENT THIS FUNCTION.
    // AFTER THIS FUNCTION IS EXECUTED THE TABLE CAPACITY MUST BE
    // EQUAL TO newCapacity AND ALL THE EXISTING ITEMS MUST BE REHASHED
    // ACCORDING TO THIS NEW CAPACITY.
    // WHEN CHANGING THE SIZE, YOU MUST REHASH ALL OF THE ENTRIES FROM 0TH ENTRY TO LAST ENTRY
    void Resize(int newCapacity);

    // TODO: IMPLEMENT THIS FUNCTION.
    // RETURNS THE AVERAGE NUMBER OF PROBES FOR SUCCESSFUL SEARCH
    double getAvgSuccessfulProbe();

    // TODO: IMPLEMENT THIS FUNCTION.
    // RETURNS THE AVERAGE NUMBER OF PROBES FOR UNSUCCESSFUL SEARCH
    double getAvgUnsuccessfulProbe();

    // THE IMPLEMENTATION OF THESE FUNCTIONS ARE GIVEN TO YOU
    // DO NOT MODIFY!
    int Capacity() const;
    int Size() const;
};



template <class T>
HashTable<T>::HashTable() {
    _size = 0;
    _capacity = 0;
    _table = NULL;
    s=0;
// TODO: CONSTRUCTOR

}

template <class T>
HashTable<T>::HashTable(const HashTable<T>& rhs) {
    _table=NULL;
    _table = new Bucket[rhs.Capacity()];
    for(int i=0;i<rhs.Capacity();i++){
        for(int j=0;j<3;j++){
            _table[i].entries[j] = rhs._table[i].entries[j];
        }
    }
    _size=rhs.Size();
    _capacity=rhs.Capacity();
    s=rhs.s;
// TODO: COPY CONSTRUCTOR

}

template <class T>
HashTable<T>& HashTable<T>::operator=(const HashTable<T>& rhs) {
    if(_table){
        delete[] _table;
    }
    _table=NULL;
    _table = new Bucket[rhs.Capacity()];
    for(int i=0;i<rhs.Capacity();i++){
        for(int j=0;j<3;j++){
            _table[i].entries[j] = rhs._table[i].entries[j];
        }
    }
    _size=rhs.Size();
    _capacity=rhs.Capacity();
    s=rhs.s;

    return *this;
// TODO: OPERATOR=

}

template <class T>
HashTable<T>::~HashTable() {
// TODO: DESTRUCTOR
    delete [] _table;
    _capacity=0;
    _size=0;
    s=0;
}

template <class T>
void HashTable<T>::Insert(std::string key, const T& value) {
    if(_table==NULL){
        _capacity=NextCapacity(_capacity);
        _table = new Bucket[_capacity];
    }
    if((float)_size/(3*_capacity) > 0.5){
        Resize(NextCapacity(_capacity));
        //std::cout<<"resizing..   "<< _capacity<<std::endl;
    }

    int adres = Hash(key) % _capacity;
    int artis = 1;
    bool done = false;

    while(!done){
        for(int i=0;i<3;i++){
            if(key == _table[adres].entries[i].Key){
                done=true;
                break;
            }
            if(_table[adres].entries[i].Active == false){
                _table[adres].entries[i].Value = value;
                _table[adres].entries[i].Active = true;
                _table[adres].entries[i].Key = key;
                _size++;
                done = true;
                break;
            }
        }
        adres = (Hash(key) % _capacity + artis*artis) % _capacity;
        artis++;
        s++;
    }


    //_table[Hash(key)%_capacity].entries[0].Value = value;
    //std::cout<<"inserting"<<std::endl;


    /*_table[300].entries[1].Key="asdsg";
    std::cout<< _table[300].entries[1].Key <<std::endl;*/

// TODO: IMPLEMENT THIS FUNCTION.
// INSERT THE ENTRY IN THE HASH TABLE WITH THE GIVEN KEY & VALUE
// IF THE GIVEN KEY ALREADY EXISTS, THE NEW VALUE OVERWRITES
// THE ALREADY EXISTING ONE. IF LOAD FACTOR OF THE TABLE IS BIGGER THAN 0.5,
// RESIZE THE TABLE WITH THE NEXT PRIME NUMBER.

}

template <class T>
void HashTable<T>::Delete(std::string key) {
    for(int i=0;i<_capacity;i++){
        for(int j=0;j<3;j++){
            if(_table[i].entries[j].Key == key){
                _table[i].entries[j] = Entry();
                _table[i].entries[j].Active=false;
                _table[i].entries[j].Deleted=true;
                _size--;
                break;
            }
        }
    }
    return;

// TODO: IMPLEMENT THIS FUNCTION.
// DELETE THE ENTRY WITH THE GIVEN KEY FROM THE TABLE
// IF THE GIVEN KEY DOES NOT EXIST IN THE TABLE, JUST RETURN FROM THE FUNCTION
// HINT: YOU SHOULD UPDATE ACTIVE & DELETED FIELDS OF THE DELETED ENTRY.

}

template <class T>
T HashTable<T>::Get(std::string key) const {
    for(int i=0;i<_capacity;i++){
        for(int j=0;j<3;j++){
            if(_table[i].entries[j].Key == key){
                return _table[i].entries[j].Value;
            }
        }
    }
    return T();
// TODO: IMPLEMENT THIS FUNCTION. IT SHOULD RETURN THE VALUE THAT
// IT SHOULD RETURN THE VALUE THAT CORRESPONDS TO THE GIVEN KEY.
// IF THE KEY DOES NOT EXIST, THIS FUNCTION MUST RETURN T()

}

template <class T>
void HashTable<T>::Resize(int newCapacity) {
    //Bucket *temp = new Bucket[NextCapacity(_capacity)];
    s=1;

    T *temp = new T[_size];
    int index=0;
    //std::cout<<"resizuuuying.."<<std::endl;

    for(int i=0;i<3;i++){
        for(int j=0;j<_capacity;j++){
            if(_table[j].entries[i].Active == true){
                temp[index] = _table[j].entries[i].Value;
                index++;
            }
        }
    }

    delete[] _table;
    _table = new Bucket[newCapacity];
    _size = 0;
    _capacity = newCapacity;

    for(int i=0;i<index;i++){
        Insert(temp[i].getIsbn(),temp[i]);
    }

    delete[] temp;
    temp=NULL;

// TODO: IMPLEMENT THIS FUNCTION. AFTER THIS FUNCTION IS EXECUTED
// THE TABLE CAPACITY MUST BE EQUAL TO newCapacity AND ALL THE
// EXISTING ITEMS MUST BE REHASHED ACCORDING TO THIS NEW CAPACITY.
// WHEN CHANGING THE SIZE, YOU MUST REHASH ALL OF THE ENTRIES FROM 0TH ENTRY TO LAST ENTRY

}


template <class T>
double HashTable<T>::getAvgSuccessfulProbe() {
    return (double)s/_size;
// TODO: IMPLEMENT THIS FUNCTION.
// RETURNS THE AVERAGE NUMBER OF PROBES FOR SUCCESSFUL SEARCH

}

template <class T>
double HashTable<T>::getAvgUnsuccessfulProbe() {
    int us = 0;
    int adres = 0;
    int artis = 1;
    bool done = false;

    for(int i=0;i<_capacity;i++){
        adres = i;
        artis = 1;
        done = false;
        while(!done){
            if(_table[adres].entries[0].Active == true){
                if(_table[adres].entries[1].Active == true){
                    if(_table[adres].entries[2].Active == true){
                        adres = (i + artis*artis) % _capacity;
                        artis++;
                        us++;
                        continue;
                    }
                }
            }
            done = true;
            us++;
        }
    }

    return (double)us/_capacity;

// TODO: IMPLEMENT THIS FUNCTION.
// RETURNS THE AVERAGE NUMBER OF PROBES FOR UNSUCCESSFUL SEARCH

}

template <class T>
int HashTable<T>::Capacity() const {
    return _capacity;
}

template <class T>
int HashTable<T>::Size() const {
    return _size;
}

#endif
