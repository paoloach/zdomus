package it.achdjian.paolo.domusviewer.on_off;

import android.app.Activity;
import android.app.AlertDialog;
import android.content.DialogInterface;
import android.support.annotation.NonNull;

import it.achdjian.paolo.domusviewer.DomusEngine;
import it.achdjian.paolo.domusviewer.Element;
import it.achdjian.paolo.domusviewer.zigbee.BindRequestData;
import it.achdjian.paolo.domusviewer.zigbee.ClustersId;

/**
 * Created by Paolo Achdjian on 06/05/16.
 */
class Binding implements DialogInterface.OnClickListener {
    private final Activity activity;
    private Element switchElement;
    private Element lightElement;
    private boolean bind;

    public Binding(Activity activity) {
        this.activity = activity;
    }

    public void bind(@NonNull Element switchElement, @NonNull Element lightElement) {
        bind=true;
        this.switchElement = switchElement;
        this.lightElement = lightElement;
        String text = "Do you want bind the switch " + switchElement.getName() + " with the light " + lightElement.getName() + " ?";
        AlertDialog.Builder builder = new AlertDialog.Builder(activity);
        AlertDialog alertDialog = builder.setTitle("Bind").setMessage(text).setNegativeButton("NO", this).setPositiveButton("YES", this).create();
        alertDialog.show();
    }

    public void unbind(@NonNull Element switchElement, @NonNull Element lightElement) {
        bind=false;
        this.switchElement = switchElement;
        this.lightElement = lightElement;
        String text = "Do you want bind the switch " + switchElement.getName() + " with the light " + lightElement.getName() + " ?";
        AlertDialog.Builder builder = new AlertDialog.Builder(activity);
        AlertDialog alertDialog = builder.setTitle("Bind").setMessage(text).setNegativeButton("NO", this).setPositiveButton("YES", this).create();
        alertDialog.show();
    }

    @Override
    public void onClick(DialogInterface dialog, int which) {
        dialog.dismiss();
        if (which == DialogInterface.BUTTON_POSITIVE) {
            DomusEngine domusEngine = DomusEngine.getInstance();
            BindRequestData data = new BindRequestData(switchElement.network, switchElement.endpoint, ClustersId.ON_OFF_CLUSTER, lightElement.network, lightElement.endpoint);
            if (bind) {
                domusEngine.bind(data);
            } else {
                domusEngine.unbind(data);
            }
            domusEngine.requestBindMap();
        }
    }
}
