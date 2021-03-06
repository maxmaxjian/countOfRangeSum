#include <iostream>
#include <vector>
#include <memory>
#include <unordered_map>
#include <functional>
#include <queue>
#include <numeric>

using std::shared_ptr;
using std::unordered_map;

class TreeNode {
    public:
        size_t start, end;
        shared_ptr<TreeNode> left, right;

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

        TreeNode(size_t a_start, size_t a_end, const shared_ptr<TreeNode> & lchild, const shared_ptr<TreeNode> & rchild)
            : start(a_start), end(a_end), left(lchild), right(rchild)
        {
        }

        TreeNode(){}

        bool equals(const TreeNode & other) {
            return start == other.start && end == other.end;
        }

        bool overlap(const shared_ptr<TreeNode> & other, shared_ptr<TreeNode> & inter) {
            size_t x1 = std::max(start, other->start), x2 = std::min(end, other->end);
            if (x1 <= x2) {
                inter->start = x1;
                inter->end = x2;
                return true;
            }
            else
                return false;
        }
};

class NodeHasher {
    public:
        size_t operator()(const shared_ptr<TreeNode> & node) const {
            return std::hash<size_t>()(node->start) ^ std::hash<size_t>()(node->end);
        }
};

bool operator==(const shared_ptr<TreeNode> & n1, const shared_ptr<TreeNode> & n2) {
    return n1->equals(*n2);
}

class solution {
    private:
        std::vector<int> vec;
        shared_ptr<TreeNode> root;
        unordered_map<shared_ptr<TreeNode>, int, NodeHasher> result;

    public:
        int countRangeSum(std::vector<int> & nums, int lower, int upper) {
            root = std::make_shared<TreeNode>(0, nums.size()-1);
            std::queue<shared_ptr<TreeNode>> qu;
            qu.push(root);
            while (!qu.empty()) {
                auto curr = qu.front();
                qu.pop();
                result[curr] = sumRange_impl(nums, curr->start, curr->end);
                if (curr->left != nullptr)
                    qu.push(curr->left);
                if (curr->right != nullptr)
                    qu.push(curr->right);
            }

            int counts = 0;
            for (size_t i = 0; i < nums.size(); ++i) {
                for (size_t j = i; j < nums.size(); ++j) 
                {   
                    int sum = sumRange(nums, i, j);
                    if (sum >= lower && sum <= upper)
                        counts++;
                }
            }
            return counts;
        }

    private:
        int sumRange(const std::vector<int> & nums, size_t start, size_t end) {
            auto found = find_union(root, start, end);
            int sum = 0;
            for (auto node : found)
                sum += result[node];
            return sum;
        }

        int sumRange_impl(const std::vector<int> & nums, size_t start, size_t end) {
            return std::accumulate(nums.begin()+start, nums.begin()+end+1, 0);
        }

        std::vector<shared_ptr<TreeNode>> find_union(const shared_ptr<TreeNode> & root, size_t a_start, size_t a_end) {
            std::vector<shared_ptr<TreeNode>> vec;
            auto curr = std::make_shared<TreeNode>(a_start, a_end, nullptr, nullptr);
            auto temp = std::make_shared<TreeNode>();
            bool isOverlapped  = curr->overlap(root, temp);
            if (isOverlapped && temp == root ) {
                vec.push_back(root);
            }
            else if (isOverlapped && !temp->equals(*root)){
                auto left = find_union(root->left, a_start, a_end);
                for (auto elm : left)
                    vec.push_back(elm);
                auto right = find_union(root->right, a_start, a_end);
                for (auto elm : right)
                    vec.push_back(elm);
            }
            return vec;
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
