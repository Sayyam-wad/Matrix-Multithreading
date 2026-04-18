#include <bits/stdc++.h>
#include <thread>
#include <chrono>
#include <fstream>
using namespace std;

int N;
vector<vector<int>> A, B, C;

void multiply(int start, int end) {
    for (int i = start; i < end; i++) {
        for (int j = 0; j < N; j++) {
            int sum = 0;
            for (int k = 0; k < N; k++) {
                sum += A[i][k] * B[k][j];
            }
            C[i][j] = sum;
        }
    }
}

int main() {
    cout << "Number of cores: " << thread::hardware_concurrency() << endl;

    N = 2400; // 

    A.assign(N, vector<int>(N));
    B.assign(N, vector<int>(N));
    C.assign(N, vector<int>(N));

    srand(time(0));

    // Fill matrices
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++) {
            A[i][j] = rand() % 10;
            B[i][j] = rand() % 10;
        }

    int max_threads = thread::hardware_concurrency() * 2;

    ofstream file("results.txt");
    file << "Threads Time(sec)\n";

    for (int t = 1; t <= max_threads; t++) {

        auto start = chrono::high_resolution_clock::now();

        vector<thread> threads;
        int rows_per_thread = N / t;

        for (int i = 0; i < t; i++) {
            int start_row = i * rows_per_thread;
            int end_row = (i == t - 1) ? N : start_row + rows_per_thread;
            threads.push_back(thread(multiply, start_row, end_row));
        }

        for (auto &th : threads) th.join();

        auto end = chrono::high_resolution_clock::now();

        double time_taken = chrono::duration<double>(end - start).count();

        cout << "Threads: " << t << " Time: " << time_taken << " sec\n";
        file << t << " " << time_taken << endl;
    }

    file.close();

    return 0;
}