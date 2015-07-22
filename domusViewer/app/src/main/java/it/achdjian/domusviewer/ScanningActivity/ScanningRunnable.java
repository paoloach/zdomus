package it.achdjian.domusviewer.ScanningActivity;

import android.os.Handler;
import android.util.Log;
import android.widget.ProgressBar;

import java.io.IOException;
import java.net.Inet4Address;
import java.net.InetAddress;
import java.net.InterfaceAddress;
import java.net.NetworkInterface;
import java.net.SocketException;
import java.util.ArrayList;
import java.util.Collections;
import java.util.Enumeration;
import java.util.List;

/**
 * Created by Paolo Achdjian on 21/07/15.
 * Copyright Paolo Achdjian
 */
public class ScanningRunnable implements Runnable {
	private static String TAG = ScanningRunnable.class.getName();
	private final Handler uiHandler;
	private final ProgressBar progressBar;

	public ScanningRunnable(Handler uiHandler, ProgressBar progressBar) {
		this.uiHandler = uiHandler;
		this.progressBar = progressBar;
	}

	@Override
	public void run() {
		final List<InterfaceAddress> availableAddress = new  ArrayList<InterfaceAddress>();
		try {
			Enumeration<NetworkInterface> nets = NetworkInterface.getNetworkInterfaces();
			for (NetworkInterface netInt : Collections.list(nets)){
				if (netInt.isLoopback() || !netInt.isUp() || netInt.isVirtual()){
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
				progressBar.setMax(availableAddress.size()*255);
			}
		});

		int pos = 0;
		for (InterfaceAddress interfaceAddress : availableAddress) {
			InetAddress address = interfaceAddress.getAddress();
			String hostAddress = address.getHostAddress();
			Log.d(TAG, "address: " + hostAddress + " networkPrefixLength: " + interfaceAddress.getNetworkPrefixLength());
			String[] split = hostAddress.split("[.]");
			for (int i=1; i <= 255; i++){
				String target = split[0]+"."+split[1]+"."+split[2]+"."+i;
				if (checkTarget(target)) return;
				updateProgressBar(pos);
				pos++;
			}
		}

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
		try {
			if (InetAddress.getByName(target).isReachable(100)){
				if (checkZEngine(target)){
					saveAddress(target);
					return true;
				}
			}
		} catch (IOException e) {
		}
		return false;
	}

	private void saveAddress(String target) {

	}

	private boolean checkZEngine(String target) {
		Log.d(TAG, "Check if " + target + " is a DomusEngine");
		return false;
	}
}
