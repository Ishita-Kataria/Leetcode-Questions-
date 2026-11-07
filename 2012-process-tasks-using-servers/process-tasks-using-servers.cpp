
class Solution {
public:
    vector<int> assignTasks(vector<int>& servers, vector<int>& tasks) {

        int n = servers.size();

        priority_queue<
            pair<int,int>,
            vector<pair<int,int>>,
            greater<pair<int,int>>
        > available;

        priority_queue<
            tuple<long long,int,int>,
            vector<tuple<long long,int,int>>,
            greater<tuple<long long,int,int>>
        > busy;

        for (int i = 0; i < n; i++) {
            available.push({servers[i], i});
        }

        vector<int> ans;

        long long time = 0;

        for (int i = 0; i < tasks.size(); i++) {

            time = max(time, (long long)i);

            // Free all servers whose tasks are completed
            while (!busy.empty() &&
                   get<0>(busy.top()) <= time) {

                auto [finish, weight, idx] = busy.top();
                busy.pop();

                available.push({weight, idx});
            }

            // If no server is available, wait
            if (available.empty()) {

                time = get<0>(busy.top());

                while (!busy.empty() &&
                       get<0>(busy.top()) <= time) {

                    auto [finish, weight, idx] = busy.top();
                    busy.pop();

                    available.push({weight, idx});
                }
            }

            // Select the best available server
            auto [weight, idx] = available.top();
            available.pop();

            ans.push_back(idx);

            // Mark server as busy
            busy.push({
                time + tasks[i],
                weight,
                idx
            });
        }

        return ans;
    }
};
