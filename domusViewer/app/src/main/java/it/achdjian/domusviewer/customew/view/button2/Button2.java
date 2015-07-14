package it.achdjian.domusviewer.customew.view.button2;

import android.content.Context;
import android.graphics.Canvas;
import android.graphics.Paint;
import android.util.AttributeSet;
import android.util.Log;
import android.view.View;

/**
 * Created by Paolo Achdjian on 13/07/15.
 * Copyright Paolo Achdjian
 */
public class Button2 extends View {
	private final static String TAG = Button2.class.getName();

	public Button2(Context context) {
		super(context);
	}

	public Button2(Context context, AttributeSet attrs) {
		super(context, attrs);
	}

	public Button2(Context context, AttributeSet attrs, int defStyleAttr) {
		super(context, attrs, defStyleAttr);
	}

	@Override
	public void onDraw(Canvas canvas) {
		int width = getWidth();
		int height = getHeight();
		Paint paint = new Paint();
		paint.setColor(0);
		canvas.drawLine(0, 0, width, height, paint);
		Log.d(TAG,"with = " + width + ", height=" + height);
	}

	@Override
	public void onMeasure(int widthMeasureSpec, int heightMeasureSpec) {
		super.onMeasure(widthMeasureSpec, heightMeasureSpec);
	}
}
