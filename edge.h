#pragma once
#include "types.h"
namespace path
{
    class node;
    class edge
    {
      public:
        edge(node* _origin = nullptr, node* _destination = nullptr, u32 _cost = 0);
        ~edge();

        node* get_origin() { return origin;}
        node* get_destination() { return destination;}
        const fu32& get_cost() { return cost;}

      private:
        node* origin;
        node* destination;
        fu32 cost;
    };
}
