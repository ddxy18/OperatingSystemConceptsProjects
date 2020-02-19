package org.example;

import java.util.ArrayList;
import java.util.List;

public class PriorityRR implements Algorithm {

    private static final int MAX_PRIORITY = 10;
    private static final int QUANTUM = 10;
    private final int size;
    private int totalResponseTime;
    private int totalBurstTime;
    private int totalExecuteTime;
    private int timer;
    private final List<Task>[] taskArray;

    public PriorityRR(List<Task> taskList) {
        size = taskList.size();
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
        for (int i = MAX_PRIORITY - 1; i >= 0; i--) {
            int iSize = taskArray[i].size(), j = 0;
            while (taskArray[i].size() != 0) {
                Task task = taskArray[i].remove(0);
                int burst = Math.min(task.getBurst(), QUANTUM);
                CPU.run(task, burst);
                totalBurstTime += burst;
                timer += burst;
                if (burst < task.getBurst()) {
                    taskArray[i].add(new Task(task.getName(), task.getPriority(), task.getBurst() - QUANTUM));
                } else {
                    totalExecuteTime += timer;
                }
                if (j < iSize) {
                    totalResponseTime += (timer - burst);
                    j++;
                }
            }
        }
        /*System.out.println("average turnaround time:" + getAverageTurnaroundTime());
        System.out.println("average waiting time:" + getAverageWaitingTime());
        System.out.println("average response time:" + getAverageResponseTime());*/
    }

    @Override
    public Task pickNextTask() {
        return null;
    }

    public int getAverageTurnaroundTime() {
        return totalExecuteTime / size;
    }

    public int getAverageWaitingTime() {
        return (totalExecuteTime - totalBurstTime) / size;
    }

    public int getAverageResponseTime() {
        return totalResponseTime / size;
    }
}
