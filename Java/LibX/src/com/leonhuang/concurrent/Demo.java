package com.leonhuang.concurrent;

public class Demo {
    public static void main(String[] args) throws Exception {
        final Promise<Integer> p = new Promise<Integer>() {
            @Override
            public Integer run() {
                try {
                    Thread.sleep(1000);
                } catch (InterruptedException e) {
                    e.printStackTrace();
                }
                return 2 / 1;
            }
        };
        final Future<Integer> f = p.future();
        f.tryAwait(600);
        System.out.println(f.get());
    }
}
