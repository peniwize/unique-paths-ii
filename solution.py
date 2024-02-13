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

class Solution:
    def uniquePathsWithObstacles(self, obstacleGrid: List[List[int]]) -> int:
        #
        # TODO: >>> Under Construction <<<
        #
        return -1

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
    expected = 0
    startTime = time.time()
    result = solution.uniquePathsWithObstacles(obstacleGrid)
    endTime = time.time()
    print("{}:{}({:.6f} sec) result = {}".format(inspect.currentframe().f_code.co_name, type(solution), endTime - startTime, result))
    assert(expected == result)

def test101(solution):
    obstacleGrid = [
        [1]
    ]
    expected = 1
    startTime = time.time()
    result = solution.uniquePathsWithObstacles(obstacleGrid)
    endTime = time.time()
    print("{}:{}({:.6f} sec) result = {}".format(inspect.currentframe().f_code.co_name, type(solution), endTime - startTime, result))
    assert(expected == result)

def test102(solution):
    obstacleGrid = [
    ]
    expected = 0
    startTime = time.time()
    result = solution.uniquePathsWithObstacles(obstacleGrid)
    endTime = time.time()
    print("{}:{}({:.6f} sec) result = {}".format(inspect.currentframe().f_code.co_name, type(solution), endTime - startTime, result))
    assert(expected == result)

if "__main__" == __name__:
    test1(Solution())

    test2(Solution())

    test100(Solution())

    test101(Solution())

    test102(Solution())

# End of "solution.py".
