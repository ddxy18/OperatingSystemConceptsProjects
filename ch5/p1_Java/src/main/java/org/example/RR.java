package org.example;

import java.util.List;

public class RR implements Algorithm {

    private static final int QUANTUM = 10;
    private final int size;
    private int totalResponseTime;
    private int totalBurstTime;
    private int totalExecuteTime;
    private int timer;
    private final List<Task> taskList;

    public RR(List<Task> taskList) {
        this.taskList = taskList;
        size = taskList.size();
    }

    @Override
    public void schedule() {
        int i = 0;
        while (taskList.size() != 0) {
            Task task = pickNextTask();
            int burst = Math.min(task.getBurst(), QUANTUM);
            CPU.run(task, burst);
            totalBurstTime += burst;
            timer += burst;
            if (task.getBurst() > QUANTUM) {
                taskList.add(new Task(task.getName(), task.getPriority(), task.getBurst() - QUANTUM));
            } else {
                totalExecuteTime += timer;
            }
            if (i < size) {
                totalResponseTime += (timer - burst);
                i++;
            }
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
        return (totalExecuteTime - totalBurstTime) / size;
    }

    public int getAverageResponseTime() {
        return totalResponseTime / size;
    }
}
