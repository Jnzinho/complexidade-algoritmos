#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    while (cin >> n) {
        vector<long long> cards(n);
        for (int i = 0; i < n; ++i) {
            cin >> cards[i];
        }

        vector<long long> dp(n);
        for (int i = 0; i < n; ++i) {
            dp[i] = cards[i];
        }

        for (int len = 2; len <= n; ++len) {
            for (int i = 0; i + len - 1 < n; ++i) {
                int j = i + len - 1;
                long long take_left = cards[i] - dp[i + 1];
                long long take_right = cards[j] - dp[i];
                dp[i] = max(take_left, take_right);
            }
        }

        long long total = 0;
        for (long long value : cards) {
            total += value;
        }

        long long diff = dp[0];
        long long alberto = (total + diff) / 2;
        cout << alberto << '\n';
    }

    return 0;
}
