#ifndef ALGORITHM_PASSBY_H
#define ALGORITHM_PASSBY_H

/* [1,2,3,4,5] k=1 => [5,1,2,3,4]; k=2 => [4,5,1,2,3];
 * 在不考虑额外存储空的情况下，进行数组的旋转
 */

void reverseK() {
    std::vector<int> v{1,2,3,4,5};
    int k = 2;

    for(auto i = 0; i < k; ++i) {
        int&& a = std::move(v.back());
        v.pop_back();
        v.insert(std::begin(v), a);
    }

    for(auto i : v) {
        std::cout << i << std::endl;
    }
}




#endif // ALGORITHM_PASSBY_H
