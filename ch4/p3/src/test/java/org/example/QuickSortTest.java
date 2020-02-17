package org.example;

import org.junit.Test;

import java.util.concurrent.ForkJoinPool;

/**
 * Unit test for QuickSort.
 */
public class QuickSortTest {

    @Test
    public void shouldAnswerWithTrue() {
        int[] array = {1, 9, 5, 6, 3, 8, 4, 7, 2};
        ForkJoinPool pool = new ForkJoinPool();
        pool.invoke(new QuickSort(0, array.length - 1, array));
        for (int i : array) {
            System.out.println(i);
        }
    }
}
