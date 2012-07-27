#pragma once
#include "types.h"
#include <vector>
#include <tuple>

using std::vector;
using std::tuple;
using std::tie;

namespace path
{
    class node;
    class edge;
    class grid
    {
      public:
        grid(u32 _width, u32 _height, u32 default_orthagonal_cost = 10, u32 default_diagonal_cost = 14);
        ~grid();

        node*& get(u32 x, u32 y);
        void print_path(const vector<edge*> & path);
      private:
        size_t find_node_index(node* goal);
        tuple<u32, u32> get_x_y_from_index(size_t index);
        u32 width;
        u32 height;
        vector<node*> nodes;
    };
}
