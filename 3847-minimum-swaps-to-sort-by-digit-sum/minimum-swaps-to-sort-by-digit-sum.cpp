class Solution {
public:
    int digitSum(int x) {
        int sum = 0;
        while (x > 0) {
            sum += x % 10;
            x /= 10;
        }
        return sum;
    }

    int minSwaps(vector<int>& nums) {
        int n = nums.size();
        vector<int> sorted = nums;

        sort(sorted.begin(), sorted.end(), [&](int a, int b) {
            int x = digitSum(a);
            int y = digitSum(b);

            if (x == y) return a < b;
            return x < y;
        });

        unordered_map<int, int> target;

        for (int i = 0; i < n; i++) {
            target[sorted[i]] = i;
        }

        vector<bool> visited(n, false);
        int swaps = 0;

        for (int i = 0; i < n; i++) {
            if (visited[i] || target[nums[i]] == i)
                continue;

            int j = i;
            int cycle = 0;

            while (!visited[j]) {
                visited[j] = true;
                j = target[nums[j]];
                cycle++;
            }

            swaps += cycle - 1;
        }

        return swaps;
    }
};