package it.achdjian.domusviewer.ScanningActivity;

import android.support.v4.app.Fragment;
import android.os.Bundle;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;

import it.achdjian.domusviewer.R;

/**
 * A placeholder fragment containing a simple view.
 */
public class ScanningActivityFragment extends Fragment {

	public ScanningActivityFragment() {
	}

	@Override
	public View onCreateView(LayoutInflater inflater, ViewGroup container,
							 Bundle savedInstanceState) {
		return inflater.inflate(R.layout.fragment_scanning, container, false);
	}
}
