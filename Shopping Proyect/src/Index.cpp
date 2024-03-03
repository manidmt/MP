/* 
 * File:   Index.cpp
 * @author MP-Team DECSAI
 * @warning To be implemented by students 
 */
#include <string>
#include <iostream>
#include <fstream>
#include "Index.h"

using namespace std;

void Index::copy(const Index &orig){

    deallocate();
    
    _capacity = orig._capacity;
    _nEntries = orig.size();
    _onBrand  = orig.getIOnWhich();
   
    _entries = new Pair [_capacity];
    
    for (int i = 0; i < size(); i++)
        
        _entries[i] = orig._entries[i];
}

void Index::copy(Pair *dest){
    
    dest = _entries;
}

void Index::reallocate(int size){
    
    if (_capacity < size){
        
        while (_capacity < size)    _capacity = _capacity*2 + 1;

        Pair *aux;
        aux = new Pair [_capacity];

        for (int i = 0; i < _nEntries; i++)

            aux[i] = _entries[i];
        
        int capacity = _capacity;
        int nentries = _nEntries;
        
        deallocate();
        
        _entries = aux;
        _capacity = capacity;
        _nEntries = nentries;
        
        aux = nullptr;
    }
    
}

void Index::deallocate(){
    
    if (_entries != nullptr){
        
        _nEntries = 0;
        _capacity = 0;
        delete [] _entries;
        _entries = nullptr;  
    }
}

Index::Index(const Index & orig){
        
    _nEntries = 0;
    _capacity = 0;
    _entries = nullptr;
    copy(orig);
}

Index & Index::operator=(const Index &one){
    
    if (this != &one)
        
        copy(one);
    
    return *this;
}
    
Index::~Index(){
    
    deallocate();
}


Index::Index(int onBrand) {
    
    _nEntries = 0;
    _capacity = 0;
    _entries = nullptr;
    setIOnWhich(onBrand);
}

void Index::setIOnWhich(int val) {
    
    _onBrand = val;
}

int Index::size() const {
    
    return _nEntries;
}

void Index::clear() {
    
    _nEntries = 0;
}

int Index::getIOnWhich() const {
    
    return _onBrand;
}

int Index::add(const Pair & pair) {
    
    if (!pair.isEmpty()) {
        
        int up_bound = upper_bound(pair.getKey());
        
        reallocate(size()+1);
        
        for (int i = size(); i > up_bound; i--) 
            
            _entries [i] = _entries [i-1];
        
        _entries[up_bound] = pair;
        
        _nEntries++;
        
        return 1;    
    }

    else return 0;
}

void Index::build(const EventSet & evSet, int onBrand) {
  
    clear();
    setIOnWhich(onBrand);
    
    string field;
    
    if (onBrand == 2)       field = "Session";
    else if (onBrand == 1)  field == "UserID";
    else                    field == "Brand";
    
    for (int i=0; i < evSet.size(); i++) {
        
        Pair pair (evSet.at(i).getField(field), i);
        
        if (pair.getKey() != "")       add (pair);
    }   
}

int Index::lower_bound(const string & key) const {
    
    int output = _nEntries;
    
    bool not_found = true;

    for (int i = 0; i < _nEntries && not_found; i++)

        if (key <= _entries[i].getKey()) {
            
            not_found = false;
            output = i;
        }

    return output;    
}

int Index::upper_bound(const string & key) const {
    
    
    int output = _nEntries;
    
    bool not_found = true;
    
    for (int i=0; i < _nEntries && not_found; i++) 
        
        if(_entries[i].getKey() > key) {
            
            not_found = false;
            output = i;
        }  
    
    return (output);
}

const Pair & Index::at(int pos) const {
    
    return _entries[pos];
}

Pair & Index::at(int pos) {
    
    return _entries[pos];
}

void Index::print()const {
    
    for (int i=0; i<size(); i++)
        
        cout << at(i).to_string();
}

Event getEvent(const EventSet & evSet, const Index & indx, int pos) {
    
    return evSet.at(indx.at(pos).getPos());
}

void write(ofstream &os, const EventSet & evSet, const Index & indx) {
    
    for (int i=0; i<indx.size(); i++) 
        
        evSet.at(indx.at(i).getPos()).write(os);
}

Index rawFilterIndex(const EventSet & evSet, const Index & indx, const std::string &field, const std::string &value) {
    
    Index result (indx.getIOnWhich());
    
    if (field == "DateTime") {
        
        for (int i=0; i<indx.size(); i++) 
            
            if (evSet.at(indx.at(i).getPos()).getDateTime().sameDay(value))
                
                result.add(indx.at(i));
    } 
    
    else {
        
        for (int i=0; i<indx.size(); i++) {
            
            if (evSet.at(indx.at(i).getPos()).getField(field) == value)
                
                result.add(indx.at(i));
        }
    }
    
    return result;
}

float sumPrice(const EventSet & evSet, const Index & indx) {
    
    float result = 0;
    EventSet e;
    
    for (int i=0; i<indx.size(); i++)
        
        e.add(evSet.at(indx.at(i).getPos()));
    
    result = sumPrice (e);
    
    return result;
}