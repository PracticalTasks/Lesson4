#ifndef ARRAYINT_H
#define ARRAYINT_H

//TASK 1
#include <cassert> // для assert()

class ArrayInt
{
private:
	int m_length;
	int* m_data;

	void swap(int* a, int* b)
	{
		int t = *a;
		*a = *b;
		*b = t;
	}

public:
	ArrayInt() : m_length(0), m_data(nullptr)
	{ }

	ArrayInt(int length) :
		m_length(length)
	{
		assert(length >= 0);

		if (length > 0)
			m_data = new int[length];
		else
			m_data = nullptr;
	}

	void erase()
	{
		delete[] m_data;

		// Здесь нам нужно указать m_data значение nullptr, чтобы на выходе не было висячего указателя
		m_data = nullptr;
		m_length = 0;
	}

	int getLength()
	{
		return m_length; 
	}

	int& operator[](int index)
	{
		assert(index >= 0 && index < m_length);
		return m_data[index];
	}

	// Функция resize изменяет размер массива. Все существующие элементы сохраняются. Процесс медленный
	void resize(int newLength)
	{
		// Если массив уже нужной длины — return
		if (newLength == m_length)
			return;

		// Если нужно сделать массив пустым — делаем это и затем return
		if (newLength <= 0)
		{
			erase();
			return;
		}

		// Теперь знаем, что newLength >0
		// Выделяем новый массив
		int* data = new int[newLength];

		// Затем нужно разобраться с количеством копируемых элементов в новый массив
		// Нужно скопировать столько элементов, сколько их есть в меньшем из массивов
		if (m_length > 0)
		{
			int elementsToCopy = (newLength > m_length) ? m_length : newLength;

			// Поочередно копируем элементы
			for (int index = 0; index < elementsToCopy; ++index)
				data[index] = m_data[index];
		}

		// Удаляем старый массив, так как он нам уже не нужен
		delete[] m_data;

		// И используем вместо старого массива новый! Обратите внимание, m_data указывает
		// на тот же адрес, на который указывает наш новый динамически выделенный массив. Поскольку
		// данные были динамически выделенные — они не будут уничтожены, когда выйдут из области видимости
		m_data = data;
		m_length = newLength;
	}

	void insertBefore(int value, int index)
	{
		// Проверка корректности передаваемого индекса
		assert(index >= 0 && index <= m_length);

		// Создаем новый массив на один элемент больше старого массива
		int* data = new int[m_length + 1];

		// Копируем все элементы до index-а
		for (int before = 0; before < index; ++before)
			data[before] = m_data[before];

		// Вставляем новый элемент в новый массив
		data[index] = value;

		// Копируем все значения после вставляемого элемента
		for (int after = index; after < m_length; ++after)
			data[after + 1] = m_data[after];

		// Удаляем старый массив и используем вместо него новый 
		delete[] m_data;
		m_data = data;
		++m_length;
	}

	void push_back(int value)
	{
		insertBefore(value, m_length); 
	}

	void pop_back()
	{
		m_length--;
	}

	void pop_front()
	{
		memcpy(m_data, m_data + 1, sizeof(int) * --m_length);
	}

	void sort(int first, int last)
	{
		int i = first;
		int j = last;

		int x = m_data[(first + last) / 2];

		do
		{
			while (m_data[i] < x)
				i++;
			while (m_data[j] > x)
				j--;

			if (i <= j)
			{
				swap(&m_data[i], &m_data[j]);
				i++;
				j--;
			}

		} while (i <= j);

		if (i < last)
			sort(i, last);
		if (first < i)
			sort(first, j);
	}

	void print()
	{
		for (int i{}; i < m_length; i++)
			std::cout << m_data[i] << ' ';

		std::cout << '\n';
	}

	~ArrayInt()
	{
		delete[] m_data;
	}
};
		
//TASK 3
enum CardSuit
{
	clubs,
	spades,
	heart,
	diamonds
};

enum CardValue
{
	six = 6, seven, eight,
	nine, ten, jack = 2,
	lady, king, ace = 11
};

class Card
{
	CardSuit suit;
	CardValue value;
	bool position;
public:
	void Flip()
	{
		if (position)
			position = false;
		else
			position = true;
	}

	CardValue GetValue()
	{
		return value;
	}

};

class Hand
{
	std::vector<Card*> card;

public:
	void Add(Card* newCard)
	{
		card.push_back(newCard);
	}

	void Clear()
	{
		card.clear();
	}

	int GetValue()
	{
		int sumCard{};
		for (int i{}; i < card.size(); i++)
		{
			sumCard += card[i]->GetValue();
		}
		return sumCard;
	}
};

#endif

