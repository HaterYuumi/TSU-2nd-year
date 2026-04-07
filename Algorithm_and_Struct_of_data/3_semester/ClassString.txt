#include <iostream>
#include <cmath>
#include <sstream>
#include <cstring>
#include <vector>
using namespace std;

class String {
    char *str;
    int len;
    
    public:
        String(int l = 0): len(l) {
            str = new char[len + 1];
            str[0] = '\0';
        }
        String(const char* s) {
            len = strlen(s);
            str = new char[len + 1];
            strcpy(str, s);
        }
        String(String &other) {
            len = other.len;
            str = new char[len + 1];
            strcpy(str, other.str);
        }
        
        ~String() {
         if(str) delete []str; 
         str = NULL;
        }
        
        int strLenght(){
            return len;
        }
        
        const char* getStr() const {
            return str;
        }
        
        String & operator = (const String &other){
            if(this != &other) {
                delete [] str;
                str = new char [(len = other.len)+1];
                strcpy(str, other.str);
            }
            return *this;
        }
        
        char &operator [](int i){
            if (i < 0 || i >= len) {
                throw out_of_range("Index out of range");
            }
            return str[i];
        }
        
        bool operator == (String &other){
            return strcmp(str, other.str) == 0;
        }
        
        bool operator != (String &other){
            return strcmp(str, other.str) != 0;
        }
        
        String operator + (const String &other){
            String line("");
            line.len = (this->len + other.len);
            line.str = new char[line.len + 1];
            for (int i = 0; i < line.len; i++){
                if (i < this->len){
                    line.str[i] = this->str[i];
                }
                else{
                    line.str[i] = other.str[i - this->len];
                }
            }
            line.str[line.len] = '\0';
            return line;
        }
        
        String operator += (const String &other){
            
            int oldlen = this->len;
            this->len += other.len;
            char *newstr = new char[this->len + 1];
            
            for (int i = 0; i < oldlen; i++){
                newstr[i] = this->str[i];
            }
            
            for (int i = 0; i < other.len; i++){
                newstr[oldlen + i] = other.str[i];
            }
            
            newstr[this->len] = '\0';
            delete[] this->str;
            this->str = newstr;
            return *this;
        }
        
        friend istream & operator >> (istream &result, String &str) {
            char buffer[1024];
            cout << "Введите строку: ";
            result.getline(buffer, 1024);
            str = String(buffer);
            return result;
        }
        
        friend ostream & operator << (ostream &result, const String &s) {
            result << s.str;
            return result;
        }
        
        int BMSearch (String &other){
            int m = other.strLenght(); // Длина образца
            int n = len; // Длина текста
            if (m > n) return -1; // Если образец длиннее текста, совпадения быть не может
            
            vector<int> Tab(256, m); // Таблица сдвигов для каждого символа (по умолчанию все сдвиги равны длине образца)
            
                for (int i = 0; i < m - 1; i++) {
                Tab[(unsigned char)other.getStr()[i]] = m - i - 1;
            } // Заполнение таблицы сдвигов для каждого символа образца
            int i = m - 1; // Указатель на последний символ образца
            int j = m - 1; // Указатель на текущий символ текста
            int k = j; //вспомгательный символ для сравнения
            while (j < n) {
                if (other.getStr()[i] == str[k]){ // Если символы совпали, сдвигаемся
                    if (i == 0){ // Если весь образец совпал с частью текста, возвращаем позицию совпадения
                        return k;
                    }
                    --i; // Переходим к предыдущему символу в образце
                    --k; // Переходим к следующему символу в тексте
                } else { // Если символы не совпали, используем таблицу сдвигов
                    j += Tab[(unsigned char)str[j]]; // Сдвигаем текст на соответствующее расстояние
                    i = m - 1; // Возвращаемся в начало образца
                    k = j;
                }
            }
            
            return -1; // Если совпадения не найдено, возвращаем -1
        }
};

int main() {
    String s("AAAABABAA");
    // A A A A B A B A A
    // 0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15
    String pattern("BABA");
    // B A B A
    // 1 2 1 2
    int position = s.BMSearch(pattern);
    if (position != -1) {
        cout << "Found at index: " << position << endl;
    } else {
        cout << "Not found" << endl;
    }

}
