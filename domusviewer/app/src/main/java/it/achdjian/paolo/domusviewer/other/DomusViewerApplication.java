package it.achdjian.paolo.domusviewer.other;

import android.app.Application;

import org.androidannotations.annotations.Bean;
import org.androidannotations.annotations.EApplication;

/**
 * Created by Paolo Achdjian on 15/09/16.
 */
@EApplication
public class DomusViewerApplication extends Application {
    @Bean
    ActivityManager activityManager;

    @Override
    public void onCreate(){
        super.onCreate();
        registerActivityLifecycleCallbacks(activityManager);
    }
}
