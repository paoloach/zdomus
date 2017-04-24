package it.achdjian.paolo.domusviewer.utils;

import android.content.Context;
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
    Context context;
    @Bean
    ZDeviceInfoClick zDeviceInfoClick;
    @Bean
    IdentifyListener identifyListener;

    public ElementView createElementView(ViewGroup parent, int layoutId, Element element, View oldView){
        return new ElementView(context, zDeviceInfoClick, identifyListener, parent, layoutId, element,oldView);
    }
}
