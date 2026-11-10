class Solution {
public:
    int climbStairs(int n, vector<int>& costs) {

        vector<int> dp(n + 1, INT_MAX);

        dp[0] = 0;

        for (int i = 1; i <= n; i++) {

            for (int j = max(0, i - 3); j < i; j++) {

                int jump = i - j;

                int cost = costs[i - 1] + jump * jump;

                dp[i] = min(dp[i], dp[j] + cost);
            }
        }

        return dp[n];
    }
};