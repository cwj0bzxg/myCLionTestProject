//
// Created by 冰镇西瓜哈 on 2023/6/17.
//
#include <iostream>
#include <regex>
#include <chrono>
#include <thread>
#include <array>
#include <initializer_list>
#include <random>
#include <atomic>
#include <condition_variable>
#include <filesystem>
#include <tuple>
#include <type_traits>
#include <future>


void Task(std::promise<int>& p)
{
    // 模拟一些计算任务...
    int result = 42;
    // 设置值到 promise
    p.set_value(result);
}

template<typename T>
void print_type_info() {
    std::cout << "Type: " << typeid(T).name() << '\n';
    std::cout << "Is integer: " << std::is_integral<T>::value << '\n';
    std::cout << "Is floating-point: " << std::is_floating_point<T>::value << '\n';
    std::cout << "Is pointer: " << std::is_pointer<T>::value << '\n';
    std::cout << "Is reference: " << std::is_reference<T>::value << '\n';
    std::cout << std::endl;
}

void print_list(std::initializer_list<int> list) {
    for (auto &i : list) {
        std::cout << i << " ";
    }
    std::cout << std::endl;
}

//std::atomic<int> counter(0);
//void increment() {
//    for (int i = 0; i < 1000; ++i) {
//        counter++;
//    }
//}
//
//std::condition_variable cv;
//std::mutex mtx;
//bool isReady = false;
//
//void WorkerThread()
//{
//    std::cout << "Worker thread is running." << std::endl;
//
//    // 等待主线程发出准备好的信号
//    std::unique_lock<std::mutex> lock(mtx);
//    cv.wait(lock, [] { return isReady; });
//
//    // 收到信号后执行任务
//    std::cout << "Worker thread starts working." << std::endl;
//    // 执行一些任务...
//    std::this_thread::sleep_for(std::chrono::seconds(2));
//    std::cout << "Worker thread finishes its work." << std::endl;
//}

int main() {

    std::promise<int> p;
    std::future<int> f = p.get_future();
    std::thread workerThread(Task, std::ref(p));
    std::cout << "Waiting for result..." << std::flush;
    std::cout << "Result is: " << f.get() << std::endl;
    workerThread.join();

    print_type_info<int>();
    print_type_info<float>();
    print_type_info<double>();
    print_type_info<int*>();
    print_type_info<float&>();

    std::tuple<int, std::string, float> t(1, "hello", 3.14);
    std::cout << std::get<0>(t) << std::endl;
    std::cout << std::get<1>(t) << std::endl;
    std::cout << std::get<2>(t) << std::endl;

//    std::string path = "..\\";
//    for(auto &p: std::filesystem::directory_iterator(path)) {
//        std::cout << p.path() << std::endl;
//    }

//    std::cout << "Main thread starts." << std::endl;
//    std::thread workerThread(WorkerThread);
//    std::this_thread::sleep_for(std::chrono::seconds(1));
//    std::cout << "Main thread signals worker thread to start." << std::endl;
//    {
//        std::lock_guard<std::mutex> lock(mtx);
//        isReady = true;
//    }
//    cv.notify_one();
//    workerThread.join();
//    std::cout << "Main thread finishes." << std::endl;
//
//    std::thread t1(increment);
//    std::thread t2(increment);
//
//    t1.join();
//    t2.join();

//    std::cout <<"counter: "<< counter << std::endl;

    std::default_random_engine generator;
    std::normal_distribution<double> distribution(0.0, 1.0);
    for(int i=0; i<10; ++i) {
        std::cout << distribution(generator) << " ";
    }
    std::cout << std::endl;

    print_list({1, 2, 3, 4, 5});

    std::array<int, 5> arr = {1, 2, 3, 4, 5};
    for (auto &i : arr) {
        std::cout << i << " ";
    }
    std::cout << std::endl;
    arr.fill(0);
    for (auto &i : arr) {
        std::cout << i << " ";
    }
    std::cout << std::endl;


    std::string s = "hello world";
    std::regex r("hello");

    if (std::regex_search(s, r)) {
        std::cout << "found" << std::endl;
    } else {
        std::cout << "not found" << std::endl;
    }

    auto start = std::chrono::high_resolution_clock::now();
    std::this_thread::sleep_for(std::chrono::seconds(1));
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
    std::cout<< "duration: " << duration << "ms" << std::endl; // "duration: 1000ms
    return 0;
}