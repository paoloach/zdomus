package it.achdjian.domusviewer.ScanningActivity;

import android.app.Activity;
import android.content.SharedPreferences;
import android.os.Handler;
import android.util.Log;
import android.widget.ProgressBar;

import java.net.Inet4Address;
import java.net.InetAddress;
import java.net.InterfaceAddress;
import java.net.NetworkInterface;
import java.net.SocketException;
import java.util.ArrayList;
import java.util.Collections;
import java.util.Enumeration;
import java.util.List;

import it.achdjian.domusviewer.common.SharedKeys;
import it.achdjian.domusviewer.common.Stoppable;
import it.achdjian.domusviewer.domus_engine.DomusEngine;

/**
 * Created by Paolo Achdjian on 21/07/15.
 * Copyright Paolo Achdjian
 */
public class ScanningRunnable implements Runnable, Stoppable {
	private boolean stop;
	private static final String TAG = ScanningRunnable.class.getName();
	private final Handler uiHandler;
	private final ProgressBar progressBar;
	private final SharedPreferences sharedPreferences;
	private final Activity parent;
	private final ScanningResult scanningResult;

	public ScanningRunnable(Handler uiHandler, ProgressBar progressBar, SharedPreferences sharedPreferences, Activity parent, ScanningResult scanningResult) {
		this.uiHandler = uiHandler;
		this.progressBar = progressBar;
		this.sharedPreferences = sharedPreferences;
		this.parent = parent;
		this.scanningResult = scanningResult;
		stop=false;
	}

	@Override
	public void run() {
		final List<InterfaceAddress> availableAddress = new ArrayList<>();
		try {
			Enumeration<NetworkInterface> nets = NetworkInterface.getNetworkInterfaces();
			for (NetworkInterface netInt : Collections.list(nets)) {
				if(stop){
					return;
				}
				if (netInt.isLoopback() || !netInt.isUp() || netInt.isVirtual()) {
					continue;
				}
				List<InterfaceAddress> interfaceAddresses = netInt.getInterfaceAddresses();
				for (InterfaceAddress interfaceAddress : interfaceAddresses) {
					InetAddress address = interfaceAddress.getAddress();
					if (address instanceof Inet4Address) {
						availableAddress.add(interfaceAddress);
					}
				}
			}
		} catch (SocketException e) {
			e.printStackTrace();
		}
		uiHandler.post(new Runnable() {
			@Override
			public void run() {
				progressBar.setMax(availableAddress.size() * 255);
			}
		});

		int pos = 0;
		for (InterfaceAddress interfaceAddress : availableAddress) {
			InetAddress address = interfaceAddress.getAddress();
			String hostAddress = address.getHostAddress();
			Log.d(TAG, "address: " + hostAddress + " networkPrefixLength: " + interfaceAddress.getNetworkPrefixLength());
			String[] split = hostAddress.split("[.]");
			for (int i = 1; i <= 255; i++) {
				if(stop){
					return;
				}
				String target = split[0] + "." + split[1] + "." + split[2] + "." + i;
				if (checkTarget(target)) {
					parent.runOnUiThread(new Runnable() {
						@Override
						public void run() {
							scanningResult.serverFound();
							parent.finish();
						}
					});
					return;
				}
				updateProgressBar(pos);
				pos++;
			}
		}
		parent.runOnUiThread(new Runnable() {
			@Override
			public void run() {
				scanningResult.serverNotFound();
			}
		});

	}

	private void updateProgressBar(int pos) {
		final int uiPos = pos;
		uiHandler.post(new Runnable() {
			@Override
			public void run() {
				progressBar.setProgress(uiPos);
			}
		});
	}

	private boolean checkTarget(String target) {
		Log.d(TAG, "Check if " + target);
		DomusEngineVersion domusEngineVersion = DomusEngine.requestVersion(target);
		if (domusEngineVersion != null && domusEngineVersion.isValid()) {
			Log.d(TAG, "found domusEngine at " + target + " version: " + domusEngineVersion);
			SharedKeys.saveDomusEngineLocation(sharedPreferences, target, domusEngineVersion);
			return true;
		}
		return false;
	}


	@Override
	public void stop() {
		stop=true;
	}
}
