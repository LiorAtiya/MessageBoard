#include "Board.hpp"
#include "Direction.hpp"
using ariel::Direction;

#include <iostream>
#include <stdexcept>
// #include <climits>
using namespace std;

int main() {
	ariel::Board board;
	// board.post(UINT_MAX-1,UINT_MAX-1,Direction::Horizontal,"V");
	// cout << board.read(3,4,Direction::Horizontal, 10) << endl;
	board.post(4,4,Direction::Horizontal,"banana");
	// board.post(4,2,Direction::Vertical,"lior");
	// cout << board.read(4,2,Direction::Horizontal, 10);
	//down
	// board.post(5,0,Direction::Horizontal,"banana");
	//right
	// board.post(4,0,Direction::Horizontal,"lior");
	// board.post(0,0,Direction::Horizontal,"banana");
	// cout << board.read(0,0,Direction::Horizontal, 10);
    // cout << board.read(1,0, Direction::Horizontal, 10) << endl;
	// board.post(/*row=*/100, /*column=*/200, Direction::Horizontal, "abcd");
	// cout << board.read(100,200,Direction::Horizontal, 10);
	// cout << board.read(/*row=*/99, /*column=*/201, Direction::Vertical, /*length=*/3) << endl;  
	// // prints "_b_" (starts at row 99 which is empty; then at row 100 there is "b"; then row 101 is empty again).
	// board.post(/*row=*/99, /*column=*/202, Direction::Vertical, "xyz");
	// board.post(/*row=*/103, /*column=*/205, Direction::Horizontal, "lior");
	// board.post(/*row=*/101, /*column=*/205, Direction::Horizontal, "atiya");
	// board.post(/*row=*/102, /*column=*/202, Direction::Vertical, "david");
	// cout << board.read(/*row=*/100, /*column=*/200, Direction::Horizontal, /*length=*/6) << endl;  
	// // prints "abyd__" (First letters are ab; then y from the "xyz"; then d; then two empty cells).

    // cout << board.read(1, 2, Direction::Horizontal, 4) << endl;
    // board.post(10000000, 200, Direction::Horizontal, "abcd");
    // cout << board.read(10000000, 200, Direction::Horizontal, 4) << endl;
    // board.post(100000000, 1000000000, Direction::Horizontal, "T");
	// board.show(); // shows the board in a reasonable way. For example:
	// // 	//    98:  _________
	// // 	//    99:  ____x____
	// // 	//    100: __abyd___
	// // 	//    101: ____z____
	// // 	//    102: _________

	// board.post(10,10,Direction::Horizontal, "david");
    // board.post(11,10,Direction::Horizontal, "atiya");
	board.show();

    return 0;
}

