/* 
 * File:   EventSet.cpp
 * @author MP-Team DECSAI
 * @note To be implemented by students 
 */


#include <unordered_map>
#include <fstream>
#include "EventSet.h"

using namespace std;


/**
 * @brief Give string[] and a string, it searches for string within string[]
 * @param array     The set of strings to llok for
 * @param n_array   The size of string[]
 * @param name      The string that is being seeked
 * @return          The position of the first occurrence of string within string[]
 *  -1 if the string does not belong to string[]
 */
int findString(const string array[], int n_array, const string & name){
    
    bool found = false; 
    int i = 0;
    
    
    while (!found && i < n_array){
        
        found = array[i] == name;
        i++;
    }
    
    if (!found) i = 0;
    
    return (i-1);
}

void EventSet::reallocate(unsigned size){
    
    if (_capacity < size){
        
        while (_capacity < size)    _capacity = _capacity*2 + 1;

        Event *aux = new Event [_capacity];

        for (int i = 0; i < _nEvents; i++)

            aux[i] = _events[i];
        
        int capacity = _capacity;
        int nevents = _nEvents;
        
        deallocate();
        
        _events = aux;
        _capacity = capacity;
        _nEvents = nevents;
        
        aux = nullptr;
    }
}

void EventSet::deallocate(){
    
    if (_events != nullptr){
        
        _nEvents = 0;
        _capacity = 0;
        delete [] _events;
        _events = nullptr;  
    }
}

void EventSet::copy(Event *dest) const{
    
    dest = _events;
}

void EventSet::copy(const EventSet &orig){
    
    deallocate();
    
    _capacity = orig._capacity;
    _nEvents  = orig.size();
   
    _events = new Event [_capacity];
    
    for (int i = 0; i < size(); i++)
        
        _events[i] = orig._events[i];
    
}

EventSet::EventSet(const EventSet & orig){
    
     _nEvents = 0;
    _capacity = 0;
    _events = nullptr;
    copy(orig);
}

EventSet & EventSet::operator=(const EventSet & one){
    
    if (this != &one)
        
        copy(one);
    
    return *this;
}

EventSet::~EventSet(){
    
    deallocate();
}

std::string EventSet::to_string() const {
    string result;
    result = std::to_string(_nEvents) + " ";
    for (int i = 0; i < _nEvents; i++)
        result += _events[i].to_string() + "\n";
    return result;
}

EventSet::EventSet() {
    
    _nEvents = 0;
    _capacity = 0;
    _events = nullptr;
}

int EventSet::size() const {

    return _nEvents;
}


void EventSet::clear() {
    
    _nEvents = 0;
}

int EventSet::add(const Event & e) {
    
    reallocate(size()+1);
    _events[size()] = e;
    _nEvents++;
    
    return true;
}

int EventSet::add(const std::string& line) {
  
    reallocate(size()+1);
    _events[size()].set(line);
    _nEvents++;
    
    return true;
}

const Event & EventSet::at(int pos) const {
    
    if ((pos >= 0) && (pos < size())){
        
        return(_events[pos]);
    }
    
    else    return NULL_EVENT;
}


EventSet rawFilterEvents(const EventSet& es, const std::string &field, const std::string &value) {
    
    EventSet output;
    if (field == "DateTime") {
        DateTime aux (value);
        for (int i=0; i<es.size(); i++) 
            if (es.at(i).getDateTime().sameDay(aux))
                output.add(es.at(i));
    } else {
        for (int i=0; i<es.size(); i++) 
            if (es.at(i).getField(field) == value)
                output.add(es.at(i));
    }
      
    return (output);
}

void findUnique(const EventSet& es, const std::string &field, std::string values[], int & n_values) {
    
    n_values = 0;
    
    if (field == "DateTime") {
        
        for (int i=0; i < es.size(); i++) {
            
            Event e_aux;
            
            int year    = es.at(i).getDateTime().year();
            int month   = es.at(i).getDateTime().month();
            int day     = es.at(i).getDateTime().day();
            
            char local[64];
            sprintf(local, "%04i-%02i-%02i %02i:%02i:%02i UTC", year, month, day, 0, 0, 0);
            e_aux.setDateTime(local); 
            
            bool not_found = (findString(values, n_values, e_aux.getDateTime().to_string()) == -1);
        
            if (not_found) {
                
                values[n_values] = e_aux.getDateTime().to_string();
                n_values++;
            }
        }
        
    } else {
    
        for (int i = 0; i < es.size(); i++){

            bool not_found = (findString(values, n_values, es.at(i).getField(field)) == -1);

            if (not_found) {
                
                values[n_values] = es.at(i).getField(field);
                n_values++;
            }
        }
    }
}

float sumPrice(const EventSet & evSet) {
    
    float total = 0;
    float price;
    
    for (int i = 0; i < evSet.size(); i++) {
        
        price = evSet.at(i).getPrice();
        
        if (price > 0) total += price;
    }
    
    return total;
}

Event NULL_EVENT=Event();


void EventSet::write(ofstream &os) const { 
    
    std::string aux = to_string();
    
    int i=0; 
    while (aux[i] != ' ')  i++;
        
    std::string output = aux.substr(i+1, aux.length());
    
    os << output;
}	

 bool EventSet::read(std::ifstream &is, int nelements) {
     
    // Clear the EventSet
    clear();
     
    Event e;
    bool noerror = true;
    
    // Add all the events from the file
    
    for (int i = 0; i < nelements && noerror; i++) {
        
        e.read(is);  
        
        if (is)     add(e);           
        else        noerror = false;            
    }
 
    return noerror;
 }