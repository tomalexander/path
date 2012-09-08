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
#include "bheap.h"
#include "path.h"
#include <iostream>

using std::cout;

int main(int argc, char** argv)
{
    path::grid g(32,32);
    bheap<int> test;

    test.push(1);
    test.push(7);
    test.push(3);
    test.push(5);
    test.push(2);
    test.push(6);

    while (!test.empty())
    {
        cout << test.top() << "\n";
        test.pop();
    }

    bheap<int> list_test = {1,7,3,5,2,6};
    list_test.remove(list_test.find(3));
    while (!list_test.empty())
    {
        cout << list_test.top() << "\n";
        list_test.pop();
    }
    list_test.sort();
    list_test.push(3);
    list_test.sort();

    vector<path::edge*> found_path = generate_path(g.get(0,0), g.get(5,5));
    cout << "Length of Path: " << found_path.size() << " with cost: " << g.get(5,5)->get_g() << "\n";
    g.print_path(found_path);
    return 0;
}
