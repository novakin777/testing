#include <algorithm>
#include <atomic>
#include <chrono>
#include <cmath>
#include <iostream>
#include <mutex>
#include <random>
#include <thread>
#include <vector>

using namespace std;
using namespace std::chrono;

// Эмуляция одного запроса к серверу.
bool simulate_network_request()
{
    thread_local mt19937 generator(random_device{}());
    uniform_int_distribution<int> delay_distribution(10, 50);
    uniform_int_distribution<int> result_distribution(1, 100);

    int delay = delay_distribution(generator);
    this_thread::sleep_for(milliseconds(delay));

    // Около 95% запросов выполняются успешно.
    return result_distribution(generator) <= 95;
}

// Один виртуальный пользователь выполняет один запрос.
void virtual_user(vector<double>& latencies,
    atomic<int>& successful_requests,
    atomic<int>& failed_requests,
    mutex& latencies_mutex)
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

double get_percentile(vector<double> latencies, double percent)
{
    if (latencies.empty())
    {
        return 0;
    }

    sort(latencies.begin(), latencies.end());

    size_t index = static_cast<size_t>(ceil(percent * latencies.size())) - 1;
    if (index >= latencies.size())
    {
        index = latencies.size() - 1;
    }

    return latencies[index];
}

void run_load_test(int number_of_threads)
{
    vector<thread> threads;
    vector<double> latencies;
    mutex latencies_mutex;
    atomic<int> successful_requests(0);
    atomic<int> failed_requests(0);

    threads.reserve(number_of_threads);
    latencies.reserve(number_of_threads);

    cout << "\nLoad test for " << number_of_threads << " virtual users\n";
    cout << "Ramp-up: 100 ms between users\n";

    steady_clock::time_point test_start = steady_clock::now();

    for (int i = 0; i < number_of_threads; i++)
    {
        threads.emplace_back(virtual_user,
            ref(latencies),
            ref(successful_requests),
            ref(failed_requests),
            ref(latencies_mutex));

        this_thread::sleep_for(milliseconds(100));
    }

    for (thread& current_thread : threads)
    {
        current_thread.join();
    }

    steady_clock::time_point test_finish = steady_clock::now();
    double total_time = duration<double>(test_finish - test_start).count();
    double tps = number_of_threads / total_time;
    double p95 = get_percentile(latencies, 0.95);
    double p99 = get_percentile(latencies, 0.99);
    double error_percent = failed_requests * 100.0 / number_of_threads;

    cout << "Results:\n";
    cout << "Total requests: " << number_of_threads << "\n";
    cout << "Successful requests: " << successful_requests << "\n";
    cout << "Failed requests: " << failed_requests << "\n";
    cout << "Error percent: " << error_percent << "%\n";
    cout << "Total test time: " << total_time << " s\n";
    cout << "TPS: " << tps << " requests/s\n";
    cout << "P95 latency: " << p95 << " ms\n";
    cout << "P99 latency: " << p99 << " ms\n";
}

int main()
{
    cout << "Load Testing Lab\n";
    cout << "The program starts with 50 virtual users.\n";
    cout << "Change number_of_threads to 500 for the second experiment.\n";

    const int number_of_threads = 500;
    run_load_test(number_of_threads);

    return 0;
}



