#include "Board.hpp"
#include "Direction.hpp"
#include <limits.h>
using ariel::Direction;

#include <iostream>
#include <stdexcept>
using namespace std;

int main() {
	//Post strings on each other and around
	ariel::Board name;
	name.post(50,50,Direction::Horizontal,"L I O $");
	name.post(50,56,Direction::Vertical,"R_?");
	name.post(52,56,Direction::Horizontal,"D A V I $");
	name.post(52,64,Direction::Vertical,"D_?");
	name.post(54,64,Direction::Horizontal,"A T I Y A");

	name.post(49,49,Direction::Horizontal,"o~~~~~~~~~~~~~~~~~~~~~~~o");
	name.post(49,49,Direction::Vertical,"o|||||o");
	name.post(49,73,Direction::Vertical,"o|||||o");
	name.post(55,49,Direction::Horizontal,"o~~~~~~~~~~~~~~~~~~~~~~~o");

	cout << name.read(50,48, Direction::Horizontal, 15) << endl;
	cout << name.read(48,73, Direction::Vertical, 15) << endl << endl;

	name.show();
	cout << endl;

	//The flag of Israel in the maximum number of rows
	ariel::Board flag;
	flag.post(UINT_MAX-19,0,Direction::Horizontal,"oooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooo");
	flag.post(UINT_MAX-18,0,Direction::Horizontal,"oooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooo");
	flag.post(UINT_MAX-17,0,Direction::Horizontal,"oooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooo");
	flag.post(UINT_MAX-16,0,Direction::Horizontal,"                                                                      ");
	flag.post(UINT_MAX-15,0,Direction::Horizontal,"                                  /\\                                  ");
	flag.post(UINT_MAX-14,0,Direction::Horizontal,"                                 oddo                                 ");
	flag.post(UINT_MAX-13,0,Direction::Horizontal,"                         `......sd//ds......`                         ");
	flag.post(UINT_MAX-12,0,Direction::Horizontal,"                          odhoydyooooydyohdo                          ");
	flag.post(UINT_MAX-11,0,Direction::Horizontal,"                           +d+hs`    `sh+d+                           ");
	flag.post(UINT_MAX-10,0,Direction::Horizontal,"                            odh`      `hdo                            ");
	flag.post(UINT_MAX-9,0,Direction::Horizontal,"                           +d+hs`    `sh+d+                           ");
	flag.post(UINT_MAX-8,0,Direction::Horizontal,"                          odhoydyooooydyohdo                          ");
	flag.post(UINT_MAX-7,0,Direction::Horizontal,"                         `......sd//ds......`                         ");
	flag.post(UINT_MAX-6,0,Direction::Horizontal,"                                 oddo                                 ");
	flag.post(UINT_MAX-5,0,Direction::Horizontal,"                                  \\/                                  ");
	flag.post(UINT_MAX-4,0,Direction::Horizontal,"                                                                      ");
	flag.post(UINT_MAX-3,0,Direction::Horizontal,"oooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooo");
	flag.post(UINT_MAX-2,0,Direction::Horizontal,"oooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooo");
	flag.post(UINT_MAX-1,0,Direction::Horizontal,"oooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooo");

	flag.show();

    return 0;
}

