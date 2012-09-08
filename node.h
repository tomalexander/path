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
