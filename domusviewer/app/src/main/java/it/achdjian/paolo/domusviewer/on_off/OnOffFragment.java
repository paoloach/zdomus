package it.achdjian.paolo.domusviewer.on_off;

import android.os.Bundle;
import android.support.v4.app.Fragment;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.Button;
import android.widget.ListView;

import it.achdjian.paolo.domusviewer.R;

/**
 * Created by paolo on 14/04/16.
 */
public class OnOffFragment extends Fragment  {
    private SwitchAdapter switchAdapter;
    private LightAdapter lightAdapter;
    private BindController bindController;

    public static OnOffFragment newInstance() {
        return new OnOffFragment();
    }

    @Override
    public View onCreateView(LayoutInflater inflater, ViewGroup container,
                             Bundle savedInstanceState) {
        View rootView = inflater.inflate(R.layout.on_off_layout, container, false);

        switchAdapter = new SwitchAdapter(this.getContext());
        lightAdapter = new LightAdapter(this.getContext());

        ListView switches = (ListView) rootView.findViewById(R.id.switches);
        switches.setAdapter(switchAdapter);

        ListView lights = (ListView)rootView.findViewById(R.id.lghts);
        lights.setAdapter(lightAdapter);


        Button bindBound= (Button)rootView.findViewById(R.id.bindButton);
        bindController = new BindController(bindBound);
        switchAdapter.addListener(bindController);
        lightAdapter.addListener(bindController);
        return rootView;
    }


    @Override
    public void onDestroyView(){
        super.onDestroyView();
        if (switchAdapter!=null){
            switchAdapter.onDestroy();
            lightAdapter.onDestroy();
        }

    }

}
