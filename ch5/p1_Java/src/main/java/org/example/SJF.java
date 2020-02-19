package org.example;

import java.util.Comparator;
import java.util.List;

public class SJF implements Algorithm {

    private final List<Task> taskList;

    public SJF(List<Task> taskList) {
        this.taskList = taskList;
    }

    @Override
    public void schedule() {
        taskList.sort(Comparator.comparingInt(Task::getBurst));
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