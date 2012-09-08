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
#include "grid.h"
#include "node.h"
#include "edge.h"
#include <iostream>

using std::cout;

namespace path
{
    grid::grid(u32 _width, u32 _height, u32 default_orthagonal_cost, u32 default_diagonal_cost) : width(_width), height(_height)
    {
        fu64 num_of_nodes = width*height;
        nodes.reserve(num_of_nodes);
        for (fu64 i = 0; i < num_of_nodes; ++i)
            nodes.push_back(new node());
        for (fu64 x = 0; x < width; ++x)
        {
            for (fu64 y = 0; y < height; ++y)
            {
                node* current_node = get(x,y);
                for (fs64 mod_x = -1; mod_x <= 1; ++mod_x)
                {
                    for (fs64 mod_y = -1; mod_y <= 1; ++mod_y)
                    {
                        if (mod_x == 0 && mod_y == 0)
                            continue;
                        if (mod_x == -1 && x == 0)
                            continue;
                        if (mod_x + x == width)
                            continue;
                        if (mod_y == -1 && y == 0)
                            continue;
                        if (mod_y + y == height)
                            continue;
                        current_node->edges.push_back(new edge(current_node, get(x+mod_x, y+mod_y), (mod_x == 0 || mod_y == 0 ? default_orthagonal_cost : default_diagonal_cost)));
                    }
                }
            }
        }
    }

    grid::~grid()
    {
        for (node* n : nodes)
            delete n;
    }

    /** 
     * Get the node pointer at coordinates x,y with the top left corner being coordinate 0,0
     * 
     * @param x The x coordinate
     * @param y The y coordinate
     * 
     * @return A reference to the pointer to the node at coordinates x,y
     */
    node*& grid::get(u32 x, u32 y)
    {
        return nodes[height*x+y];
    }

    /** 
     * Find the index of the node in the underlying structure
     * 
     * @param goal The node to search for
     * 
     * @return The index of the node in the underlying vector
     */
    size_t grid::find_node_index(node* goal)
    {
        for (size_t i = 0; i < nodes.size(); ++i)
            if (nodes[i] == goal)
                return i;
        return -1;
    }

    /** 
     * Get the coordinations of the index for the underlying vector
     * 
     * @param index The index in the underlying vector
     * 
     * @return A tuple containing x,y coordinates
     */
    tuple<u32, u32> grid::get_x_y_from_index(size_t index)
    {
        return std::make_tuple(index/height, index%height);
    }

    /** 
     * Print a path to the console. The result will be a series of asterisks
     * 
     * @param path The path to print
     */
    void grid::print_path(const vector<edge*> & path)
    {
        char* output = new char[nodes.size()];
        for (size_t i = 0; i < nodes.size(); ++i)
            output[i] = ' ';
        output[find_node_index(path[0]->get_origin())] = '*';
        for (edge* cur : path)
            output[find_node_index(cur->get_destination())] = '*';

        for (fu64 x = 0; x < width+2; ++x)
            cout << '-';
        cout << '\n';
        for (fu64 y = 0; y < height; ++y)
        {
            cout << '|';
            for (fu64 x = 0; x < width; ++x)
            {
                cout << output[height*x+y];
            }
            cout << "|\n";
        }
        for (fu64 x = 0; x < width+2; ++x)
            cout << '-';
        cout << '\n';
        
        delete [] output;
    }
}
