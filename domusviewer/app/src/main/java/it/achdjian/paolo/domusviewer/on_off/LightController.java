package it.achdjian.paolo.domusviewer.on_off;

import android.os.Handler;
import android.os.SystemClock;
import android.view.View;
import android.widget.ImageButton;

import java.util.List;
import java.util.Random;

import it.achdjian.paolo.domusviewer.Constants;
import it.achdjian.paolo.domusviewer.DTO.CmdRequest;
import it.achdjian.paolo.domusviewer.DomusEngine;
import it.achdjian.paolo.domusviewer.DomusEngineRest.JSonAttribute;
import it.achdjian.paolo.domusviewer.DomusEngineRest.Stoppable;
import it.achdjian.paolo.domusviewer.Element;

/**
 * Created by Paolo Achdjian on 15/06/16.
 */
public class LightController implements View.OnClickListener, Runnable, DomusEngine.AttributesListener, Stoppable {
    private static final int REQUEST_DELAY = 2000;
    private static final int REQUEST_DELAY_SHUFFLE = 300;
    private static final int DELAY_FROM_CLICK = 2000;
    private final DomusEngine domusEngine;
    private final ImageButton imageButton;
    private final Element element;
    private final Handler handler;
    private final Random random = new Random();
    private long lastRequest = 0;
    private boolean toStop;


    public LightController(DomusEngine domusEngine, ImageButton light, Element element) {
        this.domusEngine = domusEngine;
        imageButton = light;
        this.element = element;
        handler = new Handler();
        handler.postDelayed(this, random.nextInt(REQUEST_DELAY_SHUFFLE));
        toStop = false;
    }

    @Override
    public void onClick(View v) {
        if (SystemClock.elapsedRealtime() - lastRequest > DELAY_FROM_CLICK) {
            CmdRequest cmdRequest = new CmdRequest();
            cmdRequest.networkId = element.network;
            cmdRequest.endpointId = element.endpoint;
            cmdRequest.clusterId = Constants.ON_OFF_CLUSTER;
            if (imageButton.isActivated()) {
                cmdRequest.cmdId = 0;
            } else {
                cmdRequest.cmdId = 1;
            }
            domusEngine.sendCmd(cmdRequest);
            lastRequest = SystemClock.elapsedRealtime();
        }
    }

    @Override
    public void run() {
        domusEngine.requestAttributes(this, element.network, element.endpoint, Constants.ON_OFF_CLUSTER, 0);
    }

    @Override
    public void newAttributes(List<JSonAttribute> attributes) {
        if (!toStop) {
            for (final JSonAttribute attribute : attributes) {
                if (attribute.isSupported && attribute.isAvailable && attribute.id == 0) {
                    if (!toStop) {
                        handler.post(new Runnable() {
                            @Override
                            public void run() {
                                imageButton.setActivated(attribute.value.equals("1"));
                            }
                        });
                    }
                }
            }
            handler.postDelayed(this, REQUEST_DELAY + random.nextInt(REQUEST_DELAY_SHUFFLE));
        }
    }

    @Override
    public void stop() {
        toStop = true;
    }
}
