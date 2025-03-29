#pragma once
#include <iostream>
#include <vector>
#include <list>
#include <deque>
#include <climits>
#include <algorithm>
#include <ctime>
#include <cmath>

struct pairs {
    double num;
    std::vector<pairs> p;
};

struct graph {
    double num;
    std::list<graph> p;
};

class PmergeMe
{
private:
    std::list<unsigned int> _list;
    std::vector<unsigned int> _vector;
    PmergeMe();
    
    // Comparison counters
    size_t _vector_comparisons;
    size_t _list_comparisons;
    
public:
    PmergeMe(int argc,char *argv[]);
    PmergeMe(const PmergeMe &other);
    virtual ~PmergeMe();
    PmergeMe& operator=(const PmergeMe &other);
    

    size_t jacobsthal(size_t n);
    // Display methods
    void display(); // General display method
    void display(std::vector<pairs> out); // Helper method for vector display
    
    // Vector sort methods
    void vectorSort();
    std::vector<pairs> vector_sort(std::vector<pairs> arr);
    size_t BS_vec(std::vector<pairs> res, size_t right, int value);
    // size_t group_size(size_t n);
    
    // List sort methods
    void listSort();
    std::list<graph> list_sort(std::list<graph> arr);
    size_t BS_list(std::list<graph> res, size_t right, int value);
};