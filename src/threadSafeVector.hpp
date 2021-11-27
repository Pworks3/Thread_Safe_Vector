#ifndef THREAD_SAFE_VECTOR_HPP
#define THREAD_SAFE_VECTOR_HPP

#include <vector>
#include <mutex>
#include <cstddef>

template <typename dataType>
class ThreadSafeVector
{
    public:

        // Constructors
        //-------------------------------------

            // Default
            ThreadSafeVector() = default;

            // Parameterized
            /*
             * Reserves space "size" in memory for the vector
             */
            ThreadSafeVector(std::size_t size);

        //-------------------------------------

        // Capacity
        //-------------------------------------

            // Check if container is empty
            bool empty() const;

            // Return the number of elements in the container
            std::size_t size() const;

            // Return the capacity of the container
            std::size_t capacity() const;

        //-------------------------------------

        // Element Access
        //-------------------------------------
            
            // Returns a reference to the element at desired index, throws std::out_of_range if index > size
            dataType& at(std::size_t index);

            // Returns a constant reference to the element at desired index, throws std::out_of_range if index > size
            const dataType& at(std::size_t index) const;

        //-------------------------------------

        // Element Addition and Removal
        //-------------------------------------

            // Add an element to the back of the vector
            void push_back(const dataType& newElement);

            // Remove an element from the back of the vector
            void pop_back();

        //-------------------------------------


        // Deletions
        //-------------------------------------
            
            // Copy Constructor
            ThreadSafeVector(const ThreadSafeVector<dataType>& other) = delete;

            // Copy Assignment Operator
            ThreadSafeVector<dataType>& operator=(const ThreadSafeVector<dataType>& other) = delete;

        //-------------------------------------

    private:

        // Data Structures
        std::vector<dataType> dataVector;

        // Thread Safety
        mutable std::mutex dataMutex;
};


#include "threadSafeVector.tpp"
#endif