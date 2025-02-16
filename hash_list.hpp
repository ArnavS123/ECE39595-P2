#include "hash_list.h"

template <typename K, typename V>
hash_list<K, V>::hash_list() : size(0), head(nullptr) {}

/**-----------------------------------------------------------------------------------
 * START Part 1
 *------------------------------------------------------------------------------------*/

template <typename K, typename V>
void hash_list<K, V>::insert(K key, V value)
{
    node<K, V>* curr = head;

    while (curr != nullptr)
    {
        if (curr->key == key)
        {
            curr->value = value;
            return;
        }
        curr = curr->next;
    }

    node<K, V>* new_node = new node<K, V>{key, value, head}; // next is set to head
    head = new_node;

    size++;
    return;
}

template <typename K, typename V>
std::optional<V> hash_list<K, V>::get_value(K key) const
{
    node<K, V>* curr = head;

    while (curr != nullptr)
    {
        if (curr->key == key)
        {
            return(curr->value);
        }
        curr = curr->next;
    }

    return(std::nullopt);
}

template <typename K, typename V>
bool hash_list<K, V>::remove(K key)
{
    node<K, V>* curr = head;
    node<K, V>* prev = nullptr;

    while (curr != nullptr)
    {
        if (curr->key == key)
        {
            if (curr == head)
            {
                head = curr->next;
            }
            else
            {
                prev->next = curr->next;
            }
            delete(curr);
            size--;
            return(true);
        }
        prev = curr;
        curr = curr->next;
    }

    return(false);
}

template <typename K, typename V>
size_t hash_list<K, V>::get_size() const
{
    return(size);
}

template <typename K, typename V>
hash_list<K, V>::~hash_list()
{
    node<K, V>* curr = head;

    while (curr != nullptr)
    {
        node<K, V>* next_curr = curr->next;
        delete(curr);
        curr = next_curr;
    }

    return;
}

/**-----------------------------------------------------------------------------------
 * END Part 1
 *------------------------------------------------------------------------------------*/


/**-----------------------------------------------------------------------------------
 * START Part 2
 *------------------------------------------------------------------------------------*/

template <typename K, typename V>
hash_list<K, V>::hash_list(const hash_list<K, V> &other) : head(nullptr), size(0), iter_ptr(nullptr)
{
    if (other.head == nullptr)
    {
        return;
    }

    node<K, V>* curr_original = other.head;
    node<K, V>* prev_new = nullptr;

    while (curr_original != nullptr)
    {
        node<K, V>* new_node = new node<K, V>{curr_original->key, curr_original->value, nullptr};

        if (head == nullptr)
        {
            head = new_node;
        }
        else
        {
            prev_new->next = new_node;
        }

        prev_new = new_node;
        curr_original = curr_original->next;
    }

    size = other.size;
    return;
}

template <typename K, typename V>
hash_list<K, V> &hash_list<K, V>::operator=(const hash_list<K, V> &other)
{
    // self assessment
    if (this == &other)
    {
        return(*this);
    }

    // delete current
    node<K, V>* curr = head;
    while (curr != nullptr)
    {
        node<K, V>* next_n = curr->next;
        delete(curr);
        curr = next_n;
    }
    head = nullptr;
    size = 0;
    iter_ptr = nullptr;

    // copy
    node<K, V>* curr_original = other.head;
    node<K, V>* prev_new = nullptr;

    while (curr_original != nullptr)
    {
        node<K, V>* new_node = new node<K, V>{curr_original->key, curr_original->value, nullptr};

        if (head == nullptr)
        {
            head = new_node;
        }
        else
        {
            prev_new->next = new_node;
        }

        prev_new = new_node;
        curr_original = curr_original->next;
    }

    size = other.size;
    return(*this);
}

template <typename K, typename V>
void hash_list<K, V>::reset_iter()
{
    iter_ptr = head;

    if (head == nullptr)
    {
        iter_ptr = NULL;
    }

    return;
}

template <typename K, typename V>
void hash_list<K, V>::increment_iter()
{
    if (iter_ptr == NULL)
    {
        return;
    }
    
    if (iter_ptr->next == nullptr)
    {
        iter_ptr = NULL;
    }
    else
    {
        iter_ptr = iter_ptr->next;
    }

    return;
}

template <typename K, typename V>
std::optional<std::pair<const K *, V *>> hash_list<K, V>::get_iter_value()
{
    if (iter_ptr == NULL)
    {
        return(std::nullopt);
    }
    else
    {
        return(std::optional<std::pair<const K *, V *>>({&(iter_ptr->key), &(iter_ptr->value)}));
    }
}

template <typename K, typename V>
bool hash_list<K, V>::iter_at_end()
{
    if (iter_ptr == NULL)
    {
        return(true);
    }
    else
    {
        return(false);
    }
}

/**-----------------------------------------------------------------------------------
 * END Part 2
 *------------------------------------------------------------------------------------*/