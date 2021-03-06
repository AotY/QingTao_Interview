#include <iostream>
#include <vector>

using namespace std;


class NumArray {
private:
    int n;
    vector<int> sums;

    vector<int> data;
public:
    NumArray(vector<int> nums) {

        n = nums.size();

        // 保留nums副本
        data = nums;

        sums = vector<int>(n + 1);

        // 初始化
        sums[0] = 0;

        for (int i = 1; i <= n; ++i) {
            sums[i] = sums[i - 1] + nums[i - 1];
        }

    }

    // 更新操作
    void update(int index, int val) {
        if (index < 0 || index >= n) {
            throw invalid_argument("index out of range");
        }
        data[index] = val;

        for (int i = index + 1; i <= n; ++i) {
            sums[i] = sums[i - 1] + data[i - 1];
        }
    }

    int sumRange(int i, int j) {
        if (i < 0 || j >= n) {
            throw invalid_argument("i or j out of range");
        }

        return sums[j + 1] - sums[i];
    }

};

/**
 * Your NumArray object will be instantiated and called as such:
 * NumArray obj = new NumArray(nums);
 * int param_1 = obj.sumRange(i,j);
 */

int main() {

    vector<int> nums = {-2, 0, 3, -5, 2, -1};
    NumArray numArray(nums);

    cout << numArray.sumRange(2, 5) << endl;

    std::cout << "Hello, World!" << std::endl;
    return 0;
}