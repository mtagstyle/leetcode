directions = [[-1,0], [0,-1], [1,0], [0,1]] # left, up, right, down

def print_temp(tmp_grid):
    grid_string = ""
    
    for y, rows in enumerate(tmp_grid):
        for x, cols in enumerate(rows):
            grid_string += str(cols)
            
        grid_string += "\n"
    
    #print(grid_string)

def BFS(x, y, grid, tmp_grid, rows, cols):
    # Mark the current direction as visited
    tmp_grid[y][x] = 1
    
    for direction in directions:
        new_x = x + direction[0]
        new_y = y + direction[1]
        
        if new_x >= 0 and new_y >= 0 and new_x < cols and new_y < rows:
            if not tmp_grid[new_y][new_x] and grid[new_y][new_x] == "1":
                #print("Doing BFS for: x={} y={}".format(new_x, new_y))
                BFS(new_x, new_y, grid, tmp_grid, rows, cols)
                
class Solution(object):
    def numIslands(self, grid):
        """
        :type grid: List[List[str]]
        :rtype: int
        """
        num_islands = 0
        # Origin is top left
        x = 0
        y = 0
        
        try:
            rows = len(grid)
            cols = len(grid[0])
        except IndexError:
            return 0
        
        tmp_grid = []
        
        for row in range(rows):
            tmp_grid.append([])
            for col in range(cols):
                tmp_grid[row].append(None)
        
        #print("Rows: {} Cols: {}".format(rows, cols))
        
        # Iterate through each element O(n), this can probably be optimized
        for y, row in enumerate(grid):
            for x, column in enumerate(row):
                #print("grid[{}][{}]={} tmp_grid[{}][{}]={}".format(y,x,grid[y][x], y,x,tmp_grid[y][x]))
                if grid[y][x] == "1" and not tmp_grid[y][x]:
                    #print("Doing BFS for: x={} y={}".format(x, y))
                    BFS(x, y, grid, tmp_grid, rows, cols)
                    num_islands += 1
                #print("grid[{}][{}]={} tmp_grid[{}][{}]={}".format(y,x,grid[y][x], y,x,tmp_grid[y][x]))
                #print("----")

        return num_islands
                    
