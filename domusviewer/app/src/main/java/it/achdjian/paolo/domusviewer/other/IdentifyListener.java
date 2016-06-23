package it.achdjian.paolo.domusviewer.other;

import android.view.View;

import org.androidannotations.annotations.Bean;
import org.androidannotations.annotations.EBean;

import it.achdjian.paolo.domusviewer.DomusEngine;
import it.achdjian.paolo.domusviewer.Element;

/**
 * Created by Paolo Achdjian on 20/04/16.
 */
@EBean
public class IdentifyListener implements View.OnClickListener {
    @Bean
    DomusEngine domusEngine;

    @Override
    public void onClick(View v) {
        Object tag = v.getTag();
        if (tag instanceof Element){
            Element element = (Element) tag;

            domusEngine.requestIdentify(element.network, element.endpoint);
        }
    }
}
