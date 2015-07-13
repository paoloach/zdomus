package it.achdjian.domusviewer.View3D;

import android.view.View;

import com.badlogic.gdx.graphics.PerspectiveCamera;

import it.achdjian.domusviewer.R;

/**
 * Created by Paolo Achdjian on 11/07/15.
 * Copyright Paolo Achdjian
 */
public class UpDownCamera implements View.OnClickListener {
	private DomusGDXListener gdxListener;

	public UpDownCamera(DomusGDXListener gdxListener) {

		this.gdxListener = gdxListener;
	}

	@Override
	public void onClick(View view) {
		PerspectiveCamera camera = gdxListener.getCamera();
		if (camera != null) {
			switch (view.getId()) {
				case R.id.upButton:
					camera.position.add(0,0.1f,0);
					break;
				case R.id.downButton:
					camera.position.add(0,-0.1f,0);
					break;
			}
		}
	}
}
