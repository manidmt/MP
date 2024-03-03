/* 
 * File:   Pair.cpp
 * @author MP-Team DECSAI
 * @warning To be implemented by students
 */
#include <string>

#include "Pair.h"

using namespace std;

Pair NULL_PAIR;

Pair::Pair()  {
    initDefault();
}

bool Pair::isEmpty() const {
    
    return (_key == EMPTY_FIELD && _pos == -1);
}

Pair::Pair(const std::string & key, int pos) {
    
    set(key, pos);
}

const std::string & Pair::getKey() const {
    
    return _key;
}

const int Pair::getPos() const {
    
    return _pos;
}

void Pair::setKey(const std::string & key) {
    
    _key = key;
}

void Pair::setPos(int pos) {
    
    _pos = pos;
}

void Pair::set(const std::string & key, int pos) {
 
    setKey(key);
    setPos(pos);
}

std::string Pair::to_string() const { /** necessary ?*/
    string result;
    result = _key + " " + std::to_string(_pos);
    return result;
}

void Pair::initDefault() {

    _key = EMPTY_FIELD;
    _pos = -1;
}

bool equalKey(const Pair & left, const Pair & right) {
    
    return ((left.getKey() == right.getKey()) && (left.getPos() == right.getPos()));
}
