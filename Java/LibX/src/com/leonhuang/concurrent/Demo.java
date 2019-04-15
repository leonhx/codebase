package com.leonhuang.concurrent;

import com.leonhuang.common.Function1;

public class Demo {
    public static void main(String[] args) throws Exception {
        Promise<Integer> p = new Promise<Integer>() {
            @Override
            public Integer run() {
                try {
                    Thread.sleep(1000);
                } catch (InterruptedException e) {
                    e.printStackTrace();
                }
                System.out.println("in Promise");
                return 2 / 1;
            }
        };
        final Future<Integer> f = p.future();
        final Future<Integer> f1 = f.map(new Future.MapFunction<Integer, Integer>() {
            @Override
            public Integer apply(Integer integer) {
                return integer + 1;
            }
        });
        System.out.println("in main1");
        f.onSuccess(new Future.SuccessCallback<Integer>() {
            @Override
            public void apply(Integer integer) {
                System.out.println("f");
                System.out.println(integer);
            }
        }).onFailure(new Future.FailureCallback() {
            @Override
            public void apply(Exception e) {
                System.out.println("onFailure");
                if (e instanceof ArithmeticException)
                    e.printStackTrace();
            }
        }).onComplete(new Future.CompleteCallback() {
            @Override
            public void apply() {
                System.out.println("onComplete");
            }
        });
        System.out.println("in main2");
        f1.onSuccess(new Future.SuccessCallback<Integer>() {
            @Override
            public void apply(Integer value) {
                System.out.println("f1");
                System.out.println(value);
            }
        });
        System.out.println("in main3");
        System.out.println(f.flatMap(new Future.MapFunction<Integer, Integer>() {
            @Override
            public Integer apply(Integer integer) {
                return integer * 2;
            }
        }));
    }
}
