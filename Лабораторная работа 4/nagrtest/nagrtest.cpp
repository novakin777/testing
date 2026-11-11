#include <algorithm>
#include <atomic>
#include <chrono>
#include <cmath>
#include <functional>
#include <iomanip>
#include <iostream>
#include <mutex>
#include <numeric>
#include <random>
#include <thread>
#include <vector>

using namespace std;
using namespace std::chrono;

// Эмуляция одного запроса с вероятностью успеха 95%.
bool simulate_network_request()
{
    thread_local mt19937 generator(random_device{}());
    uniform_int_distribution<int> delay_distribution(10, 50);
    uniform_int_distribution<int> result_distribution(1, 100);
    this_thread::sleep_for(milliseconds(delay_distribution(generator)));
    return result_distribution(generator) <= 95;
}

// Каждый пользователь последовательно выполняет 20 запросов.
void virtual_user(int requests_per_user, vector<double>& latencies,
    atomic<int>& successful_requests, atomic<int>& failed_requests,
    mutex& latencies_mutex)
{
    for (int i = 0; i < requests_per_user; i++)
    {
        steady_clock::time_point start = steady_clock::now();
        bool success = simulate_network_request();
        steady_clock::time_point finish = steady_clock::now();
        double latency = duration<double, milli>(finish - start).count();

        {
            lock_guard<mutex> lock(latencies_mutex);
            latencies.push_back(latency);
        }

        if (success)
        {
            successful_requests++;
        }
        else
        {
            failed_requests++;
        }
    }
}

// Вектор уже отсортирован. Метод ближайшего ранга.
double get_percentile(const vector<double>& latencies, double percent)
{
    size_t index = static_cast<size_t>(ceil(percent * latencies.size())) - 1;
    return latencies[index];
}

void run_load_test(int number_of_threads, int ramp_up_ms)
{
    const int requests_per_user = 20;
    int total_requests = number_of_threads * requests_per_user;
    vector<thread> threads;
    vector<double> latencies;
    mutex latencies_mutex;
    atomic<int> successful_requests(0);
    atomic<int> failed_requests(0);
    threads.reserve(number_of_threads);
    latencies.reserve(total_requests);

    cout << "\nVirtual users: " << number_of_threads << "\n";
    cout << "Requests per user: " << requests_per_user << "\n";
    cout << "Ramp-up step: " << ramp_up_ms << " ms\n";

    steady_clock::time_point test_start = steady_clock::now();
    for (int i = 0; i < number_of_threads; i++)
    {
        threads.emplace_back(virtual_user, requests_per_user,
            ref(latencies), ref(successful_requests),
            ref(failed_requests), ref(latencies_mutex));
        if (i + 1 < number_of_threads)
        {
            this_thread::sleep_for(milliseconds(ramp_up_ms));
        }
    }
    for (thread& current_thread : threads)
    {
        current_thread.join();
    }

    double total_time = duration<double>(steady_clock::now() - test_start).count();
    double tps = successful_requests.load() / total_time;
    double average_latency = accumulate(latencies.begin(), latencies.end(), 0.0)
        / latencies.size();
    double error_percent = failed_requests.load() * 100.0 / total_requests;
    sort(latencies.begin(), latencies.end());

    cout << fixed << setprecision(4);
    cout << "\nResults:\n";
    cout << "Total requests: " << total_requests << "\n";
    cout << "Successful requests: " << successful_requests.load() << "\n";
    cout << "Failed requests: " << failed_requests.load() << "\n";
    cout << "Error percent: " << error_percent << "%\n";
    cout << "Total test time: " << total_time << " s\n";
    cout << "TPS (successful): " << tps << " requests/s\n";
    cout << "Average latency: " << average_latency << " ms\n";
    cout << "P95 latency: " << get_percentile(latencies, 0.95) << " ms\n";
    cout << "P99 latency: " << get_percentile(latencies, 0.99) << " ms\n";
}

int main()
{
    cout << "Load Testing Lab\n";
#ifdef NDEBUG
    cout << "Build configuration: Release\n";
#else
    cout << "Build configuration: Debug\n";
#endif
    int number_of_threads;
    int ramp_up_ms;
    cout << "Enter virtual users (50 or 500 for the lab):\n";
    if (!(cin >> number_of_threads) || number_of_threads < 1 || number_of_threads > 1000)
    {
        cout << "Error: users must be between 1 and 1000.\n";
        return 1;
    }
    cout << "Enter ramp-up step in ms (100 for the lab, 0 for comparison):\n";
    if (!(cin >> ramp_up_ms) || ramp_up_ms < 0 || ramp_up_ms > 1000)
    {
        cout << "Error: ramp-up must be between 0 and 1000 ms.\n";
        return 1;
    }
    run_load_test(number_of_threads, ramp_up_ms);
    return 0;
}
