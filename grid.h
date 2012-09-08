/*
 * Copyright (c) 2012 Tom Alexander
 * 
 * This software is provided 'as-is', without any express or implied
 * warranty. In no event will the authors be held liable for any damages
 * arising from the use of this software.
 * 
 * Permission is granted to anyone to use this software for any purpose,
 * including commercial applications, and to alter it and redistribute it
 * freely, subject to the following restrictions:
 * 
 *    1. The origin of this software must not be misrepresented; you must not
 *    claim that you wrote the original software. If you use this software
 *    in a product, an acknowledgment in the product documentation would be
 *    appreciated but is not required.
 * 
 *    2. Altered source versions must be plainly marked as such, and must not be
 *    misrepresented as being the original software.
 * 
 *    3. This notice may not be removed or altered from any source
 *    distribution.
 */
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
