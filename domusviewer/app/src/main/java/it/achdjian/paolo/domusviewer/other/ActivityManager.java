package it.achdjian.paolo.domusviewer.other;

import android.app.Activity;
import android.app.Application;
import android.os.Bundle;

import org.androidannotations.annotations.EBean;

/**
 * Created by Paolo Achdjian on 15/09/16.
 */
@EBean(scope = EBean.Scope.Singleton)
public class ActivityManager implements Application.ActivityLifecycleCallbacks {
    private Activity activity;

    @Override
    public void onActivityCreated(Activity activity, Bundle savedInstanceState) {
        this.activity = activity;
    }

    @Override
    public void onActivityStarted(Activity activity) {
        this.activity = activity;
    }

    @Override
    public void onActivityResumed(Activity activity) {
        this.activity = activity;
    }

    @Override
    public void onActivityPaused(Activity activity) {
        this.activity = null;
    }

    @Override
    public void onActivityStopped(Activity activity) {
        this.activity = null;
    }

    @Override
    public void onActivitySaveInstanceState(Activity activity, Bundle outState) {
    }

    @Override
    public void onActivityDestroyed(Activity activity) {
        this.activity = null;
    }

    public void runOnActivityThread(Runnable runner){
        if (activity != null){
            activity.runOnUiThread(runner);
        }
    }
}
