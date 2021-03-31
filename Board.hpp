#include <string>
#include "Direction.hpp"
#include <vector>
using namespace std;

namespace ariel {
    class Board {
        vector<vector<char>> matrix;
        uint indexMinCol;
        uint indexMaxCol;
        uint indexMinRow;
        uint indexMaxRow;
    public:
        void post(uint row, uint column, Direction direction, std::string message);
        string read(uint row, uint column, Direction direction, uint length);
        void show();
    };
}