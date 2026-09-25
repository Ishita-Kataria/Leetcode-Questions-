class Solution {
public:
    set<string> s;

    void dfs(string exp) {
        int j = exp.find('}');

        if (j == string::npos) {
            s.insert(exp);
            return;
        }

        int i = exp.rfind('{', j);

        string left = exp.substr(0, i);
        string right = exp.substr(j + 1);

        string inside = exp.substr(i + 1, j - i - 1);

        string part = "";

        for (char c : inside) {
            if (c == ',') {
                dfs(left + part + right);
                part = "";
            } else {
                part += c;
            }
        }

        dfs(left + part + right);
    }

    vector<string> braceExpansionII(string expression) {
        dfs(expression);
        return vector<string>(s.begin(), s.end());
    }
};