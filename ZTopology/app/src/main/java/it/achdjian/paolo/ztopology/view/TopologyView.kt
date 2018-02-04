package it.achdjian.paolo.ztopology.view

import android.content.Context
import android.graphics.Bitmap
import android.graphics.BitmapFactory
import android.graphics.Canvas
import android.graphics.PointF
import android.graphics.drawable.Drawable
import android.support.graphics.drawable.VectorDrawableCompat
import android.util.AttributeSet
import android.util.Log
import android.view.MotionEvent
import android.view.View
import it.achdjian.paolo.ztopology.ChildrenCallback
import it.achdjian.paolo.ztopology.DomusEngine
import it.achdjian.paolo.ztopology.R
import it.achdjian.paolo.ztopology.rest.Children
import it.achdjian.paolo.ztopology.view.ChildView.Companion.deviceId
import it.achdjian.paolo.ztopology.zigbee.DeviceConnectionStatus
import it.achdjian.paolo.ztopology.zigbee.Topology
import it.achdjian.paolo.ztopology.zigbee.TopologyManager
import it.achdjian.paolo.ztopology.zigbee.TopologyUpdate
import kotlinx.android.synthetic.main.activity_main.*

class TopologyView : View, View.OnTouchListener, TopologyUpdate {


    private var devicesPos: ChildView? = null

    companion object {
        const val TAG = "TopologyView"
        var DISCONNECTED_DRAWABLE: VectorDrawableCompat? = null
    }
    constructor(context: Context) : super(context) {
    }

    constructor(context: Context, attrs: AttributeSet) : super(context, attrs) {
    }

    constructor(context: Context, attrs: AttributeSet, defStyle: Int) : super(context, attrs, defStyle) {
    }

    override fun onAttachedToWindow() {
        super.onAttachedToWindow()
        TopologyManager.addView(this)
        setOnTouchListener(this)
        DISCONNECTED_DRAWABLE = VectorDrawableCompat.create(resources, R.drawable.disconnected_chains, null)
    }

    override fun onDetachedFromWindow() {
        super.onDetachedFromWindow()
        TopologyManager.removeView(this)
    }

    override fun onDraw(canvas: Canvas) {
        super.onDraw(canvas)
        canvas.drawRGB(255, 255, 255)
        devicesPos?.paint(canvas)
    }

    override fun onSizeChanged(w: Int, h: Int, oldw: Int, oldh: Int) {
        super.onSizeChanged(w, h, oldw, oldh)
        calcPos()
    }

    override fun onTouch(v: View?, event: MotionEvent?): Boolean {
        Log.i(TAG, "event action: " + event?.actionMasked)
        if (event != null ){
            val found = devicesPos?.find(event.x, event.y)
            if (found != null) {
                if (event.actionMasked == MotionEvent.ACTION_UP) {
                    Log.i(TAG, "found UP" + found.id)
                }
                return true
            } else
                Log.i(TAG, "not found at " + event.x + ", " + event.y)
        }
        return false
    }

    override fun update() {
        calcPos()
        postInvalidate()
    }

    private fun calcPos() {
        val center0 = PointF((left + width / 2).toFloat(), (top + height / 2).toFloat())
        val newChildView = ChildView(center0, 0, deviceId, DeviceConnectionStatus.CONNECTED)
        Log.i(TAG, "center: " + center0.x + ", " + center0.y)
        TopologyManager.log()
        val deviceDistX = width / 4f
        val deviceDistY = height / 4f

        addDevicesNode(Topology.root, newChildView, center0, deviceDistX, deviceDistY)
        devicesPos = newChildView
    }

    private fun addDevicesNode(node: Topology, childiew: ChildView, center: PointF, deviceDistX: Float, deviceDistY: Float) {
        if (node.children.isNotEmpty()) {
            val deltaAngle = 2 * Math.PI / node.children.size
            var startAngle = 0.0
            node.children.forEach({
                val childPos = PointF((center.x + deviceDistX * Math.sin(startAngle)).toFloat(), (center.y + deviceDistY * Math.cos(startAngle)).toFloat())
                val child = ChildView(childPos, it.shortAddress, deviceId, it.connectionStatus)
                childiew.children.add(child)
                addDevicesNode(it, child, childPos, deviceDistX / 2, deviceDistY / 2)
                startAngle += deltaAngle
            })
        }
    }
}
