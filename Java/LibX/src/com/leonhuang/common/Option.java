package com.leonhuang.common;

public interface Option<T> {
    public boolean isNone();
    public T get();
}
