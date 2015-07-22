package it.achdjian.domusviewer.ScanningActivity;

import android.os.Handler;
import android.support.v4.app.Fragment;
import android.os.Bundle;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.ProgressBar;

import java.net.Inet4Address;
import java.net.InetSocketAddress;
import java.net.NetworkInterface;
import java.net.SocketException;
import java.util.Enumeration;

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
		try {
			Enumeration<NetworkInterface> networkInterfaces = NetworkInterface.getNetworkInterfaces();

		} catch (SocketException e) {
			e.printStackTrace();
		}
		View v =  inflater.inflate(R.layout.fragment_scanning, container, false);

		final ProgressBar progressBar = (ProgressBar) v.findViewById(R.id.progressBar);
		new Thread(new ScanningRunnable(new Handler(), progressBar)).start();
		return v;
	}
}
