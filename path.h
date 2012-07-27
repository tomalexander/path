#pragma once
#include <vector>
#include "edge.h"
#include "node.h"

using std::vector;

namespace path
{
    vector<edge*> generate_path(node* origin, node* destination);
}
