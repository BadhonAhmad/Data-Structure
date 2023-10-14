/*
This is a code segment tree with build,query,update function to find the max element.
*/

#include <bits/stdc++.h>
using namespace std;
int a[100005], tree[4 * 100005];

void build(int node, int st, int en){

    //if returns bactracking will be execute 
    if(st == en){
        tree[node] = a[st];
        return;
    }

    //if doesn't match the base case execution starts from here
    int mid=(st + en) / 2;
    build(2 * node, st, mid);//(2 * 1 , 1 , 4) [for 1 to 8]
    build(2 * node + 1, mid + 1, en);//(2 * 1 + 1, 5 , 8) [for 3 to 8]

    //backtracking
    tree[node] = max(tree[2 * node],tree[2 * node + 1]); 

}

int query(int node, int st, int en, int l, int r){//l,r is to compare whether the range lies or not between st and en[index of nodes]

    //base case -> completely lies
    if(st >= l && en <= r){
        return tree[node];
    }

    if(en < l || st > r) return INT_MIN;//en is less than l that means out of range

    //moving towards the left and right subtree finding the max of them
    int mid = (st + en) / 2;
    int left = query(2 * node, st , mid, l, r);
    int right =query(2 * node + 1, mid + 1, en, l, r);
    return max(left , right);

}

void update(int node, int st, int en, int idx, int val){
    if(st == en){
        tree[node] = val;
        a[st] = val;
        return;
    }

    int mid = (st + en) / 2;
    if(idx <= mid){
        update(2 * node, st, mid, idx, val);
    }
    else{
        update(2 * node + 1, mid + 1, en, idx, val);
    }

    tree[node] = max(tree[2 * node],tree[2 * node + 1]); 
} 

int main()
{
    int n ;
    cin >> n;
    for(int i = 1; i <= n; i++){
        cin >> a[i];
    }

    build(1, 1, n);// (index of root, start index, ending index of range)//one based indexing
    
    int q;
    cin >> q;
    while (q--)
    {
        int type,l, r;
        cin >> type >> l >> r;
        if(type  == 1)
        cout << query(1, 1, n, l, r) << endl;
        else{
            update(1, 1, n, l, r);
        }
    }
    
}

/*
test case:
4
1 2 3 4
4
2 3 10
1 1 4
2 1 1111
1 1 3
output:
10
1111
*/
