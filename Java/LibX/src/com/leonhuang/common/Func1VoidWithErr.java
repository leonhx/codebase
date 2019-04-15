package com.leonhuang.common;

public interface Func1VoidWithErr<P, E extends Throwable> {
    public void apply(P value) throws E;
}
