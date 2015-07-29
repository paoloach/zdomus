package it.achdjian.domusviewer.ScanningActivity;

import android.support.v4.app.FragmentActivity;
import android.util.Log;

import it.achdjian.domusviewer.common.Stoppable;
import it.achdjian.domusviewer.domus_engine.DomusEngine;

/**
 * Created by Paolo Achdjian on 29/07/15.
 * Copyright Paolo Achdjian
 */
public class ScanningServer implements Runnable, Stoppable {
	private static final String TAG = ScanningServer.class.getName();
	private String target;
	private ScanningDialogFragment parent;

	public ScanningServer(String target, ScanningDialogFragment parent) {
		this.target = target;
		this.parent = parent;
	}

	@Override
	public void run() {
		Log.d(TAG, "Starting");
		FragmentActivity activity = parent.getActivity();

		DomusEngineVersion domusEngineVersion = DomusEngine.requestVersion(target);
		if (domusEngineVersion != null && domusEngineVersion.isValid()) {
			Log.d(TAG, "found domusEngine at " + target + " version: " + domusEngineVersion);
			activity.runOnUiThread(new Runnable() {
				@Override
				public void run() {
					parent.serverFound();
				}
			});
		}
		Log.d(TAG, "server not found");
		activity.runOnUiThread(new Runnable() {
			@Override
			public void run() {
				parent.serverNotFound();
			}
		});
	}

	@Override
	public void stop() {

	}
}
