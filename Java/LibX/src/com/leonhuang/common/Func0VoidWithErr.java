package com.leonhuang.common;

public interface Func0VoidWithErr<E extends Throwable> {
    public void apply() throws E;
}
