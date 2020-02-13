/******************************************************************************

                              Online C++ Compiler.
               Code, Compile, Run and Debug C++ program online.
Write your code in this editor and press "Run" button to compile and execute it.

*******************************************************************************/

#include <iostream>
#include <list>
#include <unordered_map>
#include <algorithm>
#include <string>
#include <queue>
#include <memory>

using namespace std;

class Grid
{
public:
    Grid(int rows, int cols, const list<list<int>>& grid):
        mRows(rows),
        mCols(cols)
    {
    	for(const list<int>& row : grid)
    	{
    	    vector<int> tmp;
    	    for(int item : row)
    	    {
    	        tmp.push_back(item);
    	    }
    	    mGrid.push_back(tmp);
    	}
    }

    int getValue(int x, int y)
    {
        if(x < 0 || y < 0 || x >= mCols || y >= mRows)
        { 
            return -1;
        }
        else
        {
            return mGrid.at(y).at(x);
        }
    }
    
    void setValue(int x, int y, int value)
    {
        mGrid.at(y).at(x) = value;
    }
    
    string toString()
    {
        string ret;
        
        for(const vector<int>& row : mGrid)
    	{
    	    vector<int> tmp;
    	    for(int item : row)
    	    {
    	        ret += to_string(item) + " ";
    	    }
    	    ret += "\n";
    	}
    	
    	return ret;
    }
private:
    // Vector based access is O(1)
    vector<vector<int>> mGrid;
    int mRows;
    int mCols;
};

typedef struct zombie_cord
{
    int x = 0;
    int y = 0;
} zombie_cord_t;

class Zombie
{
public:
    Zombie(int x, int y, shared_ptr<Grid> grid): 
        mGrid(grid)
    {
        mCords.x = x;
        mCords.y = y;
    }
        
    zombie_cord_t eat()
    {
        zombie_cord_t cords;
        cords.x = -1;
        cords.y = -1;
        
        bool result = checkDirection(cords, -1,  0) || // Left
                      checkDirection(cords,  0, -1) || // Up
                      checkDirection(cords,  1,  0) || // Right
                      checkDirection(cords,  0,  1);   // Down

        // If we actually ate something, then update the grid
        if(result)
        {
            mGrid->setValue(cords.x, cords.y, 1);
        }

        return cords;
    }

    zombie_cord_t getCords() { return mCords; }

protected:
    bool checkDirection(zombie_cord_t& cord, int direction_x, int direction_y)
    {
        bool ret = false;
        int result = mGrid->getValue(mCords.x + direction_x, mCords.y + direction_y);
        
        // Got a hujman
        if(result == 0)
        {
            cord.x = mCords.x + direction_x;
            cord.y = mCords.y + direction_y;
            ret = true;
        }
        
        return ret;
    }

private:
    shared_ptr<Grid> mGrid;
    zombie_cord_t    mCords;
};

queue<shared_ptr<Zombie>> preseedZombies(int rows, int cols, shared_ptr<Grid> grid)
{
    queue<shared_ptr<Zombie>> q;

    for(uint32_t j = 0; j < rows; j++)
    {
        for(uint32_t i = 0; i < cols; i++)
        {
            int result = grid->getValue(i, j);
            
            // Found a zombie
            if(result == 1)
            {
               q.push(make_shared<Zombie>(i, j, grid));
            }
        }
    }
    
    return q;
}

int minHours(int rows, int columns, const list<list<int>>& grid) 
{
	int hours = -1;

    // Make the grids
	shared_ptr<Grid> hashedGrid = make_shared<Grid>(rows, columns, grid);
	cout << hashedGrid->toString();

    // Pre-seed the Q with a list of candidates
    queue<shared_ptr<Zombie>> zombies = preseedZombies(rows, columns, hashedGrid);
	
	while(!zombies.empty())
	{
	    // Process each zombie's turn
	    queue<shared_ptr<Zombie>> tmp_q;
	    while(!zombies.empty())
	    {
	        // Try to eat
	        shared_ptr<Zombie> old_zombie = zombies.front();
	        zombie_cord_t cords = old_zombie->eat();
	        
	        // If the current zombie was able to eat something, then clone the new zombie and push both into the Q
	        if(cords.x != -1 && cords.y != -1)
	        {
	            shared_ptr<Zombie> new_zombie = make_shared<Zombie>(cords.x, cords.y, hashedGrid);
	            tmp_q.push(old_zombie);
	            tmp_q.push(new_zombie);
	        }
	        zombies.pop();
	    }
	    // Copy it back
	    zombies = tmp_q;
	    hours++;
	    
        cout << "Results after hour " << hours << " of the zombie infestation:" << endl;
    	cout << hashedGrid->toString();
	}

	// For each new zombie, add to q
	return hours;
}

int main()
{
    list<list<int>> mtx = 
    {
        {1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1}
    };
    
    int hours = minHours(4, 5, mtx);
    
    return 0;
}
