package it.achdjian.paolo.domusviewer.on_off;

import android.os.Handler;
import android.view.View;
import android.widget.ImageButton;

import java.util.List;

import it.achdjian.paolo.domusviewer.Constants;
import it.achdjian.paolo.domusviewer.DomusEngine;
import it.achdjian.paolo.domusviewer.DomusEngineRest.JSonAttribute;
import it.achdjian.paolo.domusviewer.Element;

/**
 * Created by Paolo Achdjian on 15/06/16.
 */
public class LightController implements View.OnClickListener, Runnable, DomusEngine.AttributesListener {
    private final DomusEngine domusEngine;
    private final ImageButton imageButton;
    private final Element element;
    private final Handler handler;

    public LightController(DomusEngine domusEngine, ImageButton light, Element element) {
        this.domusEngine = domusEngine;
        imageButton = light;
        this.element = element;
        handler = new Handler();
        handler.post(this);
    }

    @Override
    public void onClick(View v) {

    }

    @Override
    public void run() {
        domusEngine.requestAttributes(this, element.network, element.endpoint, Constants.ON_OFF_CLUSTER, 0);
        handler.postDelayed(this,2000);
    }

    @Override
    public void newAttributes(List<JSonAttribute> attributes) {
        for (JSonAttribute  attribute: attributes) {
            if (attribute.isSupported && attribute.isAvailable && attribute.id == 0){
                if (attribute.value.equals("1")){
                    handler.post(new Runnable() {
                        @Override
                        public void run() {
                            imageButton.setActivated(true);
                        }
                    });
                } else {
                    handler.post(new Runnable() {
                        @Override
                        public void run() {
                            imageButton.setActivated(false);
                        }
                    });
                }
            }
        }
    }
}
