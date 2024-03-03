/* 
 * File:   matrix.cpp
 * Author: MP-team 
 * @warning To be implemented by students. Follow the instructions given in the headers
 */


#include "Matrix.h"
#include <fstream>
#include <assert.h>

double v_npos = Matrix::npos;
const double c_npos = Matrix::npos;

using namespace std;


/** 
 * @brief this method reserve memory to allocate a 2D matrix of size r x c.
 * @param r number of rows
 * @param c number of cols
 * @return the pointer to the memory block containing the data
 */
double ** allocate(size_t r, size_t c) {
    
    double ** block;
    
    block = new double*[r];
    for(int i = 0; i < r; i++)   block[i] = new double[c];
    // allocate memory into block
    return block;
}

/**
 * @brief Copies the values in a 2D matrix org with nrows and ncols to an also 2D matrix dest.
 * It is assumed that org and dest have the memory properly allocated 
 * @param dest destination matrix
 * @param org  source matrix
 * @param nrows number of rows
 * @param ncols number of cols
 */
void copy(double **dest, double **org, size_t nrows, size_t ncols) {
    
//    if (dest != nullptr){
//        
//        for (int i = 0; i < nrows; i++)  delete [] dest[i];
//        
//        delete [] dest;
//        dest = nullptr;
//    }
    
//    dest = allocate(nrows, ncols);
    
    for (int i = 0; i < nrows; i++)
        
        for (int j = 0; j < ncols; j++)
            
            dest[i][j] = org[i][j];
}

/**
 * @brief In this method, given an index idx it returns the key in the position i, 
 * such that i is the first position in the index such that idx.at(i).getPos()==p
 * @param idx the input index
 * @param p number of 
 * @return the key for first position i in the index such that idx.at(i).getPos()==p
 */
string labelWithValuePosInIndex(const Index & idx, size_t p) {
    string salida;

    bool enc = false;
    for (int i = 0; i < idx.size() && !enc; i++) {
        if (idx.at(i).getPos() == p) {
            salida = idx.at(i).getKey();
            enc = true;
        }
    }
    return salida;
}

void Matrix::deallocate() {
    
    if (_data != nullptr){
        
        for (int i = 0; i < _nrows; i++){

            delete [] _data[i];
            _data[i] = nullptr;
        }
       
        delete [] _data;
        _data = nullptr;
    }
    _nrows = _ncols = 0;
    _rowLabels.~Index();
    _colLabels.~Index();    
}


Matrix::Matrix() {
   
    _data = nullptr;
    _nrows = _ncols = 0;
}

void Matrix::setValues(double value) {
     
    for (int i = 0; i < _nrows; i++)
        
        for (int j = 0; j < _ncols; j++)
            
            _data[i][j] = value;
}



Matrix::Matrix(size_t f, size_t c, double vdef) {
    
//    _nrows = f;
//    _ncols = c;
//    
//    _data = new double*[_nrows];
//    for (int i = 0; i < _nrows; i++)   _data[i] = new double[_ncols];
//    
//    for (int i = 0; i < _nrows; i++) 
//        
//        for (int j = 0; j < _ncols; j++)  
//            
//            _data[i][j] = vdef;
//    
    
    resize(f,c,vdef);  
}

Matrix::Matrix(const Matrix& orig):_nrows(0), _ncols(0), _data(nullptr) {
    
//    deallocate();
    _nrows = orig.rows();
    _ncols = orig.columns();
    
//    _data = new double*[_nrows];
//    for (int i = 0; i < _nrows; i++)   _data[i] = new double[_ncols];
//    
//    for (int i = 0; i < _nrows; i++) 
//        
//        for (int j = 0; j < _ncols; j++)  
//            
//            _data[i][j] = orig.at(i,j);
    
    _data = allocate(_nrows, _ncols);
    
    copy(_data, orig._data, _nrows, _ncols);
    
    _rowLabels = (orig._rowLabels);
    _colLabels = (orig._colLabels);
}

Matrix::Matrix(const std::string *rowsLabels, size_t nrows, const std::string * colsLabels, size_t ncols, double value) {
     
//    _nrows = nrows;
//    _ncols = ncols;
//    
//    _data = new double*[_nrows]; 
//    for (int i = 0; i < _nrows; i++)   _data[i] = new double[_ncols];
//    
//    setValues(value);
//    setLabels(_rowLabels, rowsLabels, _nrows);
//    setLabels(_colLabels, colsLabels, _ncols);
    
    resize(rowsLabels, nrows, colsLabels, ncols, value);
}



std::string Matrix::labelAtRow(size_t row) const {
    
    return labelWithValuePosInIndex(_rowLabels, row);
}

std::string Matrix::labelAtCol(size_t col) const {
    
    return labelWithValuePosInIndex(_colLabels, col);
}

void Matrix::resize(size_t nrows, size_t ncols, double value) {
    
    _nrows = nrows;
    _ncols = ncols;
    _data = allocate(nrows, ncols);
    setValues(value);
}

void Matrix::resize(const std::string * rowLabels, size_t nrows, const std::string * colLabels, size_t ncols, double value) {
    
    resize(nrows, ncols, value);
    
    for (int i = 0; i < nrows; i++){
        Pair pair (rowLabels[i],i);
        _rowLabels.add(pair);
    }
    
    for (int i = 0; i < ncols; i++){
        Pair pair (colLabels[i],i);
        _colLabels.add(pair);
    } 
    
    
//    _rowLabels(rowLabels);
//    _colLabels(colLabels);
  
}

void Matrix::clear() {
   
    _nrows = _ncols = 0;
    _data = nullptr;
}

Matrix::~Matrix() {
 
    deallocate();
}

double & Matrix::at(size_t f, size_t c) {
    
    if (f >= 0 && f < _nrows && c >= 0 && c < _ncols) return _data[f][c];
    else return v_npos;
}

const double & Matrix::at(size_t f, size_t c) const {
    
    if (f >= 0 && f < _nrows && c >= 0 && c < _ncols) return _data[f][c];
    else return c_npos;
}

double & Matrix::operator()(size_t f, size_t c) {

    return at(f,c);
}

const double & Matrix::operator()(size_t f, size_t c) const {

    return at(f,c);
}

int Matrix::rowIndexOf(const std::string & label) const {
    
    bool found = false;
    int i = 0;
    
    while (!found && (i < _nrows)){
        
        found = label == _rowLabels.at(i).getKey();
        i++;
    }
    
    int returning = 0;
    if (found) returning = i-1;
    else       returning = -1;
    
    return returning;
}

int Matrix::colIndexOf(const std::string & label) const {
   
    bool found = false;
    int i = 0;
    
    while (!found && (i < _ncols)){
        
        found = label == _colLabels.at(i).getKey();
        i++;
    }
    
    int returning = 0;
    if (found) returning = i-1;
    else       returning = -1;
    
    return returning;
}

double & Matrix::at(const std::string & rowLabel, const std::string & colLabel) {
//
//    bool found_row = false;
//    int i = 0;
//    
//    while (!found_row && (i < _nrows)){
//        
//        found_row = rowLabel == _rowLabels.at(i).getKey();
//        i++;
//    }
//    
//    i--;
//    
//    bool found_col = false;
//    int j = 0;
//    
//    while (!found_col && (j < _ncols)){
//        
//        found_col = colLabel == _colLabels.at(j).getKey();
//        j++;
//    }
//    
//    j--;
//    if (!found_row && !found_row)   return _data[i][j];
//    else                            return -1;
    
    return at(rowIndexOf(rowLabel), colIndexOf(colLabel));
}

double & Matrix::operator()(const std::string & rowLabel, const std::string & colLabel) {
 
    return at(rowLabel, colLabel);
}

const double & Matrix::at(const std::string & rowLabel, const std::string & colLabel)const {

//    bool found_row = false;
//    int i = 0;
//    
//    while (!found_row && (i < _nrows)){
//        
//        found_row = rowLabel == _rowLabels.at(i).getKey();
//        i++;
//    }
//    
//    i--;
//    
//    bool found_col = false;
//    int j = 0;
//    
//    while (!found_col && (j < _ncols)){
//        
//        found_col = colLabel == _colLabels.at(j).getKey();
//        j++;
//    }
//    
//    j--;
//    if (!found_row && !found_row)   return _data[i][j];
//    else                            return -1;
 
    assert (rowIndexOf(rowLabel) < 0 && colIndexOf(colLabel) < 0);
    return at(rowIndexOf(rowLabel), colIndexOf(colLabel));
}

const double & Matrix::operator()(const std::string & rowLabel, const std::string & colLabel)const {
  
    return at(rowLabel, colLabel);
}

ostream & operator<<(ostream & flujo, const Matrix& m) {
   
//    string *colLabels;
//    colLabels = new string [m.getColLabels(colLabels)];
//    
//    flujo << setw(15) << " ";
//    
//    for (int i = 0; i < m.columns(); i++)   flujo << setw(15) << colLabels[i];
//    
//    string *rowLabels;
//    rowLabels = new string [m.getRowLabels(rowLabels)];    
//    
//    for (int i = 0; i < m.rows(); i++){
//        
//        flujo << endl << setw(15) << rowLabels[i];
//        
//        for (int j = 0; j < m.columns(); j++)    
//                
//            flujo << setw(15) << m(i,j);
//    } 
//      
//    flujo << endl;
    
    flujo << m.rows() << " " << m.columns() << endl << "[";
    
    for (int i = 0; i < m.rows(); i++)
        
        flujo << m.labelAtRow(i) << " ";
        
    flujo << "]" << endl << "[";
    
    for (int i = 0; i < m.columns(); i++)
        
        flujo << m.labelAtCol(i) << " ";
        
    flujo << "]" << endl;
    
    for (int i = 0; i < m.rows(); i++){
        
        for (int j = 0; j < m.columns(); j++)
            
            flujo << m(i,j) << " ";
        
        flujo << endl;
    }
    
    return (flujo);
}

Matrix & Matrix::operator=(const Matrix& m) {
    
    if (this != &m){
        
        deallocate();
        
        if (m.columns() != 0 && m.rows() != 0){
            
            _nrows = m.rows();
            _ncols = m.columns();

    //        _data = new double*[_nrows];
    //        for (int i = 0; i < _nrows; i++)   _data[i] = new double[_ncols];      
    //        for (int i = 0; i < _nrows; i++) 
    //
    //            for (int j = 0; j < _ncols; j++)  
    //
    //                _data[i][j] = m.at(i,j);
            _data = allocate(_nrows, _ncols);
            copy(_data, m._data, _nrows, _ncols);

            _rowLabels = m._rowLabels;
            _colLabels = m._colLabels;
        }
    }
    
    return *this;
}

bool Matrix::setLabels(Index & idx, const string * labels, int nlabels){
    
    idx.clear();
    int lb,ub;
    bool correct = true;
    for (int i=0; i< nlabels && correct; i++){
        lb = idx.lower_bound(labels[i]);
        ub = idx.upper_bound(labels[i]);
        if (lb==ub) { // it is NOT in the set
            idx.add(Pair(labels[i],i));
        } else {
            correct = false;
         }
    }
    if (!correct) idx.clear();
    
    return correct;
 }

int Matrix::getLabels(const Index & idx, string * labels) const {
    
    if (idx.size() > 0) {
        for (int i = 0; i < idx.size(); i++) {
            labels[i] = idx.at(i).getKey();
        }
    }
    return idx.size();
}

int Matrix::getRowLabels(string * labels) const {
    return getLabels(_rowLabels,labels);
}

int Matrix::getColLabels(string *labels) const {
    return getLabels(_colLabels,labels);
}

size_t Matrix::columns() const {
    return _ncols;
}

size_t Matrix::rows() const {
    return _nrows;
}

//uncomment
void Matrix::save(const string & nf) const{
    ofstream fsal(nf);
    if (fsal.is_open()) {
        fsal << "#matrix "; 
        if (_rowLabels.size()==0)
            fsal << "unlabeled"<< endl;
        else fsal << "labeled" << endl;
        fsal << *this;
        fsal.close();
    } else cerr << "Fail creating " << nf << " file" <<endl;
}

void Matrix::load(const string & nf) {
    ifstream fent(nf);
    string labeled, cad;
    clear();
    if (fent.is_open()) {
         fent >> cad >> labeled;
         fent >> _nrows >> _ncols;
         if (labeled == "labeled"){
            for (int i=0;i<_nrows;i++){
                fent >> cad;
                _rowLabels.add(Pair(cad,i));
            }
             for (int i=0;i<_ncols;i++){
                fent >> cad;
                _colLabels.add(Pair(cad,i));
            }
        }
        _data = allocate(_nrows,_ncols); 
        for (int i = 0; i < _nrows; i++) {
            for (int j = 0; j < _ncols; j++) {
                fent >> _data[i][j];
            }
        }
        fent.close();
    } else cerr << "Fail reading " << nf << " file" <<endl;
}

Matrix & Matrix::operator*=(double val) {
   
    for (int i = 0; i < _nrows; i++)
        
        for (int j = 0; j < _ncols; j++)
            
            _data[i][j] *= val;
    
    return *this;    
}

Matrix & Matrix::operator+=(double val) {
   
    for (int i = 0; i < _nrows; i++)
        
        for (int j = 0; j < _ncols; j++)
            
            _data[i][j] += val;
    
    return *this;
}

Matrix Matrix::operator*(const Matrix & m) const {
   
    Matrix result(_nrows, m.columns(), v_npos);
    
    if (_ncols == m.rows()){
        
        result.setValues(0);

        for (int i = 0; i < _nrows; i++)

            for (int j = 0; j < m.columns(); j++)

                for (int k = 0; k < result.columns(); k++)

                    result.at(i,j) += at(i,k) * m.at(k,j);  
    }
    
    result._rowLabels = m._rowLabels;
    result._colLabels = _colLabels;
    
    return result;          
}

Matrix Matrix::operator+(double val) const {
    
    Matrix result(_nrows, _ncols);
    
    for (int i = 0; i < result.rows(); i++)
        
        for (int j = 0; j < result.columns(); j++)
            
            result.at(i,j) = at(i,j) + val;
    
    result._rowLabels = _rowLabels;
    result._colLabels = _colLabels;
    
    return result;
}

Matrix Matrix::operator*(double val) const {
    
    Matrix result(_nrows, _ncols);
    
    for (int i = 0; i < result.rows(); i++)
        
        for (int j = 0; j < result.columns(); j++)
            
            result.at(i,j) = at(i,j) * val;
    
    result._rowLabels = _rowLabels;
    result._colLabels = _colLabels; 
    
    return result;
}

Matrix operator+(double ival, const Matrix & dch) {
    
    for (int i = 0; i < dch.rows(); i++)
        
        for (int j = 0; j < dch.columns(); j++)
            
            dch._data[i][j] = dch(i,j) + ival;
    
    return dch;
}

Matrix operator*(double ival, const Matrix & dch) {

    for (int i = 0; i < dch.rows(); i++)
        
        for (int j = 0; j < dch.columns(); j++)
            
            dch._data[i][j] = dch(i,j) * ival;
    
    return dch;
}

Matrix & Matrix::normalize(){

    double *suma;
    suma = new double [_nrows];
    
    for (int i = 0; i < _nrows; i++) suma[i] = 0;   
    
    for (int i = 0; i < _nrows; i++)
        
        for (int j = 0; j < _ncols; j++)
            
            suma[i] += at(i,j);
    
    for (int i = 0; i < _nrows; i++)
        
        for (int j = 0; j < _ncols; j++){
            
            if (suma[i] == 0)   _data[i][j] = 1.0/_nrows;
            else _data[i][j] = at(i,j)/suma[i];
        } 
    
    delete [] suma;
    suma = nullptr;
    
    return *this;
}
