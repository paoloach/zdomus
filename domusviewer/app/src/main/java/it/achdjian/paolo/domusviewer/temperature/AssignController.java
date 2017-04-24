package it.achdjian.paolo.domusviewer.temperature;

import android.app.AlertDialog;
import android.content.Context;
import android.content.DialogInterface;
import android.util.Log;
import android.view.View;

import org.androidannotations.annotations.Bean;
import org.androidannotations.annotations.EBean;
import org.androidannotations.annotations.RootContext;

import it.achdjian.paolo.domusviewer.DomusEngine;
import it.achdjian.paolo.domusviewer.Element;
import it.achdjian.paolo.domusviewer.R;
import it.achdjian.paolo.domusviewer.database.TempSensorLocationDS;

/**
 * Created by Paolo Achdjian on 06/09/16.
 */
@EBean
public class AssignController implements View.OnClickListener, DialogInterface.OnClickListener {
    @Bean
    Rooms rooms;
    @Bean
    TempSensors tempSensors;
    @Bean
    TempSensorLocationDS tempSensorLocationDS;
    @Bean
    DomusEngine domusEngine;
    @RootContext
    Context context;

    public TemperatureFragment parent;

    @Override
    public void onClick(View v) {
        RoomObject selected = rooms.getSelected();
        if (selected != null) {
            Element element = tempSensors.getSelected();
            if (element != null) {
                if (!tempSensorLocationDS.isLocationUsedYet(selected.name)) {
                    assignSensor(selected, element);
                } else {
                    if (domusEngine.getDevices().existDevice(element.network)) {
                        AlertDialog.Builder builder = new AlertDialog.Builder(context);
                        AlertDialog dialog = builder.setMessage(R.string.already_assigned).
                                setPositiveButton(R.string.change_assignment, this).
                                setNegativeButton(R.string.leave_assignment, this).show();
                    } else {
                        assignSensor(selected, element);
                    }
                    Log.d(getClass().getName(), "Room " + selected.name + " is assigned yet");
                }
                if (parent != null) {
                    parent.showSensorList();
                }
            }
        }

    }

    @Override
    public void onClick(DialogInterface dialog, int which) {
        if (which == DialogInterface.BUTTON_POSITIVE) {
            Element element = tempSensors.getSelected();
            RoomObject selected = rooms.getSelected();
            if (element != null && selected != null) {
                assignSensor(selected, element);
            }
        }
    }

    private void assignSensor(RoomObject selected, Element element) {
        Log.d(getClass().getName(), "Assign " + element + " at " + selected.name);
        tempSensorLocationDS.createTempSensorLocation(element, selected.name);
        if (selected.temperatureLabel == null){
            selected.initLabels(context);
        }
    }
}
