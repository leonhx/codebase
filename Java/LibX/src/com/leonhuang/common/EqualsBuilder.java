package com.leonhuang.common;

public class EqualsBuilder {
    private boolean eq;

    public EqualsBuilder() {
        eq = true;
    }

    public EqualsBuilder appendSuper(boolean superEquals) {
        eq = eq && superEquals;
        return this;
    }

    public EqualsBuilder append(Object lhs, Object rhs) {
        if (lhs == null) eq = eq && (rhs == null);
        else eq = eq && lhs.equals(rhs);
        return this;
    }

    public EqualsBuilder append(long lhs, long rhs) {
        eq = eq && (lhs == rhs);
        return this;
    }

    public EqualsBuilder append(int lhs, int rhs) {
        eq = eq && (lhs == rhs);
        return this;
    }

    public EqualsBuilder append(short lhs, short rhs) {
        eq = eq && (lhs == rhs);
        return this;
    }

    public EqualsBuilder append(char lhs, char rhs) {
        eq = eq && (lhs == rhs);
        return this;
    }

    public EqualsBuilder append(byte lhs, byte rhs) {
        eq = eq && (lhs == rhs);
        return this;
    }

    public EqualsBuilder append(double lhs, double rhs) {
        eq = eq && (lhs == rhs);
        return this;
    }

    public EqualsBuilder append(float lhs, float rhs) {
        eq = eq && (lhs == rhs);
        return this;
    }

    public EqualsBuilder append(boolean lhs, boolean rhs) {
        eq = eq && (lhs == rhs);
        return this;
    }

    public EqualsBuilder append(Object[] lhs, Object[] rhs) {
        if (lhs == null) eq = eq && (rhs == null);
        else if (rhs == null || lhs.length != rhs.length) eq = false;
        else {
            for (int i = 0; i < lhs.length; i++) {
                this.append(lhs[i], rhs[i]);
            }
        }
        return this;
    }

    public EqualsBuilder append(long[] lhs, long[] rhs) {
        if (lhs == null) eq = eq && (rhs == null);
        else if (rhs == null || lhs.length != rhs.length) eq = false;
        else {
            for (int i = 0; i < lhs.length; i++) {
                this.append(lhs[i], rhs[i]);
            }
        }
        return this;
    }

    public EqualsBuilder append(int[] lhs, int[] rhs) {
        if (lhs == null) eq = eq && (rhs == null);
        else if (rhs == null || lhs.length != rhs.length) eq = false;
        else {
            for (int i = 0; i < lhs.length; i++) {
                this.append(lhs[i], rhs[i]);
            }
        }
        return this;
    }

    public EqualsBuilder append(short[] lhs, short[] rhs) {
        if (lhs == null) eq = eq && (rhs == null);
        else if (rhs == null || lhs.length != rhs.length) eq = false;
        else {
            for (int i = 0; i < lhs.length; i++) {
                this.append(lhs[i], rhs[i]);
            }
        }
        return this;
    }

    public EqualsBuilder append(char[] lhs, char[] rhs) {
        if (lhs == null) eq = eq && (rhs == null);
        else if (rhs == null || lhs.length != rhs.length) eq = false;
        else {
            for (int i = 0; i < lhs.length; i++) {
                this.append(lhs[i], rhs[i]);
            }
        }
        return this;
    }

    public EqualsBuilder append(byte[] lhs, byte[] rhs) {
        if (lhs == null) eq = eq && (rhs == null);
        else if (rhs == null || lhs.length != rhs.length) eq = false;
        else {
            for (int i = 0; i < lhs.length; i++) {
                this.append(lhs[i], rhs[i]);
            }
        }
        return this;
    }

    public EqualsBuilder append(double[] lhs, double[] rhs) {
        if (lhs == null) eq = eq && (rhs == null);
        else if (rhs == null || lhs.length != rhs.length) eq = false;
        else {
            for (int i = 0; i < lhs.length; i++) {
                this.append(lhs[i], rhs[i]);
            }
        }
        return this;
    }

    public EqualsBuilder append(float[] lhs, float[] rhs) {
        if (lhs == null) eq = eq && (rhs == null);
        else if (rhs == null || lhs.length != rhs.length) eq = false;
        else {
            for (int i = 0; i < lhs.length; i++) {
                this.append(lhs[i], rhs[i]);
            }
        }
        return this;
    }

    public EqualsBuilder append(boolean[] lhs, boolean[] rhs) {
        if (lhs == null) eq = eq && (rhs == null);
        else if (rhs == null || lhs.length != rhs.length) eq = false;
        else {
            for (int i = 0; i < lhs.length; i++) {
                this.append(lhs[i], rhs[i]);
            }
        }
        return this;
    }

    public boolean isEquals() {
        return eq;
    }

    public void reset() {
        eq = true;
    }
}
