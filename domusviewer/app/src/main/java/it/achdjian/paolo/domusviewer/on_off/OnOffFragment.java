package it.achdjian.paolo.domusviewer.on_off;

import android.support.v4.app.Fragment;
import android.widget.ListView;

import org.androidannotations.annotations.AfterViews;
import org.androidannotations.annotations.Bean;
import org.androidannotations.annotations.EFragment;
import org.androidannotations.annotations.ViewById;

import it.achdjian.paolo.domusviewer.DomusEngine;
import it.achdjian.paolo.domusviewer.R;

/**
 * Created by paolo on 14/04/16.
 */
@EFragment(R.layout.on_off_layout)
public class OnOffFragment extends Fragment {
    @ViewById(R.id.switches)
    ListView switches;

    @ViewById(R.id.lights)
    ListView lights;
    @Bean
    BindController bindController;
    @Bean
    DomusEngine domusEngine;
    @Bean
    Binding binding;
    @Bean
    SwitchAdapter switchAdapter;
    @Bean
    LightAdapter lightAdapter;


    @AfterViews
    public void afterView(){
        switchAdapter.init(bindController, binding);
        lightAdapter.init(bindController, binding);

        switches.setAdapter(switchAdapter);
        lights.setAdapter(lightAdapter);

        switchAdapter.addListener(bindController);
        lightAdapter.addListener(bindController);

        bindController.switchAdapter = switchAdapter;
        bindController.lightAdapter = lightAdapter;
    }

    @Override
    public void onStart() {
        super.onStart();
        domusEngine.requestBindMap();
    }


    @Override
    public void onDestroyView() {
        super.onDestroyView();
        if (switchAdapter != null) {
            switchAdapter.onDestroy();
            lightAdapter.onDestroy();
        }

    }

}
