#pragma once

#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <vector>
#include <queue>
#include <functional>
#include <future>
#include <type_traits>

namespace utils
{
    class basic_thread_pool {
    public:
        explicit basic_thread_pool(int threads) : _thread_count(threads), _stopped(false) {
            for (int i = 0; i < _thread_count; ++i) {
                std::thread worker([this]()
                {
                   while (true) {
                       std::function<void()> task;
                       {
                           std::unique_lock<std::mutex> lk(_mu);
                           _cv.wait(lk, [this]() { return _stopped || !_tasks.empty(); });

                           if (_tasks.empty() && _stopped)
                               return;

                           task = std::move(_tasks.front());
                           _tasks.pop();
                       }
                       task();
                   }
               }
                );
                _pool.emplace_back(std::move(worker));
            }
        }

        ~basic_thread_pool() {
            {
                std::lock_guard<std::mutex> lk(_mu);
                _stopped = true;
                _cv.notify_all();
            }
            for (auto &thread: _pool) {
                std::cout << "joining thread: " << thread.get_id() << "\n";
                thread.join();
            }
        }

        template<typename Function_, typename ... Args_>
        std::future<std::invoke_result_t<Function_,Args_...>> post(Function_ &&function, Args_ &&...args) {
            using return_type = std::invoke_result_t<Function_, Args_...>;
            auto task = std::make_shared<std::packaged_task<return_type()>>(
                    std::bind(std::forward<Function_>(function), std::forward<Args_>(args)...));

            std::future<return_type> res = task->get_future();
            {
                std::unique_lock<std::mutex> lk(_mu);
                if (_stopped) {
                    std::cout << "Pass away, thread pool stopped\n";
                    throw std::runtime_error("Thread pool has stopped");
                }
                _tasks.emplace([task]() { (*task)(); });
            }
            _cv.notify_one();
            return res;
        }

        void stop(const bool stop) {
            _stopped = stop;
        }

    private:
        std::vector<std::thread> _pool;
        std::queue<std::function<void()>> _tasks;
        uint8_t _thread_count;
        std::mutex _mu;
        std::condition_variable _cv;
        bool _stopped;

    };
}