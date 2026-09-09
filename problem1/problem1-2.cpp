#include <iostream>
#include <vector>
using namespace std;

int min_steps(int n) {
    if (n > 1) {
        int steps = 0;

        // Add each prime factor, including repeated factors.
        for (int factor = 2; factor <= n / factor; ++factor) {
            while (n % factor == 0) {
                steps += factor;
                n /= factor;
            }
        }

        // Any remaining factor greater than 1 is prime.
        if (n > 1) {
            steps += n;
        }
        return steps;
    }




    return 0;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    if (!(cin >> n)) {
        cout << 0 << "\n";
        return 0;
    }
    cout << min_steps(n) << "\n";
    return 0;
}