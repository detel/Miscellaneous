from collections import defaultdict
from itertools import count

def tree_cut(n, costs, edges):

    edge_map = defaultdict(set)
    for x, y in edges:
        edge_map[x].add(y)
        edge_map[y].add(x)

    # Topological sort
    visited = set()
    ordering = []
    children = defaultdict(list)
    stack = [1]
    while stack:
        node = stack.pop()
        visited.add(node)
        ordering.append(node)

        children[node] = clist = [c for c in edge_map[node] if c not in visited ]
        stack.extend(clist)

    subtree_costs = {}
    for node in reversed(ordering):
        subtree_costs[node] = costs[node] + sum(subtree_costs[c] for c in children[node])
    total_cost = sum(costs.itervalues())
    return min( abs(total_cost - 2 * subc) for subc in subtree_costs.itervalues() )

if __name__ == '__main__':
    n = int(raw_input())
    costs = dict( zip(count(1), map(int, raw_input().split())) )
    edges = []
    for i in xrange(n - 1):
        x, y = map(int, raw_input().split())
        edges.append((x, y))
    print tree_cut(n, costs, edges)
