package it.achdjian.paolo.domusviewer.on_off;

import android.os.Bundle;
import android.support.v4.app.Fragment;
import android.support.v4.app.FragmentManager;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.ListView;

import it.achdjian.paolo.domusviewer.DomusEngine;
import it.achdjian.paolo.domusviewer.R;

/**
 * Created by paolo on 14/04/16.
 */
public class OnOffFragment extends Fragment {
    private SwitchAdapter switchAdapter;
    private LightAdapter lightAdapter;

    public static OnOffFragment newInstance() {
        return new OnOffFragment();
    }

    @Override
    public View onCreateView(LayoutInflater inflater, ViewGroup container, Bundle savedInstanceState) {
        FragmentManager fragmentManager = getFragmentManager();

        ElementSelected elementSelected = new ElementSelected();
        Binding binding = new Binding(getActivity());
        View rootView = inflater.inflate(R.layout.on_off_layout, container, false);
        BindController bindController = new BindController(elementSelected);

        switchAdapter = new SwitchAdapter(this.getContext(), bindController, binding, elementSelected,fragmentManager);
        lightAdapter = new LightAdapter(this.getContext(), bindController, binding, elementSelected,fragmentManager);

        ListView switches = (ListView) rootView.findViewById(R.id.switches);
        switches.setAdapter(switchAdapter);

        ListView lights = (ListView) rootView.findViewById(R.id.lghts);
        lights.setAdapter(lightAdapter);

        switchAdapter.addListener(bindController);
        lightAdapter.addListener(bindController);

        bindController.switchAdapter = switchAdapter;
        bindController.lightAdapter = lightAdapter;
        return rootView;
    }

    @Override
    public void onStart() {
        super.onStart();
        DomusEngine.getInstance().requestBindMap();
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
