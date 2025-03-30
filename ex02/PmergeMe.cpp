#include "PmergeMe.hpp"

PmergeMe::PmergeMe() : _vector_comparisons(0), _list_comparisons(0) {}

PmergeMe::PmergeMe(int argc, char *argv[]) : _vector_comparisons(0), _list_comparisons(0) {
	std::cout << "Before: ";
	for (int i = 1; i < argc; ++i) {
		std::cout << argv[i] << " ";
	}
	std::cout << std::endl;

	for (int i = 1; i < argc; ++i) {
		char *endptr;
		long value = std::strtol(argv[i], &endptr, 10);
		
		if (*endptr != '\0' || value < 0) {
			throw std::runtime_error("Error: Invalid input. Only positive integers are allowed.");
		}
		_vector.push_back(static_cast<unsigned int>(value));
		_list.push_back(static_cast<unsigned int>(value));
	}


	clock_t start_vector = clock();
	vectorSort();
	clock_t end_vector = clock();

	clock_t start_list = clock();
	listSort();
	clock_t end_list = clock();

	double time_vector = static_cast<double>(end_vector - start_vector) / CLOCKS_PER_SEC * 1000000;
	double time_list = static_cast<double>(end_list - start_list) / CLOCKS_PER_SEC * 1000000;

	std::cout << "Time to process a range of " << _vector.size() << " elements with std::vector : " 
				<< time_vector << " us" << std::endl;
	std::cout << "Time to process a range of " << _list.size() << " elements with std::list : " 
				<< time_list << " us" << std::endl;

	std::cout << "Number of comparisons in std::vector: " << _vector_comparisons << std::endl;
	std::cout << "Number of comparisons in std::list: " << _list_comparisons << std::endl;
}

PmergeMe::PmergeMe(const PmergeMe &other) {
    *this = other;
}

PmergeMe::~PmergeMe() {
}

PmergeMe& PmergeMe::operator=(const PmergeMe &other) {
	if (this != &other) {
		_vector = other._vector;
		_list = other._list;
		_vector_comparisons = other._vector_comparisons;
		_list_comparisons = other._list_comparisons;
	}
	return *this;
}


void PmergeMe::display() {
	std::cout << "Vector: ";
	for (std::vector<unsigned int>::iterator it = _vector.begin(); it != _vector.end(); ++it) {
		std::cout << *it << " ";
	}
	std::cout << std::endl;

	std::cout << "List: ";
	for (std::list<unsigned int>::iterator it = _list.begin(); it != _list.end(); ++it) {
		std::cout << *it << " ";
	}
	std::cout << std::endl;
}

size_t PmergeMe::jacobsthal(size_t n) {
	return (std::pow(2, n + 1) - std::pow(-1, n) * 2) / 3;
}

size_t PmergeMe::BinarySearch_vector(std::vector<pairs> res, size_t right, int value) {
	size_t left = 0, mid;

	while (left <= right) {
		mid = left + (right - left) / 2;
		_vector_comparisons++;
		if (res[mid].num == value) {
			return mid;
		} 
		if (res[mid].num < value) {
			if (mid == right)
				return mid + 1;
			left = mid + 1;
		} else {
			if (mid == 0)
				return 0;
			right = mid - 1;
		}
	}
	return left;
}

std::vector<pairs> PmergeMe::vector_sort(std::vector<pairs> arr) {
	std::vector<pairs> res, big, small;

	if (arr.size() == 1)
		return arr;
	else if (arr.size() == 2) {
		_vector_comparisons++;
		if (arr[0].num > arr[1].num) {
			std::swap(arr[0], arr[1]);
			return arr;
		}
		return arr;
	}
	for (size_t i = 0; i < arr.size() - 1; i += 2) {
		_vector_comparisons++;
		if (arr[i].num > arr[i + 1].num) {
			arr[i].p.push_back(arr[i + 1]);
			big.push_back(arr[i]);
		} else {
			arr[i + 1].p.push_back(arr[i]);
			big.push_back(arr[i + 1]);
		}
	}
	res = vector_sort(big);
	if (res[0].p.size() == 0)
		return res;
	for (std::size_t i = 0; i < res.size(); i++) {
		small.push_back(res[i].p[res[i].p.size() - 1]);
		res[i].p.pop_back();
	}
	if (arr.size() % 2 != 0) {
		small.push_back(arr[arr.size() - 1]);
	}
	size_t	count = 1, group_passed = 0, groupsize;
	if (small.size() > 0) {
		res.insert(res.begin(), small[0]);
		small.erase(small.begin());
	}
	while (small.size() > 0) {
		groupsize = jacobsthal(count);
		if (groupsize > small.size())
			groupsize = small.size();
		for (size_t i = 0; i < groupsize; i++) {
			size_t	reverseIndex = groupsize - i - 1;
			size_t	right_side = 1 + group_passed * 2 + reverseIndex + i;
			size_t	insert_point = BinarySearch_vector(res, right_side, small[reverseIndex].num);
			res.insert(res.begin() + insert_point, small[reverseIndex]);
			small.erase(small.begin() + reverseIndex);
		}
		group_passed += groupsize;
		count++;
	}
	return res;
}

void PmergeMe::vectorSort() {
	std::vector<pairs> arr;
	
	for (std::vector<unsigned int>::iterator it = _vector.begin(); it != _vector.end(); it++) {
		pairs p;
		p.num = *it;
		arr.push_back(p);
	}
	std::vector<pairs> sorted = vector_sort(arr);
	_vector.clear();
	for (std::vector<pairs>::iterator it = sorted.begin(); it != sorted.end(); it++) {
		_vector.push_back(static_cast<unsigned int>((*it).num));
	}
}


size_t PmergeMe::BinarySearch_list(std::list<graph> res, size_t right, int value) {
	size_t left = 0, mid;

	while (left <= right) {
		mid = left + (right - left) / 2;
		
		std::list<graph>::iterator it = res.begin();
		std::advance(it, mid);
		
		_list_comparisons++;
		if (it->num == value) {
			return mid;
		}
		
		if (it->num < value) {
			if (mid == right)
				return mid + 1;
			left = mid + 1;
		} else {
			if (mid == 0)
				return 0;
			right = mid - 1;
		}
	}
	return left;
}
std::list<graph> PmergeMe::list_sort(std::list<graph> lis)
{
	if (lis.size() == 1)
		return lis;
	else if (lis.size() == 2)
	{
		_list_comparisons++;
		std::list<graph>::iterator it = lis.begin();
		std::list<graph>::iterator jt = it;
		++jt;
		if (it->num > jt->num)
		{
			graph temp = *it;
			*it = *jt;
			*jt = temp;
		}
		return lis;
	}

	std::list<graph> big;
	{
		std::list<graph>::iterator it = lis.begin();
		while (it != lis.end()) 
		{
			std::list<graph>::iterator jt = it;
			++jt;
			if (jt == lis.end())
			{
				break;
			}
			_list_comparisons++;
			if (it->num > jt->num)
			{
				it->p.push_back(*jt); 
				big.push_back(*it);
			}
			else
			{
				jt->p.push_back(*it); 
				big.push_back(*jt);
			}
			++it; 
			++it;
		}
	}

	std::list<graph> res = list_sort(big);

	if (!res.empty() && res.begin()->p.empty())
		return res;
	std::list<graph> small;
	{
		for (std::list<graph>::iterator rit = res.begin(); rit != res.end(); ++rit)
		{
			graph last = rit->p.back();
			rit->p.pop_back();
			small.push_back(last);
		}
	}

	if (lis.size() % 2 != 0)
	{
		graph leftover = lis.back();
		small.push_back(leftover);
	}

	size_t count         = 1;
	size_t group_passed  = 0;

	if (!small.empty())
	{
		res.insert(res.begin(), small.front());
		small.pop_front();
	}

	while (!small.empty())
	{
		size_t groupsize = jacobsthal(count);
		if (groupsize > small.size())
			groupsize = small.size();

		for (size_t i = 0; i < groupsize; ++i)
		{
			const size_t reverseIndex   = groupsize - i - 1;
			const size_t right_side = 1 + group_passed*2 + reverseIndex + i;

			std::list<graph>::iterator st = small.begin();
			for (size_t s = 0; s < reverseIndex; ++s)
				++st;

			graph val = *st; 
			small.erase(st);

			size_t insert_index = BinarySearch_list(res, right_side, val.num);

			std::list<graph>::iterator ins = res.begin();
			for (size_t j = 0; j < insert_index; ++j)
				++ins;
			res.insert(ins, val);
		}
		group_passed += groupsize;
		count++;
	}
	return res;
}

void PmergeMe::listSort() {
	std::list<graph> lis;

	for (std::list<unsigned int>::iterator it = _list.begin(); it != _list.end(); it++) {
		graph p;
		p.num = *it;
		lis.push_back(p);
	}
	std::list<graph> sorted = list_sort(lis);
	_list.clear();
	for (std::list<graph>::iterator it = sorted.begin(); it != sorted.end(); it++) {
		_list.push_back(static_cast<unsigned int>((*it).num));
	}
}
