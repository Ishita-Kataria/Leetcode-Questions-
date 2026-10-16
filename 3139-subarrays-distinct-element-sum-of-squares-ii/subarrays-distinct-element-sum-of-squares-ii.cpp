class Solution {
    static const int MOD = 1e9 + 7;

    struct Node {
        long long sum = 0;
        long long sq = 0;
        long long lazy = 0;
    };

    vector<Node> tree;
    int n;

    void apply(int node, int l, int r, long long v) {
        long long len = r - l + 1;
        tree[node].sq = (tree[node].sq
            + 2 * v * tree[node].sum + len * v * v) % MOD;
        tree[node].sum = (tree[node].sum + len * v) % MOD;
        tree[node].lazy = (tree[node].lazy + v) % MOD;
    }

    void push(int node, int l, int r) {
        if (tree[node].lazy == 0 || l == r) return;

        int mid = (l + r) / 2;
        long long v = tree[node].lazy;

        apply(node * 2, l, mid, v);
        apply(node * 2 + 1, mid + 1, r, v);

        tree[node].lazy = 0;
    }

    void update(int node, int l, int r, int ql, int qr) {
        if (ql > r || qr < l) return;

        if (ql <= l && r <= qr) {
            apply(node, l, r, 1);
            return;
        }

        push(node, l, r);
        int mid = (l + r) / 2;

        update(node * 2, l, mid, ql, qr);
        update(node * 2 + 1, mid + 1, r, ql, qr);

        tree[node].sum =
            (tree[node * 2].sum + tree[node * 2 + 1].sum) % MOD;
        tree[node].sq =
            (tree[node * 2].sq + tree[node * 2 + 1].sq) % MOD;
    }

public:
    int sumCounts(vector<int>& nums) {
        n = nums.size();
        tree.assign(4 * n, Node());
        vector<int> last(100001, -1);

        long long current = 0, ans = 0;

        for (int i = 0; i < n; i++) {
            int left = last[nums[i]] + 1;

            update(1, 0, n - 1, left, i);

            current = tree[1].sq;
            ans = (ans + current) % MOD;

            last[nums[i]] = i;
        }

        return ans;
    }
};