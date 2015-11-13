package it.achdjian.domusviewer.ScanningActivity;

import android.content.Context;
import android.os.Bundle;
import android.os.Handler;
import android.support.annotation.Nullable;
import android.support.v4.app.DialogFragment;
import android.util.Log;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.ProgressBar;
import android.widget.TextView;

import it.achdjian.domusviewer.R;
import it.achdjian.domusviewer.common.SharedKeys;
import it.achdjian.domusviewer.common.Stoppable;

/**
 * Created by Paolo Achdjian on 19/07/15.
 * Copyright Paolo Achdjian
 */
public class ScanningDialogFragment extends DialogFragment {
	public static final String LOCATION = "location";
	static final String TAG= ScanningDialogFragment.class.getName();

	private int address;
	private Handler mHandler = new Handler();
	private String domusEngineLocation;
	private Stoppable stoppable;

	public ScanningDialogFragment() {
	}

	@Override
	public void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
	}

	@Nullable
	@Override
	public View onCreateView(LayoutInflater inflater, ViewGroup container, Bundle savedInstanceState) {
		View v = inflater.inflate(R.layout.fragment_scanning, container, false);
		TextView scanningText = (TextView) v.findViewById(R.id.scanning_text);
		final ProgressBar progressBar = (ProgressBar) v.findViewById(R.id.progressBar);

		Bundle arguments = getArguments();
		String location = (String) arguments.getCharSequence(LOCATION);
		if (location != null && !location.isEmpty()){
			scanningText.setText(getActivity().getString(R.string.scanningIp, location));
			ScanningServer scanningServer = new ScanningServer(location, this);
			stoppable = scanningServer;
			new Thread(scanningServer).start();
		} else {
			scanningText.setText(R.string.scanningProgress);
			ScanningRunnable scanningRunnable = new ScanningRunnable(new Handler(), progressBar, getActivity().getSharedPreferences(SharedKeys.PREFERENCE_NAME, Context.MODE_PRIVATE), getActivity());
			stoppable = scanningRunnable;
			new Thread(scanningRunnable).start();
		}

		return v;
	}

	@Override
	public void onDestroyView() {
		super.onDestroyView();
		if (stoppable != null) {
			stoppable.stop();
		}
	}

	public void serverFound() {
		Log.d(TAG, "Server found");
		dismiss();
	}

	public void serverNotFound() {
		Log.d(TAG, "Server not found");
		final TextView scanningText = (TextView) getView().findViewById(R.id.scanning_text);
		final ProgressBar progressBar = (ProgressBar) getView().findViewById(R.id.progressBar);
		scanningText.setText(R.string.scanningProgress);
		ScanningRunnable scanningRunnable = new ScanningRunnable(new Handler(), progressBar, getActivity().getSharedPreferences(SharedKeys.PREFERENCE_NAME, Context.MODE_PRIVATE), getActivity());
		stoppable = scanningRunnable;
		new Thread(scanningRunnable).start();
	}
}
