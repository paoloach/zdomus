package it.achdjian.domusviewer.ViewZigBee;

import android.os.Bundle;
import android.support.v4.app.Fragment;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;

import it.achdjian.domusviewer.R;

/**
 * Created by Paolo Achdjian on 04/07/15.
 * Copyright Paolo Achdjian
 */
public class ZigBeeFragment extends Fragment {
	@Override
	public View onCreateView(LayoutInflater inflater, ViewGroup container, Bundle savedInstanceState) {
		View view = inflater.inflate(R.layout.fragment_zigbee, container, false);
		return view;
	}
}
