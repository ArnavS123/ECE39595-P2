#include "hash_map.h"

hash_map::hash_map(size_t capacity) : _size(0), _capacity(capacity)
{
    _head = new hash_list[capacity];
}

hash_map::hash_map(const hash_map &other) : _size(other._size), _capacity(other._capacity)
{
    _head = new hash_list[_capacity];
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
    _head = new hash_list[_capacity];

    // copy
    for (size_t i = 0; i < _capacity; i++)
    {
        _head[i] = other._head[i];
    }

    return(*this);
}

void hash_map::insert(int key, float value)
{
    // // DIY absolute value function
    // if (key < 0)
    // {
    //     key = -key; // if key >= 0, then we do nothing
    // }
    size_t ind = abs(key) % _capacity; // absolute value of the key modulo _capacity
    bool exist_tf = _head[ind].get_value(key).has_value();

    if (exist_tf == false)
    {
        _size++;
    }

    return;
}

std::optional<float> hash_map::get_value(int key) const
{
    // // DIY absolute value function
    // if (key < 0)
    // {
    //     key = -key; // if key >= 0, then we do nothing
    // }
    size_t ind = abs(key) % _capacity;

    return(_head[ind].get_value(key));
}

bool hash_map::remove(int key)
{
    // // DIY absolute value function
    // if (key < 0)
    // {
    //     key = -key; // if key >= 0, then we do nothing
    // }
    size_t ind = abs(key) % _capacity;

    bool remove_tf = _head[ind].remove(key);

    if (remove_tf == true)
    {
        _size--;
        return(true);
    }

    return(false);
}

size_t hash_map::get_size() const
{
    return(_size);
}

size_t hash_map::get_capacity() const
{
    return(_capacity);
}

void hash_map::get_all_keys(int *keys)
{
    size_t ind = 0;
    for (size_t i = 0; i < _capacity; i++)
    {
        _head[i].reset_iter();
        while (_head[i].iter_at_end() == false)
        {
            std::optional<std::pair<const int*, float*>> value = _head[i].get_iter_value();
            if (value.has_value())
            {
                keys[ind] = *(value->first); // first refers to const int*, second would refer to float*
                ind++;
            }
            _head[i].increment_iter();
        }
    }

    return;
}

void hash_map::get_bucket_sizes(size_t *buckets)
{
    for (size_t i = 0; i < _capacity; i++)
    {
        buckets[i] = _head[i].get_size();
    }

    return;
}

hash_map::~hash_map()
{
    delete[] _head;

    return;
}