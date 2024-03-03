/**
 * @file DateTime.cpp
 * @author DECSAI
 * @note To be implemented by students 
 * 
 */

#include <iostream>
#include <sstream>
#include <string>
#include "DateTime.h"
using namespace std;

/**
 * @brief auxiliary function to check if the date and the time are in correct 
 * format, taking into account, leap year etc.
 * @param year input
 * @param month input
 * @param day input
 * @param hour input
 * @param min input
 * @param sec input
 * @return true if is correct, false if not
 */
bool isCorrect(int year, int month, int day, int hour, int min, int sec);
/**
 * @brief split the first field in 6 components of the data time.
 * Please consider using string::substr(int, int)[https://en.cppreference.com/w/cpp/string/basic_string/substr] to cut the line
 * into the appropriate substrings and then convert it into integer values with 
 * the function stoi(string) [https://en.cppreference.com/w/cpp/string/basic_string/stol]
 * ~~~~
 *      YYYY-MM-dd hh:mm:ss UTC 
 *      +----+----+----+----+----+ 
 *      |    |    |    |    |    |
 *      0    5    10   15   20   25
 * ~~~~
 *  * @param line input string
 * @param y output int
 * @param m output int
 * @param d output int
 * @param h output int
 * @param mn output int
 * @param s output int
 */
void split( const std::string &line, int &y, int  &m, int  &d, int  &h, int &mn, int &s);

DateTime::DateTime() {
    
    initDefault();
}

void DateTime::initDefault() {
    
    set(DATETIME_DEFAULT);
}

bool isCorrect(int year, int month, int day, int hour, int min, int sec) {
    
    bool anio_correcto, mes_correcto, dia_correcto, hora_correcta, min_correcto;
    bool sec_correcto, anio_bisiesto, mes_31_dias, es_febrero;
    bool todo_correcto;
    
    //Año:
    anio_correcto = (year >= 1971) && (year <= 2100);
    anio_bisiesto = anio_correcto && ((year%4 == 0 && year%100 != 0) || (year%400 == 0));
    
    //Mes:
    mes_correcto = (month > 0) && (month <= 12);
    mes_31_dias = (month == 1) || (month == 3) || (month == 5) || (month == 7) ||
                  (month == 8) || (month == 10) || (month == 12);
    es_febrero = (month == 2);
    
    //Dia:
    if(mes_correcto){
        if (mes_31_dias) dia_correcto = (day > 0) && (day <= 31);
        else if(es_febrero){

            if (anio_bisiesto)  dia_correcto = (day > 0) && (day <= 29);
            else                dia_correcto = (day > 0) && (day <= 28);
        }
        else               dia_correcto = (day > 0) && (day <= 30);
    }

    
    //Hora:
    hora_correcta = (hour >= 0) && (hour <= 23);
    
    //Minutos:
    min_correcto = (min >= 0) && (min <= 59);
    
    //Segundos:
    sec_correcto = (sec >= 0) && (sec <= 59);
    
    //Comprobación:
    todo_correcto = anio_correcto && mes_correcto && dia_correcto &&
            hora_correcta && min_correcto && sec_correcto;
    
    return todo_correcto;
}

void split( const std::string &line, int &y, int  &m, int  &d, int  &h, int &mn, int &s) {
    
    if (line.length() >= 19){
    y  = stoi(line.substr(0,4));
    m  = stoi(line.substr(5,2));
    d  = stoi(line.substr(8,2));
    h  = stoi(line.substr(11,2));
    mn = stoi(line.substr(14,2));
    s  = stoi(line.substr(17,2));  
    }
    else split (DATETIME_DEFAULT, y, m, d, h, mn, s);
}

void DateTime::set( const std::string  &line) {
    
    int y, m, d, h, mn, s;
    split (line, y, m, d, h, mn, s);
    
    if(!(isCorrect(y, m, d, h, mn, s)))
        
        split(DATETIME_DEFAULT, y, m, d ,h , mn, s);
    
    _year = y;
    _month = m;
    _day = d;
    _hour = h;
    _min = mn;
    _sec = s;        
}

DateTime::DateTime( const string  &line) {
    
   set(line); 
}

int DateTime::year() const  {
    
    return _year;
}

int DateTime::month() const {
    
    return _month;
}

int DateTime::day() const {
    
    return _day;
}

int DateTime::hour() const {
    
    return _hour;
}

int DateTime::min() const {
    
    return _min;
}

int DateTime::sec() const {
    
    return _sec;
}

bool DateTime::isBefore( const DateTime  &one) const {
    
    bool anterior = false;
    bool igual_anio = one.year() == _year;
    
    if (!igual_anio) anterior = one.year() > _year;
    
    else{
        
        bool igual_mes = one.month() == _month;
        
        if (!igual_mes) anterior = one.month() > _month;
        
        else{
            
            bool igual_dia = one.day() == _day;
            
            if (!igual_dia) anterior = one.day() > _day;
            
            else{
                
                bool igual_hora = one.hour() == _hour;
                
                if (!igual_hora) anterior  = one.hour() > _hour;
                
                else{
                    
                    bool igual_min = one.min() == _min;
                    
                    if (!igual_min) anterior = one.min() > _min;
                    
                    else{
                        
                        bool igual_sec = one.sec() == _sec;
                        
                        if (!igual_sec) anterior = one.sec() > _sec;
                    }
                }
            }
        }
    }
    
    return anterior;
}

int DateTime::weekDay() const {
    
    // Zeller's congruence
    
    int a = (14-_month)/12;
    int y = _year - a;
    int m = _month + 12*a - 2;

    int day = (_day + y + int (y/4) - int (y/100) + int (y/400) + int(31*m)/12) % 7;
    
    return (day);   
}

string DateTime::to_string() const {
    char local[64];
    sprintf(local, "%04i-%02i-%02i %02i:%02i:%02i UTC", _year, _month, _day, _hour, _min, _sec);
    return local;
}


bool DateTime::sameDay(const DateTime &other) const {

    return ((_year == other.year()) && (_day == other.day()) && (_month == other.month()));
}
