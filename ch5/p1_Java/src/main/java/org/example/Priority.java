package org.example;

import java.util.Comparator;
import java.util.List;

public class Priority implements Algorithm {

    private final List<Task> taskList;

    public Priority(List<Task> taskList) {
        this.taskList = taskList;
    }

    @Override
    public void schedule() {
        taskList.sort(Comparator.comparingInt(Task::getPriority));
        while (taskList.size() != 0) {
            Task task = pickNextTask();
            CPU.run(task, task.getBurst());
        }
    }

    @Override
    public Task pickNextTask() {
        return taskList.remove(taskList.size() - 1);
    }
}
