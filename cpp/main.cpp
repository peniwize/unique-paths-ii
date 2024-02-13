/*!
    \file "main.cpp"

    Author: Matt Ervin <matt@impsoftware.org>
    Formatting: 4 spaces/tab (spaces only; no tabs), 120 columns.
    Doc-tool: Doxygen (http://www.doxygen.com/)

    https://leetcode.com/problems/unique-paths-ii/
*/

//!\sa https://github.com/doctest/doctest/blob/master/doc/markdown/main.md
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "utils.hpp"

/*
    You are given an m x n integer array grid. There is a robot initially 
    located at the top-left corner (i.e., grid[0][0]). The robot tries to 
    move to the bottom-right corner (i.e., grid[m - 1][n - 1]). The robot 
    can only move either down or right at any point in time.

    An obstacle and space are marked as 1 or 0 respectively in grid. A path 
    that the robot takes cannot include any square that is an obstacle.

    Return the number of possible unique paths that the robot can take to 
    reach the bottom-right corner.

    The testcases are generated so that the answer will be 
    less than or equal to 2 * 109.

    Constraints:

        * m == obstacleGrid.length
        * n == obstacleGrid[i].length
        * 1 <= m, n <= 100
        * obstacleGrid[i][j] is 0 or 1.
*/

class Solution {
public:
    int uniquePathsWithObstacles(vector<vector<int>>& obstacleGrid) {

//
//!\todo TODO: >>> Under Construction <<<
//
return -1;

    }
};

// {----------------(120 columns)---------------> Module Code Delimiter <---------------(120 columns)----------------}

namespace doctest {
    const char* testName() noexcept { return doctest::detail::g_cs->currentTest->m_name; }
} // namespace doctest {

TEST_CASE("Case 1")
{
    cerr << doctest::testName() << '\n';
    vector<vector<int>> obstacleGrid = {
        {0,0,0},
        {0,1,0},
        {0,0,0}
    };
    int const expected = 2;
    auto solution = Solution{};
    { // New scope.
        auto const start = std::chrono::steady_clock::now();
        auto const result = solution.uniquePathsWithObstacles(obstacleGrid);
        CHECK(expected == result);
        cerr << "Elapsed time: " << elapsed_time_t{start} << '\n';
    }
    cerr << "\n";
}

TEST_CASE("Case 2")
{
    cerr << doctest::testName() << '\n';
    vector<vector<int>> obstacleGrid = {
        {0,1},
        {0,0}
    };
    int const expected = 1;
    auto solution = Solution{};
    { // New scope.
        auto const start = std::chrono::steady_clock::now();
        auto const result = solution.uniquePathsWithObstacles(obstacleGrid);
        CHECK(expected == result);
        cerr << "Elapsed time: " << elapsed_time_t{start} << '\n';
    }
    cerr << "\n";
}

/*
    End of "main.cpp"
*/
