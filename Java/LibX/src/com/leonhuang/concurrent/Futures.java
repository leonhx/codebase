package com.leonhuang.concurrent;

import java.util.concurrent.ConcurrentLinkedQueue;

public class Futures<T> {
    private ConcurrentLinkedQueue<Future<T>> futures;

    public Futures() {
        futures = new ConcurrentLinkedQueue<Future<T>>();
    }

    public Futures<T> append(Future<T> future) {
        futures.add(future);
        return this;
    }

    public final boolean tryAwait(long millis) {
        while (millis > 0 && !this.allDone()) {
            try {
                Thread.sleep(1);
                millis--;
            } catch (InterruptedException e) {
                return false;
            }
        }
        return this.allDone();
    }

    public final ConcurrentLinkedQueue<T> get() throws Exception {
        ConcurrentLinkedQueue<T> values = new ConcurrentLinkedQueue<T>();
        for (Future<T> future : futures) {
            values.add(future.get());
        }
        return values;
    }

    public Future<Futures<T>> future() {
        final Futures<T> self = this;
        return new Promise<Futures<T>>() {
            @Override
            public Futures<T> run() throws Exception {
                while (!self.allDone()) self.tryAwait(1000);
                return self;
            }
        }.future();
    }

    public final boolean allDone() {
        for (Future<T> future : futures) {
            if (!future.isDone())
                return false;
        }
        return true;
    }

    public final boolean anyDone() {
        for (Future<T> future : futures) {
            if (future.isDone())
                return true;
        }
        return false;
    }

    public final boolean allSuccess() {
        for (Future<T> future : futures) {
            if (!future.isSuccess())
                return false;
        }
        return true;
    }

    public final boolean anySuccess() {
        for (Future<T> future : futures) {
            if (future.isSuccess())
                return true;
        }
        return false;
    }

    public final boolean allFailure() {
        for (Future<T> future : futures) {
            if (!future.isFailure())
                return false;
        }
        return true;
    }

    public final boolean anyFailure() {
        for (Future<T> future : futures) {
            if (future.isFailure())
                return true;
        }
        return false;
    }
}
