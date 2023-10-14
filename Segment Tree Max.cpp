#include <bits/stdc++.h>
using namespace std;
int a[100005], seg[4 * 100005];

void build(int ind, int low, int high){

    //if returns bactracking will be execute 
    if(low == high){
        seg[ind] = a[low];
        return;
    }

    //if doesn't match the base case execution starts from here
    int mid=(low + high) / 2;
    build(2 * ind, low, mid);//(2 * 1 , 1 , 4) [for 1 to 8]
    build(2 * ind + 1, mid + 1, high);//(2 * 1 + 1, 5 , 8) [for 3 to 8]

    //backtracking
    seg[ind] = max(seg[2 * ind],seg[2 * ind + 1]); 

}

int query(int ind, int low, int high, int l, int r){//l,r is to compare whether the range lies or not between low and high[index of nodes]

    //base case -> completely lies
    if(low >= l && high <= r){
        return seg[ind];
    }

    if(high < l || low > r) return INT_MIN;//high is less than l that means out of range

    //moving towards the left and right subtree finding the max of them
    int mid = (low + high) / 2;
    int left = query(2 * ind, low , mid, l, r);
    int right =query(2 * ind + 1, mid + 1, high, l, r);
    return max(left , right);

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
        int l, r;
        cin >> l >> r;
        cout << query(1, 1, n, l, r) << endl;
    }
    
}
