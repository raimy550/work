package com.android.raimy.utils;

import java.util.concurrent.atomic.AtomicReference;

/**
 * Created by raimy on 2018-03-15.
 */

public abstract  class AbstractSingleton<T> {

    private final AtomicReference<T> ref = new AtomicReference<T>();
    public T GetInstance() {
        T ret = ref.get();
        if (ret == null) {
            synchronized (this) {
                if (ref.get() == null) {
                    ret = NewObject();
                    ref.set(ret);
                } else {
                    ret = ref.get();
                }
            }
        }
        return ret;
    }

    protected abstract T NewObject();

}
