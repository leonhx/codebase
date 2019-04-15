package com.leonhuang.concurrent;

import com.leonhuang.common.Either;

import java.util.concurrent.atomic.AtomicBoolean;
import java.util.concurrent.atomic.AtomicReference;

public class Future<T> {
    public interface SuccessCallback<T> {
        public void apply(T value);
    }
    public interface FailureCallback {
        public void apply(Exception error);
    }
    public interface CompleteCallback<T> {
        public void apply(Either<T, Exception> result);
    }

    private final Promise<T> promise;
    private final AtomicBoolean finished = new AtomicBoolean();
    private final AtomicBoolean succeeded = new AtomicBoolean();
    private final AtomicReference<T> result = new AtomicReference<T>();
    private final AtomicReference<Exception> error = new AtomicReference<Exception>();
    private SuccessCallback<T> callOnSuccess;
    private final AtomicBoolean hasCalledOnSuccess = new AtomicBoolean();
    private FailureCallback callOnFailure;
    private final AtomicBoolean hasCalledOnFailure = new AtomicBoolean();
    private CompleteCallback<T> callOnDone;
    private final AtomicBoolean hasCalledOnDone = new AtomicBoolean();

    protected Future(final Promise<T> p) {
        this.promise = p;
        this.run();
    }

    private synchronized void applyCallback() {
        if (!this.finished.get()) return;
        final Either<T, Exception> resultOrError = new Either<T, Exception>();
        if (this.succeeded.get()) {
            resultOrError._1(this.result.get());
            if (this.callOnSuccess != null && !this.hasCalledOnSuccess.get()) {
                this.callOnSuccess.apply(this.result.get());
                this.hasCalledOnSuccess.set(true);
            }
        } else {
            resultOrError._2(this.error.get());
            if (this.callOnFailure != null && !this.hasCalledOnFailure.get()) {
                this.callOnFailure.apply(this.error.get());
                this.hasCalledOnFailure.set(true);
            }
        }
        if (this.callOnDone != null && !this.hasCalledOnDone.get()) {
            this.callOnDone.apply(resultOrError);
            this.hasCalledOnDone.set(true);
        }
    }

    private synchronized void run() {
        this.finished.set(false);
        this.hasCalledOnSuccess.set(false);
        this.hasCalledOnFailure.set(false);
        this.hasCalledOnDone.set(false);
        final Future<T> self = this;
        new Thread() {
            public void run() {
                try {
                    final T result = self.promise.run();
                    self.result.set(result);
                    self.succeeded.set(true);
                } catch (Exception e) {
                    self.error.set(e);
                    self.succeeded.set(false);
                } finally {
                    self.finished.set(true);
                }
                self.applyCallback();
            }
        }.start();
    }

    public final boolean isDone() {
        return this.finished.get();
    }

    public final boolean isSuccess() {
        return isDone() && this.succeeded.get();
    }

    public final boolean isFailure() {
        return isDone() && !this.succeeded.get();
    }

    public final T get() throws InterruptedException {
        if (this.isSuccess()) return this.result.get();
        else if (this.isFailure()) throw new IllegalStateException(String.format("%s failed to get result", this));
        else throw new InterruptedException(String.format("%s has not finished", this));
    }

    public final Future<T> onSuccess(final SuccessCallback<T> callback) {
        this.callOnSuccess = callback;
        this.applyCallback();
        return this;
    }

    public final Future<T> onFailure(final FailureCallback callback) {
        this.callOnFailure = callback;
        this.applyCallback();
        return this;
    }

    public final Future<T> onComplete(final CompleteCallback<T> callback) {
        this.callOnDone = callback;
        this.applyCallback();
        return this;
    }
}
