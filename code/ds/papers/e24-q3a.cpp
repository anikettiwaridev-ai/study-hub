#include <iostream>
#include <vector>
using namespace std;

// #region answer
vector<int> sjf_scheduling(vector<pair<int, int>> tasks) {   // (task_id, processing_time)
    for (int i = 1; i < (int) tasks.size(); i++) {            // insertion sort on time
        pair<int, int> cur = tasks[i];
        int j = i - 1;
        while (j >= 0 && tasks[j].second > cur.second) {      // > (not >=): equal times keep arrival order
            tasks[j + 1] = tasks[j];
            j--;
        }
        tasks[j + 1] = cur;
    }
    vector<int> order;
    for (auto& t : tasks) order.push_back(t.first);
    return order;
}
// #endregion answer

int main() {
    vector<pair<int, int>> tasks = {{1, 6}, {2, 2}, {3, 8}, {4, 2}, {5, 4}};
    for (int id : sjf_scheduling(tasks)) cout << id << " ";
    cout << endl;
    return 0;
}
