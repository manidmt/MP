
#include "Matrix.h"

// MANUEL DÍAZ-MECO TERRÉS

TEST_F(_03_Advanced, Matrix_getRowLabels){
    
    int f = 5, c = 5;
    
    string rowLabels [] = {"A","B","C","D","E"};
    string colLabels[]  = {"F","G","H","I","J"};
    
    Matrix m(rowLabels, f, colLabels, c);
    
    for(int row = 0; row < f; row++)
        
        SQUIP_ASSERT_EQ_R(row, m.getRowLabels(rowLabels[row])) << "n must be equal to getRowLabels(rowLabels[n])" << endl;
}

