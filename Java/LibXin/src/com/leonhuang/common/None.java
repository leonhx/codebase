package com.leonhuang.common;

public class None<T> implements Option<T> {

    private int __hash__;
    private boolean __hashed__;

    @Override
    public boolean isNone() {
        return false;
    }

    @Override
    public T get() {
        throw new UnsupportedOperationException("Illegal to get value from None.");
    }

    @Override
    public int hashCode() {
        if (__hashed__) return __hash__;
        __hash__ = new HashCodeBuilder(41, 37).append(this.getClass()).
                append(isNone()).toHashCode();
        __hashed__ = true;
        return __hash__;
    }

    @Override
    public boolean equals(Object obj) {
        if (obj == null) return false;
        if (this == obj) return true;
        return (obj instanceof None);
    }
}

