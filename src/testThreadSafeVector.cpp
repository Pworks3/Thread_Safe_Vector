#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "threadSafeVector.hpp"

#include <thread>

TEST_CASE("Single Thread Behavior: Default API", "[st_API]")
{
    // Creation of two vector objects for testing
    ThreadSafeVector<int> testVector0;
    ThreadSafeVector<int> testVector1(10);

    // Initialization testing for default vector
    REQUIRE(testVector0.empty() == true);
    REQUIRE(testVector0.size() == 0);
    REQUIRE(testVector0.capacity() == 0);
    REQUIRE_THROWS_AS(testVector0.at(0), std::out_of_range);
    REQUIRE_THROWS_AS(testVector0.at(0) = 5, std::out_of_range);

    // Initialization testing for custom vector
    REQUIRE(testVector1.empty() == true);
    REQUIRE(testVector1.size() == 0);
    REQUIRE(testVector1.capacity() == 10);
    REQUIRE_THROWS_AS(testVector1.at(0), std::out_of_range);
    REQUIRE_THROWS_AS(testVector1.at(0) = 5, std::out_of_range);
}

TEST_CASE("Singe Thread Behavior: Addition and Removal API", "[st_API]")
{
    // Creation of two vector objects for testing
    ThreadSafeVector<int> testVector0;
    ThreadSafeVector<int> testVector1(10);

    // Initialization testing for default vector
    REQUIRE(testVector0.empty() == true);
    REQUIRE(testVector0.size() == 0);
    REQUIRE(testVector0.capacity() == 0);
    REQUIRE_THROWS_AS(testVector0.at(0), std::out_of_range);
    REQUIRE_THROWS_AS(testVector0.at(0) = 5, std::out_of_range);

    // Initialization testing for custom vector
    REQUIRE(testVector1.empty() == true);
    REQUIRE(testVector1.size() == 0);
    REQUIRE(testVector1.capacity() == 10);
    REQUIRE_THROWS_AS(testVector1.at(0), std::out_of_range);
    REQUIRE_THROWS_AS(testVector1.at(0) = 5, std::out_of_range);

    // Populate the default vector
    testVector0.push_back(45);
    testVector0.push_back(12);
    testVector0.push_back(-123);

    // Populate the custom vector
    testVector1.push_back(45);
    testVector1.push_back(12);
    testVector1.push_back(-123);

    // Addition testing for default vector
    REQUIRE(testVector0.empty() == false);
    REQUIRE(testVector0.size() == 3);
    REQUIRE(testVector0.at(0) == 45);
    REQUIRE(testVector0.at(1) == 12);
    REQUIRE(testVector0.at(2) == -123);

    // Addition testing for custom vector
    REQUIRE(testVector1.empty() == false);
    REQUIRE(testVector1.size() == 3);
    REQUIRE(testVector1.at(0) == 45);
    REQUIRE(testVector1.at(1) == 12);
    REQUIRE(testVector1.at(2) == -123);

    // Remove elements from the default vector
    testVector0.pop_back();
    testVector0.pop_back();

    // Remove elements from the custom vector
    testVector1.pop_back();
    testVector1.pop_back();

    // Removal testing for default vector
    REQUIRE(testVector0.empty() == false);
    REQUIRE(testVector0.size() == 1);
    REQUIRE(testVector0.at(0) == 45);
    REQUIRE_THROWS_AS(testVector0.at(1) == 12, std::out_of_range);
    REQUIRE_THROWS_AS(testVector0.at(2) == -123, std::out_of_range);

    // Removal testing for custom vector
    REQUIRE(testVector1.empty() == false);
    REQUIRE(testVector1.size() == 1);
    REQUIRE(testVector1.at(0) == 45);
    REQUIRE_THROWS_AS(testVector1.at(1) == 12, std::out_of_range);
    REQUIRE_THROWS_AS(testVector1.at(2) == -123, std::out_of_range);
}

bool contains(const ThreadSafeVector<int>& vec, const int& element)
{
    for(std::size_t i = 0; i < vec.size(); ++i)
    {
        if(vec.at(i) == element)
        {
            return true;
        }
    }

    return false;
}

void additionThread(ThreadSafeVector<int>& vec, const int& element)
{
    vec.push_back(element);
}

void removalThread(ThreadSafeVector<int>& vec)
{
    vec.pop_back();
}

TEST_CASE("Multi Thread Behavior: Addition and Removal API", "[mt_API]")
{
    // Creation of a new vector that will be shared between three threads
    ThreadSafeVector<int> testVector0;

    // Initialization testing for default vector
    REQUIRE(testVector0.empty() == true);
    REQUIRE(testVector0.size() == 0);
    REQUIRE(testVector0.capacity() == 0);
    REQUIRE_THROWS_AS(testVector0.at(0), std::out_of_range);
    REQUIRE_THROWS_AS(testVector0.at(0) = 5, std::out_of_range);

    // Spinning up two threads
    std::thread t0(&additionThread, std::ref(testVector0), 50);
    std::thread t1(&additionThread, std::ref(testVector0), -54);

    // Adding an element from the main thread
    testVector0.push_back(-1231);

    // Wait for all threads to join
    t0.join();
    t1.join();

    // Test after thread additions for the vector
    REQUIRE(testVector0.empty() == false);
    REQUIRE(testVector0.size() == 3);
    REQUIRE(testVector0.capacity() != 0);

    // Threads could have executed in any order so we just check that the elements exist
    REQUIRE(contains(testVector0, 50) == true);
    REQUIRE(contains(testVector0, -54) == true);
    REQUIRE(contains(testVector0, -1231) == true);

    // Spinning up two threads
    std::thread t2(&removalThread, std::ref(testVector0));
    std::thread t3(&removalThread, std::ref(testVector0));

    // Removing an element from the main thread
    testVector0.pop_back();

    // Wait for all threads to join
    t2.join();
    t3.join();

    // Test after thread additions for the vector
    REQUIRE(testVector0.empty() == true);
    REQUIRE(testVector0.size() == 0);
    REQUIRE(testVector0.capacity() != 0);
    REQUIRE_THROWS_AS(testVector0.at(0), std::out_of_range);
    REQUIRE_THROWS_AS(testVector0.at(0) = 5, std::out_of_range);
    REQUIRE_THROWS_AS(testVector0.at(1) == 50, std::out_of_range);
}

