package it.achdjian.domusviewer.View3D;

import android.view.View;
import android.widget.TextView;

import com.badlogic.gdx.graphics.PerspectiveCamera;
import com.badlogic.gdx.math.Vector3;

import it.achdjian.domusviewer.R;

/**
 * Created by Paolo Achdjian on 10/07/15.
 * Copyright Paolo Achdjian
 */
public class RotateTargetCamera implements View.OnClickListener {
	private int angle=0;
	private TextView textAngle;
	private DomusGDXListener domusGDXListener;

	public RotateTargetCamera(DomusGDXListener gdxListener,TextView textAngle) {
		domusGDXListener = gdxListener;
		this.textAngle = textAngle;
	}

	@Override
	public void onClick(View view) {
		switch (view.getId()){
			case R.id.leftRotate:
				angle++;
				rotate();
				break;
			case R.id.rightRotate:
				angle--;
				rotate();
				break;
		}
	}

	private void rotate() {
		if (angle < 0){
			angle = 360-angle;
		}
		if (angle > 360){
			angle = angle-360;
		}
		PerspectiveCamera camera = domusGDXListener.getCamera();
		if (camera != null) {
			camera.direction.set(Vector3.X);
			camera.direction.rotate(Vector3.Y, angle);
			textAngle.setText(Integer.toString(angle));
		}
	}

	public void setAngle(int angle){
		this.angle = angle;
		rotate();
	}
}
