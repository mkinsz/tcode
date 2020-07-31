#include "lambda.h"
#include "binary-tree-traversal.h"

#include <iostream>
#include <functional>
#include <algorithm>
#include <vector>
#include <utility>
#include <unordered_set>

int main() {
    printf("%.2f\n", 1.0*1234);

    int&& i = 123;
    int&& j = std::move(i);
//    int&& k = i;

    std::cout << j << std::endl;

    std::vector<int> v{1,2,3,4,5, 1};

    std::function<bool(std::vector<int>)> containDuplicate = [](std::vector<int> nums) {
        return nums.size() > std::unordered_set<int>(nums.begin(), nums.end()).size();
    };

    std::cout << containDuplicate(v) << std::endl;

    return 0;
}
