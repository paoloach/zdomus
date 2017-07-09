package it.achdjian.paolo.temperaturemonitor.rajawali

import android.content.Context
import android.opengl.GLSurfaceView
import android.util.Log
import android.view.MotionEvent
import android.view.View
import org.rajawali3d.view.ISurface
import org.rajawali3d.view.SurfaceView

/**
 * Created by Paolo Achdjian on 7/6/17.
 */
class TemperatureSurface (context: Context, val render: TemperatureRender ) : SurfaceView(context) {
    init {
        setFrameRate(10.0)
        renderMode = ISurface.RENDERMODE_WHEN_DIRTY
        debugFlags = GLSurfaceView.DEBUG_CHECK_GL_ERROR or GLSurfaceView.DEBUG_LOG_GL_CALLS
        isClickable = true
        setSurfaceRenderer(render)
    }

    override fun onSizeChanged(w: Int, h: Int, oldw: Int, oldh: Int) {
     //   onPause()
    }

    override fun performClick(): Boolean {
        return false
    }

    override fun onTouchEvent(event: MotionEvent): Boolean {
        val result = super.onTouchEvent(event)
        if (event.action == MotionEvent.ACTION_DOWN) {
            render.getObjectAt(event.x, event.y)
        }
        return result
    }

}