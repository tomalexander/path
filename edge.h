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
