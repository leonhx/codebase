package com.leonhuang.common;

public abstract class Func1Void<P> {
    public abstract void apply(P value);

    public final <E extends Exception> Func1VoidWithErr<P, E> withErr() {
        final Func1Void<P> self = this;
        return new Func1VoidWithErr<P, E>() {
            @Override
            public void apply(P value) throws E {
                self.apply(value);
            }
        };
    }
}
