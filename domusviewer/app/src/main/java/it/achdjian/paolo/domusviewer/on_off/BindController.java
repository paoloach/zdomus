package it.achdjian.paolo.domusviewer.on_off;

import android.support.annotation.NonNull;
import android.view.View;
import android.widget.Button;

import java.util.HashSet;
import java.util.Set;

import it.achdjian.paolo.domusviewer.DomusEngine;
import it.achdjian.paolo.domusviewer.zigbee.BindRequestData;

/**
 * Created by Paolo Achdjian on 25/04/16.
 */
public class BindController implements SwitchListener, LightListener , View.OnClickListener{
    private final Button bindButton;
    private final Set<OnOffAdapter.Element> switchSelected = new HashSet<>();
    private final Set<OnOffAdapter.Element> lightSelected = new HashSet<>();

    public BindController(@NonNull  Button bindButton) {
        this.bindButton = bindButton;
        bindButton.setEnabled(false);
        bindButton.setOnClickListener(this);
    }

    @Override
    public void changeLight(@NonNull OnOffAdapter.Element element, boolean selected) {
        if (selected) {
            lightSelected.add(element);
        } else {
            lightSelected.remove(element);
        }
        setEnable();
    }

    private void setEnable() {
        if (!lightSelected.isEmpty() && !switchSelected.isEmpty()){
            bindButton.setEnabled(true);
        } else {
            bindButton.setEnabled(false);
        }
    }

    @Override
    public void changeSwitch(@NonNull OnOffAdapter.Element element, boolean selected) {
        if (selected) {
            switchSelected.add(element);
        } else {
            switchSelected.remove(element);
        }
        setEnable();
    }

    @Override
    public void onClick(View v) {
        if (!lightSelected.isEmpty() && !switchSelected.isEmpty()){
            DomusEngine instance = DomusEngine.getInstance();
            for (OnOffAdapter.Element switchElement :switchSelected){
                for (OnOffAdapter.Element lightElement : lightSelected) {
                    instance.bind(new BindRequestData(switchElement.network, switchElement.endpoint, 6, lightElement.network, lightElement.endpoint));
                }
            }
        }
    }
}
