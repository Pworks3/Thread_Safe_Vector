#include "threadSafeVector.hpp"

// Constructors
//-------------------------------------

    // Parameterized Constructor
    template<typename dataType>
    ThreadSafeVector<dataType>::ThreadSafeVector(std::size_t size)
    {
        dataVector.reserve(size);
    }

//-------------------------------------

// Capacity
//-------------------------------------

    // Check if Vector is empty
    template<typename dataType>
    bool ThreadSafeVector<dataType>::empty() const
    {
        // Lock the mutex, unlocks when call is out of scope
        std::lock_guard<std::mutex> lock(dataMutex);

        return dataVector.empty();
    }

    // Return the number of elements in the vector
    template<typename dataType>
    std::size_t ThreadSafeVector<dataType>::size() const
    { 
        // Lock the mutex, unlocks when call is out of scope
        std::lock_guard<std::mutex> lock(dataMutex);

        return dataVector.size();
    }

    // Return the capacity of the vector
    template<typename dataType>
    std::size_t ThreadSafeVector<dataType>::capacity() const
    {
        // Lock the mutex, unlocks when call is out of scope
        std::lock_guard<std::mutex> lock(dataMutex);

        return dataVector.capacity();
    }

//-------------------------------------

// Element Access
//-------------------------------------

    // Returns a reference to the element at desired index, throws std::out_of_range if index > size
    template<typename dataType>
    dataType& ThreadSafeVector<dataType>::at(std::size_t index)
    {
        // Lock the mutex, unlocks when call is out of scope
        std::lock_guard<std::mutex> lock(dataMutex);

        return dataVector.at(index);
    }

    // Returns a constant reference to the element at desired index, throws std::out_of_range if index > size
    template<typename dataType>
    const dataType& ThreadSafeVector<dataType>::at(std::size_t index) const
    {
        // Lock the mutex, unlocks when call is out of scope
        std::lock_guard<std::mutex> lock(dataMutex);

        return dataVector.at(index);
    }

//-------------------------------------

// Element Addition and Removal
//-------------------------------------

    // Add an element to the back of the vector
    template<typename dataType>
    void ThreadSafeVector<dataType>::push_back(const dataType& newElement)
    {
        // Lock the mutex
        std::unique_lock<std::mutex> lock(dataMutex);

        // Push the new element to the back
        dataVector.push_back(newElement);

        // Unlock the mutex
        lock.unlock();
    }

    // Remove an element from the back of the vector
    template <typename dataType>
    void ThreadSafeVector<dataType>::pop_back()
    {
        // Lock the mutex
        std::unique_lock<std::mutex> lock(dataMutex);

        // Pop the element from the rear of the vector
        dataVector.pop_back();

        // Unlock the mutex
        lock.unlock();
    }

//-------------------------------------