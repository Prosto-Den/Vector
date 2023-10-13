#include <iostream>
#include <cassert>
#include <chrono>

template <typename type>
class Vector
{
private:
	int length;
	type* data;

public:
	Vector() //конструктор. Создаёт пустой массив
	{
		data = nullptr;
		length = 0;
	}

	Vector(int size) : length(size) //конструктор. Создаёт массив определённой длины.
	{
		int i;
		assert(size >= 0);
		data = new type[length];
		for (i = 0; i < size; i++)
			data[i] = 0;
	}

	~Vector() //деструктор
	{
		delete[] data;
		data = nullptr;
	}

	int size() //возвращает размер массива
	{
		return length;
	}

	void resize(int size) //изменяет размер массива. Если новый размер больше старого, заполняем новые элементы 0
	{
		assert(size >= 0); //обработака исключения. Если размер < 0, то программа не будет работать

		int i;
		type* array = new type[size];

		if (size < length)
			for (i = 0; i < size; i++)
				array[i] = data[i];
		else
		{
			for (i = 0; i < length; i++)
				array[i] = data[i];

			for (i = length; i < size; i++)
				array[i] = 0;
		}
		length = size;

		delete[] data;

		data = array;

		array = nullptr;
	}

	void resize(int size, type n) //перегрузка оператора resize. Если размер массива < size, то новые элементы будут иметь значение n
	{
		assert(size >= 0); //обработака исключения. Если размер < 0, то программа не будет работать
		int i;

		type* array = new type[size];

		if (size < length)
			for (i = 0; i < size; i++)
				array[i] = data[i];
		else
		{
			for (i = 0; i < length; i++)
				array[i] = data[i];

			for (i = length; i < size; i++)
				array[i] = n;
		}
		length = size;

		delete[] data;

		data = array;

		array = nullptr;
	}

	bool empty() //возвращает true, если массив пуст и false в противном случае
	{
		if (length == 0)
			return true;
		else
			return false;
	}

	void push_back(type n) //вставляет число n в конец массива
	{
		resize(length + 1, n);
	}

	void pop_back() //удаляет последний элемент массива
	{
		resize(length - 1);
	}

	void insert(type n) //вставляет число n в начало массива
	{
		int i;
		type* array = new type[length + 1];
		array[0] = n;

		for (i = 1; i < length + 1; i++)
			array[i] = data[i - 1];

		length++;

		delete[] data;

		data = array;

		array = nullptr;
	}

	void insert(int index, int amount, type n) //вставляет amount чисел, значения n после индекса index
	{
		int i;
		type* array = new type[length + amount];
		int a = index + 1;

		for (i = 0; i <= index; i++)
			array[i] = data[i];

		for (i = index + 1; i <= index + amount; i++)
			array[i] = n;

		for (i = index + amount + 1; i < length + amount; i++)
		{
			array[i] = data[a];
			a++;
		}

		length += amount;

		delete[] data;

		data = array;

		array = nullptr;
	}

	type front() //возвращает первый элемент массива
	{
		return data[0];
	}

	type back() //возвращает последний элемент массива
	{
		return data[length - 1];
	}

	void erase(int index) //стирает элемент под индексом index
	{
		int i;
		type* array = new type[length - 1];

		for (i = 0; i < index; i++)
			array[i] = data[i];

		for (i = index; i < length - 1; i++)
			array[i] = data[i + 1];

		length--;

		delete[] data;

		data = array;

		array = nullptr;
	}

	void clear() //полностью очищает массив
	{
		delete[] data;
		data = nullptr;
		length = 0;
	}

	void swap(int index1, int index2) //меняет местами два элемента в массиве
	{
		type temp;

		temp = data[index1];
		data[index1] = data[index2];
		data[index2] = temp;
	}

	void inOrder()
	{
		int i;

		for (i = 0; i < length; i++)
			data[i] = i + 1;
	}

	void reverseOrder()
	{
		int i;
		int num = length;

		for (i = 0; i < length; i++)
		{
			data[i] = num;
			num--;
		}
	}

	void randomOrder()
	{
		int i;

		for (i = 0; i < length; i++)
			data[i] = rand() % 100000;
	}

	type& operator[](int index) //перегрузка оператора []. Обращается к индексу
	{
		return data[index];
	}

	friend std::ostream& operator<<(std::ostream& os, Vector& a)
	{
		int i;

		os << "[";
		for (i = 0; i < a.length; i++)
			if (i != a.length - 1)
				os << a[i] << "; ";
			else
				os << a[i];
		os << "]";

		return os;
	}
};

template <typename type>
void Insert(Vector<type>& vect) //сортировка вставками
{
	int i, j, swaps = 0;
	long double compares = 1;

	std::chrono::steady_clock::time_point start;
	std::chrono::steady_clock::time_point end;
	std::chrono::steady_clock::duration total;

	start = std::chrono::steady_clock().now();

	for (i = 1; i < vect.size(); i++)
	{
		j = i;

		compares++;

		while (j > 0 && vect[j - 1] > vect[j])
		{
			vect.swap(j - 1, j);
			j--;
			swaps++;
		}
	}

	end = std::chrono::steady_clock().now();

	total = end - start;

	std::cout << "compares = " << compares << std::endl;
	std::cout << "swaps = " << swaps << std::endl;
	std::cout << "time = " << std::chrono::duration_cast<std::chrono::microseconds> (total).count() << "\n" << std::endl;
}

template <typename type>
void Stupid(Vector<type>& vect)
{
	int i, swaps = 0;
	long double compares = 1;

	std::chrono::steady_clock::time_point start;
	std::chrono::steady_clock::time_point end;
	std::chrono::steady_clock::duration total;

	start = std::chrono::steady_clock().now();

	for (i = 1; i < vect.size(); i++)
	{
		compares++;
		if (vect[i - 1] > vect[i])
		{
			vect.swap(i - 1, i);
			swaps++;
			i = 0;
		}
	}

	end = std::chrono::steady_clock::now();

	total = end - start;

	std::cout << "compares = " << compares << std::endl;
	std::cout << "swaps = " << swaps << std::endl;
	std::cout << "time = " << std::chrono::duration_cast<std::chrono::microseconds>(total).count() << "\n" << std::endl;
}

int main()
{
	srand(time(0));

	Vector<int> test(10);
	Vector<int> test1(10);

	test.inOrder();
	test1.inOrder();

	std::cout << "test = " << test << std::endl;
	std::cout << "test1 = " << test1 << "\n" << std::endl;

	Stupid(test);
	Insert(test1);

	std::cout << "test = " << test << std::endl;
	std::cout << "test1 = " << test1 << "\n" << std::endl;

	test.randomOrder();
	test1.randomOrder();

	std::cout << "test = " << test << std::endl;
	std::cout << "test1 = " << test1 << "\n" << std::endl;

	Stupid(test);
	Insert(test1);

	std::cout << "test = " << test << std::endl;
	std::cout << "test1 = " << test1 << "\n" << std::endl;

	test.reverseOrder();
	test1.reverseOrder();

	std::cout << "test = " << test << std::endl;
	std::cout << "test1 = " << test1 << "\n" << std::endl;

	Stupid(test);
	Insert(test1);

	std::cout << "test = " << test << std::endl;
	std::cout << "test1 = " << test1 << "\n" << std::endl;

	return 0;
}
