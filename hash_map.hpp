#include "hash_map.h"

template <typename K, typename V>
hash_map<K, V>::hash_map(size_t capacity, float ulf, float llf) : _size(0), _capacity(capacity), _upper_load_factor(ulf), _lower_load_factor(llf)
{
    _head = new hash_list<K, V>[capacity];
}

template <typename K, typename V>
hash_map<K, V>::hash_map(const hash_map &other) : _size(other._size), _capacity(other._capacity), _upper_load_factor(other._upper_load_factor), _lower_load_factor(other._lower_load_factor)
{
    _head = new hash_list<K, V>[_capacity];
    for (size_t i = 0; i < _capacity; i++)
    {
        _head[i] = other._head[i];
    }
}

template <typename K, typename V>
hash_map<K, V> &hash_map<K, V>::operator=(const hash_map<K, V> &other)
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
    _upper_load_factor = other._upper_load_factor;
    _lower_load_factor = other._lower_load_factor;
    _head = new hash_list<K, V>[_capacity];

    // copy
    for (size_t i = 0; i < _capacity; i++)
    {
        _head[i] = other._head[i];
    }

    return(*this);
}

template <typename K, typename V>
void hash_map<K, V>::insert(K key, V value)
{
    // // DIY absolute value function
    // if (key < 0)
    // {
    //     key = -key; // if key >= 0, then we do nothing
    // }
    size_t ind = _hash(key) % _capacity; // altered hash function (PART 2 CHANGE)

    //std::cout << "hash value = " << ind << std::endl;

    bool exist_tf = _head[ind].get_value(key).has_value();
    _head[ind].insert(key, value);

    //return ;

    if (exist_tf == false)
    {
        _size++;
        if (need_to_rehash() == true)
        {
            rehash('+');
        }
    }

    return;
}

template <typename K, typename V>
std::optional<V> hash_map<K, V>::get_value(K key) const
{
    // // DIY absolute value function
    // if (key < 0)
    // {
    //     key = -key; // if key >= 0, then we do nothing
    // }
    size_t ind = _hash(key) % _capacity; // altered hash function (PART 2 CHANGE)

    return(_head[ind].get_value(key));
}

template <typename K, typename V>
bool hash_map<K, V>::remove(K key)
{
    // // DIY absolute value function
    // if (key < 0)
    // {
    //     key = -key; // if key >= 0, then we do nothing
    // }
    size_t ind = _hash(key) % _capacity; // altered hash function (PART 2 CHANGE)

    bool remove_tf = _head[ind].remove(key);

    if (remove_tf == true)
    {
        _size--;
        if (need_to_rehash() == true)
        {
            rehash('-');
        }
        return(true);
    }

    return(false);
}

template <typename K, typename V>
size_t hash_map<K, V>::get_size() const
{
    return(_size);
}

template <typename K, typename V>
size_t hash_map<K, V>::get_capacity() const
{
    return(_capacity);
}

template <typename K, typename V>
void hash_map<K, V>::get_all_keys(K *keys)
{
    size_t ind = 0;
    for (size_t i = 0; i < _capacity; i++)
    {
        _head[i].reset_iter();
        while (_head[i].iter_at_end() == false)
        {
            std::optional<std::pair<const K*, V*>> value = _head[i].get_iter_value();
            if (value.has_value() == true)
            {
                keys[ind] = *(value->first); // first refers to const K*, second would refer to V*
                ind++;
            }
            _head[i].increment_iter();
        }
    }

    return;
}

template <typename K, typename V>
void hash_map<K, V>::get_all_sorted_keys(K *keys)
{
    get_all_keys(keys);

    // Bubble sort
    for (int i = 0; i < _size - 1; i++) // Outer loop
    {
        for (int j = i + 1; j < _size ; j++) // Inner loop
        {
            if (keys[i] > keys[j]) // Check adjacent elements
            {
                // Swap
                K temp = keys[i];
                keys[i] = keys[j];
                keys[j] = temp;
            }
        }
    }
}

template <typename K, typename V>
void hash_map<K, V>::get_bucket_sizes(size_t *buckets)
{
    for (size_t i = 0; i < _capacity; i++)
    {
        buckets[i] = _head[i].get_size();
    }

    return;
}

template <typename K, typename V>
hash_map<K, V>::~hash_map()
{
    delete[] _head;

    return;
}

template <typename K, typename V>
bool hash_map<K, V>::need_to_rehash()
{
    float lf = float(_size) / float(_capacity); // load factor

    bool rehash = false;

    if (lf < _lower_load_factor || lf > _upper_load_factor)
    {
        rehash = true;
    }

    return(rehash);
}

template <typename K, typename V>
void hash_map<K, V>::rehash(char increase_decrease)
{
    // size_t ind = 0;

    // // Important: we want to know which index position to start at
    // while (ind < 3 && _capacities[ind] != _capacity)
    // {
    //     ind++;
    // }
    // if (ind >= 3)
    // {
    //     return;
    // }

    // // Moves index to get correct capacity value
    // if (increase_decrease == '+')
    // {
    //     if (ind != 2) // Prevent going above 2
    //     {
    //         ind += 1;
    //     }
    // }
    // else
    // {
    //     if (ind != 0) // Prevent going below 0
    //     {
    //         ind -= 1;
    //     }
    // }
    // size_t the_capacity = _capacities[ind];

    // What is this initial capacity? (209, 1021, 2039)
    size_t ind;
    bool less = false;
    if (_capacity <= _capacities[0]) // 209
    {
        ind = 0;
        if (_capacity < _capacities[0])
        {
            less = true;
        }
    }
    else if (_capacity < _capacities[1]) // 1021
    {
        ind = 1;
        if (_capacity < _capacities[1])
        {
            less = true;
        }
    }
    else // 2039
    {
        ind = 2;
        if (_capacity <= _capacities[2])
        {
            less = true;
        }
    }

    if (increase_decrease == '+')
    {
        if (less != true)
        {
            if (ind != 2)
            {
                ind += 1;
            }
        }
    }
    else // '-'
    {
        if (ind != 0)
        {
            ind -= 1;
        }
    }

    // catch-all (just in case)
    if (ind >= 3)
    {
        ind = 2;
    }
    if (ind <= -1)
    {
        ind = 0;
    }
    size_t the_capacity = _capacities[ind];

    // New hash list
    hash_list<K, V>* the_head = new hash_list<K, V>[the_capacity];

    size_t old_size = _size;

    // Retrieve all keys
    K *keys = new K[old_size];
    get_all_keys(keys);

    // Retrieve values manually (get_all_keys() does not do this)
    V *values = new V[old_size];
    for (size_t i = 0; i < old_size; i++)
    {
        std::optional<V> val = get_value(keys[i]);
        if (val.has_value() == true)
        {
            values[i] = *val;
        }
    }

    // Resize
    delete[] _head;
    _head = the_head;
    _capacity = the_capacity;
    _size = 0;

    // Reinsert
    for (size_t i = 0; i < old_size; i++)
    {
        //insert(keys[i], values[i]);
        size_t ind = _hash(keys[i]) % _capacity; // altered hash function (PART 2 CHANGE)

        //std::cout << "(2) hash value = " << ind << std::endl;

        //bool exist_tf = _head[ind].get_value(keys[i]).has_value();
        _head[ind].insert(keys[i], values[i]);

        //if (exist_tf == false)
        {
            _size++;
        }
    }

    // Clean up
    delete[] keys;
    delete[] values;

    return;
}