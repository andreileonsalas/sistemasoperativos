//https://github.com/UnJaw/Programming_HW0/blob/master/Prime.java

 #include <windows.h>

 #include <iostream>

 #define MAX_THREADS 1
 using namespace std;
 DWORD WINAPI Prime(LPVOID);
 HANDLE hThreads[MAX_THREADS];
 DWORD id[MAX_THREADS];
 DWORD waiter;
 int check_prime(int a) {
   int c;
   for (c = 2; c <= a - 1; c++) {
     if (a % c == 0)
       return 0;
   }
   if (c == a)
     return 1;
 }
 DWORD WINAPI Prime(LPVOID Param) {
   DWORD Number = * (DWORD * ) Param;
   for (DWORD i = 2; i <= Number; i++) {
     if (check_prime(i) == 0)
       cout << "";
     else
       cout << i;
   }
   return 0;
 }
 int main(int argc, char * argv[]) {
   // same your code
   return 0;
 }