#include <string>
#include "Direction.hpp"
#include <vector>
#include <limits.h>
using namespace std;

namespace ariel {
    class Board {
        vector<vector<char>> matrix;
    public:
        void post(uint row, uint column, Direction direction, std::string message);
        string read(uint row, uint column, Direction direction, uint length);
        void show();
    };
}