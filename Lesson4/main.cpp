#include<iostream>
#include"Arrayint.h"
#include<vector>
#include<algorithm>

int main()
{
	//Task 1
	{
		std::cout << "Task 1\n";
		ArrayInt arr;
		arr.push_back(42);
		arr.push_back(32);
		arr.push_back(21);
		arr.push_back(18);
		arr.print();
		arr.sort(0, arr.getLength() - 1);
		arr.print();
	}

	//Task 2
	{
		std::cout << "\n\nTask 2\n";
		std::vector<int> vec = { 32,545,76,43,32,54,76,356,545 };
		std::sort(vec.begin(), vec.end());
		int equal{};
		for (int i{0};i<vec.size()-1;i++)
		{
			if (vec[i] == vec[i+1])
				equal++;
		}
		std::cout << "There are "<< vec.size() - equal<<" different numbers in the vector\n";
	}
	//Task 3
	{
		std::cout << "\n\nTask 3\n";

	}
}