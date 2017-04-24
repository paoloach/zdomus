package it.achdjian.paolo.domusviewer.temperature;

import android.support.annotation.NonNull;
import android.support.annotation.Nullable;
import android.support.v4.app.Fragment;
import android.view.View;
import android.widget.Button;
import android.widget.FrameLayout;
import android.widget.ListView;
import android.widget.TextView;

import com.google.common.base.Optional;

import org.androidannotations.annotations.AfterViews;
import org.androidannotations.annotations.Bean;
import org.androidannotations.annotations.EFragment;
import org.androidannotations.annotations.UiThread;
import org.androidannotations.annotations.ViewById;
import org.rajawali3d.view.SurfaceView;

import java.util.Locale;

import it.achdjian.paolo.domusviewer.Element;
import it.achdjian.paolo.domusviewer.R;
import it.achdjian.paolo.domusviewer.database.TempSensorLocationDS;
import it.achdjian.paolo.domusviewer.zigbee.ZEndpoint;

/**
 * Created by Paolo Achdjian on 20/07/16.
 */
@EFragment(R.layout.temperature_layout)
public class TemperatureFragment extends Fragment implements EndpointObserver, RoomObserver, View.OnLayoutChangeListener {
    @ViewById(R.id.rajaBase)
    FrameLayout rajaBase;
    @ViewById(R.id.tempLV)
    ListView sensors;
    @ViewById(R.id.assign)
    Button assignButton;
    @ViewById(R.id.tempValue)
    TextView tempValue;
    @Bean
    TempSensors tempSensors;
    @Bean
    TempSensorLocationDS tempSensorLocationDS;
    @Bean
    TemperatureCache temperatures;
    @Bean
    Rooms rooms;
    @Bean
    AssignController assignController;
    private SurfaceView surface;

    private TemperatureRender renderer;


    @AfterViews
    public void afterView() {
        tempSensorLocationDS.createObservers();
        renderer = new TemperatureRender(getContext(), rooms, temperatures, tempSensorLocationDS);
        surface = new TemperatureSurface(getActivity(), renderer);
        temperatures.setRender(renderer);

        rajaBase.addView(surface);

        sensors.setAdapter(tempSensorLocationDS);
        tempSensors.addObserver(tempSensorLocationDS);
        tempSensors.addObserver(renderer);
        tempSensors.addObserver(this);

        assignButton.setOnClickListener(assignController);

        showSensorList();
        rajaBase.bringChildToFront(tempValue);
        rajaBase.addOnLayoutChangeListener(this);

        rooms.addObserver(this);
        assignController.parent = this;
        surface.requestRenderUpdate();
    }

    @Override
    public void onDestroyView() {
        temperatures.setRender(null);
        tempSensors.removeObserver(tempSensorLocationDS);
        tempSensors.removeObserver(this);
        tempSensors.removeObserver(renderer);
        rooms.removeObserver(this);
        super.onDestroyView();
    }

    @Override
    public void newDevice(ZEndpoint endpoint) {
        getActivity().runOnUiThread(new Runnable() {
            @Override
            public void run() {
                showSensorList();
            }
        });
    }

    public void showSensorList() {
        if (!tempSensors.someUnused()) {
            assignButton.setVisibility(View.GONE);
            sensors.setVisibility(View.GONE);
        } else {
            sensors.setVisibility(View.VISIBLE);
            assignButton.setVisibility(View.VISIBLE);
        }
    }

    @Override
    @UiThread
    public void selected(@Nullable final String selectedRoom) {
        if (selectedRoom == null) {
            tempValue.setVisibility(View.GONE);
        } else {
            Element element = tempSensorLocationDS.getElement(selectedRoom);
            if (element != null) {
                Optional<Integer> temperature = temperatures.getTemperature(selectedRoom);
                if (temperature.isPresent()) {
                    tempValue.setVisibility(View.VISIBLE);
                    double temp = temperature.get();
                    temp = temp / 100;
                    tempValue.setText(String.format(Locale.US, "%.2g", temp));
                } else {
                    tempValue.setVisibility(View.GONE);
                }
            } else {
                tempValue.setVisibility(View.GONE);
            }
        }
    }

    @Override
    @UiThread
    public void sensorAssignmentChange(@NonNull String roomName) {
        showSensorList();
    }

    @Override
    public void onLayoutChange(View v, int left, int top, int right, int bottom, int oldLeft, int oldTop, int oldRight, int oldBottom) {
        surface.onResume();
    }
}
