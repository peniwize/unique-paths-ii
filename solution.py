# Start of "solution.py".

from collections import deque
import inspect
import time
from typing import List
from typing import Optional
from typing import Set

"""
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
"""

"""
    This solution is virtually identical to problem 62 - Unique Paths.
    The following resources include the full explanation:
        * https://leetcode.com/problems/unique-paths/solutions/4718603/python-brute-force-dp-full-explanation-t-o-m-n-s-o-n/
        * https://github.com/peniwize/unique-paths.git

    The primary difference between this problem (63 - Unique Paths II) and
    leetcode problem 62 (Unique Paths) is that this problem allows cells in
    the grid to be blocked, which results in zero (0) paths from the blocked
    cell to the destination cell in the lower right corner.  Blocked cells in
    the following example are denoted with '#'.  Review the explanation in 
    "62 - Unique Paths" so this makes more sense.  The numbers in the grid are
    calculated from the bottom right corner, the recursion base case, to the 
    top left corner (the start point).

      n  0    1    2    3    4    5    6    7    8
    m +------+------+------+------+------+----+----+
    0 | 59 | 34 | 24 | 24 | 24 | 16 |  9 |  2 |  0 |
      +------+------+------+------+------+----+----+
    1 | 25 | 10 | #0 | #0 |  8 |  7 |  7 |  2 |  0 |
      +------+------+------+------+------+----+----+
    2 | 15 | 10 |  6 |  3 |  1 | #0 |  5 |  2 | #0 |
      +------+------+------+------+------+----+----+
    3 |  5 |  4 |  3 |  2 |  1 | #0 |  3 |  2 |  1 |
      +------+------+------+------+------+----+----+
    4 |  1 |  1 |  1 |  1 |  1 |  1 |  1 |  1 |  1 |
      +------+------+------+------+------+----+----+
    
    Time = O(2**[m+n])

    Space = O(m+n)  [call stack]
"""
class Solution1_BruteForce:
    def uniquePathsWithObstacles(self, obstacleGrid: List[List[int]]) -> int:
        M = len(obstacleGrid)
        N = len(obstacleGrid[0])
        def __helper(obstacleGrid: List[List[int]], x: int = 0, y: int = 0) -> int:
            if M == y or N == x:
                return 0
            if 1 == obstacleGrid[y][x]:
                return 0
            if M - 1 == y and N - 1 == x:
                return 1 if 0 == obstacleGrid[y][x] else 0
            return __helper(obstacleGrid, x + 1, y) \
                   + __helper(obstacleGrid, x, y + 1)
        return __helper(obstacleGrid);

"""
    This solution caches the result for every coordinate (when there are no 
    blocked cells - the worse case scenario) in the 2D grid, which prevents 
    all sub-problems from being solved more than once.  This results in each 
    cell in the grid being visited once.  While some cells are technically 
    visited more than once (to retrieve the memoized value) the work done 
    during each visit is constant.

    Time = O(m*n)
           m*n: number of paths when there are no blocked cells.

    Space = O(m+n + m*n)
            m+n: max call stack depth (length of longest path).
            m*n: memoized values.
"""
class Solution2_TopDownDP:
    def uniquePathsWithObstacles(self, obstacleGrid: List[List[int]]) -> int:
        M = len(obstacleGrid)
        N = len(obstacleGrid[0])
        def __helper(obstacleGrid: List[List[int]], x: int = 0, y: int = 0, cache = {}) -> int:
            if M == y or N == x:
                return 0
            if 1 == obstacleGrid[y][x]:
                return 0
            if M - 1 == y and N - 1 == x:
                return 1 if 0 == obstacleGrid[y][x] else 0
            if (x, y) in cache:
                return cache[(x, y)]
            result = __helper(obstacleGrid, x + 1, y, cache) \
                     + __helper(obstacleGrid, x, y + 1, cache)
            cache[(x, y)] = result
            return result

        return __helper(obstacleGrid);

"""
    This solution is virtually identical to problem 62 - Unique Paths.
    See the comments on 'Solution3_DP_BottomUp()' in:
        * https://leetcode.com/problems/unique-paths/solutions/4718603/python-brute-force-dp-full-explanation-t-o-m-n-s-o-n/
        * https://github.com/peniwize/unique-paths.git

    Time = O(m*n)
           m*n: Every cell in the grid is visited.

    Space = O(1)
            Grid is modified in place; no additonal space is required.
"""
class Solution3_BottomUpDP:
    def uniquePathsWithObstacles(self, obstacleGrid: List[List[int]]) -> int:
        M = len(obstacleGrid)
        N = len(obstacleGrid[0])

        # Initialize bottom row.
        col = 1
        for i in range(N):
            x = N-i-1
            y = M-1
            if 1 == obstacleGrid[y][x]: col = 0
            obstacleGrid[y][x] = col
        
        # Process rows (bottom to top).
        col = obstacleGrid[M-1][N-1]
        for y in range(M - 2, -1, -1):
            x = N-1
            if 1 == obstacleGrid[y][x]: col = 0
            obstacleGrid[y][x] = col
            
            # Process columns right to left.
            for x in range(N - 2, -1, -1):
                if 1 == obstacleGrid[y][x]:
                    obstacleGrid[y][x] = 0
                else:
                    obstacleGrid[y][x] = obstacleGrid[y][x+1] \
                                         + obstacleGrid[y+1][x]
        
        return obstacleGrid[0][0]

def test1(solution):
    obstacleGrid = [
        [0,0,0],
        [0,1,0],
        [0,0,0]
    ]
    expected = 2
    startTime = time.time()
    result = solution.uniquePathsWithObstacles(obstacleGrid)
    endTime = time.time()
    print("{}:{}({:.6f} sec) result = {}".format(inspect.currentframe().f_code.co_name, type(solution), endTime - startTime, result))
    assert(expected == result)

def test3(solution):
    obstacleGrid = [
        [0,0],
        [0,1]
    ]
    expected = 0
    startTime = time.time()
    result = solution.uniquePathsWithObstacles(obstacleGrid)
    endTime = time.time()
    print("{}:{}({:.6f} sec) result = {}".format(inspect.currentframe().f_code.co_name, type(solution), endTime - startTime, result))
    assert(expected == result)

def test2(solution):
    obstacleGrid = [
        [0,1],
        [0,0]
    ]
    expected = 1
    startTime = time.time()
    result = solution.uniquePathsWithObstacles(obstacleGrid)
    endTime = time.time()
    print("{}:{}({:.6f} sec) result = {}".format(inspect.currentframe().f_code.co_name, type(solution), endTime - startTime, result))
    assert(expected == result)

def test100(solution):
    obstacleGrid = [
        [0]
    ]
    expected = 1
    startTime = time.time()
    result = solution.uniquePathsWithObstacles(obstacleGrid)
    endTime = time.time()
    print("{}:{}({:.6f} sec) result = {}".format(inspect.currentframe().f_code.co_name, type(solution), endTime - startTime, result))
    assert(expected == result)

def test101(solution):
    obstacleGrid = [
        [1]
    ]
    expected = 0
    startTime = time.time()
    result = solution.uniquePathsWithObstacles(obstacleGrid)
    endTime = time.time()
    print("{}:{}({:.6f} sec) result = {}".format(inspect.currentframe().f_code.co_name, type(solution), endTime - startTime, result))
    assert(expected == result)

def test102(solution):
    obstacleGrid = [
        [0,1],
        [1,0]
    ]
    expected = 0
    startTime = time.time()
    result = solution.uniquePathsWithObstacles(obstacleGrid)
    endTime = time.time()
    print("{}:{}({:.6f} sec) result = {}".format(inspect.currentframe().f_code.co_name, type(solution), endTime - startTime, result))
    assert(expected == result)

def test103(solution):
    obstacleGrid = [
        [0,0,0,0],
        [0,0,0,0],
        [0,0,0,1],
        [0,0,1,0]
    ]
    expected = 0
    startTime = time.time()
    result = solution.uniquePathsWithObstacles(obstacleGrid)
    endTime = time.time()
    print("{}:{}({:.6f} sec) result = {}".format(inspect.currentframe().f_code.co_name, type(solution), endTime - startTime, result))
    assert(expected == result)

def test104(solution):
    obstacleGrid = [
        [0,0,0,0,0,0,0,0,0],
        [0,0,1,1,0,0,0,0,0],
        [0,0,0,0,0,1,0,0,1],
        [0,0,0,0,0,1,0,0,0],
        [0,0,0,0,0,0,0,0,0]
    ]
    expected = 59
    startTime = time.time()
    result = solution.uniquePathsWithObstacles(obstacleGrid)
    endTime = time.time()
    print("{}:{}({:.6f} sec) result = {}".format(inspect.currentframe().f_code.co_name, type(solution), endTime - startTime, result))
    assert(expected == result)

def test105(solution):
    obstacleGrid = [
        [0,0,0,0,0],
        [0,0,0,0,0],
        [0,0,0,0,1],
        [0,0,0,0,0],
        [0,0,0,1,0]
    ]
    expected = 20
    startTime = time.time()
    result = solution.uniquePathsWithObstacles(obstacleGrid)
    endTime = time.time()
    print("{}:{}({:.6f} sec) result = {}".format(inspect.currentframe().f_code.co_name, type(solution), endTime - startTime, result))
    assert(expected == result)

def test106(solution):
    obstacleGrid = [
        [0,0,0,0,0],
        [0,0,1,0,0],
        [0,1,0,0,1],
        [0,0,0,0,0],
        [0,0,0,1,0]
    ]
    expected = 2
    startTime = time.time()
    result = solution.uniquePathsWithObstacles(obstacleGrid)
    endTime = time.time()
    print("{}:{}({:.6f} sec) result = {}".format(inspect.currentframe().f_code.co_name, type(solution), endTime - startTime, result))
    assert(expected == result)

if "__main__" == __name__:
    test1(Solution1_BruteForce())
    test1(Solution2_TopDownDP())
    test1(Solution3_BottomUpDP())

    test2(Solution1_BruteForce())
    test2(Solution2_TopDownDP())
    test2(Solution3_BottomUpDP())

    test3(Solution1_BruteForce())
    test3(Solution2_TopDownDP())
    test3(Solution3_BottomUpDP())

    test100(Solution1_BruteForce())
    test100(Solution2_TopDownDP())
    test100(Solution3_BottomUpDP())

    test101(Solution1_BruteForce())
    test101(Solution2_TopDownDP())
    test101(Solution3_BottomUpDP())

    test102(Solution1_BruteForce())
    test102(Solution2_TopDownDP())
    test102(Solution3_BottomUpDP())

    test103(Solution1_BruteForce())
    test103(Solution2_TopDownDP())
    test103(Solution3_BottomUpDP())

    test104(Solution1_BruteForce())
    test104(Solution2_TopDownDP())
    test104(Solution3_BottomUpDP())

    test105(Solution1_BruteForce())
    test105(Solution2_TopDownDP())
    test105(Solution3_BottomUpDP())

    test106(Solution1_BruteForce())
    test106(Solution2_TopDownDP())
    test106(Solution3_BottomUpDP())

# End of "solution.py".
