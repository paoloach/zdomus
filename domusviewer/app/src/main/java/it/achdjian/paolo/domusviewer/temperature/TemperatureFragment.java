package it.achdjian.paolo.domusviewer.temperature;

import android.support.annotation.Nullable;
import android.support.v4.app.Fragment;
import android.view.MotionEvent;
import android.view.View;
import android.widget.Button;
import android.widget.FrameLayout;
import android.widget.ListView;
import android.widget.TextView;

import com.google.common.base.Optional;

import org.androidannotations.annotations.AfterViews;
import org.androidannotations.annotations.Bean;
import org.androidannotations.annotations.EFragment;
import org.androidannotations.annotations.ViewById;
import org.rajawali3d.surface.IRajawaliSurface;
import org.rajawali3d.surface.RajawaliSurfaceView;

import it.achdjian.paolo.domusviewer.Element;
import it.achdjian.paolo.domusviewer.R;
import it.achdjian.paolo.domusviewer.database.TempSensorLocationDS;
import it.achdjian.paolo.domusviewer.zigbee.ZEndpoint;

/**
 * Created by Paolo Achdjian on 20/07/16.
 */
@EFragment(R.layout.temperature_layout)
public class TemperatureFragment extends Fragment implements View.OnTouchListener, EndpointObserver, SelectedRoomObserver {
    @ViewById(R.id.rajaBase)
    FrameLayout rajaBase;
    @ViewById(R.id.tempLV)
    ListView sensors;
    @ViewById(R.id.assign)
    Button assignButton;
    @ViewById(R.id.tempValue)
    TextView tempValue;
    @Bean
    TemperatureSensorsAdapter adapter;
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

    private TemperatureRender renderer;


    @AfterViews
    public void afterView() {
        final RajawaliSurfaceView surface = new RajawaliSurfaceView(getActivity());
        surface.setFrameRate(60.0);
        surface.setRenderMode(IRajawaliSurface.RENDERMODE_WHEN_DIRTY);
        surface.setClickable(true);

        renderer = new TemperatureRender(getContext(), rooms, temperatures, tempSensorLocationDS);
        temperatures.setRender(renderer);
        surface.setSurfaceRenderer(renderer);
        surface.setOnTouchListener(this);
        rajaBase.addView(surface);

        sensors.setAdapter(adapter);
        tempSensors.addObserver(adapter);
        tempSensors.addObserver(renderer);
        tempSensors.addObserver(this);

        assignButton.setOnClickListener(assignController);

        showSensorList();
        rajaBase.bringChildToFront(tempValue);

        rooms.addObserver(this);
    }

    @Override
    public void onDestroyView() {
        temperatures.setRender(null);
        tempSensors.removeObserver(adapter);
        tempSensors.removeObserver(this);
        tempSensors.removeObserver(renderer);
        rooms.removeObserver(this);
        super.onDestroyView();
    }


    @Override
    public boolean onTouch(View v, MotionEvent event) {
        if (event.getAction() == MotionEvent.ACTION_DOWN) {
            renderer.getObjectAt(event.getX(), event.getY());
        }
        return getActivity().onTouchEvent(event);
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

    private void showSensorList() {
        if (!tempSensors.someUnused()) {
            assignButton.setVisibility(View.GONE);
            sensors.setVisibility(View.GONE);
        } else {
            sensors.setVisibility(View.VISIBLE);
            assignButton.setVisibility(View.VISIBLE);
        }
    }

    @Override
    public void selected(@Nullable final String selectedRomm) {
        if (selectedRomm == null) {
            tempValue.setVisibility(View.GONE);
        } else {
            Element element = tempSensorLocationDS.getElement(selectedRomm);
            if (element != null) {
                getActivity().runOnUiThread(new Runnable() {
                    @Override
                    public void run() {

                        Optional<Integer> temperature = temperatures.getTemperature(selectedRomm);
                        if (temperature.isPresent()) {
                            tempValue.setVisibility(View.VISIBLE);
                            double temp = temperature.get();
                            temp = temp / 100;
                            tempValue.setText(Double.toString(temp));
                        } else {
                            tempValue.setVisibility(View.GONE);
                        }
                    }
                });

            } else {
                getActivity().runOnUiThread(new Runnable() {
                    @Override
                    public void run() {
                        tempValue.setVisibility(View.GONE);
                    }
                });

            }
        }
    }
}
