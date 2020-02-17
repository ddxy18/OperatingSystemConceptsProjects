package org.example;

import java.util.concurrent.RecursiveAction;

public class QuickSort extends RecursiveAction {

    private final int begin;
    private final int end;
    private final int[] array;

    public QuickSort(int begin, int end, int[] array) {
        this.begin = begin;
        this.end = end;
        this.array = array;
    }

    @Override
    protected void compute() {
        if(begin>=end) {
            return;
        }

        int base = array[end];
        int i = begin, j = end-1;
        while (i<j) {
            while (i<j&&array[i]<base){
                i++;
            }
            while (i<j&&array[j]>base) {
                j--;
            }
            if(i<j) {
                swap(i,j);
            }
        }
        if(array[i]>array[end]) {
            swap(i,end);
        }else {
            i=end;
        }



        QuickSort left=new QuickSort(begin,i-1,array);
        QuickSort right=new QuickSort(i+1,end,array);
        left.fork();
        right.fork();
        left.join();
        right.join();
    }

    private void swap(int i,int j) {
        int tmp=array[i];
        array[i]=array[j];
        array[j]=tmp;
    }
}