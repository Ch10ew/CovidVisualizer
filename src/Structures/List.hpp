#ifndef LIST_HPP
#define LIST_HPP

#include <cmath>
#include <initializer_list>
#include <iterator>
#include <memory>
#include <vector>

namespace co
{
    /// ========================================
    ///   List node structure.
    /// ========================================
    /**
     * @brief Supporting structure for List class.
     *
     * Defines a single node of the list.
     */
    template <typename T>
    struct ListNode
    {
        ListNode() = delete;
        ListNode(T data);

        T data = NULL;
        std::shared_ptr<ListNode<T>> prev = nullptr;
        std::shared_ptr<ListNode<T>> next = nullptr;
    };

    /// ========================================
    ///   Optimization structures.
    /// ========================================
    /**
     * @brief Defines the node to start from when transversing through the list.
     */
    enum class TransversalStartNode
    {
        HEAD,
        CURRENT,
        TAIL
    };

    /**
     * @brief Defines the direction to transverse when transversing through the list.
     */
    enum class TransversalDirection
    {
        LEFT = -1,
        RIGHT = 1
    };

    /**
     * @brief Defines the transversal start node, direction, and distance for operations in the list
     */
    struct TransversalInfo
    {
        TransversalStartNode start_node;
        TransversalDirection direction;
        int distance;
    };

    /// ========================================
    ///   List class.
    /// ========================================
    /**
     * @brief Meta class for a list "structure". Type supplied in T should have operator== and
     * operator< overloads for `Search()` and `Sort()` respectively.
     */
    template <typename T>
    class List
    {
    public:
        // Constructors
        List();
        List(const List<T>& source);
        List(std::initializer_list<T> initializer_list);

        // Element Access
        T& Head() const;
        T& Tail() const;
        T& At(const int n) const;

        // Capacity
        const bool Empty() const;
        const int Size() const;

        // Modifiers
        void Clear();
        void ShrinkToFit(const int size);
        void InsertHead(const T data);
        void InsertInPlace(const T data, const int index);
        void InsertTail(const T data);
        void RemoveHead();
        void RemoveInPlace(const int index);
        void RemoveTail();
        T Pop();
        T Poll();

        // Operations
        int Search(const T data);
        int Search(const T data, const int start_index);

        template <class Compare>
        int Search(const T data, Compare func);

        template <class Compare>
        int Search(const T data, Compare func, const int start_index);

        void Swap(const int a, const int b);
        void Sort();

        template <class Compare>
        void Sort(Compare func);

        // Operator Overloads
        void operator=(const List<T>& source);

        class iterator
        {
        public:
            std::shared_ptr<ListNode<T>> node_;

            iterator() : node_(nullptr) {}
            iterator(std::shared_ptr<ListNode<T>> node) : node_(node) {}

            const T& operator*() const { return node_->data; }

            iterator& operator++()
            {
                node_ = node_->next;
                return *this;
            }

            bool operator==(iterator rhs) const { return node_ == rhs.node_; }
            bool operator!=(iterator rhs) const { return node_ != rhs.node_; }
        };

        iterator begin() { return iterator(head_); }
        iterator end() { return iterator(); }

    private:
        // Auxiliary functions for `Sort()`
        List<T>
        Sorter(List<T> input_list);

        template <class Compare>
        List<T> Sorter(List<T> input_list, Compare func);

        List<T> Merge(List<T> left_list, List<T> right_list);

        template <class Compare>
        List<T> Merge(List<T> left_list, List<T> right_list, Compare func);

        // Optimization auxiliary functions
        const TransversalInfo GetTransversalInfo(const int index) const;

    private:
        std::shared_ptr<ListNode<T>> head_ = nullptr;
        std::shared_ptr<ListNode<T>> tail_ = nullptr;
        std::shared_ptr<ListNode<T>> current_ = nullptr;
        int size_ = 0;
        int current_index_ = 0;
    };

    /// ========================================
    ///   List node structure member function definitions.
    /// ========================================
    /*template <typename T>
    ListNode<T>::ListNode()
    {
    }*/

    /**
     * @brief Construct a new ListNode<T>::List Node object
     *
     * @param data Data to initialize node with.
     */
    template <typename T>
    ListNode<T>::ListNode(T data) : data(data)
    {
    }

    /// ========================================
    ///   List class constructor definitions.
    /// ========================================
    /**
     * @brief Default Constructor. Does nothing.
     */
    template <typename T>
    List<T>::List()
    {
    }

    /**
     * @brief Copy constructor.
     *
     * @param source
     */
    template <typename T>
    List<T>::List(const List<T>& source)
    {
        *this = source;
    }

    /**
     * @brief Constructor overload for initializer list.
     *
     * @param initializer_list
     */
    template <typename T>
    List<T>::List(std::initializer_list<T> initializer_list)
    {
        for (auto iterator = initializer_list.begin(); iterator != initializer_list.end(); ++iterator)
        {
            InsertTail(*iterator);
        }
    }

    /// ========================================
    ///   List class member functions definitions.
    /// ========================================
    // Element Access
    /**
     * @brief Gets the head element.
     *
     * @return T& Head element.
     */
    template <typename T>
    T& List<T>::Head() const
    {
        if (size_ > 0)
            return head_->data;

        throw std::out_of_range("co::List<T>::Head(): List is empty");
    }

    /**
     * @brief Gets the tail element.
     *
     * @return T& Tail element.
     */
    template <typename T>
    T& List<T>::Tail() const
    {
        if (size_ > 0)
            return tail_->data;

        throw std::out_of_range("co::List<T>::Tail(): List is empty");
    }

    /**
     * @brief Gets the element at `n`
     *
     * @param n Index of the element to be accessed.
     * @return T& Element at `n`.
     */
    template <typename T>
    T& List<T>::At(const int n) const
    {
        if (n < 0)
            throw std::out_of_range("co::List<T>::At(): Negative index");

        std::shared_ptr<ListNode<T>> current = current_;
        TransversalInfo transversal_info = GetTransversalInfo(n);

        switch (transversal_info.start_node)
        {
        case TransversalStartNode::HEAD:
            current = head_;
            break;
        case TransversalStartNode::TAIL:
            current = tail_;
            break;
        }

        int counter = 0;
        while (current)
        {
            if (counter == transversal_info.distance)
            {
                return current->data;
            }

            if (transversal_info.direction == TransversalDirection::RIGHT)
                current = current->next;
            else
                current = current->prev;

            ++counter;
        }

        throw std::out_of_range("co::List<T>::At(): List is empty");
    }

    // Capacity
    /**
     * @brief Gets if list is empty.
     *
     * @return true if list is empty
     * @return false if list is not empty.
     */
    template <typename T>
    const bool List<T>::Empty() const
    {
        return size_ == 0;
    }

    /**
     * @brief Gets the size of the list.
     *
     * @return const int The size of the list.
     */
    template <typename T>
    const int List<T>::Size() const
    {
        return size_;
    }

    // Modifiers
    /**
     * @brief Clears the list.
     */
    template <typename T>
    void List<T>::Clear()
    {
        if (size_ == 0)
            return;

        std::shared_ptr<ListNode<T>> current = head_;
        std::shared_ptr<ListNode<T>> prev = head_;
        if (current)
            current = current->next;

        while (current)
        {
            prev = current;
            current = current->next;
            if (current)
            {
                prev->next = nullptr;
                current->prev = nullptr;
            }
        }
        head_->next = nullptr;

        head_ = nullptr;
        current_ = nullptr;
        tail_ = nullptr;
        size_ = 0;
    }

    /**
     * @brief Shrinks the list to fit in `size`.
     *
     * @param size Size to shrink the list to.
     */
    template <typename T>
    void List<T>::ShrinkToFit(const int size)
    {
        if (size < 0)
            throw std::out_of_range("co::List<T>::Head(): Negative index");

        int difference = int(size_) - int(size);
        if (difference > 0)
        {
            for (int i = 0; i < difference; ++i)
            {
                RemoveTail();
            }
            return;
        }

        throw std::length_error("co::List<T>::Head(): New size given is larger than size of original list");
    }

    /**
     * @brief Inserts an element to the start of the list.
     *
     * @param data Data to insert.
     */
    template <typename T>
    void List<T>::InsertHead(const T data)
    {
        std::shared_ptr<ListNode<T>> tmp = std::make_shared<ListNode<T>>(data);

        if (head_)
        {
            head_->prev = tmp;
            tmp->next = head_;
        }

        head_ = tmp;

        if (size_ == 0)
            tail_ = tmp;

        ++size_;
        current_ = head_;
        current_index_ = 0;
    }

    /**
     * @brief Inserts an element to the specified index into the list.
     *
     * @param data Data to insert.
     * @param index Index to insert.
     */
    template <typename T>
    void List<T>::InsertInPlace(const T data, const int index)
    {
        if (index < 0)
            throw std::out_of_range("co::List<T>::Head(): Negative index");

        if (index > size_)
            throw std::out_of_range("co::List<T>::Head(): Index out of range");

        if (index == size_)
        {
            InsertTail(data);
            return;
        }

        std::shared_ptr<ListNode<T>> tmp = std::make_shared<ListNode<T>>(data);
        std::shared_ptr<ListNode<T>> current = current_;
        TransversalInfo transversal_info = GetTransversalInfo(index);

        switch (transversal_info.start_node)
        {
        case TransversalStartNode::HEAD:
            current = head_;
            current_index_ = 0;
            break;
        case TransversalStartNode::TAIL:
            current = tail_;
            current_index_ = size_ - 1;
            break;
        }

        int counter = 0;
        while (current)
        {
            if (counter == transversal_info.distance)
            {
                std::shared_ptr<ListNode<T>> prev = current->prev;

                if (prev)
                {
                    prev->next = tmp;
                    tmp->prev = prev;
                }
                else
                    head_ = tmp;

                current->prev = tmp;
                tmp->next = current;

                ++size_;
                return;
            }

            if (transversal_info.direction == TransversalDirection::RIGHT)
            {
                current = current->next;
                ++current_index_;
            }
            else
            {
                current = current->prev;
                --current_index_;
            }
            ++counter;
        }
    }

    /**
     * @brief Inserts an element to the end of the list.
     *
     * @param data Data to insert.
     */
    template <typename T>
    void List<T>::InsertTail(const T data)
    {
        std::shared_ptr<ListNode<T>> tmp = std::make_shared<ListNode<T>>(data);
        std::shared_ptr<ListNode<T>> current = tail_;

        if (size_ == 0)
        {
            head_ = tmp;
            tail_ = tmp;
        }
        else
        {
            current->next = tmp;
            tmp->prev = current;
            tail_ = tmp;
        }
        ++size_;
        current_ = tail_;
        current_index_ = size_ - 1;
    }

    /**
     * @brief Removes an element from the start of the list.
     */
    template <typename T>
    void List<T>::RemoveHead()
    {
        if (size_ < 1)
            return;

        if (size_ == 1)
        {
            Clear();
            return;
        }

        std::shared_ptr<ListNode<T>> tmp = head_;
        head_ = head_->next;
        tmp->next = nullptr; // clean up `next` ptr from head
        head_->prev = nullptr;

        --size_;
        current_ = head_;
        current_index_ = 0;
    }

    /**
     * @brief Removes an element from the specified index from the list.
     *
     * @param index Index to remove.
     */
    template <typename T>
    void List<T>::RemoveInPlace(const int index)
    {
        if (index < 0)
            throw std::out_of_range("co::List<T>::Head(): Negative index");

        if (index >= size_)
            throw std::out_of_range("co::List<T>::RemoveInPlace(): Index out of range");

        if (index == size_ - 1)
        {
            RemoveTail();
            return;
        }

        std::shared_ptr<ListNode<T>> current = current_;
        TransversalInfo transversal_info = GetTransversalInfo(index);

        switch (transversal_info.start_node)
        {
        case TransversalStartNode::HEAD:
            current = head_;
            current_index_ = 0;
            break;
        case TransversalStartNode::TAIL:
            current = tail_;
            current_index_ = size_ - 1;
            break;
        }

        int counter = 0;
        while (current)
        {
            if (index == counter)
            {
                std::shared_ptr<ListNode<T>> prev = current->prev;
                std::shared_ptr<ListNode<T>> next = current->next;

                if (prev)
                    prev->next = next;
                else
                    head_ = next;

                if (next)
                    next->prev = prev;
                else
                    tail_ = prev;

                current->prev = nullptr;
                current->next = nullptr;
                --size_;
                return;
            }

            if (transversal_info.direction == TransversalDirection::RIGHT)
            {
                current = current->next;
                ++current_index_;
            }
            else
            {
                current = current->prev;
                --current_index_;
            }
            ++counter;
        }
    }

    /**
     * @brief Removes an element from the end of the list.
     */
    template <typename T>
    void List<T>::RemoveTail()
    {
        if (size_ < 1)
            return;

        if (size_ == 1)
        {
            Clear();
            return;
        }

        std::shared_ptr<ListNode<T>> current = tail_;
        tail_ = current->prev;
        tail_->next = nullptr;
        current->prev = nullptr;
        --size_;
        current_ = tail_;
        current_index_ = size_ - 1;
    }

    /**
     * @brief Removes an element from the end of the list and returns it.
     *
     * @return T Element popped.
     */
    template <typename T>
    T List<T>::Pop()
    {
        if (size_ == 0)
            throw std::out_of_range("co::List<T>::Pop(): List is empty");

        T data_copy = tail_->data;
        RemoveTail();
        return data_copy;
    }

    /**
     * @brief Removes an element from the start of the list and returns it.
     *
     * @return T Element polled.
     */
    template <typename T>
    T List<T>::Poll()
    {
        if (size_ == 0)
            throw std::out_of_range("co::List<T>::Poll(): List is empty");

        T data_copy = head_->data;
        RemoveHead();
        return data_copy;
    }

    // Operations
    /**
     * @brief Searches the list for a matching `data`.
     *
     * @param data Data to be matched.
     * @return int Index of the match in the list. Returns -1 if not found.
     */
    template <typename T>
    int List<T>::Search(const T data)
    {
        int counter = 0;
        current_ = head_;

        while (current_)
        {
            if (current_->data == data)
            {
                return counter;
            }

            current_ = current_->next;
            ++current_index_;
            ++counter;
        }

        return -1;
    }

    /**
     * @brief Searches the list for a matching `data`.
     *
     * @param data Data to be matched.
     * @param start_index Starting index of search.
     * @return int Index of the match in the list. Returns -1 if not found.
     */
    template <typename T>
    int List<T>::Search(const T data, const int start_index)
    {
        int counter = 0;
        current_ = head_;

        while (current_)
        {
            if (current_->data == data)
            {
                if (counter >= start_index)
                {
                    return counter;
                }
            }

            current_ = current_->next;
            ++current_index_;
            ++counter;
        }

        return -1;
    }

    /**
     * @brief Searches the list for a matching `data`.
     *
     * @param data Data to be matched.
     * @param func Comparison function to be used in the search.
     * @return int Index of the match in the list. Returns -1 if not found.
     */
    template <typename T>
    template <class Compare>
    int List<T>::Search(const T data, Compare func)
    {
        int counter = 0;
        current_ = head_;

        while (current_)
        {
            if (func(current_->data, data))
            {
                return counter;
            }

            current_ = current_->next;
            ++current_index_;
            ++counter;
        }

        return -1;
    }

    /**
     * @brief Searches the list for a matching `data`.
     *
     * @param data Data to be matched.
     * @param func Comparison function to be used in the search.
     * @param start_index Starting index of search.
     * @return int Index of the match in the list. Returns -1 if not found.
     */
    template <typename T>
    template <class Compare>
    int List<T>::Search(const T data, Compare func, const int start_index)
    {
        int counter = 0;
        current_ = head_;

        while (current_)
        {
            if (func(current_->data, data))
            {
                if (counter >= start_index)
                {
                    return counter;
                }
            }

            current_ = current_->next;
            ++current_index_;
            ++counter;
        }

        return -1;
    }

    /**
     * @brief Swaps the position of two elements in the list.
     *
     * @param a Index of first element.
     * @param b Index of second element.
     */
    template <typename T>
    void List<T>::Swap(const int a, const int b)
    {
        if (a > size_ || b > size_)
            throw std::out_of_range("co::List<T>::Swap(): Index out of range");

        if (a == b)
            throw std::logic_error("co::List<T>::Swap(): Logic error; same index given");

        std::shared_ptr<ListNode<T>> a_node;
        std::shared_ptr<ListNode<T>> b_node;
        T tmp_data;
        std::shared_ptr<ListNode<T>> current = head_;

        int counter = 0;
        while (current)
        {
            if (counter == a)
                a_node = current;

            if (counter == b)
                b_node = current;

            if (a_node && b_node)
                break;

            current = current->next;
            ++counter;
        }

        tmp_data = a_node->data;

        a_node->data = b_node->data;
        b_node->data = tmp_data;
    }

    /**
     * @brief Sorts the current list.
     *
     * Does not return a copy but performs the sort on the list.
     */
    template <typename T>
    void List<T>::Sort()
    {
        if (size_ == 0)
            throw std::length_error("co::List<T>::Sort(): List is empty");

        *this = Sorter(*this);
    }

    /**
     * @brief Sorts the current list
     *
     * Does not return a copy but performs the sort on the list.
     *
     * @param func Comparison function in the form of `bool foo(const T& lhs, const T& rhs)`
     */
    template <typename T>
    template <class Compare> // trying to use a named requirement, might fail if compiler doesnt like this
    void List<T>::Sort(Compare func)
    {
        if (size_ == 0)
            throw std::length_error("co::List<T>::Sort(): List is empty");

        *this = Sorter(*this, func);
    }

    /**
     * @brief Overload for assignment operator to perform deep copy of a list.
     *
     * @param source List to be deep copied.
     */
    template <typename T>
    void List<T>::operator=(const List<T>& source)
    {
        Clear();

        for (int i = 0; i < source.Size(); ++i)
        {
            InsertTail(source.At(i));
        }
    }

    /**
     * @brief Merge sort main routine.
     *
     * @param input_list List to be broken down to sublists.
     * @return List<T> Merged list.
     */
    template <typename T>
    List<T> List<T>::Sorter(List<T> input_list)
    {
        // No sorting needed
        if (input_list.Size() <= 1)
            return input_list;

        // Divide List into sublists
        List<T> left_list;
        List<T> right_list;

        for (int i = 0; i < input_list.Size(); ++i)
        {
            T data_copy = input_list.At(i);
            if (i < input_list.Size() / 2)
            {
                left_list.InsertTail(data_copy);
            }
            else
            {
                right_list.InsertTail(data_copy);
            }
        }

        // Recursively sort the sublists
        left_list = Sorter(left_list);
        right_list = Sorter(right_list);

        // Merge sorted sublists
        return Merge(left_list, right_list);
    }

    /**
     * @brief Merge sort main routine.
     *
     * @param input_list List to be broken down to sublists.
     * @param func Comparison function to be used for sorting.
     * @return List<T> Merged list.
     */
    template <typename T>
    template <class Compare>
    List<T> List<T>::Sorter(List<T> input_list, Compare func)
    {
        // No sorting needed
        if (input_list.Size() <= 1)
            return input_list;

        // Divide List into sublists
        List<T> left_list;
        List<T> right_list;

        for (int i = 0; i < input_list.Size(); ++i)
        {
            if (i < input_list.Size() / 2)
            {
                T data_copy = input_list.At(i);
                left_list.InsertTail(data_copy);
            }
            else
            {
                T data_copy = input_list.At(i);
                right_list.InsertTail(data_copy);
            }
        }

        // Recursively sort the sublists
        left_list = Sorter(left_list, func);
        right_list = Sorter(right_list, func);

        // Merge sorted sublists
        return Merge(left_list, right_list, func);
    }

    /**
     * @brief Merge sort subroutine. Sorts and merges two `List<T>`
     *
     * @tparam T Type used for List<T>
     * @param left_list (Sorted) Left list to be merged
     * @param right_list (Sorted) Right list to be merged
     * @return List<T> Sorted and merged list of `left_list` and `right_list`
     */
    template <typename T>
    List<T> List<T>::Merge(List<T> left_list, List<T> right_list)
    {
        List<T> return_list;

        while (left_list.Size() != 0 && right_list.Size() != 0)
        {
            if (left_list.Head() < right_list.Head()) // Normal comparison
            {
                T data_copy = left_list.Head();
                return_list.InsertTail(data_copy);
                left_list.RemoveHead();
            }
            else
            {
                T data_copy = right_list.Head();
                return_list.InsertTail(data_copy);
                right_list.RemoveHead();
            }
        }

        // In the case where the lists were not balanced, e.g. left list size 4, right list size 3
        while (left_list.Size() != 0)
        {
            T data_copy = left_list.Head();
            return_list.InsertTail(data_copy);
            left_list.RemoveHead();
        }

        while (right_list.Size() != 0)
        {
            T data_copy = right_list.Head();
            return_list.InsertTail(data_copy);
            right_list.RemoveHead();
        }

        return return_list;
    }

    /**
     * @brief Merge sort subroutine. Sorts and merges two `List<T>`
     *
     * @tparam T Type used for List<T>
     * @param left_list (Sorted) Left list to be merged
     * @param right_list (Sorted) Right list to be merged
     * @return List<T> Sorted and merged list of `left_list` and `right_list`
     */
    template <typename T>
    template <class Compare>
    List<T> List<T>::Merge(List<T> left_list, List<T> right_list, Compare func)
    {
        List<T> return_list;

        while (left_list.Size() != 0 && right_list.Size() != 0)
        {
            if (func(left_list.Head(), right_list.Head())) // Use of `func`
            {
                T data_copy = left_list.Head();
                return_list.InsertTail(data_copy);
                left_list.RemoveHead();
            }
            else
            {
                T data_copy = right_list.Head();
                return_list.InsertTail(data_copy);
                right_list.RemoveHead();
            }
        }

        // In the case where the lists were not balanced, e.g. left list size 4, right list size 3
        while (left_list.Size() != 0)
        {
            T data_copy = left_list.Head();
            return_list.InsertTail(data_copy);
            left_list.RemoveHead();
        }

        while (right_list.Size() != 0)
        {
            T data_copy = right_list.Head();
            return_list.InsertTail(data_copy);
            right_list.RemoveHead();
        }

        return return_list;
    }

    /**
     * @brief Gets information on the shortest possible transversal path to `index`.
     *
     * @param index Target index.
     * @return const TransversalInfo Information on shortest transversal path.
     */
    template <typename T>
    const TransversalInfo List<T>::GetTransversalInfo(const int index) const
    {
        TransversalInfo return_transversal_info;
        int difference_head = index;
        int difference_tail = (size_ - 1) - index;
        int difference_current = abs(current_index_ - index);

        if (difference_head > difference_tail)
        {
            if (difference_tail > difference_current)
            {
                return_transversal_info.start_node = TransversalStartNode::CURRENT;
                return_transversal_info.distance = difference_current;
                difference_current = current_index_ - index;
                if (difference_current < 0)
                    return_transversal_info.direction = TransversalDirection::LEFT;
                else
                    return_transversal_info.direction = TransversalDirection::RIGHT;
            }
            else
            {
                return_transversal_info.start_node = TransversalStartNode::TAIL;
                return_transversal_info.distance = difference_tail;
                return_transversal_info.direction = TransversalDirection::LEFT;
            }
        }
        else
        {
            if (difference_head > difference_current)
            {
                return_transversal_info.start_node = TransversalStartNode::CURRENT;
                return_transversal_info.distance = difference_current;
                difference_current = current_index_ - index;
                if (difference_current < 0)
                    return_transversal_info.direction = TransversalDirection::LEFT;
                else
                    return_transversal_info.direction = TransversalDirection::RIGHT;
            }
            else
            {
                return_transversal_info.start_node = TransversalStartNode::HEAD;
                return_transversal_info.distance = difference_head;
                return_transversal_info.direction = TransversalDirection::RIGHT;
            }
        }

        return return_transversal_info;
    }

} // namespace co

#endif // LIST_HPP
