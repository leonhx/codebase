package com.leonhuang.common;

public abstract class Func0VoidWithErr<E extends Throwable> {
    public abstract void apply() throws E;

    public final Func0Void withoutErr() {
        final Func0VoidWithErr<E> self = this;
        return new Func0Void() {
            @Override
            public void apply() {
                try {
                    self.apply();
                } catch (Throwable throwable) {
                    UnknownError err = new UnknownError(String.format(
                            "Unsafe casting from Func0VoidWithErr lead to the error: %s",
                            throwable.getMessage()));
                    err.setStackTrace(throwable.getStackTrace());
                    throw err;
                }
            }
        };
    }
}
