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
