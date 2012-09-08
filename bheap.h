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
#include <functional>
#include <vector>

template <class T>
class bheap
{
  public:
    /** 
     * Initialize the bheap with a function to compare the entries and an expected size to reduce allocations during insertion
     * 
     * @param _compare A function to compare the entries. If compare(a,b) returns true, A is located higher up in the queue to be popped off first
     * @param expected_size The amount of space to allocate for values
     */
    bheap(std::function< bool(T& a, T& b) > _compare = [](T& a, T& b) {return a < b;}, size_t expected_size = 100) :
        compare(_compare)
    {
        heap.reserve(expected_size);
    }
    /** 
     * Initialize the bheap with a list of initial values, a function to compare the entries and an expected size to reduce allocations during insertion
     * 
     * @param input An initializer list of values to be inserted into the heap
     * @param _compare A function to compare the entries. If compare(a,b) returns true, A is located higher up in the queue to be popped off first
     * @param expected_size The amount of space to allocate for values
     */
    bheap(const std::initializer_list<T> & input, std::function< bool(T& a, T& b) > _compare = [](T& a, T& b) {return a < b;}, size_t expected_size = 100) :
        compare(_compare)
    {
        heap.reserve((expected_size > input.size() ? expected_size : input.size()));
        for (const T& val : input)
            heap.push_back(val);
        sort();
    }
    ~bheap()
    {

    }

    /** 
     * Check to see if the heap has no values
     * 
     * 
     * @return true if it has no values, otherwise false
     */
    bool empty() const
    {
        return heap.empty();
    }

    /** 
     * Get the size of the heap
     * 
     * 
     * @return The size of the heap
     */
    size_t size() const
    {
        return heap.size();
    }

    /** 
     * Add a new value to the heap in the correct position
     * 
     * @param value The new value to add
     */
    void push(const T& value)
    {
        heap.push_back(value);
        percolate_up(heap.size()-1);
    }

    /** 
     * Get the lowest value in the heap
     * 
     * Gets the lowest value in the heap. This is determined by finding which value returns true compared against all other items when passed as the first parameter to the compare function. By defaul the compare function performs a simple operator<()
     * 
     * 
     * @return The lowest value in the heap
     */
    const T& top() const
    {
        return heap[0];
    }

    /** 
     * Remove the lowest value from the heap
     * 
     */
    void pop()
    {
        heap[0] = heap[heap.size()-1];
        heap.pop_back();
        percolate_down(0);
    }

    /** 
     * Fully sort the heap assuming nothing about the current state. This operation is expensive so only call it if necessary. The pop and push functions will keep the heap sorted on their own.
     * 
     */
    void sort()
    {
        if (empty())
            return;
        for (size_t i = (heap.size()-1)/2; i != -1; --i)
            percolate_down(i);
    }

    /** 
     * Find the first entry that matches value.
     * 
     * Find the first entry that matches value. If there are multiple entries with the same value there is no guarantee which one will be returned. Please note that if you change a value that affects the sorting then you must also make a call to sort()
     * 
     * @param value The value to look for
     * 
     * @return A pointer to the value in the heap matching the input value or nullptr if none is found
     */
    T* find(const T& value)
    {
        for (T& val : heap)
            if (val == value)
                return &val;
        return nullptr;
    }

    /** 
     * Remove a value from the heap.
     * 
     * Remove a value from the heap given a pointer to its location. This will call sort() automatically since the sorting of the heap will be destroyed. To remove by value, use find()
     * 
     * @param value A pointer to the value in the heap that needs to be removed.
     */
    void remove(const T* value)
    {
        bool found = false;
        for (auto it = heap.begin(); it != heap.end(); ++it)
        {
            if (&*it == value)
            {
                heap.erase(it);
                found = true;
                break;
            }
        }
        if (found)
            sort();
    }
  private:
    void percolate_down(size_t i)
    {
        while (2*i + 1 < heap.size())
        {
            size_t left_child = 2*i + 1;
            size_t right_child = 2*i + 2;
            size_t parent = (i-1)/2;
            size_t last_leaf = heap.size()-1;
            size_t child;
            if (right_child < heap.size() && compare(heap[right_child], heap[left_child]))
                child = right_child;
            else
                child = left_child;
            if (compare(heap[child], heap[i]))
            {
                //swap
                T tmp = heap[i];
                heap[i] = heap[child];
                heap[child] = tmp;
                i = child;
            } else {
                break;
            }
        }
    }

    void percolate_up(size_t i)
    {
        size_t parent = (i-1)/2;
        while (parent < i)
        {
            if (compare(heap[i], heap[parent]))
            {
                T tmp = heap[i];
                heap[i] = heap[parent];
                heap[parent] = tmp;
                i = parent;
                parent = (i-1)/2;
            } else {
                break;
            }
        }
    }

    std::function< bool(T& a, T& b) > compare;
    std::vector<T> heap;
};

