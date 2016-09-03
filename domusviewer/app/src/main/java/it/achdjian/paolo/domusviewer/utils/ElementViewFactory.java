package it.achdjian.paolo.domusviewer.utils;

import android.support.v7.app.AppCompatActivity;
import android.view.View;
import android.view.ViewGroup;

import org.androidannotations.annotations.Bean;
import org.androidannotations.annotations.EBean;
import org.androidannotations.annotations.RootContext;

import it.achdjian.paolo.domusviewer.Element;
import it.achdjian.paolo.domusviewer.other.IdentifyListener;
import it.achdjian.paolo.domusviewer.other.ZDeviceInfoClick;

/**
 * Created by Paolo Achdjian on 30/08/16.
 */
@EBean
public class ElementViewFactory {
    @RootContext
    AppCompatActivity activity;
    @Bean
    ZDeviceInfoClick zDeviceInfoClick;
    @Bean
    IdentifyListener identifyListener;

    public ElementView createElementView(ViewGroup parent, int layoutId, Element element, View oldView){
        return new ElementView(activity, zDeviceInfoClick, identifyListener, parent, layoutId, element,oldView);
    }
}
