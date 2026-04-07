#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;


void PrintVector(vector<int> vec) {
  for (int i = 0; i < vec.size(); i++)
    cout << vec[i] << "  " ;
  cout << endl;
}

vector<int> Dijkstra(vector<int> P)
{
    unsigned int size = P.size();
    
    for (int i = size - 2; i >= 0; i--)
    {
        if (P[i] < P[i + 1])
        {
            for (int j = size - 1; j > i; j--)
            {
                if (P[i] < P[j])
                {
                    swap(P[i], P[j]);
                    reverse(P.begin() + i + 1, P.end());
                    return P;
                }
            }
        }
    }
    return P;
}

int main()
{
    vector<int> vec1, vec2;
    int size;
    cout << "Print size: ";
    cin >> size;
    cout << endl;
    cout << "Dijkstra's algorithm:" << endl;
    cout << endl;
    for (int i = 1; i <= size; i++){
        vec1.emplace_back(i);
        vec2.emplace_back(i);
    }
    reverse(vec2.begin(), vec2.end());
    int i = 0;
    while (vec1 != vec2)
    {
        cout << i << ": ";
        PrintVector(vec1);
        vec1 = Dijkstra(vec1);
        i++;
    }
    cout << i << ": ";
    PrintVector(vec2);
    
    return 0;
}
