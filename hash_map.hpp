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

    bool exist_tf = _head[ind].get_value(key).has_value();
    _head[ind].insert(key, value);

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
    for (size_t i = 0; i < _size - 1; i++) // Outer loop
    {
        for (size_t j = 0; j < _size - i - 1; j++) // Inner loop
        {
            if (keys[j] > keys[j + 1]) // Check adjacent elements
            {
                // Swap
                K temp = keys[j];
                keys[j] = keys[j + 1];
                keys[j + 1] = temp;
            }
        }
    }

    return;
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
    size_t ind = 0;

    // Important: we want to know which index position to start at
    while (_capacities[ind] != _capacity)
    {
        ind++;
    }

    // Moves index to get correct capacity value
    if (increase_decrease == '+')
    {
        if (ind != 2) // Prevent going above 2
        {
            ind += 1;
        }
    }
    else
    {
        if (ind != 0) // Prevent going below 0
        {
            ind -= 1;
        }
    }
    size_t the_capacity = _capacities[ind];

    // New hash list
    hash_list<K, V>* the_head = new hash_list<K, V>[the_capacity];

    // Retrieve all keys
    K *keys = new K[_size];
    get_all_keys(keys);

    // Retrieve values manually (get_all_keys() does not do this)
    V *values = new V[_size];
    for (size_t i = 0; i < _size; i++)
    {
        std::optional<V> val = get_value(keys[i]);
        if (val.has_value() == true)
        {
            values[i] = *val;
        }
    }

    // Resize
    delete[] _head;
    _capacity = the_capacity;
    _head = the_head;

    // Reinsert
    size_t original_size = _size;
    for (size_t i = 0; i < original_size; i++)
    {
        insert(keys[i], values[i]);
    }

    // Clean up
    delete[] keys;
    delete[] values;

    return;
}