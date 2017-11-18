package it.achdjian.paolo.temperaturemonitor.graphic

import android.content.Context
import android.util.Log
import android.view.MotionEvent
import android.view.ScaleGestureDetector
import android.view.View
import it.achdjian.paolo.temperaturemonitor.domusEngine.DomusEngine
import org.joda.time.LocalDateTime

/**
 * Created by Paolo Achdjian on 11/14/17.
 */
class GraphViewScale(val networkAddress:Int, context: Context, val domusEngine: DomusEngine) : View.OnTouchListener, ScaleGestureDetector.OnScaleGestureListener {
    val scaleGestureDetector = ScaleGestureDetector(context, this)
    var startSpanX = 0.0f;
    var end = LocalDateTime()
    var start = end.minusDays(1)

    override fun onScaleBegin(detector: ScaleGestureDetector?): Boolean {
        if (detector != null)
            startSpanX = detector.currentSpanX;
        return true;
    }

    override fun onScaleEnd(detector: ScaleGestureDetector?) {
        if (detector != null) {
            val factor = detector.getCurrentSpanX() / startSpanX
            val period = (end.toDate().time - start.toDate().time)*factor
            val toNow = LocalDateTime().toDate().time - end.toDate().time
            if (toNow < period/2){
                end= LocalDateTime()
                start = end.minusMillis(period.toInt())
            } else {
                end = end.plusMillis((period/2).toInt())
                start = start.minusMillis((period/2).toInt())
            }
            domusEngine.getTemperatureData(networkAddress, start, end)
            Log.i("UI", "span: " + factor)
            Log.i("UI", "start: " + start + ", end: " + end)

        }
    }

    override fun onScale(detector: ScaleGestureDetector?): Boolean{
        if (detector != null) {
            Log.i("UI", "span: " + detector.getCurrentSpanX() / startSpanX)
        }
        return true;
    }

    override fun onTouch(v: View?, event: MotionEvent?): Boolean {
        return scaleGestureDetector.onTouchEvent(event);
    }
}