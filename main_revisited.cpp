#include <iostream>
#include <vector>
#include <numeric>

using std::vector;

// class solution {
    // public:
    // O(n^2) solution
    // int countRangeSum(const vector<int> &nums, int lower, int upper)
//       {
//           int count;
//           if (nums.size() == 1)
//           {
//               if (nums.front() >= lower && nums.front() <= upper)
//               {
//                   count = 1;
//               }
//               else
//               {
//                   count = 0;
//               }
//           }
//           else if (nums.size() > 1)
//           {
//               auto copy = nums;
//               copy.erase(copy.begin());
//               int prev_count = countRangeSum(copy, lower, upper);
//               int curr_count = 0;
//               /*if (nums.front() <= upper && nums.front() >= lower) {
//                   curr_count++;
//               }*/
//               std::cout << "Count " << copy.size() << std::endl;
//               for (size_t i = 0; i < copy.size() + 1; i++)
//               {
//                   int temp = std::accumulate(copy.begin(), copy.begin() + i, 0);
//                   if (temp + nums.front() <= upper && temp + nums.front() >= lower)
//                   {
//                       curr_count++;
//                   }
//               }
//               count = prev_count + curr_count;
//           }
//           return count;
//       }
// };

class solution
{
  public:
    int countRangeSum(const vector<int> &nums, int lower, int upper)
    {
        vector<int> sums{nums.front()};
        for (size_t i = 1; i < nums.size(); i++) {
            sums.push_back(sums.back()+nums[i]);
        }
        return countRangeSum_fcn(sums, 0, nums.size()-1, lower, upper);
    }

  private:
    int countRangeSum_fcn(const vector<int> &sums, size_t head, size_t tail, int lower, int upper)
    {
        if (head < tail)
        {
            size_t mid = (head + tail) / 2;
            int left_count = countRangeSum_fcn(sums, head, mid, lower, upper);
            int right_count = countRangeSum_fcn(sums, mid + 1, tail, lower, upper);
            int cross_count(0);
            std::cout << "Count " << (mid-head+1)*(tail-mid) << std:: endl;
            for (size_t i = head; i <= mid; i++)
            {
                for (size_t j = mid + 1; j <= tail; j++)
                {
                    // int temp = std::accumulate(nums.begin() + i, nums.begin() + j + 1, 0);
                    // if (temp >= lower && temp <= upper)
                    // {
                    //     cross_count++;
                    // }
                    if (sums[j]-sums[i] <= upper && sums[j]-sums[i] >= lower) {
                        cross_count++;
                    }
                }
            }
            return left_count + right_count + cross_count;
        }
        else if (head == tail)
        {
            // return (nums[head] >= lower && nums[head] <= upper) ? 1 : 0;
            if (head == 0)
            {
                return sums[head] >= lower && sums[head] <= upper ? 1 : 0;
            }
            else
            {
                return (sums[head] - sums[head - 1] >= lower) && (sums[head] - sums[head - 1] <= upper) ? 1 : 0;
            }
        }
        return 0;
    }
};

int main() {
    vector<int> nums{-2,5,-1,3,2,4,3,2,2,1};
    size_t lower = -2, upper = 2;

    solution soln;
    int count = soln.countRangeSum(nums, lower, upper);
    std::cout << "The number of ranges is: " << std::endl;
    std::cout << count << std::endl;

    return 0;
}