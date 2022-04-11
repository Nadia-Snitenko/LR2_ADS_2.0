﻿#include <iostream>
#include <vector>
#include <time.h>

using namespace std;

struct stats {
	size_t comparison_count = 0; // количество сравнений
	size_t copy_count = 0; // количество копий
};

stats selection_sort(vector<int>& data) {
	stats stat;
	size_t min;
	for (size_t i = 0; i < data.size() - 1; i++) {
		min = i;
		for (size_t j = i + 1; j < data.size(); j++) {
			stat.comparison_count++;
			if (data[j] < data[min]) min = j;
		}
		if (data[i] > data[min]) { swap(data[i], data[min]); stat.copy_count++; }
	}
	return stat;
};

stats quick_sort_(vector<int>& vec, size_t left, size_t right) {
	stats stat;
	size_t i = left, j = right;
	int pivot = vec[left];
	while (i < j) // пока границы не сомкнутся
	{
		while ((vec[j] >= pivot) && (i < j))
			j--; // сдвигаем правую границу пока элемент [j] больше [pivot]
		if (i != j) // если границы не сомкнулись
		{
			vec[i] = vec[j]; // перемещаем элемент [j] на место разрешающего
			i++; // сдвигаем левую границу вправо
		}
		while ((vec[i] <= pivot) && (i < j))
			i++; // сдвигаем левую границу пока элемент [i] меньше [pivot]
		if (i != j) // если границы не сомкнулись
		{
			vec[j] = vec[i]; // перемещаем элемент [i] на место [j]
			j--; // сдвигаем правую границу влево
		}
	}
	vec[i] = pivot; // ставим разрешающий элемент на место
	pivot = i;
	if (left < pivot) // Рекурсивно вызываем сортировку для левой и правой части массива
		quick_sort_(vec, left, pivot - 1);
	if (right > pivot)
		quick_sort_(vec, pivot + 1, right);
	return stat;
};

stats quick_sort(vector<int>& data) { if (!data.empty()) return quick_sort_(data, 0, data.size() - 1); };

stats comb_sort(vector<int>& data)
{
	stats stat;
	double factor = 1.2473309; // фактор уменьшения
	int step = data.size() - 1; // шаг сортировки

	//Последняя итерация цикла, когда step==1 эквивалентна одному проходу сортировки пузырьком
	while (step >= 1) {
		for (int i = 0; i + step < data.size(); i++) {
			if (data[i] > data[i + step]) {
				swap(data[i], data[i + step]);
			}
		}
		step /= factor;
	}
	return stat;
};


void print(vector<int>& data) {
	for (auto i = data.begin(); i != data.end(); ++i) cout << *i << " ";
	cout << endl;
};

void fill(vector<int>& data, const size_t n) {
	for (size_t i = 0; i < n; i++) {
		data.push_back(rand() % 100);
	}
};

int main() {
	vector<int> v1, v2,v3;
	const size_t size = 10;

	srand(time(NULL));

	fill(v1,size);
	cout << "vector 1 before sort: ";
	print(v1);
	selection_sort(v1);
	cout << "vector 1 after selection sort: ";
	print(v1);
	cout << endl;

	fill(v2, size);
	cout << "vector 2 before sort: ";
	print(v2);
	quick_sort(v2);
	cout << "vector 2 after quick sort: ";
	print(v2);
	cout << endl;

	fill(v3, size);
	cout << "vector 3 before sort: ";
	print(v3);
	int m = sizeof(v3) / sizeof(v3[0]);
	comb_sort(v3);
	cout << "vector 3 after comb sort: ";
	print(v3);

	return 0;
}
















//Практика 1
//int main()
//{
//	size_t n= 5;
//	vector<int>v(n);
//	vector<int> v2;
//	for (auto i : v)
//	{
//		v.push_back(rand() % 101+1);
//
//	}
//	for (auto it = v.begin(); it != v.end(); it++) {
//		cout << *it << ' ';
//		if (!(*it % 2)) {
//			v2.push_back(*it);
//		}
//	}
//	cout << endl;
//	for (auto it2 = v2.begin(); it2 != v2.end(); it2++) {
//		cout << *it2 << ' ';
//	}
//	return 0;
//}


// Практика 2
//
//template<typename int>
//class list {
//	struct Node {
//		T data;
//		Node* next;
//		Node* prev;
//
//	}*head;
//	//, *tail;
//	//size_t size;
//public:
//	list() { 
//		//head = nullptr; 
//		head.next = &head; 
//		head.prev = &head;
//		size = 0; }
//	~list() {
//		while (head.next != &head){
//			Node* temp = head.next;
//			head.next = head.next->next;
//			delete temp;
//		}
//		head.prev = &head;
//	}
//	void Popfront() {
//		if (head.next = &head) throw "empty";
//		Node* temp = head.next;
//		temp->next->prev = temp->prev;
//		temp->prev->next = temp.next;
//		delete temp;
//	}
//	void Pushfront(const T& new_data) {
//		Node* new_elem = new Node;
//		new_elem->data = new_data;
//		new_elem->next = head.next;
//		new_elem->prev = &head; 
//		new_elem->next->prev = new_elem;
//		new_elem->prev->next = new_elem;
//	}
//	friend class iterator;
//	iterator begin() {
//		return iterator(this, head->next);
//	}
//	iterator end() {
//		return iterator(this, head);
//	}
//};
//template <typename T> 
//class iterator {
//	list<T>* cont; // указатель на сам контейнер
//	list<T>::node* current; // указатель на текущий элемент контейнера
//public:
//	iterator(list* new_cont, list <T> ::node* new_current) {
//		current = new_corrent;
//		cont = new_cont; 
//	}
//	iterator& operator++() {
//		current = current->next;
//		return*this;
//	}
//	bool operator ==(const iterator& rsh) {
//		if (current == rsh.current) return true;
//		else return false; 
//	}
//	bool operator!=(const iterator& rsh) {
//		return(!current == rhs.current);
//	}
//	T operator*() {
//		return current->data;
//	}
//};



// Практика 3
// 
//int main()
//{
//    list <double> nums;
//    nums.push_back(4.9);
//    nums.push_back(7.09);
//    nums.push_back(10.0);
//    nums.push_back(2.644);
//
//    for ( int i : nums) {
//        cout << i<<'\n';
//    }
//    return 0;
//
//}




//Практика 4
// 
//template<typename T>
//class stack {
//    unsigned int size,max_size;
//    T array;
//public:
//    stack(const unsigned int max_size) {
//        size = 0;
//        this->max_size = max_size;
//        array = new T[max_size];
//    }
//    ~stack() {
//        delete[] array;
//    }
//
//    T& top() {
//        if (size == 0) throw "empty";
//        return array[size - 1];
//    }
//
//    void push(const T new_el) {
//        if (size == max_size) throw "max size";
//        array[size] = new_el;
//        size++; 
//    }
//    stack& operator=(const stack& s) {
//        if (array == s.array) return *this;
//        size = s.size;
//        max_size = s.max_size;
//        delete[] = array;
//        array = new T[max_size];
//        for (int i = 0; i < size; i++)
//            array[i] = s.array[i];
//        return *this;
//    }
//};
//

