package org.example;

import java.util.LinkedList;
import java.util.List;

/**
 * A simple thread pool API.
 * <p>
 * Tasks that wish to get run by the thread pool must implement the
 * java.lang.Runnable interface.
 */

public class ThreadPool {

    private final List<Runnable> taskQueue;
    private int ceiling = 10;
    private Worker worker;

    /**
     * Create a default size thread pool.
     */
    public ThreadPool() {
        taskQueue = new LinkedList<>();
    }


    /**
     * Create a thread pool with a specified size.
     *
     * @param size The number of threads in the pool.
     */
    public ThreadPool(int size) {
        this();
        this.ceiling = size;
    }


    /**
     * shut down the pool.
     */
    public void shutdown() {
    }

    /**
     * Add work to the queue.
     */
    public void add(Runnable task) {
        if (taskQueue.size() < ceiling) {
            taskQueue.add(task);
        }
    }

}
