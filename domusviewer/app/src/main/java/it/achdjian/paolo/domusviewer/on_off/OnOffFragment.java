package it.achdjian.paolo.domusviewer.on_off;

import android.os.Bundle;
import android.support.v4.app.Fragment;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.TextView;

import it.achdjian.paolo.domusviewer.R;

/**
 * Created by paolo on 14/04/16.
 */
public class OnOffFragment extends Fragment {
    public static OnOffFragment newInstance() {
        OnOffFragment fragment = new OnOffFragment();
        return fragment;
    }

    @Override
    public View onCreateView(LayoutInflater inflater, ViewGroup container,
                             Bundle savedInstanceState) {
        View rootView = inflater.inflate(R.layout.on_off_layout, container, false);
        return rootView;
    }

}
