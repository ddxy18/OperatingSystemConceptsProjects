package org.example;

import java.util.Comparator;
import java.util.List;

public class SJF implements Algorithm {

    private final List<Task> taskList;
    private final int size;
    private int totalResponseTime;
    private int totalExecuteTime;
    private int timer;

    public SJF(List<Task> taskList) {
        this.taskList = taskList;
        size = taskList.size();
    }

    @Override
    public void schedule() {
        taskList.sort(Comparator.comparingInt(Task::getBurst));
        while (taskList.size() != 0) {
            Task task = pickNextTask();
            int burst = task.getBurst();
            totalResponseTime += timer;
            CPU.run(task, burst);
            timer += burst;
            totalExecuteTime += timer;
        }
        /*System.out.println("average turnaround time:" + getAverageTurnaroundTime());
        System.out.println("average waiting time:" + getAverageWaitingTime());
        System.out.println("average response time:" + getAverageResponseTime());*/

    }

    @Override
    public Task pickNextTask() {
        return taskList.remove(0);
    }

    public int getAverageTurnaroundTime() {
        return totalExecuteTime / size;
    }

    public int getAverageWaitingTime() {
        return getAverageResponseTime();
    }

    public int getAverageResponseTime() {
        return totalResponseTime / size;
    }
}