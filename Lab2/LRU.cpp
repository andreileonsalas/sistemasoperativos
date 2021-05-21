#include <bits/stdc++.h> 
#include <string>
#include <iostream>
#include <vector> 
using namespace std;

//how to run: g++ LRU.cpp -std=c++0x -o LRU.out; ./LRU.out

void pageFaultAlgorithm(int size, int* pages, int time, int length) 
{ 
	int cnt = 0; 
	vector > arr; 
	for (int i = 0; i < size; i++) { 
		arr.push_back(make_pair(-1, time)); 
	} 

	int page; 

	for (int i = 0; i < length; i++) { 
		page = pages[i]; 
		auto it = arr.begin(); 

		for (it = arr.begin(); it != arr.end(); it++) { 
			if (it->first == page) { 
				break; 
			} 
		} 

		if (it != arr.end()) { 
			it->second = time; 
		} 

		else { 
			vector >::iterator pos; 
			pos = arr.begin(); 
			int min = pos->second; 
			for (auto itr = arr.begin(); itr != arr.end(); itr++) { 
				if (itr->second < min) { 
					pos = itr; 
					min = pos->second; 
				} 
			} 
			arr.erase(pos); 
			arr.push_back(make_pair(page, time)); 
			cnt++; 
		} 
		time++; 
	} 
	cout << "The number of page faults is : " << cnt << endl; 
} 


int main () 
{
int size = 2;
int pages[] = { 0, 3, 5, 4, 3, 1, 2, 8, 7, 2, 9, 5, 4};
int n = sizeof (pages) / sizeof (pages[0]);

cout << "LRU \n";
cout << "Frames: ";
cout << size;
cout << "\nPages = ";
cout << "{";
for (int i = 0; i < n; i++)
{cout << pages[i];  cout << ", ";}
cout << "}\n";

int time = 0; 
pageFaultAlgorithm(size, pages, time, n); 

return 0;
}
