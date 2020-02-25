#include <unordered_map>

class Solution {
public:
    vector<vector<int>> groupThePeople(vector<int>& groupSizes) 
    {
        vector<vector<int>> groups;
        unordered_map<int, vector<int>> map;
        // Iterate through the array of each ID
        int id = 0;
        for(int group_size: groupSizes)
        {
            // Insert into map, where the key is the group size, and the value is a vector of people IDs
            map[group_size].emplace_back(id);
            if(map[group_size].size() >= group_size)
            {
                groups.emplace_back(move(map[group_size]));
            }
            id++;
        }
        
        return groups;
    }
};
