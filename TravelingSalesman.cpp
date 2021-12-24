#include <iostream>
#include <cstdlib>
#include <vector>
#include <cmath>
#include <climits>
#include <ctime>
#include <chrono>
#include <iomanip>
using namespace std;
float inf = 1e10;

void findway(vector<vector<float>> g, int n, vector<vector<float>> *d, int* path)
{
    int i = 0;
    int k =0;
    int mask = (1 << n) - 1;
    path[0] = 0;
    k++;
    while (mask != 0)
    {
        for (int j = 0; j < n; j++)
        {
            if (g[i][j])
                if ((mask & (1 << j)))
                    if ((*d)[mask][i] == g[i][j] + (*d)[mask ^ (1 << j)][j])
                    {
                        path[k] = j ;
                        k++;
                        i = j;
                        mask = mask ^ (1 << j);
                    }
        }
    }
}

float findcheapest(int i, int mask, vector<vector<float>> g , int n, vector<vector<float>> *d)
{
    if ((*d)[mask][i] != inf)
    {
        return (*d)[mask][i];
    }
    for (int j = 0; j < n; j++)
    {
        if (g[i][j])
        {
            if ((mask & (1 << j)))
            {

                (*d)[mask][i] = min((*d)[mask][i], findcheapest(j, mask - (1<<j), g, n,d) + g[i][j]);
            }
        }
    }
    return (*d)[mask][i];
}

int main()
{
    int n;
    cin>> n;
    int path[n];
    vector<vector<float>>d((1 << n), vector<float>(n));
    vector<vector<float>> g(n, vector<float>(n));
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            //cin >> g[i][j];
            g[i][j] = rand() % 9 ;
            if (i == j) g[i][j] = 0;
        }
    }

    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            if (g[i][j] == inf)
                cout << "  inf";
            else
                cout <<setw(4)<< g[i][j]<<" ";
        }
        cout<<endl;
    }
    for (int i = 0; i < n; i++)
        for (int mask = 0; mask < (1 << n); mask++)
            d[mask][i] = inf;
    d[0][0] = 0;
    auto begin = std::chrono::steady_clock::now();
    float ans = findcheapest(0, (1<<n) - 1, g , n, &d);
    if (ans == inf)
    {
        cout<<"There is no way "<<endl;
    }
    else
    {
        cout << ans << endl;
        findway(g,  n, &d, path);
        for (int i = 0; i < n; i++)
            cout << path[i] + 1 << " -> ";
        cout << path[0] + 1<<endl;

        int sum = 0;
        bool flag = true;
        for (int i = 0; i < n-1; i++)
        {
                sum = sum + g[path[i]][path[i+1]];
                if (g[path[i]][path[i+1]] == 0) flag = false;
        }
        sum = sum + g[path[n-1]][0];
        if (sum == ans && flag)
            cout<<"Test - OK"<< endl;
        else
            cout<<"Test - NO OK"<< endl;
    }
    auto end = std::chrono::steady_clock::now();
    auto elapsed_ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);
    int seconds = elapsed_ms.count();
    cout <<"The time: "<< seconds<<" milliseconds" <<endl;
    return 0;
}
