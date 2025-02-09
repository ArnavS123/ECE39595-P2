#include "hash_list.h"

hash_list::hash_list() : size(0), head(nullptr) {}

/**-----------------------------------------------------------------------------------
 * START Part 1
 *------------------------------------------------------------------------------------*/

void hash_list::insert(int key, float value)
{
    node* curr = head;

    while (curr != nullptr)
    {
        if (curr->key == key)
        {
            curr->value = value;
            return;
        }
        curr = curr->next;
    }

    node* new_node = new node{key, value, head}; // next is set to head
    head = new_node;

    size++;
    return;
}

std::optional<float> hash_list::get_value(int key) const
{
    node* curr = head;

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

bool hash_list::remove(int key)
{
    node* curr = head;
    node* prev = nullptr;

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

size_t hash_list::get_size() const
{
    return(size);
}

hash_list::~hash_list()
{
    node* curr = head;

    while (curr != nullptr)
    {
        node* next_curr = curr->next;
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

hash_list::hash_list(const hash_list &other) : head(nullptr), size(0), iter_ptr(nullptr)
{
    if (other.head == nullptr)
    {
        return;
    }

    node* curr_original = other.head;
    node* prev_new = nullptr;

    while (curr_original != nullptr)
    {
        node* new_node = new node{curr_original->key, curr_original->value, nullptr};

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

hash_list &hash_list::operator=(const hash_list &other)
{
    // self assessment
    if (this == &other)
    {
        return(*this);
    }

    // delete current
    node* curr = head;
    while (curr != nullptr)
    {
        node* next_n = curr->next;
        delete(curr);
        curr = next_n;
    }
    head = nullptr;
    size = 0;
    iter_ptr = nullptr;

    // copy
    node* curr_original = other.head;
    node* prev_new = nullptr;

    while (curr_original != nullptr)
    {
        node* new_node = new node{curr_original->key, curr_original->value, nullptr};

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

void hash_list::reset_iter()
{
    iter_ptr = head;

    if (head == nullptr)
    {
        iter_ptr = NULL;
    }

    return;
}

void hash_list::increment_iter()
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

std::optional<std::pair<const int *, float *>> hash_list::get_iter_value()
{
    if (iter_ptr == NULL)
    {
        return(std::nullopt);
    }
    else
    {
        return(std::optional<std::pair<const int *, float *>>({&(iter_ptr->key), &(iter_ptr->value)}));
    }
}

bool hash_list::iter_at_end()
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