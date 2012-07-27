#include "edge.h"

namespace path
{
    edge::edge(node* _origin, node* _destination, u32 _cost) : origin(_origin), destination(_destination), cost(_cost)
    {
        
    }

    edge::~edge()
    {

    }
}
