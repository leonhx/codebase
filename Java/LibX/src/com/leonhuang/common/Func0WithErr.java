package com.leonhuang.common;

public interface Func0WithErr<R, E extends Throwable> {
    public R apply() throws E;
}
