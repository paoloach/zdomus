package it.achdjian.domusviewer.View3D;

import android.support.annotation.NonNull;
import android.view.View;

import com.badlogic.gdx.graphics.PerspectiveCamera;

import it.achdjian.domusviewer.R;

/**
 * Created by Paolo Achdjian on 11/07/15.
 * Copyright Paolo Achdjian
 */
public class FrontBackCamera  implements View.OnClickListener{
	private static final float STEP = 0.1f;
	private DomusGDXListener gdxListener;

	public FrontBackCamera(@NonNull DomusGDXListener gdxListener) {

		this.gdxListener = gdxListener;
	}

	@Override
	public void onClick(View view) {
		PerspectiveCamera camera = gdxListener.getCamera();
		if (camera != null){
			switch (view.getId()){
				case R.id.onButton:
					update(camera,STEP);
					break;
				case R.id.backButton:
					update(camera,-STEP);
					break;

			}
		}
	}

	private void update(@NonNull PerspectiveCamera camera, float step) {
		float rapport = camera.direction.x/camera.direction.z;
		float r2 = rapport*rapport;
		float dx = step/(1+r2);
		float dz = step/(1+1/r2);
		camera.position.add(dx,0,dz);
		camera.update();
	}
}
