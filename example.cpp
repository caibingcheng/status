#include "status.h"

#include <stdio.h>
#include <vector>
#include <thread>
#include <chrono>

using namespace std;
using namespace sts;

enum class STATUS
{
    TASK_INVALID,
    TASK_START,
    TASK_END,
};

void processTask(int value, safe_status<STATUS> status)
{
    status.set(STATUS::TASK_START);
    using namespace chrono_literals;
    this_thread::sleep_for(2000ms);
    printf("%d\n", value);
    status.set(STATUS::TASK_END);
}

int main()
{
    static const int thread_count = 10;
    vector<thread> tasks;
    safe_status<STATUS> status[thread_count];
    for (int i = 0; i < thread_count; i++)
    {
        status[i] = sts::make_status<STATUS>(STATUS::TASK_INVALID);
        tasks.emplace_back(processTask, i, status[i]);
    }

    while (!sts::isAny(status, STATUS::TASK_START));
    printf("has status TASK_START\n");

    while (!sts::isAll(status, STATUS::TASK_START));
    printf("all status TASK_START\n");

    while (!sts::isAny(status, STATUS::TASK_END));
    printf("has status TASK_END\n");

    while (!sts::isAll(status, STATUS::TASK_END));
    printf("all status TASK_END\n");

    for (auto &task : tasks)
        if (task.joinable())
            task.join();

    return 1;
}