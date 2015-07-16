package it.achdjian.domusviewer.View3D;

import android.support.annotation.NonNull;

import com.badlogic.gdx.graphics.PerspectiveCamera;

import it.achdjian.domusviewer.customew.view.buttondouble.SlideOperator;

/**
 * Created by Paolo Achdjian on 11/07/15.
 * Copyright Paolo Achdjian
 */
public class UpDownCamera implements SlideOperator {
	private final DomusGDXListener gdxListener;

	public UpDownCamera(@NonNull DomusGDXListener gdxListener) {
		this.gdxListener = gdxListener;
	}


	@Override
	public void operatorInc() {
		PerspectiveCamera camera = gdxListener.getCamera();
		if (camera != null){
			camera.position.add(0,0.1f, 0);
		}
	}

	@Override
	public void operatorDec() {
		PerspectiveCamera camera = gdxListener.getCamera();
		if (camera != null){
			camera.position.add(0,-0.1f, 0);
		}

	}
}
