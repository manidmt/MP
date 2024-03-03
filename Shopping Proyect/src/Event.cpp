/**
 * @file Event.cpp
 * @author DECSAI
 * @note To be implemented by students 
 * 
 */

#include <string>
#include <fstream>
#include "Event.h"
using namespace std;

Event::Event() {
    
    initDefault();
}

void Event::initDefault() {
    
    set(EVENT_DEFAULT);
}

Event::Event( const std::string &line) {
    
    set(line);
}

DateTime Event::getDateTime() const {
    
    return _dateTime;
}

string Event::getType() const {
    
    return _type;
}

string Event::getProductID() const {
    
    return _prod_id;
}

string Event::getCategoryID() const {
    
    return _cat_id;
}

string Event::getCategoryCode() const {
    
    return _cat_cod;
}

string Event::getBrand() const {
    
    return _brand;
}

double Event::getPrice() const {
    
    return _price;
}

string Event::getUserID() const {
    
    return _user_id;
}

string Event::getSession() const {
    
    return _session;
}

string Event::getField(const string &field) const{
    
    string returning;
    
    if (field == "DateTime")
        
        returning = _dateTime.to_string();
    
    else if(field == "Type")
        
        returning = _type;
    
    else if(field == "ProductID")
        
        returning = _prod_id;
        
    else if(field == "CategoryID")
        
        returning = _cat_id;
    
    else if(field == "CategoryCode")
        
        returning = _cat_cod;
    
    else if(field == "Brand")
        
        returning = _brand;
     
    else if(field == "Price")
        
        returning = std::to_string(_price);
    
    else if(field == "UserID")
        
        returning = _user_id;
    
    else if(field == "Session")
        
        returning = _session;

    return returning;
    
//    switch (field){
//            
//            case "DateTime":
//                
//                return _dateTime.to_string();
//                break;
//            
//            case "Type":
//                
//                return _type;
//                break;
//            
//            case "ProductID":
//                
//                return _prod_id;
//                break;
//            
//            case "CategoryID":
//                
//                return _cat_id;
//                break;
//            
//            case "CategoryCode":
//                
//                return _cat_cod;
//                break;
//            
//            case "Brand":
//                
//                return _brand;
//                break;
//            
//            case "Price":
//                
//                return std::to_string(_price);
//                break;
//               
//            case "UserID":
//                
//                return _user_id;
//                break;
//                
//            case "Session":
//                
//                return _session;
//                break;               
//    }                     
}

void Event::setDateTime( const string  &time) {
    
    _dateTime.set(time);
}

void Event::setType( const std::string  &type) {
    
    const int NUM_TYPES = 4;
    bool tipo_correcto = false;
    
    for (int i = 0; i < NUM_TYPES; i++)
        
        if (type == VALID_TYPES[i]) tipo_correcto = true;
    
    if (!tipo_correcto)  _type = VALID_TYPES[0];
    else                 _type = type;
}

void Event::setProductID( const std::string  &prod_id) {
    if (prod_id == "")   _prod_id = EMPTY_FIELD;
    else                 _prod_id = prod_id;
 }

void Event::setCategoryID( const std::string  &cat_id) {
    
    _cat_id = cat_id;
}

void Event::setCategoryCode( const std::string  &cat_cod) {
    
    _cat_cod = cat_cod;
}

void Event::setBrand( const std::string  &brand) {
    
    _brand  = brand;
}

void Event::setPrice (double price) {
    if(0 <= price)  _price = price;
    else            _price = -1.000000;
}

void Event::setUserID (const std::string &user_id) {
    if(user_id == "") _user_id = EMPTY_FIELD;
    else              _user_id = user_id;
}

void Event::setSession (const std::string &session) {
    if(session == "") _session = EMPTY_FIELD;
    else              _session = session;
}

void Event::set( const std::string &line) {
       
    const int N_PARAMETROS = 9;
    const char COMA = ',';
    string arrayParam[N_PARAMETROS];
    int j=0;
    
    for (int i = 0; i < line.length(); i++){
        if (line[i] == COMA)
            j++;
        
        else 
            arrayParam[j].push_back(line[i]);
    }
    
    
    int i = 0;

    setDateTime (arrayParam[i]);
    i++;
    
    setType (arrayParam[i]);
    i++;

    setProductID (arrayParam[i]);
    i++;
    
    setCategoryID (arrayParam[i]);
    i++;
    
    setCategoryCode (arrayParam[i]);
    i++;
    
    setBrand (arrayParam[i]);
    i++;
  
    setPrice (stod(arrayParam[i]));      
    i++;
    
    setUserID (arrayParam[i]);
    i++;
    
    setSession (arrayParam[i]);
}

bool Event::isEmpty() const{

    bool isEmpty = false;
       
    //Comprobamos que los parámetros que no pueden ser nulos no lo son:
    
    if (_prod_id == EMPTY_FIELD) isEmpty = true;
    if (_user_id == EMPTY_FIELD) isEmpty = true;
    if (_session == EMPTY_FIELD) isEmpty = true;
    
    //Comprobamos que el precio no sea negativo:
    
    if (_price < 0) isEmpty = true;
    
    return isEmpty; 
}

string Event::to_string() const {
    string salida;
    salida += _dateTime.to_string();
    salida += "," + _type;
    salida += "," + _prod_id;
    salida += "," + _cat_id;
    salida += "," + _cat_cod;
    salida += "," + _brand;
    salida += "," + std::to_string(_price);
    salida += "," + _user_id;
    salida += "," + _session;
    return salida;
}

void Event::write(ostream &os) const {
    
    os << to_string();
}
void Event::read(istream &is) {
    
    string line;
    getline(is, line);
    if (is) set(line);
}