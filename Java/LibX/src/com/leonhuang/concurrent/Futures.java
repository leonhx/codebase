package com.leonhuang.concurrent;

import java.util.concurrent.ConcurrentLinkedQueue;

public class Futures<T> {
    private ConcurrentLinkedQueue<Future<T>> futures;

    public Futures() {
        futures = new ConcurrentLinkedQueue<Future<T>>();
    }

    public Futures<T> add(Future<T> future) {
        futures.add(future);
        return this;
    }

    public final ConcurrentLinkedQueue<T> get() throws Exception {
        ConcurrentLinkedQueue<T> values = new ConcurrentLinkedQueue<T>();
        for (Future<T> future : futures) {
            values.add(future.get());
        }
        return values;
    }

    public final Promise<ConcurrentLinkedQueue<T>> promise() {
        final Futures<T> self = this;
        return new Promise<ConcurrentLinkedQueue<T>>() {
            @Override
            public ConcurrentLinkedQueue<T> apply() throws Exception {
                while (!self.allDone()) Thread.sleep(1);
                return self.get();
            }
        };
    }

    public final int size() {
        return futures.size();
    }

    public final boolean isEmpty() {
        return futures.isEmpty();
    }

    public final boolean allDone() {
        if (isEmpty()) return false;
        for (Future<T> future : futures) {
            if (!future.isDone())
                return false;
        }
        return true;
    }

    public final boolean anyDone() {
        if (isEmpty()) return false;
        for (Future<T> future : futures) {
            if (future.isDone())
                return true;
        }
        return false;
    }

    public final boolean allSuccess() {
        if (isEmpty()) return false;
        for (Future<T> future : futures) {
            if (!future.isSuccess())
                return false;
        }
        return true;
    }

    public final boolean anySuccess() {
        if (isEmpty()) return false;
        for (Future<T> future : futures) {
            if (future.isSuccess())
                return true;
        }
        return false;
    }

    public final boolean allFailure() {
        if (isEmpty()) return false;
        for (Future<T> future : futures) {
            if (!future.isFailure())
                return false;
        }
        return true;
    }

    public final boolean anyFailure() {
        if (isEmpty()) return false;
        for (Future<T> future : futures) {
            if (future.isFailure())
                return true;
        }
        return false;
    }

    public final int countDone() {
        int count = 0;
        for (Future<T> future : futures) {
            if (future.isDone())
                count++;
        }
        return count;
    }

    public final int countSuccess() {
        int count = 0;
        for (Future<T> future : futures) {
            if (future.isSuccess())
                count++;
        }
        return count;
    }

    public final int countFailure() {
        int count = 0;
        for (Future<T> future : futures) {
            if (future.isFailure())
                count++;
        }
        return count;
    }
}
