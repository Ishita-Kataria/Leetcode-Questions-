class Solution {
public:

    bool backtrack(vector<vector<char>>& board, string& word,
                   int r, int c, int index) {

        if (index == word.size())
            return true;

        if (r < 0 || r >= board.size() ||
            c < 0 || c >= board[0].size())
            return false;

        if (board[r][c] != word[index])
            return false;

        char temp = board[r][c];
        board[r][c] = '#';

        bool found =
            backtrack(board, word, r + 1, c, index + 1) ||
            backtrack(board, word, r - 1, c, index + 1) ||
            backtrack(board, word, r, c + 1, index + 1) ||
            backtrack(board, word, r, c - 1, index + 1);

        board[r][c] = temp;

        return found;
    }

    bool exist(vector<vector<char>>& board, string word) {

        for (int i = 0; i < board.size(); i++) {
            for (int j = 0; j < board[0].size(); j++) {

                if (board[i][j] == word[0]) {

                    if (backtrack(board, word, i, j, 0))
                        return true;
                }
            }
        }

        return false;
    }
};