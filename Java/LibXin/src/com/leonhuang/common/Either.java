package com.leonhuang.common;

public class Either<A, B> {
    private A aVal;
    private boolean isASet;
    private B bVal;
    private boolean isBSet;

    private int __hash__;
    private boolean __hashed__;

    public Either<A, B> _1(A value) {
        this.aVal = value;
        this.isASet = true;
        return this;
    }

    public Either<A, B> _2(B value) {
        this.bVal = value;
        this.isBSet = true;
        return this;
    }

    public boolean has_1() {
        return this.isASet;
    }

    public boolean has_2() {
        return this.isBSet;
    }

    public A _1() {
        if (!this.has_1()) throw new UnsupportedOperationException("no such field");
        return this.aVal;
    }

    public B _2() {
        if (!this.has_2()) throw new UnsupportedOperationException("no such field");
        return this.bVal;
    }

    @Override
    public int hashCode() {
        if (__hashed__) return __hash__;
        HashCodeBuilder hcb = new HashCodeBuilder(41, 37).append(this.getClass());
        hcb = hcb.append(this.isASet);
        if (this.isASet) {
            hcb = hcb.append(this.aVal);
        }
        hcb = hcb.append(this.isBSet);
        if (this.isBSet) {
            hcb = hcb.append(this.bVal);
        }
        __hash__ = hcb.toHashCode();
        __hashed__ = true;
        return __hash__;
    }

    @Override
    public boolean equals(Object obj) {
        if (obj == null) return false;
        if (this == obj) return true;
        if (!(obj instanceof Either))
            return false;
        Either that = (Either) obj;
        EqualsBuilder eb = new EqualsBuilder();
        if (this.isASet && that.isASet) {
            eb.append(this.aVal, that.aVal);
        } else {
            return false;
        }
        if (this.isBSet && that.isBSet) {
            eb.append(this.bVal, that.bVal);
        } else {
            return false;
        }
        return eb.isEquals();
    }
}
