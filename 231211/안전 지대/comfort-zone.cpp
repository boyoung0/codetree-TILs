#include <iostream>
#include <queue>
#include <vector>
#include <memory.h>

using namespace std;

int n, m;
int grid[50][50];
int rain[50][50];
int visited[50][50];
int safe_house;

int ans_k = 100;
int ans_safe = 0;
int dx[4] = { 0,1,0,-1 };
int dy[4] = { 1,0,-1,0 };

bool InRange(int x, int y)
{
    if (x < 0 || x >= n || y < 0 || y >= m)
        return false;
    if (visited[x][y] != 0)
        return false;

    return true;
}

void BFS(int x, int y)
{
    queue<pair<int, int> > q;

    visited[x][y] = 1;
    q.push(make_pair(x, y));

    while (!q.empty())
    {
        int cx = q.front().first;
        int cy = q.front().second;
        q.pop();

        for (int dir = 0; dir < 4; dir++)
        {
            int nx = cx + dx[dir];
            int ny = cy + dy[dir];

            if (InRange(nx, ny))
            {
                visited[nx][ny] = 1;
                q.push(make_pair(nx, ny));
            }
        }
    }
}

void CalSafe(int k)
{
    int cnt = 0;

    //memcpy(visited, rain, sizeof(rain));
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            if (visited[i][j] == 0)
            {
                //cout << i << " " << j << endl;
                BFS(i, j); //인접한 안전영역 표시
                cnt++;
            }
        }
    }

    if (cnt > ans_safe)
    {
        ans_k = k;
        ans_safe = cnt;
    }
}

void Raining(int k)
{
    memcpy(visited, rain, sizeof(visited));
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            if (grid[i][j] == k) //새로 물에 잠김
            {
                rain[i][j] = 1;
                visited[i][j] = 1;
                safe_house--;
            }
        }
    }

    CalSafe(k);
}

int main() {
    //freopen("input.txt", "r", stdin);
    int k = 1;

    cin >> n >> m;
    safe_house = n * m;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            cin >> grid[i][j];
        }
    }

    while (safe_house > 0)
    {
        Raining(k);
        k++;
    }

    if(ans_k == 100) ans_k = 1;
    cout << ans_k << " " << ans_safe;

    return 0;
}