package it.achdjian.domusviewer.customew.view.button2;

import android.annotation.TargetApi;
import android.app.Activity;
import android.content.Context;
import android.content.res.Resources;
import android.content.res.TypedArray;
import android.graphics.Canvas;
import android.graphics.Paint;
import android.graphics.Rect;
import android.graphics.drawable.Drawable;
import android.graphics.drawable.StateListDrawable;
import android.os.Build;
import android.support.v7.widget.LinearLayoutCompat;
import android.util.AttributeSet;
import android.util.Log;
import android.util.TypedValue;
import android.view.MotionEvent;
import android.view.View;
import android.widget.Button;
import android.widget.LinearLayout;

import it.achdjian.domusviewer.R;

/**
 * Created by Paolo Achdjian on 13/07/15.
 * Copyright Paolo Achdjian
 */
public class Button2 extends LinearLayout implements View.OnClickListener, View.OnLongClickListener, Runnable{
	private final static String TAG = Button2.class.getName();
	private static final long REPEAT_DELAY = 400;
	private String textInc;
	private String textDec;
	private Button buttonInc;
	private Button buttonDec;
	private View continuosClicked=null;

	public Button2(Context context) {
		super(context);
	}

	public Button2(Context context, AttributeSet attrs) {
		super(context, attrs);
		init(attrs);
	}

	public Button2(Context context, AttributeSet attrs, int defStyleAttr) {
		super(context, attrs, defStyleAttr);
		init(attrs);
	}

	private void init(AttributeSet attrs){
		TypedArray a = getContext().obtainStyledAttributes(attrs, R.styleable.Button2);

		textInc = a.getString(R.styleable.Button2_textInc);
		textDec = a.getString(R.styleable.Button2_textDec);

		a.recycle();

		setOrientation(HORIZONTAL);

		buttonInc = new Button(getContext(),attrs);
		buttonDec = new Button(getContext(),attrs);
		buttonInc.setText(textInc);
		buttonDec.setText(textDec);
		addView(buttonInc);
		addView(buttonDec);

		buttonDec.setOnClickListener(this);
		buttonInc.setOnClickListener(this);

		buttonInc.setOnLongClickListener(this);
		buttonDec.setOnLongClickListener(this);

		buttonDec.setLongClickable(true);
		buttonInc.setLongClickable(true);
	}

	@Override
	protected void onLayout(boolean changed, int left, int top, int right, int bottom) {
		int width = right-left;
		buttonInc.layout(left,0, left+width/2, bottom-top);
		buttonDec.layout(left+width/2, 0, right, bottom-top);
	}

	@Override
	protected void onDraw(Canvas canvas) {
		super.onDraw(canvas);
	}


	@Override
	public void onClick(View v) {
		if (continuosClicked == v){
			continuosClicked = null;
		}
		Log.d(TAG, "click");
	}

	@Override
	public boolean onLongClick(View v) {
		Log.d(TAG, "long click");
		continuosClicked = v;
		postDelayed(this, REPEAT_DELAY);
		return false;
	}

	@Override
	public void run() {
		if (continuosClicked != null){
			Log.d(TAG,"continuos click");
			postDelayed(this, REPEAT_DELAY);
		}
	}
}
