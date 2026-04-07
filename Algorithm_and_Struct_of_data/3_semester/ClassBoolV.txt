#include <iostream>
#include <cstring>
#include <vector>
#include <fstream>
using namespace std;

class BoolV{ 
    unsigned int *vec;
    int bit, bytes; // bit – количество бит вектора, bytes – количество элементов массива v 🤢
    
    public:
    
    BoolV(int n = 1): bit(n){
        bytes = (bit - 1) /32 +1;
        vec = new unsigned int[bytes];
        for (int i = 0; i < bytes; i++){
            vec[i] = 0;
        }
    } // формируется булев вектор из n бит; все биты со значениями 0
    
    BoolV(const char*str) {
        bit = strlen(str);
        bytes = (bit - 1) / 32 + 1;
        vec = new unsigned int[bytes];
        unsigned int mask = 1;
        for (int i = 0; i < bit; i++){
            if (str[i] != '0'){
                vec[i/32] = vec[i/32] | mask;
            }
            mask = mask << 1;
        }
    } // формируется булев вектор по строке из нулей и единиц
    
    BoolV(const BoolV &other){
        bit = other.bit;
        bytes = other.bytes;
        vec = new unsigned int [bytes];
        for (int i = 0; i < bytes; i++){
            vec[i] = other.vec[i];
        }
    }
    
    ~BoolV(){
        if (vec != NULL){
            delete[] vec;
            vec = NULL;
        }
        bit = 0;
        bytes = 0;
    }
    
    void Set1(int k){
        if (k < 0 || k >= bit) {
            cout << "Index out of range" << endl;
            exit(1);
        }
        
        unsigned int mask = 1;
        int kbyte = k/32;
        mask = mask << (k % 32);
        vec[kbyte] = vec[kbyte] | mask;
        
    } // устанавливает указанный бит в 1
    
    void Set0 (int k) {
        if (k < 0 || k >= bit) {
            cout << "Index out of range" << endl;
            exit(2);
        }
        
        unsigned int mask = 1;
        int kbyte = k/32;
        mask = mask << (k % 32);
        vec[kbyte] = vec[kbyte] & (~mask);
    } // устанавливает указанный бит в 0
    
    int operator[](int k){
        if (k < 0 || k >= bit) {
            cout << "Index out of range" << endl;
            exit(3);
        }
        
        unsigned int mask = 1;
        int kbyte = k/32;
        mask = mask << (k % 32);
        bool result = vec[kbyte] & mask;
        
        return result;
    }
    
    BoolV & operator = (const BoolV &other){
        if(this == &other)
            return *this;

        delete[] vec;

        vec = new unsigned int[other.bytes];
        bit = other.bit;
        bytes = other.bytes;
        for(int i = 0; i < bytes; i++)
        {
            vec[i] = other.vec[i];
        }
        
        return *this;
    }
    
    bool operator == (const BoolV &other){
        if (bit != other.bit){
            return false;
        }
        
        for(int i = 0; i < bytes; i++){
            if (vec[i] != other.vec[i]) return false;
        }
        
        return true;
    } // равенство векторов
    
    BoolV operator | (const BoolV &other){
        int newbit = 0;
        
        if (bit > other.bit) newbit = bit;
        else newbit = other.bit;
        
        BoolV result(newbit);
        
        for(int i = 0; i < bytes; i++){
            result.vec[i] = vec[i] | other.vec[i];
        }
        
        return result;
    }
    
    BoolV operator & (const BoolV &other){
        int newbit = 0;
        
        if (bit > other.bit) newbit = bit;
        else newbit = other.bit;
        
        BoolV result(newbit);
        
        for(int i = 0; i < bytes; i++){
            result.vec[i] = vec[i] & other.vec[i];
        }
        
        return result;
    }
    
    BoolV operator ~ (){
        BoolV result(*this);
        
        for (int i = 0; i < bytes; i++){
            result.vec[i] = ~vec[i];
        }
        
        unsigned int mask = (1 << (bit % 32)) - 1;
        result.vec[bytes - 1] &= mask;
        
        return result;
    }
    
    int weight(){
        int weight = 0;
        for(int i = 0; i < bit; i++){
            unsigned int mask = 1 << (i % 32);
            if (vec[i / 32] & mask) weight++;
        }
        return weight;
    }
    
    friend ostream& operator<< (ostream &os, const BoolV &boolV)
    {
        char *str = new char[boolV.bit + 1];
        str[boolV.bit] = '\0';
        for(int i = 0; i < boolV.bit; i++)
        {
            unsigned int mask = 1;
            if(boolV.vec[i/32] & (mask << (i % 32)))
                str[i] = '1';
            else
                str[i] = '0';
        }
        os << str << endl;

        return os;
    }
    friend istream& operator >> (istream &is, BoolV &boolV){
        string input;
        is >> input;
        
        for (int i = 0; i < input.size(); ++i) {
            char c = input[i];
            if (c != '0' && c != '1'){
                cout << "Invalid input" << endl;
                exit(4);
            }
        }
        
        boolV = BoolV(input.c_str()); // Указатель char* на строку
        
        return is;
    }
};

class BoolM {
    
    BoolV *bm;
    int m, n; // m - строки, n - столбцы
    
    public:
    
    BoolM(int k = 1, int l = 1): m(k), n(l){
        if (k <= 0 || l <= 0){
            cout << "Invalid index" << endl;
            exit(4);
        }
        
        bm = new BoolV[m];
        for (int i = 0; i < m; i++){
            bm[i] = BoolV(n);
        }
    } // формируется нулевая булева матрица размера kxl
    
    BoolM(const BoolM &other): m(other.m), n(other.n) {
        bm = new BoolV[m];
        
        for(int i = 0; i < m; i++){
            bm[i] = other.bm[i];
        }
    }
    
    ~BoolM(){
        delete[] bm;
        bm = NULL;
    }
    
    BoolV & operator[] (int k){
        return bm[k];
    }
    
    BoolM & operator = (const BoolM &other){
        if(this != &other){
            
            delete[] bm;
            m = other.m;
            n = other.n;
            bm = new BoolV[m];
            
            for(int i = 0; i < m; i++){
                bm[i] = other.bm[i];
            }
        }
        return *this;
    }
    
    friend ostream & operator << (ostream &os, BoolM &boolM){
        for(int i = 0; i < boolM.m; i++){
            os << boolM[i] << endl;
        }
        return os;
    }
    
    
    
    void TopSort(BoolM &matrix, int m, vector<int> &arr) {
        BoolV vec0(m); // хранитель обработанных вершин
        BoolV null(m); // для обнуления 
    
        int idx = 0;
    
        while (vec0.weight() < m) {
            BoolV vec1(m);  // временный вектор для обработки текущих кандидатов
    
            // Для каждой вершины смотрим, есть ли она ещё не в vec0 и имеет ли исходящие ребра
            for (int i = 0; i < m; i++) {
                if (vec0[i] == 0) {  // вершина еще не обработана
                    vec1 = vec1 | matrix[i];
                }
            }
    
            // Инвертируем vec1 и исключаем уже обработанные вершины
            vec1 = ~vec1;
            BoolV vec2 = vec1 & (~vec0);
    
            if (vec2.weight() == 0) {
                cout << "Lopping error" << endl;
                exit(5);  // Ошибка, если цикл найден
            }
    
            // Добавляем в топологический порядок те вершины, которые можно обработать
            for (int i = 0; i < m; i++) {
                if (vec2[i] == 1) {
                    arr[idx++] = i;
                    matrix[i] = null;  // Обнуляем строку, т.к. вершина обработана
                }
            }
    
            vec0 = vec0 | vec2;  // Обновляем список обработанных вершин
        }
    }

};

int main(){
    ifstream fileIn("graf.txt");
    int a, b;
    int m;
        
    fileIn >> m;
    BoolM matrix(m, m);
    while (!fileIn.eof()){
        fileIn >> a;
        fileIn >> b;
        matrix[a - 1].Set1(b-1);
    }
    fileIn.close();
    
    cout << "Матрица смежности графа:" << endl;
    cout << matrix;
        
    vector<int> arr(m);
    
    matrix.TopSort(matrix, m, arr);

    for (int i = 0; i < arr.size(); i++) {
        cout << arr[i] << " ";
    }
    cout << endl;

    return 0;

}
