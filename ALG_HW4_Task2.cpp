#include <iostream>
#include <vector>

using namespace std;

void whatPageLost(int totalPage);

int main(void) {
    int n, total;

    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> total;
        whatPageLost(total);
    }

    return 0;
}

void whatPageLost(int totalPage) {
    int curTotal = 0, index = 1;
    vector<int> totals(1,0);
    if (totalPage == 0) cout << 0 << " " << 0 << endl;
    else {
        while (true) {
            if (totals[index-1]+index <= totalPage) {
                totals.push_back(totals[index-1]+index);
                index++;
            } else {
                totals.push_back(totals[index-1]+index);
                break;
            }
        }
        cout << totals[index-1]+index-totalPage << " " << index << endl;
    }
}