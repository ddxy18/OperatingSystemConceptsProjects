package org.example;

import org.junit.Test;
import java.util.concurrent.ForkJoinPool;

/**
 * Unit test for MergeSort.
 */
public class MergeSortTest {

    @Test
    public void shouldAnswerWithTrue() {
        int[] array = {1, 9, 5, 6, 3, 8, 4, 7, 2};
        ForkJoinPool pool = new ForkJoinPool();
        pool.invoke(new MergeSort(0, array.length - 1, array));
        for (int i : array) {
            System.out.println(i);
        }
    }
}
