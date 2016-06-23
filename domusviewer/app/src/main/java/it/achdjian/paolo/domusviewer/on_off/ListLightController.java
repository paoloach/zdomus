package it.achdjian.paolo.domusviewer.on_off;

import android.widget.ImageButton;

import java.util.ArrayList;
import java.util.List;

import it.achdjian.paolo.domusviewer.DomusEngine;
import it.achdjian.paolo.domusviewer.Element;

/**
 * Created by Paolo Achdjian on 23/06/16.
 */
class ListLightController {
    private final DomusEngine domusEngine;
    private final List<LightController> lightControllers = new ArrayList<>();

    public ListLightController(DomusEngine domusEngine) {

        this.domusEngine = domusEngine;
    }

    public void destroy(){
        for (LightController lightController : lightControllers) {
            lightController.stop();
        }
    }

    public void add(ImageButton light, Element element) {
        for(LightController lightController: lightControllers){
            if (lightController.imageButton == light){
                return;
            }
        }
        lightControllers.add(new LightController(domusEngine, light, element));
    }
}
