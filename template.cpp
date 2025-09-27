#include <bits/stdc++.h>

using namespace std;

// ================ Typedefs ================
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
typedef vector<int> vi;
typedef vector<ll> vll;

// ================ Macros ================
// #define fastio ios_base::sync_with_stdio(0)
#define fastio                    \
    ios_base::sync_with_stdio(0); \
    cin.tie(nullptr);

#define pb push_back
#define mp make_pair
#define all(x) (x).begin(), (x).end()
#define rall(x) (x).rbegin(), (x).rend()
#define sz(x) ((int)(x).size())
#define fi first
#define se second
#define endl '\n'

// ================ Constants ================
const ll MOD = 1e9 + 7;
const ll INF = 1e18;
const ld EPS = 1e-9;
const ld PI = acos(-1);

// ================ Sieve of Eratosthenes (Start)  ================

vector<bool> isPrime;
vector<int> primes;

// Generate primes up to n
void sieve(int n)
{
    isPrime.assign(n + 1, true);
    isPrime[0] = isPrime[1] = false;

    for (int i = 2; i * i <= n; i++)
    {
        if (isPrime[i])
        {
            for (int j = i * i; j <= n; j += i)
            {
                isPrime[j] = false;
            }
        }
    }

    // Store primes in a vector
    for (int i = 2; i <= n; i++)
    {
        if (isPrime[i])
            primes.push_back(i);
    }
}

// bool isPrime(int n) {
//     if (n <= 1) return false;
//     if (n <= 3) return true;  // 2 and 3 are prime
//     if (n % 2 == 0 || n % 3 == 0) return false;

//     // Check divisibility up to √n
//     for (int i = 5; i * i <= n; i += 6) {
//         if (n % i == 0 || n % (i + 2) == 0)
//             return false;
//     }
//     return true;
// }

// ================ Sieve of Eratosthenes (End)  ================

// ================ Binary Exponentiation (Start)  ================

long long binPow(long long a, long long b)
{
    long long res = 1;
    while (b > 0)
    {
        if (b & 1)
            res *= a; // multiply if current bit is 1
        a *= a;       // square the base
        b >>= 1;      // shift exponent
    }
    return res;
}

long long binPowMod(long long a, long long b, long long mod = MOD)
{
    long long res = 1;
    a %= mod;
    while (b > 0)
    {
        if (b & 1)
            res = (res * a) % mod;
        a = (a * a) % mod;
        b >>= 1;
    }
    return res;
}

// ================ Binary Exponentiation (End)  ================

// ================ GCD & LCM (Start)  ================

// Recursive GCD
long long gcd(long long a, long long b)
{
    if (b == 0)
        return a;
    return gcd(b, a % b);
}

// Iterative GCD (alternative)
long long gcd_iter(long long a, long long b)
{
    while (b != 0)
    {
        long long temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

long long lcm(long long a, long long b)
{
    return (a / gcd(a, b)) * b; // avoid overflow
}

// ================ GCD & LCM (End)  ================

// ================ Kadane’s algorithm (Start)  ================

long long kadane(const vector<int> &arr)
{
    long long maxSum = arr[0];  // max sum so far
    long long currSum = arr[0]; // current sum ending at current index

    for (int i = 1; i < arr.size(); i++)
    {
        currSum = max((long long)arr[i], currSum + arr[i]);
        maxSum = max(maxSum, currSum);
    }

    return maxSum;
}

// ================ Kadane’s algorithm (End)  ================

// ================ Binary search - (lower bound,upper bound) (Start)  ================

// Standard binary search (returns index of target, -1 if not found)
int binarySearch(const vector<int> &arr, int target)
{
    int low = 0, high = arr.size() - 1;
    while (low <= high)
    {
        int mid = low + (high - low) / 2;
        if (arr[mid] == target)
            return mid;
        else if (arr[mid] < target)
            low = mid + 1;
        else
            high = mid - 1;
    }
    return -1; // not found
}

// Lower Bound: first index where arr[i] >= target
int lowerBound(const vector<int> &arr, int target)
{
    int low = 0, high = arr.size();
    while (low < high)
    {
        int mid = low + (high - low) / 2;
        if (arr[mid] < target)
            low = mid + 1;
        else
            high = mid;
    }
    return low; // can be arr.size() if target is larger than all elements
}

// Upper Bound: first index where arr[i] > target
int upperBound(const vector<int> &arr, int target)
{
    int low = 0, high = arr.size();
    while (low < high)
    {
        int mid = low + (high - low) / 2;
        if (arr[mid] <= target)
            low = mid + 1;
        else
            high = mid;
    }
    return low; // can be arr.size() if target >= all elements
}

// ================ Binary search - (lower bound,upper bound) (End)  ================

// ================ Merge Sort (Start)  ================

// Merge two sorted halves of arr
void merge(vector<int> &arr, int left, int mid, int right)
{
    vector<int> temp(right - left + 1);
    int i = left, j = mid + 1, k = 0;

    while (i <= mid && j <= right)
    {
        if (arr[i] <= arr[j])
            temp[k++] = arr[i++];
        else
            temp[k++] = arr[j++];
    }

    while (i <= mid)
        temp[k++] = arr[i++];
    while (j <= right)
        temp[k++] = arr[j++];

    for (int p = 0; p < temp.size(); p++)
        arr[left + p] = temp[p];
}

// Recursive merge sort
void mergeSort(vector<int> &arr, int left, int right)
{
    if (left >= right)
        return;

    int mid = left + (right - left) / 2;
    mergeSort(arr, left, mid);
    mergeSort(arr, mid + 1, right);
    merge(arr, left, mid, right);
}

// ================ Merge Sort (End)  ================

// ================ Quick Sort (Start)  ================

// Partition function (Lomuto partition scheme)
int partition(vector<int> &arr, int low, int high)
{
    int pivot = arr[high]; // pivot element
    int i = low - 1;       // index of smaller element

    for (int j = low; j < high; j++)
    {
        if (arr[j] <= pivot)
        {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[high]);
    return i + 1; // pivot index
}

// Recursive Quick Sort
void quickSort(vector<int> &arr, int low, int high)
{
    if (low < high)
    {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

// ================ Quick Sort (End)  ================

// ================ KMP (Start)  ================

// Build the LPS array (Longest Prefix Suffix)
vector<int> computeLPS(const string &pattern)
{
    int m = pattern.size();
    vector<int> lps(m, 0);
    int len = 0; // length of previous longest prefix suffix
    int i = 1;

    while (i < m)
    {
        if (pattern[i] == pattern[len])
        {
            len++;
            lps[i] = len;
            i++;
        }
        else
        {
            if (len != 0)
            {
                len = lps[len - 1]; // fallback
            }
            else
            {
                lps[i] = 0;
                i++;
            }
        }
    }
    return lps;
}

// KMP search
vector<int> KMP(const string &text, const string &pattern)
{
    int n = text.size();
    int m = pattern.size();
    vector<int> lps = computeLPS(pattern);
    vector<int> occurrences; // store starting indices of matches

    int i = 0, j = 0;
    while (i < n)
    {
        if (text[i] == pattern[j])
        {
            i++;
            j++;
        }

        if (j == m)
        {
            occurrences.push_back(i - j);
            j = lps[j - 1]; // continue searching
        }
        else if (i < n && text[i] != pattern[j])
        {
            if (j != 0)
                j = lps[j - 1];
            else
                i++;
        }
    }
    return occurrences;
}

// ================ KMP (End)  ================

// ================ All Subsets Generation (Start)  ================

vector<vector<int>> subsetsDFS(vector<int> &nums)
{
    vector<vector<int>> res;
    vector<int> temp;

    function<void(int)> dfs = [&](int index)
    {
        if (index == nums.size())
        {
            res.push_back(temp);
            return;
        }
        // Include nums[index]
        temp.push_back(nums[index]);
        dfs(index + 1);
        temp.pop_back();
        // Exclude nums[index]
        dfs(index + 1);
    };

    dfs(0);
    return res;
}

// ================ All Subsets Generation (End)  ================

// ================ All Permutations Generation (Start)  ================

vector<vector<int>> permuteDFS(vector<int> &nums)
{
    vector<vector<int>> res;
    vector<int> temp;
    vector<bool> used(nums.size(), false);

    function<void()> dfs = [&]()
    {
        if (temp.size() == nums.size())
        {
            res.push_back(temp);
            return;
        }
        for (int i = 0; i < nums.size(); i++)
        {
            if (used[i])
                continue;
            used[i] = true;
            temp.push_back(nums[i]);
            dfs();
            temp.pop_back();
            used[i] = false;
        }
    };

    dfs();
    return res;
}

// ================ All Permutations Generation (End)  ================

// ================ LCS Longest Common Subsequence (Start)  ================

// Function to compute LCS length
int LCSLength(const string &a, const string &b)
{
    int n = a.size(), m = b.size();
    vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));

    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= m; j++)
        {
            if (a[i - 1] == b[j - 1])
                dp[i][j] = dp[i - 1][j - 1] + 1;
            else
                dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
        }
    }
    return dp[n][m];
}

// Optional: Function to reconstruct LCS string
string LCSString(const string &a, const string &b)
{
    int n = a.size(), m = b.size();
    vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));

    // Fill DP table
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= m; j++)
        {
            if (a[i - 1] == b[j - 1])
                dp[i][j] = dp[i - 1][j - 1] + 1;
            else
                dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
        }
    }

    // Reconstruct LCS
    string lcs;
    int i = n, j = m;
    while (i > 0 && j > 0)
    {
        if (a[i - 1] == b[j - 1])
        {
            lcs.push_back(a[i - 1]);
            i--;
            j--;
        }
        else if (dp[i - 1][j] > dp[i][j - 1])
            i--;
        else
            j--;
    }
    reverse(lcs.begin(), lcs.end());
    return lcs;
}

// ================ LCS Longest Common Subsequence (End)  ================

// ================ LIS Longest Increasing Subsequence (Start)  ================

// Function to compute LIS length
int LISLength(const vector<int> &arr)
{
    int n = arr.size();
    vector<int> dp(n, 1); // dp[i] = LIS ending at i

    for (int i = 1; i < n; i++)
    {
        for (int j = 0; j < i; j++)
        {
            if (arr[i] > arr[j])
                dp[i] = max(dp[i], dp[j] + 1);
        }
    }

    return *max_element(dp.begin(), dp.end());
}

// Optional: Reconstruct one LIS
vector<int> LISSequence(const vector<int> &arr)
{
    int n = arr.size();
    vector<int> dp(n, 1), prev(n, -1);

    for (int i = 1; i < n; i++)
    {
        for (int j = 0; j < i; j++)
        {
            if (arr[i] > arr[j] && dp[i] < dp[j] + 1)
            {
                dp[i] = dp[j] + 1;
                prev[i] = j;
            }
        }
    }

    // Find index of max LIS
    int idx = max_element(dp.begin(), dp.end()) - dp.begin();
    vector<int> lis;
    while (idx != -1)
    {
        lis.push_back(arr[idx]);
        idx = prev[idx];
    }
    reverse(lis.begin(), lis.end());
    return lis;
}

// ================ LIS Longest Increasing Subsequence (End)  ================

// ================ BFS in Graph (Start)  ================

// BFS on adjacency list graph
// n = number of nodes, adj = adjacency list
// Returns vector of distances from source (or -1 if unreachable)

vector<int> BFS(int n, vector<vector<int>> &adj, int src)
{
    vector<int> dist(n, -1); // distance array
    queue<int> q;

    dist[src] = 0;
    q.push(src);

    while (!q.empty())
    {
        int u = q.front();
        q.pop();

        for (int v : adj[u])
        {
            if (dist[v] == -1)
            {                          // not visited
                dist[v] = dist[u] + 1; // set distance
                q.push(v);
            }
        }
    }
    return dist;
}

// ================ BFS in Graph (End)  ================

// ================ DFS in Graph (Start)  ================

// DFS on adjacency list graph
// n = number of nodes, adj = adjacency list
// visited keeps track of visited nodes

void dfsUtil(int u, vector<vector<int>> &adj, vector<bool> &visited)
{
    visited[u] = true;
    // Do something with node u here (e.g., print or process)

    for (int v : adj[u])
    {
        if (!visited[v])
        {
            dfsUtil(v, adj, visited);
        }
    }
}

// Wrapper to call DFS on entire graph (handles disconnected graphs)
void DFS(int n, vector<vector<int>> &adj)
{
    vector<bool> visited(n, false);
    for (int i = 0; i < n; i++)
    {
        if (!visited[i])
        {
            dfsUtil(i, adj, visited);
        }
    }
}

// ================ DFS in Graph (End)  ================

// ================ Topological Sort (Start)  ================

// Kahn's Algorithm (BFS-based)
// Works for Directed Acyclic Graph (DAG)
vector<int> topoSortKahn(int n, vector<vector<int>> &adj)
{
    vector<int> indeg(n, 0);
    for (int u = 0; u < n; u++)
    {
        for (int v : adj[u])
            indeg[v]++;
    }

    queue<int> q;
    for (int i = 0; i < n; i++)
        if (indeg[i] == 0)
            q.push(i);

    vector<int> topo;
    while (!q.empty())
    {
        int u = q.front();
        q.pop();
        topo.push_back(u);

        for (int v : adj[u])
        {
            indeg[v]--;
            if (indeg[v] == 0)
                q.push(v);
        }
    }
    // If topo.size() < n → graph has a cycle
    return topo;
}

// DFS-based Topological Sort
void topoDFSUtil(int u, vector<vector<int>> &adj, vector<bool> &visited, stack<int> &st)
{
    visited[u] = true;
    for (int v : adj[u])
    {
        if (!visited[v])
            topoDFSUtil(v, adj, visited, st);
    }
    st.push(u);
}

vector<int> topoSortDFS(int n, vector<vector<int>> &adj)
{
    vector<bool> visited(n, false);
    stack<int> st;
    for (int i = 0; i < n; i++)
    {
        if (!visited[i])
            topoDFSUtil(i, adj, visited, st);
    }

    vector<int> topo;
    while (!st.empty())
    {
        topo.push_back(st.top());
        st.pop();
    }
    return topo;
}

// ================ Topological Sort (End)  ================

// ================ Dijkstra's Algorithm (Start) ================
// Finds shortest path from source to all nodes in weighted graph (non-negative edges)

vector<long long> dijkstra(int n, vector<vector<pair<int, int>>> &adj, int src)
{
    const long long INF = 1e18;
    vector<long long> dist(n, INF);
    dist[src] = 0;

    // min-heap {dist, node}
    priority_queue<pair<long long, int>, vector<pair<long long, int>>, greater<pair<long long, int>>> pq;
    pq.push({0, src});

    while (!pq.empty())
    {
        auto [d, u] = pq.top();
        pq.pop();
        if (d != dist[u])
            continue; // stale entry

        for (auto [v, w] : adj[u])
        {
            if (dist[v] > d + w)
            {
                dist[v] = d + w;
                pq.push({dist[v], v});
            }
        }
    }
    return dist;
}
// ================ Dijkstra's Algorithm (End) ================

// ================ Bellman-Ford Algorithm (Start) ================
// Finds shortest paths from src to all nodes
// Handles negative weights (but no negative cycles)

struct Edge
{
    int u, v, w;
};

vector<long long> bellmanFord(int n, vector<Edge> &edges, int src)
{
    const long long INF = 1e18;
    vector<long long> dist(n, INF);
    dist[src] = 0;

    // Relax edges n-1 times
    for (int i = 0; i < n - 1; i++)
    {
        bool updated = false;
        for (auto &e : edges)
        {
            if (dist[e.u] != INF && dist[e.u] + e.w < dist[e.v])
            {
                dist[e.v] = dist[e.u] + e.w;
                updated = true;
            }
        }
        if (!updated)
            break; // optimization
    }

    // Check for negative cycle
    for (auto &e : edges)
    {
        if (dist[e.u] != INF && dist[e.u] + e.w < dist[e.v])
        {
            cout << "Negative weight cycle detected\n";
            break;
        }
    }

    return dist;
}
// ================ Bellman-Ford Algorithm (End) ================

// ================ Floyd-Warshall Algorithm (Start) ================
// All-Pairs Shortest Paths
// Handles negative weights but not negative cycles

vector<vector<long long>> floydWarshall(int n, vector<vector<long long>> dist)
{
    const long long INF = 1e18;

    for (int k = 0; k < n; k++)
    {
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                if (dist[i][k] < INF && dist[k][j] < INF)
                {
                    dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
                }
            }
        }
    }
    return dist;
}
// ================ Floyd-Warshall Algorithm (End) ================

// ================ Disjoint Set Union (DSU) ================
struct DSU
{
    vector<int> parent, sz;
    DSU(int n)
    {
        parent.resize(n);
        sz.resize(n, 1);
        iota(parent.begin(), parent.end(), 0); // parent[i] = i
    }

    int find(int x)
    {
        if (parent[x] == x)
            return x;
        return parent[x] = find(parent[x]); // path compression
    }

    bool unite(int a, int b)
    {
        a = find(a);
        b = find(b);
        if (a == b)
            return false;
        if (sz[a] < sz[b])
            swap(a, b);
        parent[b] = a;
        sz[a] += sz[b];
        return true;
    }
};

// ================ Kruskal's Algorithm (MST) ================
// struct Edge {
//     int u, v, w;
// };

long long kruskalMST(int n, vector<Edge> &edges)
{
    sort(edges.begin(), edges.end(), [](Edge &a, Edge &b)
         { return a.w < b.w; });

    DSU dsu(n);
    long long mst_cost = 0;
    vector<Edge> mst_edges;

    for (auto &e : edges)
    {
        if (dsu.unite(e.u, e.v))
        {
            mst_cost += e.w;
            mst_edges.push_back(e);
        }
    }

    // If mst_edges.size() != n-1 → graph not connected
    return mst_cost;
}
// ================ Kruskal's Algorithm (End) ================

// ================ Prim's Algorithm (Start) ================
// Minimum Spanning Tree using Prim's Algorithm (with priority queue)
// Works on connected, weighted, undirected graphs

long long primMST(int n, vector<vector<pair<int, int>>> &adj)
{
    const long long INF = 1e18;
    vector<long long> key(n, INF); // min edge weight to connect node
    vector<bool> inMST(n, false);  // MST inclusion flag
    priority_queue<pair<long long, int>, vector<pair<long long, int>>, greater<pair<long long, int>>> pq;

    key[0] = 0; // start from node 0
    pq.push({0, 0});
    long long mst_cost = 0;

    while (!pq.empty())
    {
        auto [w, u] = pq.top();
        pq.pop();
        if (inMST[u])
            continue;
        inMST[u] = true;
        mst_cost += w;

        for (auto [v, wt] : adj[u])
        {
            if (!inMST[v] && wt < key[v])
            {
                key[v] = wt;
                pq.push({wt, v});
            }
        }
    }

    return mst_cost;
}

// ================ Prim's Algorithm (End) ================

// ================ Tarjan's Algorithm (Start) ================
// Finds Strongly Connected Components (SCC) in a directed graph

vector<vector<int>> tarjanSCC(int n, vector<vector<int>> &adj)
{
    vector<int> disc(n, -1), low(n, -1), inStack(n, 0);
    stack<int> st;
    vector<vector<int>> sccs;
    int time = 0;

    function<void(int)> dfs = [&](int u)
    {
        disc[u] = low[u] = time++;
        st.push(u);
        inStack[u] = 1;

        for (int v : adj[u])
        {
            if (disc[v] == -1)
            { // not visited
                dfs(v);
                low[u] = min(low[u], low[v]);
            }
            else if (inStack[v])
            { // back edge
                low[u] = min(low[u], disc[v]);
            }
        }

        // If u is root of SCC
        if (low[u] == disc[u])
        {
            vector<int> scc;
            while (true)
            {
                int v = st.top();
                st.pop();
                inStack[v] = 0;
                scc.push_back(v);
                if (v == u)
                    break;
            }
            sccs.push_back(scc);
        }
    };

    for (int i = 0; i < n; i++)
        if (disc[i] == -1)
            dfs(i);

    return sccs;
}

// ================ Tarjan's Algorithm (End) ================

// ================ Kosaraju's Algorithm (Start) ================
// Finds Strongly Connected Components (SCC) in a directed graph

vector<vector<int>> kosarajuSCC(int n, vector<vector<int>> &adj)
{
    vector<bool> visited(n, false);
    stack<int> st;

    // 1. Standard DFS to fill finish times
    function<void(int)> dfs1 = [&](int u)
    {
        visited[u] = true;
        for (int v : adj[u])
            if (!visited[v])
                dfs1(v);
        st.push(u);
    };

    for (int i = 0; i < n; i++)
        if (!visited[i])
            dfs1(i);

    // 2. Transpose the graph
    vector<vector<int>> adjT(n);
    for (int u = 0; u < n; u++)
    {
        for (int v : adj[u])
            adjT[v].push_back(u);
    }

    // 3. DFS on transposed graph in stack order
    fill(visited.begin(), visited.end(), false);
    vector<vector<int>> sccs;

    function<void(int, vector<int> &)> dfs2 = [&](int u, vector<int> &scc)
    {
        visited[u] = true;
        scc.push_back(u);
        for (int v : adjT[u])
            if (!visited[v])
                dfs2(v, scc);
    };

    while (!st.empty())
    {
        int u = st.top();
        st.pop();
        if (!visited[u])
        {
            vector<int> scc;
            dfs2(u, scc);
            sccs.push_back(scc);
        }
    }

    return sccs;
}

// ================ Kosaraju's Algorithm (End) ================

// ================ Binary Tree Traversals (Start) ================
struct TreeNode
{
    int val;
    TreeNode *left, *right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

// Preorder Traversal (Root -> Left -> Right)
void preorder(TreeNode *root, vector<int> &res)
{
    if (!root)
        return;
    res.push_back(root->val);
    preorder(root->left, res);
    preorder(root->right, res);
}

// Inorder Traversal (Left -> Root -> Right)
void inorder(TreeNode *root, vector<int> &res)
{
    if (!root)
        return;
    inorder(root->left, res);
    res.push_back(root->val);
    inorder(root->right, res);
}

// Postorder Traversal (Left -> Right -> Root)
void postorder(TreeNode *root, vector<int> &res)
{
    if (!root)
        return;
    postorder(root->left, res);
    postorder(root->right, res);
    res.push_back(root->val);
}

// Optional: Iterative traversals using stack can be added if needed
// ================ Binary Tree Traversals (End) ================

// ================ LCA (Binary Lifting) (Start) ================
const int MAXN = 100005;
const int LOG = 20; // 2^20 > 1e6
vector<int> adj[MAXN];
int up[MAXN][LOG]; // up[v][i] = 2^i-th ancestor of v
int depth[MAXN];

// DFS to compute depth and 1st ancestors
void dfs(int v, int p)
{
    up[v][0] = p;
    for (int i = 1; i < LOG; i++)
    {
        if (up[v][i - 1] != -1)
            up[v][i] = up[up[v][i - 1]][i - 1];
        else
            up[v][i] = -1;
    }
    for (int u : adj[v])
    {
        if (u != p)
        {
            depth[u] = depth[v] + 1;
            dfs(u, v);
        }
    }
}

// Lift node u by k levels
int lift(int u, int k)
{
    for (int i = 0; i < LOG; i++)
    {
        if (k & (1 << i))
        {
            u = up[u][i];
            if (u == -1)
                break;
        }
    }
    return u;
}

// LCA query
int LCA(int u, int v)
{
    if (depth[u] < depth[v])
        swap(u, v);
    u = lift(u, depth[u] - depth[v]); // bring u and v to same depth
    if (u == v)
        return u;

    for (int i = LOG - 1; i >= 0; i--)
    {
        if (up[u][i] != -1 && up[u][i] != up[v][i])
        {
            u = up[u][i];
            v = up[v][i];
        }
    }
    return up[u][0];
}

// ================ LCA (Binary Lifting) (End) ================

// ================ Diameter of Tree (Start) ================
// vector<int> adj[MAXN];

// BFS to find farthest node and its distance from start
pair<int, int> bfs(int start, int n)
{
    vector<int> dist(n + 1, -1);
    queue<int> q;
    q.push(start);
    dist[start] = 0;
    int farthest_node = start;

    while (!q.empty())
    {
        int u = q.front();
        q.pop();
        for (int v : adj[u])
        {
            if (dist[v] == -1)
            {
                dist[v] = dist[u] + 1;
                q.push(v);
                if (dist[v] > dist[farthest_node])
                    farthest_node = v;
            }
        }
    }
    return {farthest_node, dist[farthest_node]};
}

// Compute diameter of tree
int treeDiameter(int n)
{
    auto t1 = bfs(1, n);        // first BFS from any node (say 1)
    auto t2 = bfs(t1.first, n); // BFS from farthest node found
    return t2.second;           // distance = diameter
}

// ================ Diameter of Tree (End) ================

// ================ Main Code ================
void solve()
{
    // int n;
    // cin >> n;
    // vector<int> a(n);
    // for (int &z : a)
    // {
    //     cin >> z;
    // }
}

int main()
{
    fastio;

#ifdef LOCAL
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif

    int t = 1;
    // cin >> t;
    while (t--)
        solve();

    return 0;
}