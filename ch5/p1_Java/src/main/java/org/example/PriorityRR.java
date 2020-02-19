package org.example;

import java.util.ArrayList;
import java.util.List;

public class PriorityRR implements Algorithm {

    private static final int MAX_PRIORITY = 10;
    private static final int QUANTUM = 10;

    private final List<Task>[] taskArray;

    public PriorityRR(List<Task> taskList) {
        taskArray = new List[MAX_PRIORITY];
        for (int i = 0; i < MAX_PRIORITY; i++) {
            taskArray[i] = new ArrayList<>();
        }
        while (taskList.size() != 0) {
            Task task = taskList.remove(0);
            taskArray[task.getPriority() - 1].add(task);
        }
    }

    @Override
    public void schedule() {
        for (int i = MAX_PRIORITY-1; i >= 0; i--) {
            while (taskArray[i].size() != 0) {
                Task task = taskArray[i].remove(0);
                int burst = task.getBurst();
                if (burst <= QUANTUM) {
                    CPU.run(task, burst);
                } else {
                    CPU.run(task, QUANTUM);
                    taskArray[i].add(new Task(task.getName(), task.getPriority(), task.getBurst() - QUANTUM));
                }
            }
        }
    }

    @Override
    public Task pickNextTask() {
        return null;
    }
}
