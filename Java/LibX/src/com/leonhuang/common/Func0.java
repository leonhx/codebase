package com.leonhuang.common;

public abstract class Func0<R> {
    public abstract R apply();

    public final <E extends Exception> Func0WithErr<R, E> withErr() {
        final Func0<R> self = this;
        return new Func0WithErr<R, E>() {
            @Override
            public R apply() throws E {
                return self.apply();
            }
        };
    }
}
