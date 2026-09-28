class Solution {
public:
    vector<string> ans;
    string path;

    void backtrack(int n, int open, int close) {

        if (path.size() == 2 * n) {
            ans.push_back(path);
            return;
        }

        if (open < n) {
            path.push_back('(');

            backtrack(n, open + 1, close);

            path.pop_back();
        }

        if (close < open) {
            path.push_back(')');

            backtrack(n, open, close + 1);

            path.pop_back();
        }
    }

    vector<string> generateParenthesis(int n) {
        backtrack(n, 0, 0);
        return ans;
    }
};