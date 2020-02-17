package org.example;

import java.util.concurrent.RecursiveAction;

public class MergeSort extends RecursiveAction {

    private final int begin;
    private final int end;
    private final int[] array;

    public MergeSort(int begin, int end, int[] array) {
        this.begin = begin;
        this.end = end;
        this.array = array;
    }

    @Override
    protected void compute() {
        if (begin < end) {
            int mid = (begin + end) / 2;
            MergeSort left = new MergeSort(begin, mid, array);
            MergeSort right = new MergeSort(mid + 1, end, array);
            left.fork();
            right.fork();
            left.join();
            right.join();
            merge();
        }
    }

    public void merge() {
        int mid=(begin+end)/2;
        int[] tmp=new int[end-begin+1];
        int i=begin,p=begin,j=mid+1;

        if (end + 1 - begin >= 0) {
            System.arraycopy(array, begin, tmp, 0, end + 1 - begin);
        }

        while (i <= mid && j <= end) {
            if (tmp[i - begin] > tmp[j - begin]) {
                array[p] = tmp[j - begin];
                j++;
            } else {
                array[p] = tmp[i - begin];
                i++;
            }
            p++;
        }
        for (; i <= mid; ++i) {
            array[p] = tmp[i - begin];
            p++;
        }
        for (; j <= end; ++j) {
            array[p] = tmp[j - begin];
            p++;
        }
    }
}