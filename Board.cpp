#include "Board.hpp"
#include <iostream>
#include <stdexcept>
#include <vector>
using namespace std;

namespace ariel
{
    //Gets a position (row and column), direction (horizontal or vertical)
    //, and a string that represents an ad, and pastes the string on the board
    //in the appropriate place.
    void Board::post(uint row, uint column, Direction direction, string message){
        uint lengthMsg = message.length();

        //The string is horizontal
        if(direction == Direction::Horizontal){
            //Init the matrix at the first time
            if(matrix.empty()){
                indexMinCol = column;
                indexMaxCol = column + lengthMsg - 1;
                indexMaxRow = indexMinRow = row;
                matrix.resize(indexMaxRow-indexMinRow+1,vector<char>(indexMaxCol-indexMinCol+1,'_'));
            }
            //Adds rows to the matrix downwards
            if(row > indexMaxRow){
                indexMaxRow = row;
                matrix.resize(indexMaxRow-indexMinRow+1,vector<char>(matrix[0].size(),'_'));
            }
            //Adds columns to the right of the matrix.
            if(column + lengthMsg - 1 > indexMaxCol){
                // matrix.resize(indexMaxRow-indexMinRow+1,vector<char>(0,'_'));
                for(uint i=0 ; i < matrix.size() ; i++){
                    for(uint j=0 ; j < column + lengthMsg - 1 - indexMaxCol ; j++){
                        matrix[i].insert(matrix[i].end(),'_');
                    }
                }
                indexMaxCol = column + lengthMsg - 1;
            }
            //Adds columns to the left of the matrix.
            if(column < indexMinCol){
                for(uint i=0 ; i < matrix.size() ; i++){
                    for(uint j=0 ; j < indexMinCol - column ; j++){
                        matrix[i].insert(matrix[i].begin(),'_');
                    }
                }
                indexMinCol = column; 
            }
            //Add rows to the matrix upwards
            if(row < indexMinRow){
                for(int i=0 ; i < indexMinRow - row ; i++){
                     matrix.insert(matrix.begin(),vector<char>((matrix[0].size()),'_'));
                }
                indexMinRow = row;
            }
            //Inserts the string into the matrix
            uint indexMessage = 0;
            for (uint i = (column - indexMinCol); i < lengthMsg + (column - indexMinCol) ; i++){ 
                matrix[row - indexMinRow][i] = message[indexMessage++];
            }
        //The string is vertical
        }else if(direction == Direction::Vertical){
            //Init the matrix at the first time
            if(matrix.empty()){
                indexMinCol = indexMaxCol = column;
                indexMaxRow = row + lengthMsg - 1;
                indexMinRow = row;
                matrix.resize(indexMaxRow-indexMinRow+1,vector<char>(indexMaxCol-indexMinCol+1,'_'));
            }
            //Adds rows to the matrix downwards
            if(row + lengthMsg > indexMaxRow){
                indexMaxRow = row + lengthMsg;
                matrix.resize(indexMaxRow-indexMinRow,vector<char>(matrix[0].size(),'_'));
            }

            //Adds columns to the right of the matrix.
            if(column > indexMaxCol){
                // matrix.resize(indexMaxRow-indexMinRow,vector<char>(0,'_'));
                for(uint i=0 ; i < matrix.size() ; i++){
                    for(uint j=0 ; j < column - indexMaxCol ; j++){
                        matrix[i].insert(matrix[i].end(),'_');
                    }
                }
                indexMaxCol = column;
            }

            //Adds columns to the left of the matrix.
            if(column < indexMinCol){
                for(uint i=0 ; i < matrix.size() ; i++){
                    for(uint j=0 ; j < indexMinCol - column ; j++){
                        matrix[i].insert(matrix[i].begin(),'_');
                    }
                }
                indexMinCol = column; 
            }

            //Add rows to the matrix upwards
            if(row < indexMinRow){
                for(int i=0 ; i < indexMinRow - row ; i++){
                     matrix.insert(matrix.begin(),vector<char>((matrix[0].size()),'_'));
                }
                indexMinRow = row;
            }

            //Inserts the string into the matrix
            uint indexMessage = 0;
            for (uint i = (row - indexMinRow); i < lengthMsg + (row - indexMinRow) ; i++){ 
                matrix[i][column - indexMinCol] = message[indexMessage++];
            }
        }
    }

    //Gets position (row and column), direction (horizontal or vertical), 
    //and number of characters, reads what is written on the board at the given
    //position and length, and returns a string. The letter in each slot on the 
    //board is the last letter pasted there.
    string Board::read(uint row, uint column, Direction direction, uint length){
        string msg;
    
        //The reading is horizontal
        if (direction == Direction::Horizontal){
            //Checks whether the input is out of range
            if (matrix.empty() || row > indexMaxRow || row < indexMinRow){
                for(int i=0 ; i < length ; i++){
                    msg += '_';
                }
                return msg;
            }
            //If the reading begins before the string
            uint j = column;
            while(j < indexMinCol){
                msg += '_';
                j++;
            }
            //Threads of the string
            for (j = (uint)(max((int)(column - indexMinCol),0)); j < min((int)(column - indexMinCol + length),(int)matrix[0].size()); j++){
                msg += matrix[row - indexMinRow][j];
            }
            //If the reading continues after the string
            while(j < (column - indexMinCol + length)){
                msg += '_';
                j++;
            }
        //The reading is vertical
        }else if (direction == Direction::Vertical){
            //Checks whether the input is out of range
            if(matrix.empty() || column < indexMinCol || column > indexMaxCol){
                for(int i=0 ; i < length ; i++){
                    msg += '_';
                }
                return msg;
            }
            //If the reading begins before the string
            uint i = row;
            while(i < indexMinRow){
                msg += '_';
                i++;
            }
            //Threads of the string
            for (i = (uint)(max((int)(row - indexMinRow),0)) ; i < min((uint)(row - indexMinRow + length),(uint)matrix.size()); i++){
                msg += matrix[i][column - indexMinCol];
            }
            //If the reading continues after the string
            while(i < (row - indexMinRow + length)){
                msg += '_';
                i++;
            }
        }
        return msg;
    }

    //Displays the current bulletin board for easy reading.
    void Board::show(){
        string board;

        //Puts all the messeges in the string "board"
        for (uint i = 0; i < matrix.size(); i++) {
            for (uint j = 0; j < matrix[0].size(); j++) {
                if(matrix[i][j] != '\0'){
                    board += matrix[i][j];
                }else{
                    board += "_";
                }   
            }
            board += '\n';
        }
        cout << board;
    }
}
