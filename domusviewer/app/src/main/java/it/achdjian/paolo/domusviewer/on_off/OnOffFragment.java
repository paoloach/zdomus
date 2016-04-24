package it.achdjian.paolo.domusviewer.on_off;

import android.os.Bundle;
import android.support.v4.app.Fragment;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.ListView;

import it.achdjian.paolo.domusviewer.R;

/**
 * Created by paolo on 14/04/16.
 */
public class OnOffFragment extends Fragment  {
    private SwitchAdapter switchAdapter;
    private LightAdapter lightAdapter;

    public static OnOffFragment newInstance() {
        return new OnOffFragment();
    }

    @Override
    public View onCreateView(LayoutInflater inflater, ViewGroup container,
                             Bundle savedInstanceState) {
        View rootView = inflater.inflate(R.layout.on_off_layout, container, false);

        switchAdapter = new SwitchAdapter(this.getContext(), inflater);
        lightAdapter = new LightAdapter(this.getContext(), inflater);

        ListView switches = (ListView) rootView.findViewById(R.id.switches);
        switches.setAdapter(switchAdapter);

        ListView ligths = (ListView)rootView.findViewById(R.id.lghts);
        ligths.setAdapter(lightAdapter);

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
