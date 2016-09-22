#include <iostream>
#include <vector>
#include <memory>

class TreeNode {
    public:
        size_t start, end;
        std::shared_ptr<TreeNode> left, right;

        TreeNode(size_t a_start, size_t a_end) : start(a_start), end(a_end){
            if (a_start < a_end) {
                size_t mid = (a_start+a_end)/2;
                left = std::make_shared<TreeNode>(a_start, mid);
                right = std::make_shared<TreeNode>(mid+1, a_end);
            }
            else {
                left = nullptr;
                right = nullptr;
            }
        }
};

class solution {
    public:
        int countRangeSum(std::vector<int> & nums, int lower, int upper) {

        }
};

int main() {
    std::vector<int> nums{-2,5,-1};
    int lower = -2, upper = 2;

    solution soln;
    int count = soln.countRangeSum(nums, lower, upper);

    std::cout << "The count of range sum is:\n";
    std::cout << count << std::endl; 
}
