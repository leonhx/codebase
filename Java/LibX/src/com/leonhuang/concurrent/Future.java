package com.leonhuang.concurrent;

import com.leonhuang.common.*;

import java.util.concurrent.atomic.AtomicBoolean;
import java.util.concurrent.atomic.AtomicReference;

public class Future<T> {
    private final Promise<T> promise;
    private final AtomicBoolean finished = new AtomicBoolean();
    private final AtomicBoolean succeeded = new AtomicBoolean();
    private final AtomicReference<T> result = new AtomicReference<T>();
    private final AtomicReference<Exception> error = new AtomicReference<Exception>();
    private Func1Void<T> successCallback;
    private final AtomicBoolean hasCalledOnSuccess = new AtomicBoolean();
    private Func1Void<Exception> failureCallback;
    private final AtomicBoolean hasCalledOnFailure = new AtomicBoolean();
    private Func0Void completeCallback;
    private final AtomicBoolean hasCalledOnComplete = new AtomicBoolean();

    protected Future(final Promise<T> p) {
        this.promise = p;
        this.run();
    }

    private synchronized void applyCallback() {
        if (!this.finished.get()) return;
        final Either<T, Exception> resultOrError = new Either<T, Exception>();
        if (this.succeeded.get()) {
            resultOrError._1(this.result.get());
            if (this.successCallback != null && !this.hasCalledOnSuccess.get()) {
                this.successCallback.apply(this.result.get());
                this.hasCalledOnSuccess.set(true);
            }
        } else {
            resultOrError._2(this.error.get());
            if (this.failureCallback != null && !this.hasCalledOnFailure.get()) {
                this.failureCallback.apply(this.error.get());
                this.hasCalledOnFailure.set(true);
            }
        }
        if (this.completeCallback != null && !this.hasCalledOnComplete.get()) {
            this.completeCallback.apply();
            this.hasCalledOnComplete.set(true);
        }
    }

    private synchronized void run() {
        this.finished.set(false);
        this.hasCalledOnSuccess.set(false);
        this.hasCalledOnFailure.set(false);
        this.hasCalledOnComplete.set(false);
        final Future<T> self = this;
        new Thread() {
            public void run() {
                try {
                    final T result = self.promise.apply();
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

    public boolean retry() {
        if (!this.finished.get() || this.succeeded.get()) return false;
        this.run();
        return true;
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

    public final T get() throws Exception {
        if (this.isSuccess()) return this.result.get();
        else if (this.isFailure()) throw error.get();
        else throw new RuntimeException(String.format("%s has not finished", this));
    }

    public final T waitThenGet(long millis) throws Exception {
        this.tryAwait(millis);
        return this.get();
    }

    public final T waitThenGet() throws Exception {
        while (!this.isDone() && this.tryAwait(1000)) ;
        return this.get();
    }

    public final boolean tryAwait(long millis) {
        while (millis > 0 && !this.isDone()) {
            try {
                Thread.sleep(1);
                millis--;
            } catch (InterruptedException e) {
                return false;
            }
        }
        return true;
    }

    public final Future<T> onSuccess(final Func1Void<T> callback) {
        this.successCallback = callback;
        this.applyCallback();
        return this;
    }

    public final Future<T> onFailure(final Func1Void<Exception> callback) {
        this.failureCallback = callback;
        this.applyCallback();
        return this;
    }

    public final Future<T> onComplete(final Func0Void callback) {
        this.completeCallback = callback;
        this.applyCallback();
        return this;
    }

    public final <R> Future<R> map(final Func1<T, R> func) {
        return this.map(func.withErr());
    }

    public final <R, E extends Exception> Future<R> map(final Func1WithErr<T, R, E> func) {
        final Future<T> self = this;
        return new Promise<R>() {
            @Override
            public R apply() throws Exception {
                while (!self.isDone()) {
                    try {
                        Thread.sleep(1);
                    } catch (InterruptedException e) {
                        break;
                    }
                }
                return func.apply(self.get());
            }
        }.future();
    }

    public final <R> R flatMap(final Func1<T, R> func) throws Exception {
        return this.flatMap(func.withErr());
    }

    public final <R, E extends Exception> R flatMap(final Func1WithErr<T, R, E> func) throws Exception {
        final Future<R> mappedResult = this.map(func);
        return mappedResult.waitThenGet();
    }
}
