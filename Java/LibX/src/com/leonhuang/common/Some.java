package com.leonhuang.common;

public class Some<T> implements Option<T> {
    private T value;

    private int __hash__;
    private boolean __hashed__;

    public Some(T value) {
        this.value = value;
    }

    @Override
    public boolean isNone() {
        return false;
    }

    @Override
    public T get() {
        return this.value;
    }

    @Override
    public int hashCode() {
        if (__hashed__) return __hash__;
        __hash__ = new HashCodeBuilder(41, 37).append(this.getClass()).
                append(isNone()).append(this.value).toHashCode();
        __hashed__ = true;
        return __hash__;
    }

    @Override
    public boolean equals(Object obj) {
        if (obj == null) return false;
        if (this == obj) return true;
        if (!(obj instanceof Some))
            return false;
        final Some that = (Some) obj;
        return new EqualsBuilder().append(this.value, that.value).isEquals();
    }

    @Override
    public String toString() {
        return String.format("Some(%s)", this.value);
    }
}
