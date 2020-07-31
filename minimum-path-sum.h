#ifndef MINIMUMPATHSUM_H
#define MINIMUMPATHSUM_H

/*
 *给定一个包含非负整数的 m x n 网格，请找出一条从左上角到右下角的路径，使得路径上的数字总和为最小。
 * 说明：每次只能向下或者向右移动一步。
 * 示例:
 * 输入:
 * [
 *   [1,3,1],
 *   [1,5,1],
 *   [4,2,1]
 * ]
 * 输出: 7
 * 解释: 因为路径 1→3→1→1→1 的总和最小。
 */

#include <vector>
#include <algorithm>

int minPathSum(vector<vector<int>>& grid) {
    if(!grid.size() || !grid[0].size()) return 0;
    int rows = grid.size(), columns = grid[0].size();

    auto dp = std::vector<std::vector<int>>(rows, std::vector<int>(columns));
    dp[0][0] = grid[0][0];

    for(int i = 1; i < rows; ++i)
        dp[i][0] = dp[i - 1][0] + grid[i][0];
    for(int j = 1; j < columns; ++j)
        dp[0][j] = dp[0][j-1] + grid[0][j];

    for(int i = 1; i < rows; ++i) {
        for(int j = 1; j < columns; ++j) {
            dp[i][j] = std::min(dp[i-1][j], dp[i][j-1]) + grid[i][j];
        }
    }
    return dp[rows-1][columns-1];
}

#endif // MINIMUMPATHSUM_H
