package it.achdjian.paolo.domusviewer.temperature;

import android.support.v4.app.Fragment;
import android.util.Log;
import android.view.MotionEvent;
import android.view.View;
import android.widget.Button;
import android.widget.FrameLayout;
import android.widget.ListView;

import org.androidannotations.annotations.AfterViews;
import org.androidannotations.annotations.Bean;
import org.androidannotations.annotations.EFragment;
import org.androidannotations.annotations.ViewById;
import org.rajawali3d.surface.IRajawaliSurface;
import org.rajawali3d.surface.RajawaliSurfaceView;

import java.util.Collection;

import it.achdjian.paolo.domusviewer.Element;
import it.achdjian.paolo.domusviewer.R;
import it.achdjian.paolo.domusviewer.database.TempSensorLocationDS;

/**
 * Created by Paolo Achdjian on 20/07/16.
 */
@EFragment(R.layout.temperature_layout)
public class TemperatureFragment extends Fragment implements View.OnTouchListener, View.OnClickListener {
    @ViewById(R.id.rajaBase)
    FrameLayout rajaBase;
    @ViewById(R.id.tempLV)
    ListView sensors;
    @ViewById(R.id.assign)
    Button assignButton;
    @Bean
    TemperatureSensorsAdapter adapter;
    @Bean
    TempSensors tempSensors;
    @Bean
    TempSensorLocationDS tempSensorLocationDS;
    @Bean
    TemperatureCacheLoader temperatures;

    Rooms rooms;
    TemperatureRender renderer;

    @AfterViews
    public void afterView() {
        rooms = new Rooms();
        final RajawaliSurfaceView surface = new RajawaliSurfaceView(getActivity());
        surface.setFrameRate(60.0);
        surface.setRenderMode(IRajawaliSurface.RENDERMODE_WHEN_DIRTY);
        surface.setClickable(true);

        renderer = new TemperatureRender(getContext(), rooms,temperatures);
        surface.setSurfaceRenderer(renderer);
        surface.setOnTouchListener(this);
        rajaBase.addView(surface);

        sensors.setAdapter(adapter);

        assignButton.setOnClickListener(this);

        if (!tempSensors.someUnused()){
            assignButton.setVisibility(View.GONE);
            sensors.setVisibility(View.GONE);
        }
    }


    @Override
    public boolean onTouch(View v, MotionEvent event) {
        if (event.getAction() == MotionEvent.ACTION_DOWN) {
            renderer.getObjectAt(event.getX(), event.getY());
        }
        return getActivity().onTouchEvent(event);
    }

    @Override
    public void onClick(View v) {
        RoomObject selected = rooms.getSelected();
        Collection<Element> selectedSensors = tempSensors.getSelected();
        if (tempSensorLocationDS.isLocationUsedYet(selected.name) == false) {
            for (Element element : selectedSensors) {
                Log.d(getClass().getName(), "Assign " + element + " at " + selected.name);
                tempSensorLocationDS.createTempSensorLocation(element, selected.name);
            }
        } else {
            Log.d(getClass().getName(), "Room " + selected.name + " is assigned yet");
        }
    }
}
