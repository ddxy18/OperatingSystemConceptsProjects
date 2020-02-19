package org.example;

import java.util.List;

public class RR implements Algorithm {

    private static final int QUANTUM = 10;

    private final List<Task> taskList;

    public RR(List<Task> taskList) {
        this.taskList = taskList;
    }

    @Override
    public void schedule() {
        while (taskList.size() != 0) {
            Task task = pickNextTask();
            int burst=task.getBurst();
            if (burst<=QUANTUM) {
                CPU.run(task,burst);
            }else {
                CPU.run(task,QUANTUM);
                taskList.add(new Task(task.getName(),task.getPriority(),task.getBurst()-QUANTUM));
            }
        }
    }

    @Override
    public Task pickNextTask() {
        return taskList.remove(0);
    }
}
