
class Solution {
public:
    vector<int> countServers(int n, vector<vector<int>>& logs,
                             int x, vector<int>& queries) {

        sort(logs.begin(), logs.end(),
             [](vector<int>& a, vector<int>& b) {
                 return a[1] < b[1];
             });

        int m = queries.size();

        vector<pair<int,int>> q;

        for (int i = 0; i < m; i++) {
            q.push_back({queries[i], i});
        }

        sort(q.begin(), q.end());

        unordered_map<int, int> mp;

        vector<int> ans(m);

        int left = 0, right = 0;
        int active = 0;

        for (auto [t, idx] : q) {

            int start = t - x;

            while (right < logs.size() && logs[right][1] <= t) {

                int id = logs[right][0];

                if (mp[id] == 0) {
                    active++;
                }

                mp[id]++;
                right++;
            }

            while (left < right && logs[left][1] < start) {

                int id = logs[left][0];

                mp[id]--;

                if (mp[id] == 0) {
                    active--;
                }

                left++;
            }

            ans[idx] = n - active;
        }

        return ans;
    }
};
