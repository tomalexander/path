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
#include "path.h"
#include "node.h"
#include "edge.h"
#include "bheap.h"
#include <vector>
#include <unordered_set>
#include <iostream>

using std::vector;
using std::unordered_set;

namespace path
{
    std::function<void (node* moving)> move_to_closed_list_hook;
    std::function<void (node* moving)> move_to_open_list_hook;
    
    void set_move_to_closed_list_hook(std::function<void (node* moving)> hook)
    {
        move_to_closed_list_hook = hook;
    }

    void set_move_to_open_list_hook(std::function<void (node* moving)> hook)
    {
        move_to_open_list_hook = hook;
    }

    vector<edge*> generate_path(node* origin, node* destination)
    {
        vector<edge*> ret;
        bheap<node*> open_list([destination](node* a, node* b) {return a->get_f(destination) < b->get_f(destination);});
        unordered_set<node*> closed_list;
        origin->set_g(0);
        open_list.push(origin);
        if (move_to_open_list_hook) move_to_open_list_hook(origin);

        while (true)
        {
            node* current_node = open_list.top();
            open_list.pop();
            closed_list.insert(current_node);
            if (current_node == destination)
                break;
            if (move_to_closed_list_hook) move_to_closed_list_hook(current_node);
            for (edge* e : current_node->get_edges())
            {
                node* destination = e->get_destination();
                if (closed_list.find(destination) != closed_list.end())
                { //Already on closed list
                    continue;
                }
                else if (open_list.find(destination) != nullptr)
                { // On open list already
                    fu32 new_g = current_node->get_g() + e->get_cost();
                    if (new_g < destination->get_g())
                    {
                        destination->set_g(new_g);
                        destination->parent = e;
                        open_list.sort();
                    }
                }
                else
                { // Never been visited before
                    destination->set_g(current_node->get_g() + e->get_cost());
                    destination->parent = e;
                    open_list.push(destination);
                    if (move_to_open_list_hook) move_to_open_list_hook(destination);
                }
            }

            if (open_list.empty()) //Failed to find destination
                return ret;
        }
        vector<edge*> reverse_ret;
        for (node* cur = destination; cur != origin; cur = cur->parent->get_origin())
            reverse_ret.push_back(cur->parent);
        for (auto it = reverse_ret.rbegin(); it != reverse_ret.rend(); ++it)
            ret.push_back(*it);
        return ret;
    }
    
    vector<edge*> generate_path(node* origin, std::function<bool (node*)> is_destination)
    {
        vector<edge*> ret;
        bheap<node*> open_list([](node* a, node* b) {return a->get_f(nullptr) < b->get_f(nullptr);});
        unordered_set<node*> closed_list;
        origin->set_g(0);
        open_list.push(origin);
        if (move_to_open_list_hook) move_to_open_list_hook(origin);

        node* destination = nullptr;
        while (true)
        {
            node* current_node = open_list.top();
            open_list.pop();
            closed_list.insert(current_node);
            if (is_destination(current_node))
            {
                destination = current_node;
                break;
            }
            if (move_to_closed_list_hook) move_to_closed_list_hook(current_node);
            for (edge* e : current_node->get_edges())
            {
                node* destination = e->get_destination();
                if (closed_list.find(destination) != closed_list.end())
                { //Already on closed list
                    continue;
                }
                else if (open_list.find(destination) != nullptr)
                { // On open list already
                    fu32 new_g = current_node->get_g() + e->get_cost();
                    if (new_g < destination->get_g())
                    {
                        destination->set_g(new_g);
                        destination->parent = e;
                        open_list.sort();
                    }
                }
                else
                { // Never been visited before
                    destination->set_g(current_node->get_g() + e->get_cost());
                    destination->parent = e;
                    open_list.push(destination);
                    if (move_to_open_list_hook) move_to_open_list_hook(destination);
                }
            }

            if (open_list.empty()) //Failed to find destination
                return ret;
        }
        vector<edge*> reverse_ret;
        for (node* cur = destination; cur != origin; cur = cur->parent->get_origin())
            reverse_ret.push_back(cur->parent);
        for (auto it = reverse_ret.rbegin(); it != reverse_ret.rend(); ++it)
            ret.push_back(*it);
        return ret;
    }
}
