#include <iostream>
#include <vector>

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
