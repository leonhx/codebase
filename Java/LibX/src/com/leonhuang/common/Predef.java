package com.leonhuang.common;

import com.leonhuang.concurrent.Future;
import com.leonhuang.concurrent.Futures;
import com.leonhuang.concurrent.Promise;

public class Predef {
    public static <T> Some<T> some(T value) {
        return new Some<T>(value);
    }

    public static <T> None<T> none() {
        return new None<T>();
    }

    public static <T> Future<T> future(Promise<T> promise) {
        return promise.future();
    }

    public static <T> Func1<T, T> identity() {
        return new Func1<T, T>() {
            @Override
            public T apply(T value) {
                return value;
            }
        };
    }

    public static <T> Futures<T> futures() {
        return new Futures<T>();
    }

}
