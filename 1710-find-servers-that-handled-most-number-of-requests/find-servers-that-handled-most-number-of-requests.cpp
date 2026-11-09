class Solution {
public:
    vector<int> busiestServers(int k, vector<int>& arrival, vector<int>& load) {

        set<int> available;

        priority_queue<pair<int, int>,
                       vector<pair<int, int>>,
                       greater<pair<int, int>>> busy;

        vector<int> count(k, 0);

        for (int i = 0; i < k; i++) {
            available.insert(i);
        }

        for (int i = 0; i < arrival.size(); i++) {

            int time = arrival[i];

            // Free all servers whose requests are completed
            while (!busy.empty() && busy.top().first <= time) {
                available.insert(busy.top().second);
                busy.pop();
            }

            // If no server is available, drop the request
            if (available.empty()) {
                continue;
            }

            // Preferred server
            int preferred = i % k;

            // Find preferred or next available server
            auto it = available.lower_bound(preferred);

            // If not found, start from the smallest server
            if (it == available.end()) {
                it = available.begin();
            }

            int server = *it;

            // Remove server from available set
            available.erase(it);

            // Increase request count
            count[server]++;

            // Store finishing time and server number
            busy.push({time + load[i], server});
        }

        // Find maximum requests handled by any server
        int maxi = *max_element(count.begin(), count.end());

        vector<int> ans;

        // Return all servers having maximum requests
        for (int i = 0; i < k; i++) {
            if (count[i] == maxi) {
                ans.push_back(i);
            }
        }

        return ans;
    }
};