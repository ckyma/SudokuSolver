/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: yuchen
 *
 * Created on January 17, 2017, 5:18 PM
 */

#include <iostream>
#include <vector>

#define N 9
#define UNDEFINED 0

using namespace std;

class Sudoku {
private:
    int(*matrix)[9];
    
public:
    
    Sudoku(int matrix[][N]){
        this->matrix = new int[N][N];
        
        for(int i = 0; i < N; ++i){
            for(int j = 0; j < N; ++j){
                this->matrix[i][j] = matrix[i][j];
            }
        }
    }
    
    bool solve(){
        int row, col;
        
        if(!getPlaceLeft(row, col)){
            return true;
        }
        
        for(int num = 1; num <= N; ++num){
            if(isPlacable(row, col, num)){
                matrix[row][col] = num;
                if(solve()){
                    return true;
                }
                matrix[row][col] = UNDEFINED;
            }
        }
        
        return false;
    }
    
    bool getPlaceLeft(int& row, int& col){
        for(int i = 0; i < N; ++i){
            for(int j = 0; j < N; ++j){
                if(matrix[i][j] == UNDEFINED ){
                    row = i;
                    col = j;
                    return true;
                }
            }
        }
        return false;
    }
    
    bool isPlacable(int row, int col, int num){
        if( ! inRow(row, num) &&
                ! inCol(col, num) &&
                ! inUnit(row, col, num)){
            return true;
        }
        return false;
    }
    
    bool inRow( int row, int num ){
        for(int j = 0; j < N; ++j){
            if(matrix[row][j] == num){
                return true;
            }
        }
        return false;
    }
    
    bool inCol( int col, int num ){
        for(int i = 0; i < N; ++i){
            if(matrix[i][col] == num){
                return true;
            }
        }
        return false;
    }
    
    bool inUnit(int row, int col, int num){
        int rowInit = int(row/3) * 3;
        int colInit = int(col/3) * 3;
        
        for(int i = 0; i < 3; ++i){
            for(int j = 0; j < 3; ++j){
                if(matrix[rowInit + i][colInit + j] == num){
                    return true;
                }
            }
        }
        
        return false;
    }
    
    void print(){
        for(int i = 0; i < N; ++i){
            for(int j = 0; j < N; ++j){
                cout << matrix[i][j] << " ";
            }
            cout << endl;
        }
    }
    
    ~Sudoku(){
        if( matrix != nullptr ){
            delete [] matrix;
        }
    }
};

/*
 * 
 */
int main(int argc, char** argv) {

    // 0 means unassigned cells
    int grid[N][N] = {{3, 0, 6, 5, 0, 8, 4, 0, 0},
                      {5, 2, 0, 0, 0, 0, 0, 0, 0},
                      {0, 8, 7, 0, 0, 0, 0, 3, 1},
                      {0, 0, 3, 0, 1, 0, 0, 8, 0},
                      {9, 0, 0, 8, 6, 3, 0, 0, 5},
                      {0, 5, 0, 0, 9, 0, 6, 0, 0},
                      {1, 3, 0, 0, 0, 0, 2, 5, 0},
                      {0, 0, 0, 0, 0, 0, 0, 7, 4},
                      {0, 0, 5, 2, 0, 6, 3, 0, 0}};
    
    Sudoku sudo(grid);
    
    if(sudo.solve()){
        sudo.print();
    } else {
        cout << "There is no solution.";
    }
    
    cout << endl;
    
    // Generate a simple Sudoku root
    auto gridRoot = new int[N][N]();
    Sudoku sudoRoot(gridRoot);
    if(sudoRoot.solve()){
        sudoRoot.print();
    }
    delete [] gridRoot;
    
    cout << endl;
    
    // Using Vector of Vector to store
    vector<vector<int>> gridVector(N, vector<int>(N, 0));
    for(int i = 0; i < N; ++i){
        for(int j = 0; j < N; ++j){
            cout << gridVector[i][j] << " ";
        }
        cout << endl;
    }
    
    cout << endl;
    
    vector<vector<int>>* gridVectorPtr = new vector<vector<int>>(N, vector<int>(N, 0));
    for(int i = 0; i < N; ++i){
        for(int j = 0; j < N; ++j){
            cout << (*gridVectorPtr)[i][j] << " ";
        }
        cout << endl;
    }
    delete gridVectorPtr;
    
    return 0;
}

