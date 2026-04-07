#include <chrono>
#include <algorithm>
#include <bitset>
#include <iostream>
#include <ctime> 
#include <cmath>

using namespace std;

class Array{
    int *a;
    size_t n;
    
    public:
    
    Array(int len = 1, int t = 1, int d = 10): n(len) {
        a = new int[n];
        for (int i = 0; i < n; i++){
                a[i] = 0 + rand() % d;
        }
        if (t == 2){
            sort(a, a + n);
        }
        else if (t == 3){
            sort(a, a + n);
            reverse(a, a+n);
        }
    }
    
    Array(int *arr, int len){
        n = len;
        a = new int[n];
        for (int i = 0; i < n; i++){
            a[i] = arr[i];
        }
    }
    
    Array(Array &other){
        n = other.n;
        a = new int[n];
        for (int i = 0; i < n; i++){
            a[i] = other.a[i];
        }
    }
    
    ~Array() {
        delete[] a;
        a = NULL;
    }
    
    Array& operator = (Array &other){
        if (this != &other){
            delete []a;
            n = other.n;
            a = new int[n = other.n];
            for (int i = 0; i < n; i++){
                a[i] = other.a[i];
            }
        }
        return *this;
    }
    
    int& operator[](int index) {
        if (index >= 0 && index < n) {
            return a[index];
        }
        throw out_of_range("Index out of range");
    }
    
    bool Test() const{
        for (int i = 0; i < n-1; i++){
            if(a[i] > a[i+1]) return false;
        }
        return true;
    }
    
    bool operator == (Array other){
        Array arr(*this);
        sort(arr.a, arr.a+arr.n);
        sort(other.a, other.a+other.n);
        for (int i = 0; i < n; i++){
            if(arr[i] != other.a[i]) return false;
        }
        return true;
    }
    
    friend istream& operator>>(istream& in, Array& arr) {
        for (int i = 0; i < arr.n; ++i) {
            in >> arr.a[i];
        }
        return in;
    }

    friend ostream& operator<<(ostream& out, Array& arr) {
        out << "[ ";
        for (int i = 0; i < arr.n; ++i) {
            out << arr.a[i] << " ";
        }
        out << "]" << endl;
        return out;
    }
    
    void Shell_sort(){
        for(int step = n / 2; step > 0; step /= 2){
            for(int i = step; i < n; i+=step){
                int tmp = a[i];
                int j;
                for(j = i; j >= step && a[j - step] > tmp; j -= step){
                    a[j] = a[j - step];
                }
                a[j] = tmp;
            }
        }
    }

    void Heap_sort() {
        for(int i = n / 2 - 1; i >= 0; i--)
            sift(n, i);

        for(int i = n - 1;  i >= 0; i--){
            swap(a[0], a[i]);

            sift(i, 0);
        }
    }
    
    void sift (int n, int i){
        int j = 2 * i + 1;
        int x = a[i];
        bool flag = true;
        
        while (j < n && flag){
            
            if(j + 1 < n  && a[j + 1] > a[j]) j++;
            
            if(a[j] > x){
                a[i] = a[j];
                i = j;
                j = 2 * i + 1;
            } else {
                flag = false;
            }
        }
        a[i] = x;
    }
    
    void Hoar_sort(){
        Hoar3(a, 0, n-1);
    }
    
    void Hoar3(int *arr, int left, int right){
        if (left >= right) return;
        
        int i = left;
        int j = right;
        int xm = arr[(left+right)/2];
        
        while (i <= j){
            while (arr[i] < xm) i++;
            while (arr[j] > xm) j--;
            if (i <= j){
                swap(arr[i], arr[j]);
                i++;
                j--;
            }
        }
        Hoar3(arr, left, j);
        Hoar3(arr, i, right);
    }
    
    void Bit(int *arr, int left, int right, int k, int size) {
        if (left >= right || k < 0) return;
        int i = left;
        int j = right;
        int tmp = arr[i];
        while (i <= j){
            while (arr[j] & (1 << k)) j--;
            while (~(tmp) & (1 << k)){ 
                i++;
                tmp = arr[i];
            }
            if(i <= j){
                swap(arr[i], arr[j]);
                i++;
                tmp = arr[i];
                j--;
            }
            // for (int i = left; i<=right; i++){
                // cout << arr[i] << " <-> ";
                // print_binary(arr[i], size);
            // }
            // cout << "----------\n";
        }
        
        Bit(arr, left, j, k-1, size);
        Bit(arr, i, right, k-1, size);
        return;
    }
    
    void Bit_sort(){
        int k = -1;
        for(int i = 0; i < n; i++){
            if (a[i] > k) k = a[i];
        }
        int const size = (int)log2(k)+1;
        
        Bit(a, 0, n-1, size-1, size);
    }    
            
    
    void print_binary(int num, int const size) {
        bitset<32> bin(num);  // Используем 32 бита для отображения числа
        cout << bin.to_string().substr(32 - size) << endl;
    }

};

int main() {
    srand(time(NULL));
    Array arr1(15, 1, 10);
    Array arr2(arr1);
    Array arr3(arr1);
    
    auto begin = std::chrono::steady_clock::now();
    cout << arr1 << endl;
    arr1.Shell_sort();
    cout << arr1 << endl;
    auto end = std::chrono::steady_clock::now();
    cout << "Time in nanoseconds for arr1 = " 
         << std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin).count() 
         << endl;
    cout << endl;
    begin = std::chrono::steady_clock::now();
    cout << arr2 << endl;
    arr2.Heap_sort();
    cout << arr2 << endl;
    end = std::chrono::steady_clock::now();
    cout << "Time in nanoseconds for arr2 = " 
         << std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin).count() 
         << endl;
    cout << endl;
    begin = std::chrono::steady_clock::now();
    cout << arr3 << endl;
    arr3.Hoar_sort();
    cout << arr3 << endl;
    end = std::chrono::steady_clock::now();
    cout << "Time in nanoseconds for arr2 = " 
         << std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin).count() 
         << endl;
}
