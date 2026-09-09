#include<iostream>
#include<vector>
using namespace std;

vector<int> min_multiplications(int n) {
    vector<int> powers;

    //TODO : complete min multiplication


    return powers;
}

int main(){

    int n;
    cin >> n;

    
    vector<int> steps = min_multiplications(n);
    cout << steps.size() - 1 << " ";
    for (int step : steps) {
        cout << step << " ";
    }

    return 0;
}