/**
 * AUTHORS: <Lior Atiya>
 */

#include "doctest.h"
#include "Board.hpp"
#include <string>
#include <algorithm>
#include <random>
#include <iostream>
#include <stdexcept>
using namespace std;
using namespace ariel;

random_device rd;
mt19937 rng(rd());
uniform_int_distribution<int> uni(0,1000000);

char letters[] = "abcdefghijklmnopqrstuvwxyz";
string randomString(int length){
    string str;
    for(int i=0 ; i < length ; i++){
        str += letters[rand() % 26];
    }
    return str;
}

Direction randomDirection(){
    int randomBit = rand() % 2;
    if(randomBit == 0){
        return Direction::Horizontal;
    }else{
        return Direction::Vertical;
    }
}

TEST_CASE("Checks random strings and places"){
    for(int i = 0 ; i < 20 ; i++){
        Board b;
        auto row = uni(rng);
        auto col = uni(rng);
        string str = randomString(uni(rng));
        Direction dir = randomDirection();
        b.post(row,col,dir, str);
        CHECK(b.read(row,col,dir, str.length()) == string(str));
    }
}

TEST_CASE("Checks from index[0][0] on board - horizontal message") {
    Board board;
    //Post
    board.post(0,0,Direction::Horizontal, "lior");
    board.post(1,1,Direction::Horizontal, "lior");
    board.post(3,3,Direction::Horizontal, "lior");
    board.post(4,4,Direction::Horizontal, "lior");
    //Read from current - right 
    CHECK(board.read(0,0,Direction::Horizontal, 4) == string("lior"));
    CHECK(board.read(0,2,Direction::Horizontal, 4) == string("or__"));
    CHECK(board.read(0,4,Direction::Horizontal, 4) == string("____"));
    //Read from current - left
    CHECK(board.read(3,0,Direction::Horizontal, 4) == string("___l"));
    CHECK(board.read(3,0,Direction::Horizontal, 7) == string("___lior"));
    CHECK(board.read(4,0,Direction::Horizontal, 3) == string("___"));
    CHECK(board.read(5,0,Direction::Horizontal, 5) == string("_____"));
}

TEST_CASE("Checks center and around on board - horizontal message") {
    Board board;
    //Post center
    board.post(10,10,Direction::Horizontal, "david");
    board.post(11,10,Direction::Horizontal, "atiya");
    //Read center
    CHECK(board.read(10,10,Direction::Horizontal, 5) == string("david"));
    CHECK(board.read(10,10,Direction::Horizontal, 4) == string("davi"));
    CHECK(board.read(10,10,Direction::Horizontal, 3) == string("dav"));
    CHECK(board.read(10,10,Direction::Horizontal, 2) == string("da"));
    CHECK(board.read(10,10,Direction::Horizontal, 1) == string("d"));
    CHECK(board.read(11,8,Direction::Horizontal, 9) == string("__atiya__"));
    //Post around the center
    //Above
    board.post(8,10,Direction::Horizontal, "aaaaa");
    //Right
    board.post(10,16,Direction::Horizontal, "bbbbb");
    //Below
    board.post(13,10,Direction::Horizontal, "ccccc");
    //Left
    board.post(11,4,Direction::Horizontal, "ddddd");

    //Read above
    CHECK(board.read(8,9,Direction::Horizontal, 6) == string("_aaaaa"));
    //Read right and left from center
    CHECK(board.read(10,10,Direction::Horizontal, 11) == string("david_bbbbb"));
    CHECK(board.read(10,10,Direction::Horizontal, 12) == string("david_bbbbb_"));
    CHECK(board.read(11,4,Direction::Horizontal, 11) == string("ddddd_atiya"));
    CHECK(board.read(11,3,Direction::Horizontal, 12) == string("_ddddd_atiya"));

    //Read below
    CHECK(board.read(13,11,Direction::Horizontal, 5) == string("cccc_"));
}

TEST_CASE("Checks vertical message") {
    Board board;
    //Post
    board.post(1000,1000,Direction::Vertical, "lior");
    board.post(1000,1002,Direction::Vertical, "lior");
    board.post(1000,1004,Direction::Vertical, "lior");
    board.post(1000,1006,Direction::Vertical, "lior");
    //Read above and below the center
    CHECK(board.read(1000,1000,Direction::Vertical, 4) == string("lior"));
    CHECK(board.read(998,1000,Direction::Vertical, 6) == string("__lior"));
    CHECK(board.read(1002,1000,Direction::Vertical, 4) == string("or__"));
    CHECK(board.read(999,1000,Direction::Vertical, 6) == string("_lior_"));
}

TEST_CASE("Combined checks - vertical and horizontal message"){
    Board board;
    board.post(10000,10000,Direction::Horizontal, "lior");
    board.post(10001,10000,Direction::Horizontal, "lior");
    board.post(10002,10000,Direction::Horizontal, "lior");
    board.post(10003,10000,Direction::Horizontal, "lior");

    CHECK(board.read(9998,10002,Direction::Vertical, 8) == string("__oooo__"));
    CHECK(board.read(10000,10000,Direction::Vertical, 4) == string("llll"));
    
    //Message over another message
    board.post(10000,10001,Direction::Vertical, "   ");
    CHECK(board.read(9999,10001,Direction::Vertical, 6) == string("_   i_"));
    board.post(9997,10000,Direction::Vertical, "atiya");
    CHECK(board.read(9996,10000,Direction::Vertical, 9) == string("_atiyall_"));
    board.post(10001,9998,Direction::Vertical, "aaaaaa");
    CHECK(board.read(10001,9998,Direction::Vertical, 7) == string("aaaaaa_"));

    board.post(10005,10000,Direction::Horizontal, "I like to travel");
    board.post(10005,10010,Direction::Horizontal, "play__");
    CHECK(board.read(10005,10000,Direction::Horizontal, 14) == string("I like to play"));
}

TEST_CASE("Extreme cases"){
    ariel::Board board;
    CHECK(board.read(50,50,Direction::Horizontal, 5) == string("_____"));

    //Limit uint
    board.post(4294967290,4294967290,Direction::Horizontal, "VVVVV");
    board.post(4294967291,4294967290,Direction::Horizontal, "VVVVV");
    board.post(4294967292,4294967290,Direction::Horizontal, "VVVVV");
    board.post(4294967293,4294967290,Direction::Horizontal, "VVVVV");
    board.post(4294967294,4294967290,Direction::Horizontal, "VVVVV");

    CHECK(board.read(4294967290,4294967289,Direction::Horizontal, 6) == string("_VVVVV"));
    CHECK(board.read(4294967294,4294967290,Direction::Horizontal, 10) == string("VVVVV_____"));
}

TEST_CASE("Full matrix 5x5"){
    ariel::Board board;
    for(int i=0 ; i < 5 ; i++){
       board.post(i,0,Direction::Horizontal, "LEVEL");
    }
    CHECK(board.read(0,4,Direction::Vertical, 5) == string("LLLLL"));
    CHECK(board.read(0,3,Direction::Vertical, 5) == string("EEEEE"));
    CHECK(board.read(0,2,Direction::Vertical, 5) == string("VVVVV"));
    CHECK(board.read(0,1,Direction::Vertical, 5) == string("EEEEE"));
    CHECK(board.read(0,0,Direction::Vertical, 5) == string("LLLLL"));
}




