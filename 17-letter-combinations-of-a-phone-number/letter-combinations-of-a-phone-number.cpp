class Solution {
public:

    vector<string> ans;
    string path;

    vector<string> keypad = {
        "", "", "abc", "def",
        "ghi", "jkl", "mno",
        "pqrs", "tuv", "wxyz"
    };

    void backtrack(string &digits, int index) {

        if (index == digits.size()) {
            ans.push_back(path);
            return;
        }

        string letters = keypad[digits[index] - '0'];

        for (char ch : letters) {

            path.push_back(ch);

            backtrack(digits, index + 1);

            path.pop_back();
        }
    }

    vector<string> letterCombinations(string digits) {

        if (digits.empty())
            return {};

        backtrack(digits, 0);

        return ans;
    }
};