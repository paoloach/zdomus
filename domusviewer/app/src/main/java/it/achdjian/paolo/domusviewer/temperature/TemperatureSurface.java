package it.achdjian.paolo.domusviewer.temperature;

import android.content.Context;
import android.view.MotionEvent;

import org.rajawali3d.view.ISurface;
import org.rajawali3d.view.SurfaceView;

/**
 * Created by Paolo Achdjian on 20/04/17.
 */

public class TemperatureSurface extends SurfaceView {
    private final TemperatureRender render;

    public TemperatureSurface(Context context, TemperatureRender render) {
        super(context);
        this.render = render;
        setFrameRate(10.0);
        setRenderMode(ISurface.RENDERMODE_WHEN_DIRTY);
        setDebugFlags(DEBUG_CHECK_GL_ERROR |    DEBUG_LOG_GL_CALLS);
        setClickable(true);
        setSurfaceRenderer(render);
    }

    @Override
    protected void onSizeChanged (int w, int h, int oldw, int oldh){
        onPause();
    }

    @Override
    public boolean performClick(){
        return false;
    }

    @Override
    public boolean onTouchEvent(MotionEvent event) {
        boolean result = super.onTouchEvent(event);
        if (event.getAction() == MotionEvent.ACTION_DOWN) {
            render.getObjectAt(event.getX(), event.getY());
        }
        return result;
    }
}
