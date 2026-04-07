#include <iostream>
#include <algorithm>
using namespace std;

class route {
    int *r, n;
    
    public:
      route(int num = 0) : n(num) {
        if (n > 0) {
            r = new int[n];  
            for (int i = 0; i < n; ++i) {
                r[i] = i;  
            }
        } else {
            r = nullptr;  
        }
      }
      route(const route &other) : n(other.n) {
          if (n > 0){
              r = new int[n];  
            for (int i = 0; i < n; ++i) {
                r[i] = other.r[i];  
            }
          } else {
              r = nullptr;
          }
      }
      
      route & operator = (const route&other){
        if (this == &other) return *this;
          
        delete[] r;
        
        if (n > 0) {
            r = new int[n];
            for (int i = 0; i < n; ++i) {
                r[i] = other.r[i];
            }
        } else {
            r = nullptr;
        }

          return *this;
      }
      
      ~route() {
          if(r){
              delete []r;
              r = NULL;
          }
      }
      
      int routePrice(int **costWay) {
        int totalPrice = 0;
        
        for (int i = 0; i < n - 1; ++i)
            totalPrice += costWay[r[i]][r[i + 1]];
            
        totalPrice += costWay[r[n-1]][r[0]];
        
        return totalPrice;
      }
      
      bool nextRoute(){
        if (n <= 1) return false;

        // Найти наибольший индекс i
        int i = n - 2;
        while (i >= 0 && r[i] >= r[i + 1]) {
            --i;
        }

        if (i < 0) return false;

        // Найти наибольший индекс j
        int j = n - 1;
        while (r[i] >= r[j]) {
            --j;
        }

        // Поменять местами r[i] и r[j]
        swap(r[i], r[j]);

        // Инвертировать последовательность после i
        reverse(r + i + 1, r + n);

        return true;
      }
      
      friend ostream &operator<<(ostream &result, const route& ro) {
        for (int i = 0; i < ro.n; ++i) {
            result << ro.r[i] << " ";
        }
        return result;
      }
};

int main() {
    int n;

    cout << "Введите количество точек пути: ";
    cin >> n;

    int **costWay = new int*[n];
    for (int i = 0; i < n; ++i) {
        costWay[i] = new int[n];
    }

    // Ввод данных для матрицы стоимости
    cout << "Введите матрицу стоимости (стоимость от i к j):\n";
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cin >> costWay[i][j];
        }
    }
    cout  << endl;
    route way(n);
    route min_way(way);
    cout << "Исходный путь: " << way << endl;
    cout  << endl;
    cout << "Стоимость пути: " << way.routePrice(costWay) << endl;
    cout  << endl;
   
    do
        {
            cout << "Путь: " << way;
            cout << "Стоимотсть пути: " << way.routePrice(costWay) << endl;
            cout  << endl;
            if(way.routePrice(costWay) < min_way.routePrice(costWay))
            {
                min_way = way;
            }
        } while (way.nextRoute());
    
    for (int i = 0; i < n; ++i) {
        delete[] costWay[i];
    }
    delete[] costWay;
}
