#include <iostream>
#include <vector>
#include <unordered_map>
#include <queue>
#include <string>
#include <algorithm>

using namespace std;

using Move = pair<string, string>;
vector<string> pegs = {"Start", "A1", "A2", "A3", "Dest"};

// Adjacency list of allowed moves (directed graph)
unordered_map<string, vector<string>> graph = {
    {"Start", {"A1"}},
    {"A1", {"Dest"}},
    {"Dest", {"A2"}},
    {"A2", {"A3"}},
    {"A3", {"A1"}}
};

// Store the moves globally
vector<string> moves;

// Find the shortest path from one peg to another (BFS)
vector<string> findPath(const string& from, const string& to) {
    unordered_map<string, string> parent;
    queue<string> q;
    q.push(from);
    parent[from] = "";

    while (!q.empty()) {
        string curr = q.front();
        q.pop();
        if (curr == to) break;

        for (const string& neighbor : graph[curr]) {
            if (parent.find(neighbor) == parent.end()) {
                parent[neighbor] = curr;
                q.push(neighbor);
            }
        }
    }

    vector<string> path;
    string curr = to;
    while (curr != "") {
        path.push_back(curr);
        curr = parent[curr];
    }
    reverse(path.begin(), path.end());
    return path;
}

// Move one disk using the allowed path
void moveOneDisk(int disk, const string& from, const string& to) {
    vector<string> path = findPath(from, to);
    for (size_t i = 1; i < path.size(); ++i) {
        moves.push_back("Move disk " + to_string(disk) + " from " + path[i-1] + " to " + path[i]);
    }
}

// Recursive constrained Hanoi
void constrainedHanoi(int n, const string& from, const string& to, const string& aux1, const string& aux2) {
    if (n == 0) return;
    // Move n-1 disks to aux1
    constrainedHanoi(n - 1, from, aux1, aux2, to);
    // Move largest disk to destination
    moveOneDisk(n, from, to);
    // Move n-1 disks to destination
    constrainedHanoi(n - 1, aux1, to, from, aux2);
}

void printMovesForN(int n) {
    moves.clear();
    constrainedHanoi(n, "Start", "Dest", "A1", "A2");

    cout << "==============================\n";
    cout << "Moves for n = " << n << " (Total: " << moves.size() << " moves)\n";

    if (moves.size() <= 200) {
        for (const string& m : moves)
            cout << m << '\n';
    } else {
        // First 100
        for (int i = 0; i < 100; ++i)
            cout << moves[i] << '\n';
        cout << "...\n";
        // Last 100
        for (int i = moves.size() - 100; i < moves.size(); ++i)
            cout << moves[i] << '\n';
    }
}

int main() {
    for (int n = 1; n <= 10; ++n) {
        printMovesForN(n);
    }
    return 0;
}
