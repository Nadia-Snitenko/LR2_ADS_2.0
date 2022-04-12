#include <iostream>
#include <vector>
#include <time.h>
#include<cmath>
#include <thread>   // this_thread::sleep_for – поток приостанавливает выполнение на некий, заданный промежуток времени
#include <chrono>   // chrono::seconds
using namespace std;

struct steady_clock;
const double factor = 1.2473309; // фактор уменьшения
const double _factor = 1/(1-exp(-1.62));

struct stats {
	size_t comparison_count = 0; // количество сравнений
	size_t copy_count = 0; // количество копий
};

template<typename T, typename TCompare = std::less<T>>
void Swap(T& i,T& j) {
	T temp = i;
	i = j;
	j = temp;
}

template<typename T, typename TCompare = std::less<T>>
stats selection_sort(vector<T>& data) {
	stats stat;
	size_t min;

	for (size_t i = 0; i < data.size() - 1; i++) {
		min = i;

		for (size_t j = i + 1; j < data.size(); j++) {
			stat.comparison_count++;
			if (data[j] < data[min]) min = j;
		}

		stat.comparison_count++;
		if (data[i] > data[min]) { 
			stat.copy_count++; Swap(data[i], data[min]); 
		}
	}
	return stat;
};

template<typename T, typename TCompare = std::less<T>>
stats quick_sort_(vector<T>& vec, size_t left, size_t right) {
	stats stat;
	long long i = left, j = right;
	T pivot = vec[left];
	stat.copy_count++;
	
	while (i < j) // пока границы не сомкнутся
	{
		stat.comparison_count++;
		while ((vec[j] >= pivot) && (i < j)) {
			stat.comparison_count++; 
			j--; // сдвигаем правую границу пока элемент [j] больше [pivot]
		}
		stat.comparison_count++; //+1 сравнение при выходе из цикла

		stat.comparison_count++;
		if (i != j) // если границы не сомкнулись
		{
			stat.copy_count++;
			vec[i] = vec[j]; // перемещаем элемент [j] на место разрешающего
			i++; // сдвигаем левую границу вправо
		}

		while ((vec[i] <= pivot) && (i < j)) {
			stat.comparison_count++; //+1
			i++; // сдвигаем левую границу пока элемент [i] меньше [pivot]
		}
		stat.comparison_count++; //+1 сравнение при выходе из цикла

		stat.comparison_count++;
		if (i != j) // если границы не сомкнулись
		{
			stat.copy_count++;
			vec[j] = vec[i]; // перемещаем элемент [i] на место [j]
			j--; // сдвигаем правую границу влево
		}
	}
	stat.comparison_count++;//+1 сравнение при выходе из цикла

	stat.copy_count++;
	vec[i] = pivot; // ставим разрешающий элемент на место
	pivot = i;

	stat.comparison_count++;
	if (left < pivot) // Рекурсивно вызываем сортировку для левой и правой части массива
		quick_sort_(vec, left, pivot - 1);

	stat.comparison_count++; //+1 сравнение при выходе из цикла
	if (right > pivot)
		quick_sort_(vec, pivot + 1, right);

	return stat;
};

template<typename T, typename TCompare = std::less<T>>
stats quick_sort(vector<T>& data) { if (!data.empty()) return quick_sort_(data, 0, data.size() - 1); };

template<typename T, typename TCompare = std::less<T>>
stats comb_sort(vector<T>& data)
{
	stats stat;
	int step = data.size() - 1; // шаг сортировки

	//Последняя итерация цикла, когда step==1 эквивалентна одному проходу сортировки пузырьком
	while (step >= 1) {
		for (int i = 0; i + step < data.size(); i++){

			stat.comparison_count++; 
			if (data[i] > data[i + step]) {

				stat.copy_count++;
				Swap(data[i], data[i + step]);
			}
		}
		step /= factor;
	}
	return stat;
};

template<typename T, typename TCompare = std::less<T>>
void print(vector<T>& data) {
	for (auto i = data.begin(); i != data.end(); ++i) cout << *i << " ";
	cout << endl;
};

template<typename T, typename TCompare = std::less<T>>
void fill(vector<T>& data, const size_t n) {
	for (size_t i = 0; i < n; i++) {
		data.push_back(rand()%100);
	}
};

template<typename T, typename TCompare = std::less<T>>
void fill_increasing(vector<T>& data, const size_t n) {
	for (size_t i = 0; i < n; i++) {
		data.push_back(i);
	}
};

template<typename T, typename TCompare = std::less<T>>
void fill_decreasing(vector<T>& data, const size_t n) {
	for (size_t i = n; i >0 ; i--) {
		data.push_back(i);
	}
};

template<typename T, typename TCompare = std::less<T>>
class V {
private:
	size_t size;
	vector<T> v;
	stats s;
public:
	V() {
		size = 0;
	}
	V(size_t _size) {
		size = _size;
		//fill(v, size);
		//fill_increasing(v, size);
		fill_decreasing(v, size);
	}
	~V() {
		v.clear();
		size = 0;
	}

	void _selection_sort()
	{
		s=selection_sort(v);
	}
	void _quick_sort()
	{
		s = quick_sort(v);
	}
	void _comb_sort()
	{
		s = comb_sort(v);
	}

	void _print()
	{
		print(v);
	}
	void print_state()
	{
		cout<< s.comparison_count << "         " << s.copy_count << endl;
	}
	size_t _comparison_count()
	{
		return s.comparison_count;
	}
	size_t _copy_count()
	{
		return s.copy_count;
	}
};


int main() {
	chrono::steady_clock::time_point begin = chrono::steady_clock::now();
	chrono::steady_clock::time_point end = chrono::steady_clock::now();
	srand(time(NULL));
	const size_t size = 4000;
	
	vector<V<int>> VV;
	size_t c1, c2;
	c1 = c2 = 0;

	begin = chrono::steady_clock::now();
	for (size_t i = 0; i < 100; i++) {
		VV.push_back(V<int>(size));
		//VV[i]._print();
		VV[i]._selection_sort();
		c1 += VV[i]._comparison_count();
		c2+= VV[i]._copy_count();
	}
	c1 /= 100;
	c2 /= 100;

	cout <<"for "<<size<<" elements:\n";
	cout << "sort  "  <<"||" << "  comparison count " << "||" << "copy count " << "\n";
	cout << "____________________________________________\n";
	cout << "selection:"<<'\t' << c1 << '\t' << '\t' << c2 << endl;

	end = std::chrono::steady_clock::now();
	cout << "Diff(ms) = " << chrono::duration_cast<chrono::milliseconds>(end - begin).count() << endl;

	VV.clear();
	c1 = c2 = 0;

	begin = chrono::steady_clock::now();
	for (size_t i = 0; i < 100; i++) {
		VV.push_back(V<int>(size));
		//VV[i]._print();
		VV[i]._quick_sort();
		c1 += VV[i]._comparison_count();
		c2 += VV[i]._copy_count();
	}
	c1 /= 100;
	c2 /= 100;
	cout << "quick:       " << '\t'<< c1 << '\t' << '\t' << c2 <<  endl;
	end = std::chrono::steady_clock::now();
	cout << "Diff(ms) = " << chrono::duration_cast<chrono::milliseconds>(end - begin).count() << endl;

	VV.clear();
	c1 = c2 = 0;

	begin = chrono::steady_clock::now();
	for (size_t i = 0; i < 100; i++) {
		VV.push_back(V<int>(size));
		//VV[i]._print();
		VV[i]._comb_sort();
		c1 += VV[i]._comparison_count();
		c2 += VV[i]._copy_count();
	}
	c1 /= 100;
	c2 /= 100;
	cout << "comb:        " << '\t' << c1 << '\t' << '\t' << c2 << endl;

	end = std::chrono::steady_clock::now();
	cout << "Diff(ms) = " << chrono::duration_cast<chrono::milliseconds>(end - begin).count() << endl;

//отдельные векторы с сортировками и c их states
	vector<int> v1, v2, v3;
	stats s1, s2, s3;

	fill(v1,size);
	cout << "vector 1 before sort: ";
	print(v1);
	s1=selection_sort(v1);
	cout << "vector 1 after selection sort: ";
	print(v1);
	cout << endl;

	fill(v2, size);
	cout << "vector 2 before sort: ";
	print(v2);
	s2=quick_sort(v2);
	cout << "vector 2 after quick sort: ";
	print(v2);
	cout << endl;

	fill(v3, size);
	cout << "vector 3 before sort: ";
	print(v3);
	s3=comb_sort(v3);
	cout << "vector 3 after comb sort: ";
	print(v3);

	


	cout << size << " elements:\n";
	cout << "sort   " << "     comparison count " << " copy count " << "\n";
	cout << "__________________________________________\n";
	cout <<"selection:       "<< s1.comparison_count << "          " << s1.copy_count << endl;
	cout <<"quick:           "<< s2.comparison_count << "          " << s2.copy_count << endl;
	cout <<"comb:            "<< s3.comparison_count << "          " << s3.copy_count << endl;

	return 0;
}