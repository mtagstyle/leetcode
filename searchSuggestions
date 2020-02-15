from collections import OrderedDict

class TrieNode(object):
    def __init__(self, character=""):
        self._character = character
        self._word = ""
        self._dict = OrderedDict()
        self._end = False
    
    def getWord(self):
        return self._word
    
    def getChildrenDict(self):
        return self._dict
    
    def setWord(self, word):
        self._word = word
    
    def isWord(self):
        return self._end
        
    def setWordStatus(self, is_word):
        self._end = is_word
    
class Trie(object):

    def __init__(self):
        """
        Initialize your data structure here.
        """
        self._root = TrieNode()

    def insert(self, word):
        """
        Inserts a word into the trie.
        :type word: str
        :rtype: None
        """
        # Iterate through all characters
        current_node = self._root

        for idx, character in enumerate(word):
            children = current_node.getChildrenDict()
            
            # If the key doesn't exist for the current letter, then create a new node
            if character not in children:
                children[character] = TrieNode(character)
                
                # Update the dictionary on insertion, so it preserves lexicographic order
                new_dict = OrderedDict()
                for c, n in sorted(current_node.getChildrenDict().items()):
                    new_dict[c] = n
                current_node._dict = new_dict

            # Traverse to the next trie node
            current_node = children[character]
        
        current_node.setWordStatus(True)
        current_node.setWord(word)
        
    def search(self, word):
        """
        Returns if the word is in the trie.
        :type word: str
        :rtype: bool
        """
        found = False
        
        # Iterate through all characters
        current_node = self._root
        
        # Traverse the tree
        for idx, character in enumerate(word):
            children = current_node.getChildrenDict()
            
            if character not in children:
                return False
                
            # Traverse to the next trie node
            current_node = children[character]
            
        found = current_node.isWord()
        return found

    def startsWith(self, prefix):
        """
        Returns if there is any word in the trie that starts with the given prefix.
        :type prefix: str
        :rtype: bool
        """
        found = True
        
        # Iterate through all characters
        current_node = self._root
        
        # Traverse the tree
        for idx, character in enumerate(prefix):
            
            children = current_node.getChildrenDict()
            
            if character not in children:
                found = False
                break
                
            # Traverse to the next trie node
            current_node = children[character]
            
        return found

    def getBestMatches(self, prefix, limit):
        """
        Returns a list of products in lexicographic order
        """
       
        # Iterate through all characters
        current_node = self._root
        
        # Traverse the tree
        for idx, character in enumerate(prefix):
            children = current_node.getChildrenDict()
            
            # If a single letter doesnt match in the prefix, then there is no match in the tree
            if character not in children:
                return []
                
            # Traverse to the next trie node
            current_node = children[character]
            
        matches = []
        self.DFS(current_node, limit, matches)
        return matches
    
    def DFS(self, current_node, limit, matches=None):
        """
        Given a trie node, finds all words that are children of the node
        """
        if current_node.isWord():
            matches.append(current_node.getWord())
            # If we've already hit our limit, dont bother recursing
            if len(matches) >= limit:
                return
            
        for character, node in current_node.getChildrenDict().items():                   
            self.DFS(node, limit, matches)
            if len(matches) >= limit:
                return
        
        return

        
class Solution(object):
    def suggestedProducts(self, products, searchWord):
        """
        :type products: List[str]
        :type searchWord: str
        :rtype: List[List[str]]
        """
        suggestion = []

        trie = Trie()
        
        for product in products:
            trie.insert(product)
            
        prefix = ""
        for character in searchWord:
            prefix+=character
            suggestion.append(trie.getBestMatches(prefix, 3))
            
        return suggestion
            
