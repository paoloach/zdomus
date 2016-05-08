package it.achdjian.paolo.domusviewer.on_off;

import android.view.View;

import it.achdjian.paolo.domusviewer.DomusEngine;
import it.achdjian.paolo.domusviewer.Element;

/**
 * Created by Paolo Achdjian on 20/04/16.
 */
class IdentifyListener implements View.OnClickListener {
    private final DomusEngine domusEngine;

    public IdentifyListener(){
        domusEngine = DomusEngine.getInstance();
    }

    @Override
    public void onClick(View v) {
        Object tag = v.getTag();
        if (tag instanceof Element){
            Element element = (Element) tag;

            domusEngine.requestIdentify(element.network, element.endpoint);
        }
    }
}
