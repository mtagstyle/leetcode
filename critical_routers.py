from collections import defaultdict
import copy
def parseData(num_nodes, num_edges, edges):
    """
        Returns a tuple, where the tuple[0] = node_map, tuple[1] = edge_map
    """
    node_map = defaultdict(set)
    edge_map = {}
    i = 0
    # Iterate through all edges and hash them O(e)
    for edge in edges:
        # Assign a hash, and add it to the edge map
        hash_name = "L" + str(i)
        edge_map[hash_name] = edge
        
        # Populate the node map with edges
        src_node = edge[0]
        dst_node = edge[1]
        node_map[src_node].add(hash_name)
        node_map[dst_node].add(hash_name)
        
        i+=1

    return node_map, edge_map

def deleteNode(node_number, connected_edges, node_map, edge_map):   
    # Get rid of all references to the edges first, hashing everything makes this operation super efficient
    for edge_hash in connected_edges:
        src_node = edge_map[edge_hash][0]
        dst_node = edge_map[edge_hash][1]
        node_map[src_node].remove(edge_hash)
        node_map[dst_node].remove(edge_hash)
        
        # If we've orphaned a vertex on deletion
        if (src_node != node_number and not node_map[src_node]) or (dst_node != node_number and not node_map[dst_node]):
            return False

    # Get rid of the node
    del node_map[node_number]
    
    return True

def DFS(root_node, node_map, edge_map, traversed_list = []):
    """
        Returns a set containing all nodes traversed from the root node
    """
    for edge_name in node_map[root_node]:
        src_node = edge_map[edge_name][0]
        dst_node = edge_map[edge_name][1]
        
        if src_node != root_node:
            next_node = src_node   
        elif dst_node != root_node:
            next_node = dst_node
            
        # Traverse if we haven't yet
        if next_node not in traversed_list:
            traversed_list.append(next_node)
            DFS(next_node, node_map, edge_map, traversed_list)
            
    return traversed_list
    
def findCriticalNodes(num_nodes, num_edges, edges):
    """
        Returns a list of vertices indicating the critical nodes
    """
    critical_nodes = []
    # This operation is O(E)
    original_node_map, edge_map = parseData(num_nodes,num_edges, edges)
    
    # Go through each node - O(V)
    for node_number, connected_edges in original_node_map.items():
        # We keep a copy of the original, so we dont need to recalculate the original graph every time
        node_map = copy.deepcopy(original_node_map)
        # If the node only has 1 edge, it can't be critical
        if len(connected_edges) > 1:
            # Remove the node, and all references to its edges in the map 
            # The complexity of this scales linearly as the average number of edges connected to a vertex increases
            result = deleteNode(node_number, connected_edges, node_map, edge_map)
            
            # If deletion was successful
            if(result):
                # Traverse graph O(V+E)
                root_node = list(node_map.keys())[0]
                traversed_list = []
                traversed_list = DFS(root_node, node_map, edge_map, traversed_list)
                
                if (len(traversed_list) +1) < num_nodes:
                    print("Critical node found for node {}".format(node_number))
                    critical_nodes.append(node_number)
            # Otherwise, deletion caused an orphan, meaning the node is critical
            else:
                print("Critical node found for node {}".format(node_number))
                critical_nodes.append(node_number)

    return critical_nodes

if __name__ == "__main__":
    critical = findCriticalNodes(7, 7, [[0, 1], [0, 2], [1, 3], [2, 3], [2, 5], [5, 6], [3, 4]])
    print(critical)
