#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
#include <cmath>
using namespace std;

struct Coin {
    int ID;
    int x;
    int y;
};
int N;
int grid[20][20];
vector<Coin> coins; //동전 정보 오름차순 정리
Coin S;
Coin E;

int mini = INT_MAX;

bool cmp(Coin a, Coin b)
{
    return a.ID < b.ID;
}

void Choose(int curr_idx, int cnt, int last_idx, int dist)
{
    if (curr_idx == coins.size())
    {
        if (cnt == 3)
        {
            int E2E = dist + abs(coins[last_idx].x - E.x) + abs(coins[last_idx].y - E.y);
            mini = E2E < mini ? E2E : mini;
        }

        return;
    }

    int curr_dist = abs(coins[last_idx].x - coins[curr_idx].x) + abs(coins[last_idx].y - coins[curr_idx].y);
    Choose(curr_idx + 1, cnt + 1, curr_idx, dist + curr_dist);

    Choose(curr_idx + 1, cnt, last_idx, dist);
}

int main() {
   // freopen("input.txt", "r", stdin);
    cin >> N;
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            char c; cin >> c;

            if (c == '.')
                continue;
            else if (c == 'S')
            {
                S.ID = 0;
                S.x = i;
                S.y = j;
                coins.push_back(S);
            }
            else if (c == 'E')
            {
                E.ID = 100;
                E.x = i;
                E.y = j;
                //coins.push_back(E);
            }
            else { //숫자
                coins.push_back({ c - '0', i, j });
            }
        }
    }
    if (coins.size()-1 < 3) {
        cout << -1;
        return 0;
    }

    sort(coins.begin(), coins.end(), cmp);

    //동전 세 개를 선택하는 함수
    Choose(1, 0, 0, 0);
    cout << mini;
    return 0;
}