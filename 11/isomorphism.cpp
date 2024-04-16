#include <iostream>
#include <vector>
#include <thread>
#include <mutex>
#include <chrono>
#include <algorithm>

using namespace std;

const int MAXN = 100;
vector<vector<int>> gr1;
vector<vector<int>> gr2;
int n = 100;
long long counter = 0;
mutex mtx; // мьютекс для синхронизации вывода
bool flag1 = 1, flag2 = 1;

vector<vector<int>> generateRandomGraph(int n) {
    vector<vector<int>> g1(n, vector<int>(n, 0));
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++) {
            g1[i][j] = g1[j][i] = rand() % 2;
        }
    return g1;
}

void print(vector<vector<int>> graph) {
    for (int i = 0; i < graph.size(); i++) {
        for (int j = 0; j < graph.size(); j++)
            cout << graph[i][j] << " ";
        cout << endl;
    }
}

vector<int> renumber(int n) {
    vector<int> renumber;
    for (int i = 0; i < n; i++) {
        renumber.push_back(i);
    }
    for (int i = n - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        swap(renumber[i], renumber[j]);
    }
    return renumber;
}

vector<vector<int>> renumberGraph(const vector<vector<int>>& orig, vector<int> r) {
    int n = orig.size();
    vector<vector<int>> newgraph(n, vector<int>(n, 0));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (orig[i][j] == 1) {
                newgraph[r[i]][r[j]] = newgraph[r[j]][r[i]] = 1;
            }
        }
    }
    return newgraph;
}

vector<int> degreeOfVertices(const vector<vector<int>>& adjacencyMatrix) {
    vector<int> degrees;
    for (int i = 0; i < adjacencyMatrix.size(); i++) {
        int degree = 0;
        for (int j = 0; j < adjacencyMatrix[i].size(); j++) {
            if (adjacencyMatrix[i][j] == 1) {
                degree++;
            }
        }
        degrees.push_back(degree);
    }
    return degrees;
}

bool isIsomorphic(const vector<vector<int>>& g1, const vector<vector<int>>& g2) {
    vector<int> degreeG1 = degreeOfVertices(g1);
    vector<int> degreeG2 = degreeOfVertices(g2);
    sort(degreeG1.begin(), degreeG1.end());
    sort(degreeG2.begin(), degreeG2.end());
    if (degreeG1 != degreeG2) {
        flag2 = 0;
        return false;
    }
    return true;
}

void checkIsomorphism(int id, const vector<vector<int>>& gr1, const vector<vector<int>>& gr2, int start, int end, int numThreads) {
    for (int i = start; i < end; i++) {
        vector<vector<int>> temp = renumberGraph(gr1, renumber(gr1.size()));
        if (isIsomorphic(temp, gr2)&&flag1==1&&id==numThreads) {
            mtx.lock();
            cout << "Graphs are isomorphic" << endl;
            mtx.unlock();
            return;
        }
        else if (id == numThreads && flag2 == 0) {
            mtx.lock();
            cout << "Graphs are not isomorphic" << endl;
            mtx.unlock();
            return;
        }
    }
}

int main() {
    srand(time(0));
    gr1 = generateRandomGraph(n);
    vector<int> r = renumber(n);
    gr2 = generateRandomGraph(n);

   /* cout << "Graph 1:" << endl;
    print(gr1);
    cout << "Graph 2:" << endl;
    print(gr2);
    cout << endl;*/

    int numThreads = 2;
    vector<thread> threads;
    int perThread = gr1.size() / numThreads;
    int start = 0;
    int end = perThread;
    auto s = std::chrono::high_resolution_clock::now();
    for (int i = 1; i <= numThreads; ++i) {
        threads.push_back(thread(checkIsomorphism, i + 1, ref(gr1), ref(gr2), start, end, numThreads));
        start = end;
        end += perThread;
    }

    for (auto& th : threads) {
        th.join();
    }
    auto e = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(e-s);
    std::cout << "Time taken with " << numThreads << " threads: " << duration.count() << " microseconds" << std::endl;
    return 0;
}
