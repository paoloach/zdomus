package it.achdjian.domusviewer.ScanningActivity;

import android.support.v4.app.Fragment;
import android.os.Bundle;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.ProgressBar;

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
		View v =  inflater.inflate(R.layout.fragment_scanning, container, false);
		Bundle arguments = getArguments();
		if (arguments != null) {
			CharSequence startingLocation = arguments.getCharSequence(ScanningDialogFragment.LOCATION);
		}
		final ProgressBar progressBar = (ProgressBar) v.findViewById(R.id.progressBar);
		//new Thread(new ScanningRunnable(new Handler(), progressBar, getActivity().getSharedPreferences(SharedKeys.PREFERENCE_NAME, Context.MODE_PRIVATE),this)).start();
		return v;
	}
}
