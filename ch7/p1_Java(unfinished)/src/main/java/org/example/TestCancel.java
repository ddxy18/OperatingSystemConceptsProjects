package org.example;

public class TestCancel
{
    public static void main(String[] args) throws InterruptedException {
        Runnable task = new Worker();
        Thread worker = new Thread(task);

        worker.start();

        Thread.sleep(3000); 

        // sets the interruption status of the worker thread
        worker.interrupt();
    }
}
