package com.leonhuang.concurrent;

public abstract class Promise<T> {
    public abstract T run();
    public final Future<T> future() {
        return new Future<T>(this);
    }
}
