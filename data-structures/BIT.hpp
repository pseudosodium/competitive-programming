/*
Binary Indexed Tree (Fenwick Tree)
Description: Computes range sum for a contiguous range l,r
             i.e. a[l]+a[l+1]+..+a[r] and also updates value at
             at a point.
Time: O(log n)
Source: CP-Algorithms
*/

struct BIT {
    vector<int> bit;
    int n;
    BIT(int n) {
        this->n = n;
        bit.assign(n, 0);
    }
    int sum(int r) {
        int ret = 0;
        for (; r >= 0; r = (r & (r + 1)) - 1)
            ret += bit[r];
        return ret;
    }
    int sum(int l, int r) {
        return sum(r) - sum(l - 1);
    }
    void add(int idx, int delta) {
        for (; idx < n; idx = idx | (idx + 1))
            bit[idx] += delta;
    }
};