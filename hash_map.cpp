#include "hash_map.h"

hash_map::hash_map(size_t capacity) : _size(0), _capacity(capacity), _head(nullptr) {}

hash_map::hash_map(const hash_map &other) : _size(other._size), _capacity(other._capacity), _head(other._head)
{
    for (size_t i = 0; i < _capacity; i++)
    {
        _head[i] = other._head[i];
    }
}

hash_map &hash_map::operator=(const hash_map &other)
{
    // self assessment
    if (this == &other)
    {
        return(*this);
    }

    // delete current
    delete[] _head;

    _size = other._size;
    _capacity = other._capacity;
    _head = other._head;

    // copy
    for (size_t i = 0; i < _capacity; i++)
    {
        _head[i] = other._head[i];
    }

    return(*this);
}

void hash_map::insert(int key, float value)
{
    // absolute value
    if (key < 0)
    {
        key = -key; // if key >= 0, then we do nothing
    }
    size_t ind = key % _capacity; // absolute value of the key modulo _capacity

    size_t initial_size = _head[ind].get_size(); // calling hash_list function get_size

    _head[ind].insert(key, value); // calling hash_list function insert

    if (_head[ind].get_size() > initial_size) // insertion successful
    {
        _size++;
    }
}