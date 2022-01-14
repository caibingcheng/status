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
    vector<thread> tasks;
    vector<safe_status<STATUS>> statuses;
    for (int i = 0; i < 10; i++)
    {
        safe_status<STATUS> status = make_status<STATUS>(STATUS::TASK_INVALID);
        tasks.emplace_back(processTask, i, status);
        statuses.emplace_back(status);
    }

    while (!sts::isAll(statuses, STATUS::TASK_START));
    printf("all status TASK_START\n");
    while (!sts::isAll(statuses, STATUS::TASK_END));
    printf("all status TASK_END\n");

    for (auto &task : tasks)
        if (task.joinable())
            task.join();

    return 1;
}