package it.achdjian.domusviewer.ScanningActivity;

import android.content.Context;
import android.os.Bundle;
import android.os.Handler;
import android.support.annotation.Nullable;
import android.support.v4.app.DialogFragment;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.ProgressBar;

import it.achdjian.domusviewer.R;

/**
 * Created by Paolo Achdjian on 19/07/15.
 * Copyright Paolo Achdjian
 */
public class ScanningDialogFragment extends DialogFragment {

	private int address;
	private Handler mHandler = new Handler();

	@Override
	public void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
	}

	@Nullable
	@Override
	public View onCreateView(LayoutInflater inflater, ViewGroup container, Bundle savedInstanceState) {
		View v = inflater.inflate(R.layout.fragment_scanning, container, false);
		final ProgressBar progressBar = (ProgressBar) v.findViewById(R.id.progressBar);
		address=0;
		new Thread(new ScanningRunnable(mHandler, progressBar, getActivity().getPreferences(Context.MODE_PRIVATE))).start();
		return v;
	}
}
