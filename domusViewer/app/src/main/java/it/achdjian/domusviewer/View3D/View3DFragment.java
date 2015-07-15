package it.achdjian.domusviewer.View3D;

import android.content.res.AssetManager;
import android.os.Bundle;
import android.support.annotation.NonNull;
import android.util.Log;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.FrameLayout;
import android.widget.LinearLayout;
import android.widget.TextView;

import com.badlogic.gdx.backends.android.AndroidApplicationConfiguration;
import com.badlogic.gdx.backends.android.AndroidFragmentApplication;
import com.badlogic.gdx.math.Vector3;

import java.io.IOException;
import java.io.InputStream;

import it.achdjian.domusviewer.R;

/**
 * Created by Paolo Achdjian on 04/07/15.
 * Copyright Paolo Achdjian
 */
public class View3DFragment extends AndroidFragmentApplication implements NotifyCreation {
	private DomusGDXListener gdxListener;
	private Vector3 startingTarget = new Vector3(0,0,0);
	private DirectionUpdate directionUpdate;
	private PositionUpdate positionUpdate;
	private RotateTargetCamera rotateTargetCamera;
	private UpDownCamera upDownCamera;
	private FrontBackCamera frontBackCamera;

	public View3DFragment() {
	}

	@Override
	public View onCreateView(LayoutInflater inflater, ViewGroup container, Bundle savedInstanceState) {
		setLogLevel(LOG_DEBUG);
		AssetManager assets = getContext().getAssets();

		try {
			InputStream stream = assets.open("PianoTerra2.g3db");
			Log.d(View3DFragment.class.getName(), stream.toString());
		} catch (IOException e) {
			e.printStackTrace();
		}

		super.onCreateView(inflater, container, savedInstanceState);
		AndroidApplicationConfiguration config = getGDXConfiguration();
		LinearLayout parentLayout = (LinearLayout) inflater.inflate(R.layout.fragment_3d, container, false);
		TextView textArc = (TextView)parentLayout.findViewById(R.id.angle);


		gdxListener = new DomusGDXListener(startingTarget, this);
		rotateTargetCamera = new RotateTargetCamera(gdxListener, textArc);
		upDownCamera = new UpDownCamera(gdxListener);
		frontBackCamera = new FrontBackCamera(gdxListener);
		parentLayout.findViewById(R.id.leftRotate).setOnClickListener(rotateTargetCamera);
		parentLayout.findViewById(R.id.rightRotate).setOnClickListener(rotateTargetCamera);
		parentLayout.findViewById(R.id.upButton).setOnClickListener(upDownCamera);
		parentLayout.findViewById(R.id.downButton).setOnClickListener(upDownCamera);
		parentLayout.findViewById(R.id.onButton).setOnClickListener(frontBackCamera);
		parentLayout.findViewById(R.id.backButton).setOnClickListener(frontBackCamera);


		directionUpdate = new DirectionUpdate((TextView) parentLayout.findViewById(R.id.direction), gdxListener);
		positionUpdate = new PositionUpdate((TextView) parentLayout.findViewById(R.id.position), gdxListener);

		FrameLayout layout3D = (FrameLayout) parentLayout.findViewById(R.id.layout3D);
		View view = initializeForView(gdxListener, config);
		layout3D.addView(view);

		return parentLayout;
	}



	@NonNull
	private AndroidApplicationConfiguration getGDXConfiguration() {
		AndroidApplicationConfiguration configuration = new AndroidApplicationConfiguration();
		configuration.useAccelerometer = false;
		configuration.useCompass = false;
		configuration.disableAudio=true;
		configuration.useGLSurfaceView20API18=false;

		return  configuration;
	}

	@Override
	public void create() {
		getActivity().runOnUiThread(new Runnable() {
			@Override
			public void run() {
				rotateTargetCamera.setAngle(135);
			}
		});
	}
}
