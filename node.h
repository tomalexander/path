#pragma once
#include <list>
#include "types.h"

using std::list;

namespace path
{
    class edge;
    class node
    {
      public:
        node();
        ~node();

        list<edge*> edges;
        edge* parent;
        const fu32& get_f();
        void set_g(fu32 _g);
        const fu32& get_g();
        bool need_to_calculate_h;
        const fu32& get_h();
        
      private:
        fu32 g;                 /**< Movement cost to this node */
        fu32 h;                 /**< Heuristic cost to destination */
        fu32 f;                 /**< g+h */
        bool need_to_calculate_f;
    };
    class lowest_f
    {
      public:
        bool operator()(node* a, node* b)
        {
            return a->get_f() < b->get_f();
        }
    };
}
