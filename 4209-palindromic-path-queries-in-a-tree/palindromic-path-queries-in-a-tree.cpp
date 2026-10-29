class Solution {
public:
    vector<bool> palindromePath(int n, vector<vector<int>>& edges,
                                string s, vector<string>& queries) {
        vector<vector<int>> adj(n);

        for (auto &e : edges) {
            adj[e[0]].push_back(e[1]);
            adj[e[1]].push_back(e[0]);
        }

        int LOG = 1;
        while ((1 << LOG) <= n) LOG++;

        vector<vector<int>> up(n, vector<int>(LOG));
        vector<int> tin(n), tout(n), depth(n);
        vector<int> mask(n);
        int timer = 0;

        function<void(int, int)> dfs = [&](int u, int p) {
            tin[u] = timer++;
            up[u][0] = p;
            for (int j = 1; j < LOG; j++)
                up[u][j] = up[up[u][j - 1]][j - 1];

            for (int v : adj[u]) {
                if (v == p) continue;
                depth[v] = depth[u] + 1;
                mask[v] = mask[u] ^ (1 << (s[v] - 'a'));
                dfs(v, u);
            }
            tout[u] = timer - 1;
        };

        mask[0] = 1 << (s[0] - 'a');
        dfs(0, 0);

        auto lca = [&](int u, int v) {
            if (depth[u] < depth[v]) swap(u, v);

            int diff = depth[u] - depth[v];
            for (int j = 0; j < LOG; j++)
                if (diff & (1 << j))
                    u = up[u][j];

            if (u == v) return u;

            for (int j = LOG - 1; j >= 0; j--) {
                if (up[u][j] != up[v][j]) {
                    u = up[u][j];
                    v = up[v][j];
                }
            }
            return up[u][0];
        };

        vector<int> bit(n + 2, 0);

        auto update = [&](int i, int val) {
            for (i++; i <= n; i += i & -i)
                bit[i] ^= val;
        };

        auto query = [&](int i) {
            int res = 0;
            for (i++; i > 0; i -= i & -i)
                res ^= bit[i];
            return res;
        };

        auto rangeUpdate = [&](int l, int r, int val) {
            update(l, val);
            if (r + 1 < n) update(r + 1, val);
        };

        vector<bool> ans;

        for (string q : queries) {
            stringstream ss(q);
            string op;
            int u, v;
            ss >> op >> u;

            if (op == "update") {
                char c;
                ss >> c;
                int change = (1 << (s[u] - 'a')) ^ (1 << (c - 'a'));
                rangeUpdate(tin[u], tout[u], change);
                s[u] = c;
            } else {
                ss >> v;

                int a = lca(u, v);
                int mu = mask[u] ^ query(tin[u]);
                int mv = mask[v] ^ query(tin[v]);

                int pathMask = mu ^ mv ^ (1 << (s[a] - 'a'));

                ans.push_back((pathMask & (pathMask - 1)) == 0);
            }
        }

        return ans;
    }
};