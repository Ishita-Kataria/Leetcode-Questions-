
class Solution {
public:
    long long minOperations(vector<int>& nums, int x, int k) {

        int n = nums.size();

        multiset<int> low, high;
        long long lowSum = 0, highSum = 0;

        int target = (x + 1) / 2;

        auto add = [&](int val) {
            if (low.empty() || val <= *low.rbegin()) {
                low.insert(val);
                lowSum += val;
            } else {
                high.insert(val);
                highSum += val;
            }
        };

        auto remove = [&](int val) {
            auto it = low.find(val);

            if (it != low.end()) {
                low.erase(it);
                lowSum -= val;
            } else {
                it = high.find(val);
                high.erase(it);
                highSum -= val;
            }
        };

        auto balance = [&]() {
            while ((int)low.size() > target) {
                int val = *low.rbegin();
                low.erase(prev(low.end()));
                lowSum -= val;

                high.insert(val);
                highSum += val;
            }

            while ((int)low.size() < target) {
                int val = *high.begin();
                high.erase(high.begin());
                highSum -= val;

                low.insert(val);
                lowSum += val;
            }
        };

        vector<long long> cost;

        // Sliding window
        for (int i = 0; i < n; i++) {

            add(nums[i]);

            if (i >= x) {
                remove(nums[i - x]);
            }

            if (i >= x - 1) {

                balance();

                long long median = *low.rbegin();

                long long operations =
                    median * low.size() - lowSum +
                    highSum - median * high.size();

                cost.push_back(operations);
            }
        }

        // Dynamic Programming
        const long long INF = 1e18;

        vector<vector<long long>> dp(
            n + 1, vector<long long>(k + 1, INF)
        );

        for (int i = 0; i <= n; i++) {
            dp[i][0] = 0;
        }

        for (int i = 1; i <= n; i++) {

            for (int j = 1; j <= k; j++) {

                // Skip current element
                dp[i][j] = dp[i - 1][j];

                // Select a window of size x
                if (i >= x && dp[i - x][j - 1] != INF) {

                    dp[i][j] = min(
                        dp[i][j],
                        dp[i - x][j - 1] + cost[i - x]
                    );
                }
            }
        }

        return dp[n][k];
    }
};
