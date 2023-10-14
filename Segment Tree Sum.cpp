#include <bits/stdc++.h>
using namespace std;
#define int long long
const int N = 1e5 + 10;
int a[N], tree[4 * N];

void build(int node, int st, int en)
{
    if (st == en)
    {
        tree[node] = a[st];
        return;
    }

    int mid = (st + en) / 2;
    build(2 * node, st, mid);
    build(2 * node + 1, mid + 1, en);

    tree[node] = tree[2 * node] + tree[2 * node + 1];
}

int query(int node, int st, int en, int l, int r)
{
    if (l > en || r < st)
    {
        return 0;
    }

    if (r >= en && l <= st)
    { // st r en mane ami j segment ta niyechi tai eta l and r er moddhe thakbe
        return tree[node];
    }

    int mid = (st + en) / 2;
    int left = query(2 * node, st, mid, l, r);
    int right = query(2 * node + 1, mid + 1, en, l, r);
    return left + right;
}
void update(int node, int st, int en, int idx, int val)
{
    if (st == en)
    {
        a[st] = val;
        tree[node] = val;
        return;
    }
    int mid = (st + en) / 2;
    if (idx <= mid)
    {
        update(2 * node, st, mid, idx, val);
    }
    else
    {
        update(2 * node + 1, mid + 1, en, idx, val);
    }
    tree[node] = tree[2 * node] + tree[2 * node + 1];
}
int32_t main()
{
    int n, m;
    cin >> n >> m;
    for (int i = 0; i < n; i++)
        cin >> a[i];

    build(1, 0, n - 1);

    while (m--)
    {
        int type;
        cin >> type;
        if (type == 1)
        {
            int idx, val;
            cin >> idx >> val;
            update(1, 0, n - 1, idx, val);
        }
        else
        {
            int l, r;
            cin >> l >> r;
            cout << query(1, 0, n - 1, l, r - 1) << endl;
        }
    }
}
