class Solution {
public:
    int findTargetSumWays(vector<int>& nums, int target) {
        int total = 0;

        for (int num : nums) {
            total += num;
        }

        if (abs(target) > total) {
            return 0;
        }

        if ((total + target) % 2 != 0) {
            return 0;
        }

        int required = (total + target) / 2;

        vector<int> dp(required + 1, 0);
        dp[0] = 1;

        for (int num : nums) {
            for (int j = required; j >= num; j--) {
                dp[j] += dp[j - num];
            }
        }

        return dp[required];
    }
};