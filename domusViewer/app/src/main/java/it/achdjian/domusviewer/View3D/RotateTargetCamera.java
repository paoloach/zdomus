package it.achdjian.domusviewer.View3D;

import android.support.annotation.NonNull;
import android.view.View;
import android.widget.TextView;

import com.badlogic.gdx.graphics.PerspectiveCamera;
import com.badlogic.gdx.math.Vector3;

import it.achdjian.domusviewer.R;
import it.achdjian.domusviewer.customew.view.buttondouble.SlideOperator;

/**
 * Created by Paolo Achdjian on 10/07/15.
 * Copyright Paolo Achdjian
 */
public class RotateTargetCamera implements SlideOperator {
	private int angle=0;
	private final DomusGDXListener domusGDXListener;

	public RotateTargetCamera(@NonNull DomusGDXListener gdxListener) {
		domusGDXListener = gdxListener;
	}

	public void setAngle(int angle){
		this.angle = angle;
		rotate();
	}

	@Override
	public void operatorInc() {
		angle++;
		if (angle>=360){
			angle=360-angle;
		}
		rotate();
	}

	@Override
	public void operatorDec() {
		angle--;
		if (angle < 0){
			angle = 360+angle;
		}
		rotate();
	}

	private void rotate() {
		PerspectiveCamera camera = domusGDXListener.getCamera();
		if (camera != null) {
			camera.direction.set(Vector3.X);
			camera.direction.rotate(Vector3.Y, angle);
		}
	}

	@Override
	public String getText() {
			return Integer.toString(angle);
	}
}
