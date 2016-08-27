package it.achdjian.paolo.domusviewer.temperature;

import android.support.v4.app.Fragment;
import android.widget.CheckBox;
import android.widget.CompoundButton;
import android.widget.RelativeLayout;

import org.androidannotations.annotations.AfterViews;
import org.androidannotations.annotations.EFragment;
import org.androidannotations.annotations.ViewById;
import org.rajawali3d.surface.IRajawaliSurface;
import org.rajawali3d.surface.RajawaliSurfaceView;

import it.achdjian.paolo.domusviewer.R;

/**
 * Created by Paolo Achdjian on 20/07/16.
 */
@EFragment(R.layout.temperature_layout)
public class TemperatureFragment  extends Fragment implements CompoundButton.OnCheckedChangeListener {
    @ViewById(R.id.rajaBase)
    RelativeLayout rajaBase;
    @ViewById(R.id.cbSottoscala)
    CheckBox cbSottoscala;

    TemperatureRender renderer;

    @AfterViews
    public void afterView(){

        final RajawaliSurfaceView surface = new RajawaliSurfaceView(getActivity());
        surface.setFrameRate(60.0);
        surface.setRenderMode(IRajawaliSurface.RENDERMODE_WHEN_DIRTY);

        renderer = new TemperatureRender(getContext());
        surface.setSurfaceRenderer(renderer);
        rajaBase.addView(surface);

        cbSottoscala.setOnCheckedChangeListener(this);
    }

    @Override
    public void onCheckedChanged(CompoundButton buttonView, boolean isChecked) {
        if (buttonView == cbSottoscala){
            renderer.enableLight("Taverna",isChecked);
        }
    }
}
