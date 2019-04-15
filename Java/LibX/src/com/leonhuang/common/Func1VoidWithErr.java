package com.leonhuang.common;

public abstract class Func1VoidWithErr<P, E extends Throwable> {
    public abstract void apply(P value) throws E;

    public final Func1Void<P> withoutErr() {
        final Func1VoidWithErr<P, E> self = this;
        return new Func1Void<P>() {
            @Override
            public void apply(P value) {
                try {
                    self.apply(value);
                } catch (Throwable throwable) {
                    UnknownError err = new UnknownError(String.format(
                            "Unsafe casting from Func1VoidWithErr lead to the error: %s",
                            throwable.getMessage()));
                    err.setStackTrace(throwable.getStackTrace());
                    throw err;
                }
            }
        };
    }
}
