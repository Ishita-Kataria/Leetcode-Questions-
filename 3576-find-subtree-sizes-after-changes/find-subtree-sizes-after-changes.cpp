
class Solution {
public:
    vector<int> findSubtreeSizes(vector<int>& parent, string s) {
        int n = parent.size();

        vector<vector<int>> adj(n);

        for (int i = 1; i < n; i++) {
            adj[parent[i]].push_back(i);
        }

        vector<vector<int>> path(26);
        vector<int> ans(n, 0);

        // {node, original parent, state}
        vector<tuple<int, int, int>> st;
        st.push_back({0, -1, 0});

        while (!st.empty()) {
            auto [u, p, state] = st.back();
            st.pop_back();

            int idx = s[u] - 'a';

            if (state == 0) {
                ans[u] = 1;

                path[idx].push_back(u);

                st.push_back({u, p, 1});

                for (int v : adj[u]) {
                    st.push_back({v, u, 0});
                }
            }
            else {
                int newParent = p;

                if (path[idx].size() > 1) {
                    newParent = path[idx][path[idx].size() - 2];
                }

                if (newParent != -1) {
                    ans[newParent] += ans[u];
                }

                path[idx].pop_back();
            }
        }

        return ans;
    }
};
