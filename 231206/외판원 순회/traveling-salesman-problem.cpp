#include <iostream>
#include <vector>
#include <climits>
using namespace std;

int n;
int cost[10][10];
int visited[10];
vector<int> v;
int mini = INT_MAX;

int CalCost()
{
    int res = 0;
    //0번지점 출발 + 도착
    for (int i = 1; i < (int)v.size(); i++)
    {
        res += cost[v[i - 1]][v[i]];
    }

    return res;
}

//0~n-1까지 고르는 순열
void Permut(int cnt)
{
    if (cnt == n)
    {
        v.push_back(0);
        int ret = CalCost();
        v.pop_back();
        mini = ret < mini ? ret : mini;
        return;
    }

    for (int i = 1; i < n; i++)
    {
        if (visited[i] == 1) continue;
        v.push_back(i);
        visited[i] = 1;
        Permut(cnt + 1);
        visited[i] = 0;
        v.pop_back();
    }
}

int main() {
    //freopen("input.txt", "r", stdin);
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cin >> cost[i][j];
        }
    }

    v.push_back(0);
    Permut(1); //0번 지점은 고른셈
    v.pop_back();
    cout << mini;
    return 0;
}