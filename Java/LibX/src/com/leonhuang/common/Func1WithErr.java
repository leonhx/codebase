package com.leonhuang.common;

public interface Func1WithErr<P, R, E extends Throwable> {
    public R apply(P value) throws E;
}
