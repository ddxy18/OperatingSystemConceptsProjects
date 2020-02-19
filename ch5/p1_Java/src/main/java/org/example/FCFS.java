package org.example;

import java.util.List;

public class FCFS implements Algorithm {

    private final List<Task> taskList;

    public FCFS(List<Task> taskList) {
        this.taskList = taskList;
    }

    @Override
    public void schedule() {
        while (taskList.size() != 0) {
            Task task = pickNextTask();
            CPU.run(task, task.getBurst());
        }
    }

    @Override
    public Task pickNextTask() {
        return taskList.remove(0);
    }
}
