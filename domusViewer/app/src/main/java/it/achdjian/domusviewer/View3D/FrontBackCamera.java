package it.achdjian.domusviewer.View3D;

import android.support.annotation.NonNull;

import com.badlogic.gdx.graphics.PerspectiveCamera;

import it.achdjian.domusviewer.customew.view.buttondouble.SlideOperator;

/**
 * Created by Paolo Achdjian on 11/07/15.
 * Copyright Paolo Achdjian
 */
public class FrontBackCamera  implements  SlideOperator{
	private static final float STEP = 0.1f;
	private final DomusGDXListener gdxListener;

	public FrontBackCamera(@NonNull DomusGDXListener gdxListener) {
		this.gdxListener = gdxListener;
	}


	private void update(@NonNull PerspectiveCamera camera, float step) {
		float rapport = camera.direction.x/camera.direction.z;
		float r2 = rapport*rapport;
		float dx = step/(1+r2);
		float dz = step/(1+1/r2);
		camera.position.add(dx,0,dz);
		camera.update();
	}

	@Override
	public void operatorInc() {
		PerspectiveCamera camera = gdxListener.getCamera();
		if (camera != null) {
			update(camera, STEP);
		}
	}

	@Override
	public void operatorDec() {
		PerspectiveCamera camera = gdxListener.getCamera();
		if (camera != null) {
			update(camera, -STEP);
		}
	}
}
