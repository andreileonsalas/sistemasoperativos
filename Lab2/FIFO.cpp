#include <bits/stdc++.h> 
#include <string>
#include <iostream>
using namespace std;

 

int pageFaultAlgorithm(int pages[], int n, int size) 
{
    unordered_set <int> s;
    queue <int> indexes;
    int page_faults = 0;
    for(int i = 0; i < n; i++)
    {
        if(s.size () < size) { 
            if(s.find (pages[i]) == s.end ()) {
                s.insert (pages[i]);
	        page_faults++;
	        indexes.push (pages[i]);
            }
       }
       else {
           if(s.find (pages[i]) == s.end ()) {
           int val = indexes.front ();
           indexes.pop ();
           s.erase (val);
           s.insert (pages[i]);
           indexes.push (pages[i]);
           page_faults++;
           }
       } 
    } 
    return page_faults;
}


int main() {
	int size = 4;
    int pages[] = { 0, 3, 5, 4, 3, 1, 2, 8, 2, 2, 9, 5, 4};
    int n = sizeof(pages) /   sizeof(pages[0]);
    
    cout << "FIFO \n";
    cout << "Pages = ";
    cout << "{";
    for(int i = 0; i < n; i++) {
        cout << pages[i];  cout << ", ";
    }
    cout << "}";
    cout << "\nPage Faults: ";
    cout << pageFaultAlgorithm (pages, n, size);
    return 0;
}