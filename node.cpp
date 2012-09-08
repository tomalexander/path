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
#include "node.h"
namespace path
{
    node::node() : parent(nullptr),
                   g(0),
                   h(0),
                   f(0),
                   need_to_calculate_f(false),
                   need_to_calculate_h(true)
    {

    }

    node::~node()
    {

    }

    const fu32& node::get_f(node* goal)
    {
        if (need_to_calculate_f)
        {
            f = g + get_h(goal);
            need_to_calculate_f = false;
        }
        return f;
    }

    void node::set_g(fu32 _g)
    {
        g = _g;
        need_to_calculate_f = true;
    }

    const fu32& node::get_g()
    {
        return g;
    }

    const fu32& node::get_h(node* goal)
    {
        if (need_to_calculate_h)
        {
            need_to_calculate_h = false;
            need_to_calculate_f = true;
            ///@todo actually calculate h
            h = 0;
            if (calculate_h_function) h = calculate_h_function(goal);
        }
        return h;
    }
}
