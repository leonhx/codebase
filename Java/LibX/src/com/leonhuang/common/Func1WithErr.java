package com.leonhuang.common;

public abstract class Func1WithErr<P, R, E extends Throwable> {
    public abstract R apply(P value) throws E;

    public final Func1<P, R> withoutErr() {
        final Func1WithErr<P, R, E> self = this;
        return new Func1<P, R>() {
            @Override
            public R apply(P value) {
                try {
                    return self.apply(value);
                } catch (Throwable throwable) {
                    UnknownError err = new UnknownError(String.format(
                            "Unsafe casting from Func1WithErr lead to the error: %s",
                            throwable.getMessage()));
                    err.setStackTrace(throwable.getStackTrace());
                    throw err;
                }
            }
        };
    }
}