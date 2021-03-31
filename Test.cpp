// /**
//  * AUTHORS: <Lior Atiya>
//  */

// #include "doctest.h"
// #include "Board.hpp"
// #include <string>
// #include <algorithm>
// #include <random>
// #include <iostream>
// #include <stdexcept>
// using namespace std;
// using namespace ariel;

// random_device rd;
// mt19937 rng(rd());
// uniform_int_distribution<int> uni(0,1000000);

// char letters[] = "abcdefghijklmnopqrstuvwxyz";
// string randomString(int length){
//     string str;
//     for(int i=0 ; i < length ; i++){
//         str += letters[rand() % 26];
//     }
//     return str;
// }

// Direction randomDirection(){
//     int randomBit = rand() % 2;
//     if(randomBit == 0){
//         return Direction::Horizontal;
//     }else{
//         return Direction::Vertical;
//     }
// }

// TEST_CASE("Checks random strings and places"){
//     for(int i = 0 ; i < 20 ; i++){
//         Board b;
//         auto row = uni(rng);
//         auto col = uni(rng);
//         string str = randomString(uni(rng));
//         Direction dir = randomDirection();
//         b.post(row,col,dir, str);
//         CHECK(b.read(row,col,dir, str.length()) == string(str));
//     }
// }

// TEST_CASE("Checks from index[0][0] on board - horizontal message") {
//     Board board;
//     //Post
//     board.post(0,0,Direction::Horizontal, "lior");
//     board.post(1,1,Direction::Horizontal, "lior");
//     board.post(3,3,Direction::Horizontal, "lior");
//     board.post(4,4,Direction::Horizontal, "lior");
//     //Read from current - right 
//     CHECK(board.read(0,0,Direction::Horizontal, 4) == string("lior"));
//     CHECK(board.read(0,2,Direction::Horizontal, 4) == string("or__"));
//     CHECK(board.read(0,4,Direction::Horizontal, 4) == string("____"));
//     //Read from current - left
//     CHECK(board.read(3,0,Direction::Horizontal, 4) == string("___l"));
//     CHECK(board.read(3,0,Direction::Horizontal, 7) == string("___lior"));
//     CHECK(board.read(4,0,Direction::Horizontal, 3) == string("___"));
//     CHECK(board.read(5,0,Direction::Horizontal, 5) == string("_____"));
// }

// TEST_CASE("Checks center and around on board - horizontal message") {
//     Board board;
//     //Post center
//     board.post(10,10,Direction::Horizontal, "david");
//     board.post(11,10,Direction::Horizontal, "atiya");
//     //Read center
//     CHECK(board.read(10,10,Direction::Horizontal, 5) == string("david"));
//     CHECK(board.read(10,10,Direction::Horizontal, 4) == string("davi"));
//     CHECK(board.read(10,10,Direction::Horizontal, 3) == string("dav"));
//     CHECK(board.read(10,10,Direction::Horizontal, 2) == string("da"));
//     CHECK(board.read(10,10,Direction::Horizontal, 1) == string("d"));
//     CHECK(board.read(11,8,Direction::Horizontal, 9) == string("__atiya__"));
//     //Post around the center
//     //Above
//     board.post(8,10,Direction::Horizontal, "aaaaa");
//     //Right
//     board.post(10,16,Direction::Horizontal, "bbbbb");
//     //Below
//     board.post(13,10,Direction::Horizontal, "ccccc");
//     //Left
//     board.post(11,4,Direction::Horizontal, "ddddd");

//     //Read above
//     CHECK(board.read(8,9,Direction::Horizontal, 6) == string("_aaaaa"));
//     //Read right and left from center
//     CHECK(board.read(10,10,Direction::Horizontal, 11) == string("david_bbbbb"));
//     CHECK(board.read(10,10,Direction::Horizontal, 12) == string("david_bbbbb_"));
//     CHECK(board.read(11,4,Direction::Horizontal, 11) == string("ddddd_atiya"));
//     CHECK(board.read(11,3,Direction::Horizontal, 12) == string("_ddddd_atiya"));

//     //Read below
//     CHECK(board.read(13,11,Direction::Horizontal, 5) == string("cccc_"));
// }

// TEST_CASE("Checks vertical message") {
//     Board board;
//     //Post
//     board.post(1000,1000,Direction::Vertical, "lior");
//     board.post(1000,1002,Direction::Vertical, "lior");
//     board.post(1000,1004,Direction::Vertical, "lior");
//     board.post(1000,1006,Direction::Vertical, "lior");
//     //Read above and below the center
//     CHECK(board.read(1000,1000,Direction::Vertical, 4) == string("lior"));
//     CHECK(board.read(998,1000,Direction::Vertical, 6) == string("__lior"));
//     CHECK(board.read(1002,1000,Direction::Vertical, 4) == string("or__"));
//     CHECK(board.read(999,1000,Direction::Vertical, 6) == string("_lior_"));
// }

// TEST_CASE("Combined checks - vertical and horizontal message"){
//     Board board;
//     board.post(10000,10000,Direction::Horizontal, "lior");
//     board.post(10001,10000,Direction::Horizontal, "lior");
//     board.post(10002,10000,Direction::Horizontal, "lior");
//     board.post(10003,10000,Direction::Horizontal, "lior");

//     CHECK(board.read(9998,10002,Direction::Vertical, 8) == string("__oooo__"));
//     CHECK(board.read(10000,10000,Direction::Vertical, 4) == string("llll"));
    
//     //Message over another message
//     board.post(10000,10001,Direction::Vertical, "   ");
//     CHECK(board.read(9999,10001,Direction::Vertical, 6) == string("_   i_"));
//     board.post(9997,10000,Direction::Vertical, "atiya");
//     CHECK(board.read(9996,10000,Direction::Vertical, 9) == string("_atiyall_"));
//     board.post(10001,9998,Direction::Vertical, "aaaaaa");
//     CHECK(board.read(10001,9998,Direction::Vertical, 7) == string("aaaaaa_"));

//     board.post(10005,10000,Direction::Horizontal, "I like to travel");
//     board.post(10005,10010,Direction::Horizontal, "play__");
//     CHECK(board.read(10005,10000,Direction::Horizontal, 14) == string("I like to play"));
// }

// TEST_CASE("Extreme cases"){
//     ariel::Board board;
//     CHECK(board.read(50,50,Direction::Horizontal, 5) == string("_____"));

//     //Limit uint
//     board.post(4294967290,4294967290,Direction::Horizontal, "VVVVV");
//     board.post(4294967291,4294967290,Direction::Horizontal, "VVVVV");
//     board.post(4294967292,4294967290,Direction::Horizontal, "VVVVV");
//     board.post(4294967293,4294967290,Direction::Horizontal, "VVVVV");
//     board.post(4294967294,4294967290,Direction::Horizontal, "VVVVV");

//     CHECK(board.read(4294967290,4294967289,Direction::Horizontal, 6) == string("_VVVVV"));
//     CHECK(board.read(4294967294,4294967290,Direction::Horizontal, 10) == string("VVVVV_____"));
// }

// TEST_CASE("Full matrix 5x5"){
//     ariel::Board board;
//     for(int i=0 ; i < 5 ; i++){
//        board.post(i,0,Direction::Horizontal, "LEVEL");
//     }
//     CHECK(board.read(0,4,Direction::Vertical, 5) == string("LLLLL"));
//     CHECK(board.read(0,3,Direction::Vertical, 5) == string("EEEEE"));
//     CHECK(board.read(0,2,Direction::Vertical, 5) == string("VVVVV"));
//     CHECK(board.read(0,1,Direction::Vertical, 5) == string("EEEEE"));
//     CHECK(board.read(0,0,Direction::Vertical, 5) == string("LLLLL"));
// }


#include "doctest.h"
#include "Board.hpp"
#include <string>
#include <array>

using namespace ariel;
using namespace std;

Board board;

TEST_CASE("test read before post")
{
    CHECK(board.read(0, 0, Direction::Horizontal, 1) == string("_"));
    // CHECK(board.read(0, 0, Direction::Horizontal, 2) == string("__"));
    // CHECK(board.read(0, 0, Direction::Vertical, 1) == string("_"));
    // CHECK(board.read(0, 0, Direction::Vertical, 2) == string("__"));
    // CHECK(board.read(34, 100, Direction::Vertical, 5) == string("_____"));
    // CHECK(board.read(23, 54, Direction::Horizontal, 4) == string("____"));
    // unsigned int random_row = rand() % 100;
    // unsigned int random_col = rand() % 100;
    // unsigned int random_len = rand() % 10;
    // string ans;
    // for (unsigned int i = 0; i < random_len; i++)
    // {
    //     ans += "_";
    // }
    // CHECK(board.read(random_row, random_col, Direction::Vertical, random_len) == string(ans));
    // CHECK(board.read(random_row, random_col, Direction::Horizontal, random_len) == string(ans));
}

// TEST_CASE("test post")
// {
//     CHECK_NOTHROW(board.post(0, 0, Direction::Horizontal, "Reut"));
//     CHECK_NOTHROW(board.post(0, 0, Direction::Vertical, "Reut"));
//     CHECK_NOTHROW(board.post(0, 3, Direction::Vertical, "Mas"));
//     CHECK_NOTHROW(board.post(5, 2, Direction::Horizontal, "Yakir"));
//     CHECK_NOTHROW(board.post(4, 6, Direction::Horizontal, "temp"));
//     CHECK_NOTHROW(board.post(1, 6, Direction::Vertical, "ariela"));
//     CHECK_NOTHROW(board.post(5, 6, Direction::Vertical, "W"));
// }
// TEST_CASE("test read- 1 post- no change")
// {
//     CHECK(board.read(0, 0, Direction::Vertical, 3) == string("Reu"));
//     CHECK(board.read(0, 0, Direction::Vertical, 4) == string("Reut"));
//     CHECK(board.read(0, 0, Direction::Vertical, 5) == string("Reut_"));

//     CHECK(board.read(0, 3, Direction::Vertical, 2) == string("Ma"));
//     CHECK(board.read(0, 3, Direction::Vertical, 3) == string("Mas"));
//     CHECK(board.read(0, 3, Direction::Vertical, 4) == string("Mas_"));

//     CHECK(board.read(2, 8, Direction::Vertical, 3) == string("__m"));
//     CHECK(board.read(5, 2, Direction::Vertical, 10) == string("Y_________"));
// }
// TEST_CASE("after 2 posts at the same point")
// {
//     CHECK(board.read(0, 0, Direction::Horizontal, 3) == string("Reu"));
//     CHECK(board.read(0, 0, Direction::Horizontal, 4) == string("ReuM"));
//     CHECK(board.read(0, 0, Direction::Horizontal, 5) == string("ReuM_"));

//     CHECK(board.read(4, 6, Direction::Horizontal, 3) == string("eem"));
//     CHECK(board.read(4, 6, Direction::Horizontal, 4) == string("eemp"));
//     CHECK(board.read(4, 5, Direction::Horizontal, 5) == string("_eemp"));
// }

// TEST_CASE("after 3 posts at the same point")
// {

//     CHECK(board.read(5, 3, Direction::Horizontal, 4) == string("akiW"));
//     CHECK(board.read(5, 2, Direction::Horizontal, 5) == string("YakiW"));
//     CHECK(board.read(5, 2, Direction::Horizontal, 6) == string("YakiW_"));

//     CHECK(board.read(2, 6, Direction::Vertical, 5) == string("rieWa"));
//     CHECK(board.read(1, 6, Direction::Vertical, 6) == string("arieWa"));
//     CHECK(board.read(1, 6, Direction::Vertical, 7) == string("arieWa_"));
// }

// TEST_CASE("test read corner")
// {
//     CHECK(board.read(6, 8, Direction::Horizontal, 5) == string("_____"));
//     CHECK(board.read(5, 4, Direction::Vertical, 3) == string("k__"));
//     CHECK(board.read(0, 2, Direction::Vertical, 10) == string("u____Y____"));
//     CHECK(board.read(6, 9, Direction::Vertical, 3) == string("___"));
// }

// TEST_CASE("uppercase or lowercase letters")
// {
//     CHECK_FALSE(board.read(0, 0, Direction::Horizontal, 4) == string("reum"));
//     CHECK_FALSE(board.read(0, 0, Direction::Horizontal, 4) == string("rEUm"));
//     CHECK_FALSE(board.read(0, 0, Direction::Horizontal, 4) == string("REUM"));
//     CHECK(board.read(0, 0, Direction::Horizontal, 4) == string("ReuM"));
// }

// TEST_CASE("test Horizontal vs Vertical")
// {
//     CHECK_NOTHROW(board.post(5, 5, Direction::Horizontal, "hel"));
//     CHECK(board.read(5, 5, Direction::Horizontal, 3) == "hel");
//     CHECK_FALSE(board.read(5, 5, Direction::Vertical, 3) == "hel");
//     CHECK_NOTHROW(board.post(5, 5, Direction::Vertical, "hel"));
//     CHECK(board.read(5, 5, Direction::Vertical, 3) == "hel");
//     CHECK(board.read(5, 5, Direction::Horizontal, 3) == "hel");
//     CHECK_NOTHROW(board.post(3, 3, Direction::Vertical, "hi"));
//     CHECK(board.read(3, 3, Direction::Vertical, 2) == "hi");
//     CHECK_FALSE(board.read(3, 3, Direction::Horizontal, 2) == "hi");
// }

// TEST_CASE("test read- length 0")
// {
//     //0,0
//     CHECK(board.read(0, 0, Direction::Horizontal, 0) == "");
//     CHECK(board.read(0, 0, Direction::Vertical, 0) == "");
//     //in the board
//     CHECK(board.read(5, 4, Direction::Horizontal, 0) == "");
//     CHECK(board.read(4, 5, Direction::Vertical, 0) == "");
//     //corners of the board
//     CHECK(board.read(6, 9, Direction::Horizontal, 0) == "");
//     CHECK(board.read(6, 9, Direction::Vertical, 0) == "");
//     //out of the board
//     CHECK(board.read(10, 34, Direction::Horizontal, 0) == "");
//     CHECK(board.read(34, 10, Direction::Vertical, 0) == "");
// }

// TEST_CASE("specil chars")
// {
//     CHECK_NOTHROW(board.post(5, 5, Direction::Horizontal, "?"));
//     CHECK_NOTHROW(board.post(3, 4, Direction::Horizontal, "_"));
//     CHECK_NOTHROW(board.post(1, 2, Direction::Horizontal, " "));
//     CHECK_NOTHROW(board.post(6, 3, Direction::Horizontal, "*"));
//     CHECK(board.read(5, 5, Direction::Vertical, 1) == "?");
//     CHECK(board.read(3, 4, Direction::Vertical, 1) == "_");
//     CHECK(board.read(1, 2, Direction::Vertical, 1) == " ");
//     CHECK(board.read(6, 3, Direction::Vertical, 1) == "*");
// }

// TEST_CASE("random")
// {
//     ariel::Board bo;
//     unsigned int random_row = rand() % 100;
//     unsigned int random_col = rand() % 100;
//     unsigned int random_len = rand() % 100;

//     CHECK_NOTHROW(bo.post(random_row, random_col, Direction::Horizontal, "rand"));
//     string ans="";
//     switch (random_len)
//     {
//     case 1:
//         ans="r";
//         break;
//     case 2:
//         ans="ra";
//         break;
//      case 3:
//         ans="ran";
//         break;
//         case 4:
//         ans="rand";
//         break;
//     default:
//         break;
//     }
//     if (random_len > 4)
//     {
//         ans = "rand";
//         for (unsigned int i = 0; i < random_len - 4; i++)
//         {
//             ans += "_";
//         }
//     }
//     CHECK(bo.read(random_row, random_col, Direction::Horizontal, random_len) == string(ans));
//     CHECK_NOTHROW(bo.post(random_row, random_col, Direction::Vertical, "rand"));
//     CHECK(bo.read(random_row, random_col, Direction::Vertical, random_len) == string(ans));
// }

// TEST_CASE("example of beauty message-board")
// {

//     ariel::Board b;
//     CHECK_NOTHROW(b.post(0, 0, Direction::Horizontal, "        \\\\|||||//        "));
//     CHECK_NOTHROW(b.post(1, 0, Direction::Horizontal, "        ( O   O )        "));
//     CHECK_NOTHROW(b.post(2, 0, Direction::Horizontal, "|--ooO-----(_)----------|"));
//     CHECK_NOTHROW(b.post(3, 0, Direction::Horizontal, "|                       |"));
//     CHECK_NOTHROW(b.post(4, 0, Direction::Horizontal, "|                       |"));
//     CHECK_NOTHROW(b.post(5, 0, Direction::Horizontal, "|     Message Board     |"));
//     CHECK_NOTHROW(b.post(6, 0, Direction::Horizontal, "|                       |"));
//     CHECK_NOTHROW(b.post(7, 0, Direction::Horizontal, "|                       |"));
//     CHECK_NOTHROW(b.post(8, 0, Direction::Horizontal, "|------------------Ooo--|"));
//     CHECK_NOTHROW(b.post(9, 0, Direction::Horizontal, "        |__|  |__|       "));
//     CHECK_NOTHROW(b.post(10, 0, Direction::Horizontal, "         ||    ||        "));
//     CHECK_NOTHROW(b.post(11, 0, Direction::Horizontal, "        ooO    Ooo       "));

//     b.show();
//     array<string, 12> s;
//     s.at(0) = "        \\\\|||||//        ";
//     s.at(1) = "        ( O   O )        ";
//     s.at(2) = "|--ooO-----(_)----------|";
//     s.at(3) = "|                       |";
//     s.at(4) = "|                       |";
//     s.at(5) = "|     Message Board     |";
//     s.at(6) = "|                       |";
//     s.at(7) = "|                       |";
//     s.at(8) = "|------------------Ooo--|";
//     s.at(9) = "        |__|  |__|       ";
//     s.at(10) = "         ||    ||        ";
//     s.at(11) = "        ooO    Ooo       ";

//     for (unsigned int i = 0; i < 12; i++)
//     {
//         CHECK(b.read(i, 0, Direction::Horizontal, 25) == string(s.at(i)));
//     }
// }




