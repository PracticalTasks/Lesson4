#ifndef ARRAYINT_H
#define ARRAYINT_H

#include <cassert> // ��� assert()

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

		// ����� ��� ����� ������� m_data �������� nullptr, ����� �� ������ �� ���� �������� ���������
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

	// ������� resize �������� ������ �������. ��� ������������ �������� �����������. ������� ���������
	void resize(int newLength)
	{
		// ���� ������ ��� ������ ����� � return
		if (newLength == m_length)
			return;

		// ���� ����� ������� ������ ������ � ������ ��� � ����� return
		if (newLength <= 0)
		{
			erase();
			return;
		}

		// ������ �����, ��� newLength >0
		// �������� ����� ������
		int* data = new int[newLength];

		// ����� ����� ����������� � ����������� ���������� ��������� � ����� ������
		// ����� ����������� ������� ���������, ������� �� ���� � ������� �� ��������
		if (m_length > 0)
		{
			int elementsToCopy = (newLength > m_length) ? m_length : newLength;

			// ���������� �������� ��������
			for (int index = 0; index < elementsToCopy; ++index)
				data[index] = m_data[index];
		}

		// ������� ������ ������, ��� ��� �� ��� ��� �� �����
		delete[] m_data;

		// � ���������� ������ ������� ������� �����! �������� ��������, m_data ���������
		// �� ��� �� �����, �� ������� ��������� ��� ����� ����������� ���������� ������. ���������
		// ������ ���� ����������� ���������� � ��� �� ����� ����������, ����� ������ �� ������� ���������
		m_data = data;
		m_length = newLength;
	}

	void insertBefore(int value, int index)
	{
		// �������� ������������ ������������� �������
		assert(index >= 0 && index <= m_length);

		// ������� ����� ������ �� ���� ������� ������ ������� �������
		int* data = new int[m_length + 1];

		// �������� ��� �������� �� index-�
		for (int before = 0; before < index; ++before)
			data[before] = m_data[before];

		// ��������� ����� ������� � ����� ������
		data[index] = value;

		// �������� ��� �������� ����� ������������ ��������
		for (int after = index; after < m_length; ++after)
			data[after + 1] = m_data[after];

		// ������� ������ ������ � ���������� ������ ���� ����� 
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

	~ArrayInt()
	{
		delete[] m_data;
	}
};
		

#endif

