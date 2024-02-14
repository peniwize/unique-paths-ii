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

/*
    This solution is virtually identical to problem 62 - Unique Paths.
    See the comments on 'Solution3_DP_BottomUp()' in:
        * https://leetcode.com/problems/unique-paths-ii/solutions/4723321/python-brute-force-dp-full-explanation-t-o-m-n-s-o-1/
        * https://leetcode.com/problems/unique-paths/solutions/4718603/python-brute-force-dp-full-explanation-t-o-m-n-s-o-n/
        * https://github.com/peniwize/unique-paths.git

    Time = O(m*n)
           m*n: Every cell in the grid is visited.

    Space = O(n)
            One grid row is allocated because greater range than int is required.
*/
class Solution {
public:
    int uniquePathsWithObstacles(vector<vector<int>>& obstacleGrid) {
        int const M = obstacleGrid.size();
        int const N = obstacleGrid[0].size();
        int_fast64_t cache[N];
        
        auto const lastRow = obstacleGrid[M - 1];
        for (int idx = N; idx; --idx) {
            if (1 == lastRow[idx - 1]) {
                std::fill_n(cache, idx, 0);
                break;
            }
            cache[idx - 1] = 1;
        }

        for (int y = M - 2; 0 <= y; --y) {
            auto const& row = obstacleGrid[y];
            
            int const x = N - 1;
            if (1 == row[x]) { cache[x] = 0; }

            for (int x = N - 2; 0 <= x; --x) {
                assert((std::numeric_limits<decay_t<decltype(cache[0])>>::max)() - cache[x] >= cache[x + 1]);
                cache[x] = 1 == row[x] ? 0 : cache[x] + cache[x + 1];
            }
        }

        return cache[0];
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

TEST_CASE("Case 3")
{
    cerr << doctest::testName() << '\n';
    vector<vector<int>> obstacleGrid = {
        {0,0},
        {0,1}
    };
    int const expected = 0;
    auto solution = Solution{};
    { // New scope.
        auto const start = std::chrono::steady_clock::now();
        auto const result = solution.uniquePathsWithObstacles(obstacleGrid);
        CHECK(expected == result);
        cerr << "Elapsed time: " << elapsed_time_t{start} << '\n';
    }
    cerr << "\n";
}

TEST_CASE("Case 4")
{
    cerr << doctest::testName() << '\n';
    vector<vector<int>> obstacleGrid = {
        {0,0,0,1,0,0,0,0,0,1,0,0,0,0,0,1,0,1,1,0,0,1,0,1,1,0,1,0,0,1,0,0,0,1,0,0},
        {0,0,1,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,1,0,1,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0},
        {1,0,0,1,0,0,0,0,0,1,0,0,0,0,1,0,0,0,0,0,0,0,0,1,0,1,0,1,0,1,0,0,1,0,0,0},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,1,1,0,0,0,1,0,0,0,0,0,0,1,0,0,1,0,1},
        {0,0,0,1,0,0,0,0,0,0,0,1,1,0,0,1,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0},
        {0,0,1,0,0,0,1,1,0,0,1,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,1,1,0,0,1,0,0,1,0,0},
        {0,0,0,0,0,0,1,0,0,0,1,1,0,1,1,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,1,0,0,1,0,0},
        {1,1,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,1,0,0,1,0,1,1,0,0,0,1},
        {0,0,0,0,1,0,0,1,0,1,1,1,0,0,0,1,0,0,1,0,1,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0},
        {0,0,0,1,0,0,0,0,0,0,0,0,0,1,1,1,0,1,0,0,1,1,0,0,0,0,0,0,0,0,0,1,1,0,0,0},
        {1,0,1,0,1,1,0,1,0,1,0,0,1,0,0,0,0,0,1,0,0,0,0,1,1,1,0,0,0,0,1,0,0,0,1,0},
        {0,0,0,0,0,0,1,0,0,1,1,0,0,1,0,0,0,0,1,0,0,1,1,0,0,0,0,0,1,0,0,1,0,0,0,1},
        {0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,1,0,0,1,0,0,0,1,0,0,1,0,0,0},
        {1,0,0,0,0,0,1,0,0,0,0,0,0,1,0,0,1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,1,0,1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0},
        {0,1,0,0,1,0,0,0,0,0,1,0,1,1,0,0,0,1,0,0,0,0,0,0,0,0,1,0,0,1,0,0,0,0,0,0},
        {0,0,0,0,1,0,0,0,1,0,0,0,0,1,0,0,1,1,0,0,0,0,1,0,0,0,0,0,1,0,0,0,0,0,0,0},
        {0,0,0,0,0,1,0,0,1,1,0,0,0,0,0,0,0,0,1,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,1,0},
        {0,0,1,0,1,0,1,0,0,0,0,0,1,0,1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,1,0,0,0,1,1,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0},
        {0,0,0,1,0,1,0,0,1,0,0,0,0,0,1,1,1,0,1,1,1,0,0,1,0,1,0,1,1,1,0,0,0,0,0,0},
        {0,0,1,0,0,0,0,1,1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0},
        {1,1,0,0,0,0,1,0,0,1,1,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0},
        {0,1,0,0,0,1,0,0,0,0,0,1,0,0,0,0,1,0,0,0,0,0,0,1,0,0,0,0,0,0,1,0,0,1,0,0},
        {0,0,0,0,1,0,0,1,0,0,0,0,0,0,1,0,0,1,0,1,1,1,0,0,0,0,0,0,1,0,0,0,1,1,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,1,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0}
    };
    int const expected = 718'991'952;
    auto solution = Solution{};
    { // New scope.
        auto const start = std::chrono::steady_clock::now();
        auto const result = solution.uniquePathsWithObstacles(obstacleGrid);
        CHECK(expected == result);
        cerr << "Elapsed time: " << elapsed_time_t{start} << '\n';
    }
    cerr << "\n";
}

TEST_CASE("Case 100")
{
    cerr << doctest::testName() << '\n';
    vector<vector<int>> obstacleGrid = {
        {0},
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

TEST_CASE("Case 101")
{
    cerr << doctest::testName() << '\n';
    vector<vector<int>> obstacleGrid = {
        {1},
    };
    int const expected = 0;
    auto solution = Solution{};
    { // New scope.
        auto const start = std::chrono::steady_clock::now();
        auto const result = solution.uniquePathsWithObstacles(obstacleGrid);
        CHECK(expected == result);
        cerr << "Elapsed time: " << elapsed_time_t{start} << '\n';
    }
    cerr << "\n";
}

TEST_CASE("Case 102")
{
    cerr << doctest::testName() << '\n';
    vector<vector<int>> obstacleGrid = {
        {0,1},
        {1,0},
    };
    int const expected = 0;
    auto solution = Solution{};
    { // New scope.
        auto const start = std::chrono::steady_clock::now();
        auto const result = solution.uniquePathsWithObstacles(obstacleGrid);
        CHECK(expected == result);
        cerr << "Elapsed time: " << elapsed_time_t{start} << '\n';
    }
    cerr << "\n";
}

TEST_CASE("Case 103")
{
    cerr << doctest::testName() << '\n';
    vector<vector<int>> obstacleGrid = {
        {0,0,0,0},
        {0,0,0,0},
        {0,0,0,1},
        {0,0,1,0}
    };
    int const expected = 0;
    auto solution = Solution{};
    { // New scope.
        auto const start = std::chrono::steady_clock::now();
        auto const result = solution.uniquePathsWithObstacles(obstacleGrid);
        CHECK(expected == result);
        cerr << "Elapsed time: " << elapsed_time_t{start} << '\n';
    }
    cerr << "\n";
}

TEST_CASE("Case 104")
{
    cerr << doctest::testName() << '\n';
    vector<vector<int>> obstacleGrid = {
        {0,0,0,0,0,0,0,0,0},
        {0,0,1,1,0,0,0,0,0},
        {0,0,0,0,0,1,0,0,1},
        {0,0,0,0,0,1,0,0,0},
        {0,0,0,0,0,0,0,0,0}
    };
    int const expected = 59;
    auto solution = Solution{};
    { // New scope.
        auto const start = std::chrono::steady_clock::now();
        auto const result = solution.uniquePathsWithObstacles(obstacleGrid);
        CHECK(expected == result);
        cerr << "Elapsed time: " << elapsed_time_t{start} << '\n';
    }
    cerr << "\n";
}

TEST_CASE("Case 105")
{
    cerr << doctest::testName() << '\n';
    vector<vector<int>> obstacleGrid = {
        {0,0,0,0,0},
        {0,0,0,0,0},
        {0,0,0,0,1},
        {0,0,0,0,0},
        {0,0,0,1,0}
    };
    int const expected = 20;
    auto solution = Solution{};
    { // New scope.
        auto const start = std::chrono::steady_clock::now();
        auto const result = solution.uniquePathsWithObstacles(obstacleGrid);
        CHECK(expected == result);
        cerr << "Elapsed time: " << elapsed_time_t{start} << '\n';
    }
    cerr << "\n";
}

TEST_CASE("Case 106")
{
    cerr << doctest::testName() << '\n';
    vector<vector<int>> obstacleGrid = {
        {0},
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
