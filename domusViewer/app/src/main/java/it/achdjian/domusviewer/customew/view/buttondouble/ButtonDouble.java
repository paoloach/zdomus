package it.achdjian.domusviewer.customew.view.buttondouble;

import android.content.Context;
import android.content.res.TypedArray;
import android.graphics.Canvas;
import android.util.AttributeSet;
import android.util.Log;
import android.view.View;
import android.widget.Button;
import android.widget.LinearLayout;
import android.widget.TextView;

import it.achdjian.domusviewer.R;

/**
 * Created by Paolo Achdjian on 13/07/15.
 * Copyright Paolo Achdjian
 */
public class ButtonDouble extends LinearLayout implements View.OnClickListener, View.OnLongClickListener, Runnable {
	private final static String TAG = ButtonDouble.class.getName();
	private static final long REPEAT_DELAY = 50;
	private String textInc;
	private String textDec;
	private boolean value;
	private Button buttonInc;
	private Button buttonDec;
	private TextView textView;
	private View continuosClicked = null;
	private SlideOperator slideOperator;

	public ButtonDouble(Context context) {
		super(context);
		this.slideOperator = slideOperator;
	}

	public ButtonDouble(Context context, AttributeSet attrs) {
		super(context, attrs);
		init(attrs);
	}

	public ButtonDouble(Context context, AttributeSet attrs, int defStyleAttr) {
		super(context, attrs, defStyleAttr);
		init(attrs);
	}

	public void setOnSlideOperator(SlideOperator slideOperator) {
		this.slideOperator = slideOperator;
	}

	private void init(AttributeSet attrs) {
		TypedArray a = getContext().obtainStyledAttributes(attrs, R.styleable.ButtonDouble);

		textInc = a.getString(R.styleable.ButtonDouble_textInc);
		textDec = a.getString(R.styleable.ButtonDouble_textDec);
		value = a.getBoolean(R.styleable.ButtonDouble_value, false);

		a.recycle();

		setOrientation(HORIZONTAL);

		buttonInc = new Button(getContext(), attrs);
		buttonDec = new Button(getContext(), attrs);
		if (value) {
			textView = new TextView(getContext(), attrs);

			addView(textView);
		}
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

		if (value) {
			if (slideOperator != null) {
				textView.setText(slideOperator.getText());
				textView.setGravity(0x10 | 0x05);
			} else {
				textView.setText("10");
				textView.setGravity(0x10 | 0x05);
			}
		}
	}

	@Override
	protected void onLayout(boolean changed, int left, int top, int right, int bottom) {
		int height = bottom - top;
		if (!value) {
			int width = right - left;
			buttonInc.layout(left, 0, left + width / 2, height);
			buttonDec.layout(left + width / 2, 0, right, height);
		} else {
			int tvWidth = textView.getWidth();
			if (tvWidth == 0) {
				tvWidth = (right - left) / 3;
			}
			int width = (right - left) - tvWidth;
			int a = left + width / 2;
			int b = a + tvWidth;
			int c = b + width / 2;

			buttonInc.layout(left, 0, a, height);
			textView.layout(a, 0, b, height);
			buttonDec.layout(b, 0, right, height);

		}
	}

	@Override
	protected void onDraw(Canvas canvas) {
		super.onDraw(canvas);
	}


	@Override
	public void onClick(View v) {
		if (continuosClicked == v) {
			continuosClicked = null;
		}
		Log.d(TAG, "click");
		callSlideOperator(v);
	}

	private void callSlideOperator(View v) {
		if (slideOperator != null) {
			if (v == buttonDec) {
				slideOperator.operatorDec();
			} else if (v == buttonInc) {
				slideOperator.operatorInc();
			}
			if (value) {
				textView.setGravity(0x10 | 0x05);
				textView.setText(slideOperator.getText());
			}
		}
	}

	@Override
	public boolean onLongClick(View v) {
		Log.d(TAG, "long click");
		continuosClicked = v;
		postDelayed(this, REPEAT_DELAY);
		callSlideOperator(v);
		return false;
	}

	@Override
	public void run() {
		if (continuosClicked != null) {
			Log.d(TAG, "continuos click");
			callSlideOperator(continuosClicked);
			postDelayed(this, REPEAT_DELAY);
		}
	}
}
