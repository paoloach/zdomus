package it.achdjian.domusviewer.View3D;

import android.widget.TextView;

import com.badlogic.gdx.math.Vector3;

/**
 * Created by Paolo Achdjian on 09/07/15.
 * Copyright Paolo Achdjian
 */
public class PositionUpdate implements Runnable {
	private TextView text;
	private DomusGDXListener domusGDXListener;


	public PositionUpdate(TextView text, DomusGDXListener domusGDXListener) {
		this.text = text;
		this.domusGDXListener = domusGDXListener;
		text.postDelayed(this, 1000);
	}

	@Override
	public void run() {
		Vector3 vectorDirection = domusGDXListener.getPosition();
		String format = String.format("%1$5.3f,%2$5.3f,%3$5.3f", vectorDirection.x, vectorDirection.y, vectorDirection.z);
		text.setText("Position: " + format);
		text.postDelayed(this, 1000);
	}
}
