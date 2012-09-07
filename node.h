#pragma once
#include <list>
#include "types.h"
#include <functional>

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
        const fu32& get_f(node* goal);
        void set_g(fu32 _g);
        const fu32& get_g();
        bool need_to_calculate_h;
        const fu32& get_h(node* goal);
        
        void set_calculate_h_function(std::function<fu32 (node* goal)> hook) {calculate_h_function = hook;}
        
      private:
        fu32 g;                 /**< Movement cost to this node */
        fu32 h;                 /**< Heuristic cost to destination */
        fu32 f;                 /**< g+h */
        bool need_to_calculate_f;
        std::function<fu32 (node* goal)> calculate_h_function;
    };
}
