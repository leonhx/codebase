package com.leonhuang.common;

public class HashCodeBuilder {
    private int hash;
    private int mul;

    public HashCodeBuilder(int base, int mul) {
        this.hash = base;
        this.mul = mul;
    }

    public HashCodeBuilder append(boolean value) {
        return this.append((Object) value);
    }

    public HashCodeBuilder append(boolean[] array) {
        for (boolean val : array) {
            this.append(val);
        }
        return this;
    }

    public HashCodeBuilder append(byte value) {
        return this.append((Object) value);
    }

    public HashCodeBuilder append(byte[] array) {
        for (byte val : array) {
            this.append(val);
        }
        return this;
    }

    public HashCodeBuilder append(char value) {
        return this.append((Object) value);
    }

    public HashCodeBuilder append(char[] array) {
        for (char val : array) {
            this.append(val);
        }
        return this;
    }

    public HashCodeBuilder append(double value) {
        return this.append((Object) value);
    }

    public HashCodeBuilder append(double[] array) {
        for (double val : array) {
            this.append(val);
        }
        return this;
    }

    public HashCodeBuilder append(float value) {
        return this.append((Object) value);
    }

    public HashCodeBuilder append(float[] array) {
        for (float val : array) {
            this.append(val);
        }
        return this;
    }

    public HashCodeBuilder append(int value) {
        return this.append((Object) value);
    }

    public HashCodeBuilder append(int[] array) {
        for (int val : array) {
            this.append(val);
        }
        return this;
    }

    public HashCodeBuilder append(long value) {
        return this.append((Object) value);
    }

    public HashCodeBuilder append(long[] array) {
        for (long val : array) {
            this.append(val);
        }
        return this;
    }

    public HashCodeBuilder append(Object object) {
        return this.appendSuper(object.hashCode());
    }

    public HashCodeBuilder append(Object[] array) {
        for (Object val : array) {
            this.append(val);
        }
        return this;
    }

    public HashCodeBuilder append(short value) {
        return this.append((Object) value);
    }

    public HashCodeBuilder append(short[] array) {
        for (short val : array) {
            this.append(val);
        }
        return this;
    }

    public HashCodeBuilder appendSuper(int superHashCode) {
        hash = hash * mul + superHashCode;
        return this;
    }

    public int toHashCode() {
        return hash;
    }

    @Override
    public int hashCode() {
        final HashCodeBuilder hcb = new HashCodeBuilder(41, 37);
        return hcb.append(hash).append(mul).toHashCode();
    }
}
