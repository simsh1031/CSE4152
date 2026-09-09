#include<iostream>
#include <vector>

using namespace std;

int main(){


    int n;
    cin >> n;
    vector<int> arr(n);
    int max_num;
    
    // TODO : complete Maximum subsequence sum algorithm
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }

    int curr = 0;
    max_num = 0;

    for (int i = 0; i < n; i++) {
        curr += arr[i];
        if (curr < 0) {
            curr = 0;
        }
        if (curr > max_num) {
            max_num = curr;
        }
    }


    cout << max_num;


    return 0;
}