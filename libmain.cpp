#include "path.h"
#include "node.h"
#include "edge.h"
#include "bheap.h"
#include <vector>
#include <unordered_set>

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
        bheap<node*> open_list([](node* a, node* b) {return a->get_f() < b->get_f();});
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
            for (edge* e : current_node->edges)
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
