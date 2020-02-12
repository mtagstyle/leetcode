/******************************************************************************
Amazon's Buzzword Toys Solution
*******************************************************************************/

#include <iostream>
#include <list>
#include <unordered_map>
#include <algorithm>
#include <string>
#include <string.h>
#include <queue>

using namespace std;

class ToyFrequencyInfo
{
public:
    ToyFrequencyInfo(const string& name) : mToyName(name) {}
    
    bool operator< (const ToyFrequencyInfo& rhs) const
    {
        if( mTotalOccurrences != rhs.mTotalOccurrences )
        {
            return mTotalOccurrences < rhs.mTotalOccurrences;
        }
        else if( mQuoteOccurrences != rhs.mQuoteOccurrences )
        {
            return mQuoteOccurrences < rhs.mQuoteOccurrences;
        }
        
        else
        {
            return !lexicographical_compare( mToyName.begin(), mToyName.end(),
                                             rhs.mToyName.begin(), mToyName.end());
        }
        
    }
    
    string       mToyName;
    uint32_t     mTotalOccurrences = 0;
    uint32_t     mQuoteOccurrences = 0;
};

void updateSet(unordered_map<string, ToyFrequencyInfo>& occurrenceMap, 
               string                             quote)
{
    // Tokenize, and to_lower
    const char* tokens = " !'";
    char* dup = strdup(quote.c_str());
    transform(dup, dup + strlen(dup), dup, ::tolower);
    char* tok = strtok(dup, tokens);
    bool hasOccured = false;
    
    while( tok != nullptr )
    {
        // Look for it in our map
        string key = string(tok);
        auto it = occurrenceMap.find(key);
        
        // If the word is of interest, then update occurence numbers
        if(it != occurrenceMap.end())
        {
            it->second.mTotalOccurrences++;
            
            // If this is the first time the word has appeared in this quote, then count it
            if(!hasOccured)
            {
                it->second.mQuoteOccurrences++;
                hasOccured = true;
            }
        }
        
        tok = strtok(NULL, tokens);
    }
    
    free(dup);
}

list<string> getTopToys(uint32_t            numToys, 
                        uint32_t            topToys, 
                        const list<string>& toys, 
                        uint32_t            numQuotes, 
                        const list<string>& quotes)
{
    // First, pre-seed the map with topToys, so we know what we're looking for
    unordered_map<string, ToyFrequencyInfo> occurrenceMap;
    for(const string& toy : toys)
    {
        string tmp = toy;
        transform(toy.begin(), toy.end(), tmp.begin(), ::tolower);
        occurrenceMap.insert(make_pair(tmp, ToyFrequencyInfo(tmp)));
    }
    
    // Go through the quotes and update our occurence set (O(n))
    for(const string& quote : quotes)
    {
        updateSet(occurrenceMap, quote);
    }

    // Now that our occurrence map has been parsed, and populated, find the largest values by implementing a heap (O(k))
    priority_queue<ToyFrequencyInfo> q;
    for(auto it : occurrenceMap)
    {
        q.push(it.second);
    }
    
    // Get the top K values (O(k))
    list<string> ret_val;
    for(uint32_t i = 0 ; i < topToys; i++ )
    {
        ret_val.push_back(q.top().mToyName);
        q.pop();
    }
    return ret_val;
}

int main()
{
    list<string> toys = {"elmo", "elsa", "legos", "drone", "tablet", "warcraft"};

    list<string> quotes = { "Elmo is the hottest of the season! Elmo will be on every kid's wishlist!",
                            "The new Elmo dolls are super high quality",
                            "Expect the Elsa dolls to be very popular this year, Elsa!",
                            "Elsa and Elmo are the toys I'll be buying for my kids, Elsa is good",
                            "For parents of older kids, look into buying them a drone",
                            "Warcraft is slowly rising in popularity ahead of the holiday season" };

    list<string> top_toys = getTopToys(6, 2, toys, 6, quotes);
    
    for(const string& toy : top_toys)
    {
        cout<< toy << endl;
    }
    return 0;
}
