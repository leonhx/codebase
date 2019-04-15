package com.leonhuang.concurrent;

import com.leonhuang.common.Func1Void;
import com.leonhuang.common.Predef;

import java.util.concurrent.ConcurrentLinkedQueue;

public class Demo {
    public static void main(String[] args) throws Exception {
        final Promise<Integer> p = new Promise<Integer>() {
            @Override
            public Integer apply() {
                try {
                    Thread.sleep(1000);
                } catch (InterruptedException e) {
                    e.printStackTrace();
                }
                return 2 / 1;
            }
        };
        final Promise<Integer> p2 = new Promise<Integer>() {
            @Override
            public Integer apply() {
                try {
                    Thread.sleep(1000);
                } catch (InterruptedException e) {
                    e.printStackTrace();
                }
                return 2 / 0;
            }
        };
        final Future<Integer> f = p.future();
        final Future<Integer> f2 = p2.future().onFailure(new Func1Void<Exception>() {
            @Override
            public void apply(Exception value) {
                System.out.println("in f2");
                System.out.println(value.getMessage());
            }
        });

        Futures<Integer> fs = Predef.futures();
        Future<ConcurrentLinkedQueue<Integer>> pfs = fs.promise().future().onFailure(new Func1Void<Exception>() {
            @Override
            public void apply(Exception value) {
                System.out.println("in pfs");
                System.out.println(value.getMessage());
            }
        });
        fs.add(f);
        fs.add(f2);
        System.out.println(fs.allDone());
        System.out.println(fs.anySuccess());
        System.out.println(fs.allFailure());
    }
}
