package com.leonhuang.common;

public abstract class Func0WithErr<R, E extends Throwable> {
    public abstract R apply() throws E;

    public final Func0<R> withoutErr() {
        final Func0WithErr<R, E> self = this;
        return new Func0<R>() {
            @Override
            public R apply() {
                try {
                    return self.apply();
                } catch (Throwable throwable) {
                    UnknownError err = new UnknownError(String.format(
                            "Unsafe casting from Func0WithErr lead to the error: %s",
                            throwable.getMessage()));
                    err.setStackTrace(throwable.getStackTrace());
                    throw err;
                }
            }
        };
    }
}
