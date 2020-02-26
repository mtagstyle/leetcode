#include <queue>
#include <unordered_map>

class Solution 
{
public:
    int maxIncreaseKeepingSkyline(vector<vector<int>>& grid) 
    {
        // 2-pass solution:
        unordered_map<int, int> max_rows;
        unordered_map<int, int> max_cols;

        // pass 1: Iterate through to get maximum elements
        int y = 0;
        int x = 0;
        for(vector<int>& row : grid)
        {
            x = 0;
            for(int& col : row)
            {
                if(col > max_cols[x])
                {
                    max_cols[x] = col;
                }
                if(col > max_rows[y])
                {
                    max_rows[y] = col;
                }
                x++;
            }
            y++;
        }

        // pass 2: Iterate through each element
        int sum = 0;
        int i = 0;
        int j = 0;
        for(vector<int>& row : grid)
        {
            j = 0;
            for(int& current : row)
            {
                int max_1 = max_rows[i];
                int max_2 = max_cols[j];
                    
                // Take the diff between the smaller value
                if(max_1 < max_2)
                {
                    sum += (max_1 - current);
                }
                else
                {
                    sum += (max_2 - current);
                }
                
                j++;
            }
            
            i++;
        }
        return sum;
    }
};
