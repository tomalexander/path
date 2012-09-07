#pragma once
#include <vector>
#include <functional>
#include "edge.h"
#include "node.h"

using std::vector;

namespace path
{
    void set_move_to_closed_list_hook(std::function<void (node* moving)> hook);
    void set_move_to_open_list_hook(std::function<void (node* moving)> hook);
    vector<edge*> generate_path(node* origin, node* destination);
}
