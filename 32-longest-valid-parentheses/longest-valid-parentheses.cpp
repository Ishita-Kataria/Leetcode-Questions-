
class Solution {
public:
    int longestValidParentheses(string s) {
        int n = s.size();
        vector<int> dp(n, 0);
        int ans = 0;

        for (int i = 1; i < n; i++) {
            if (s[i] == ')') {

                if (s[i - 1] == '(') {
                    dp[i] = 2;
                    if (i >= 2)
                        dp[i] += dp[i - 2];
                }

                else if (s[i - 1] == ')') {
                    int j = i - dp[i - 1] - 1;

                    if (j >= 0 && s[j] == '(') {
                        dp[i] = dp[i - 1] + 2;

                        if (j >= 1)
                            dp[i] += dp[j - 1];
                    }
                }
            }

            ans = max(ans, dp[i]);
        }

        return ans;
    }
};