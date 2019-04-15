package com.leonhuang.common;

public abstract class Func1<P, R> {
    public abstract R apply(P value);

    public final <E extends Exception> Func1WithErr<P, R, E> withErr() {
        final Func1<P, R> self = this;
        return new Func1WithErr<P, R, E>() {
            @Override
            public R apply(P value) throws E {
                return self.apply(value);
            }
        };
    }
}
