package com.leonhuang.common;

public abstract class Func0Void {
    public abstract void apply();

    public final <E extends Exception> Func0VoidWithErr<E> withErr() {
        final Func0Void self = this;
        return new Func0VoidWithErr<E>() {
            @Override
            public void apply() throws E {
                self.apply();
            }
        };
    }
}
