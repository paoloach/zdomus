package it.achdjian.paolo.ztopology.view

import android.content.Context
import android.graphics.Canvas
import android.graphics.PointF
import android.support.v4.view.GestureDetectorCompat
import android.util.AttributeSet
import android.util.Log
import android.view.GestureDetector
import android.view.MotionEvent
import android.view.View
import it.achdjian.paolo.ztopology.zigbee.Topology
import it.achdjian.paolo.ztopology.zigbee.TopologyManager
import it.achdjian.paolo.ztopology.zigbee.TopologyUpdate
import it.achdjian.paolo.ztopology.rest.Relationship.NeighborIsParent


class TopologyView : View, View.OnTouchListener, TopologyUpdate, GestureDetector.OnGestureListener {


    val gestureDetector = GestureDetectorCompat(context, this)
    private var devicesPos: ChildView? = null

    companion object {
        const val TAG = "TopologyView"
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
        gestureDetector.onTouchEvent(event)
        return true
    }

    override fun update() {
        calcPos()
        postInvalidate()
    }

    private fun calcPos() {
        val center0 = PointF((left + width / 2).toFloat(), (top + height / 2).toFloat())
        val newChildView = ChildView(center0, 0, Topology.root)
        Log.i(TAG, "center: " + center0.x + ", " + center0.y)
        TopologyManager.log()
        val deviceDistX = width / 4f
        val deviceDistY = height / 4f

        addDevicesNode(Topology.root, newChildView, center0, deviceDistX, deviceDistY, 0.0)
        devicesPos = newChildView
    }

    private fun addDevicesNode(node: Topology, childiew: ChildView, center: PointF, deviceDistX: Float, deviceDistY: Float, startAngle: Double) {

        val children = node.children.filter { it.relationship != NeighborIsParent }
        if (children.isNotEmpty()) {
            val deltaAngle: Double
            if (node.nwkAddress == 0)
                deltaAngle = 2 * Math.PI / children.size
            else
                deltaAngle = 2 * Math.PI / (children.size+1)
            var angle = startAngle+Math.PI+deltaAngle
            children.forEach({
                val childPos = PointF((center.x + deviceDistX * Math.sin(angle)).toFloat(), (center.y + deviceDistY * Math.cos(angle)).toFloat())
                val child = ChildView(childPos, it.nwkAddress, it)

                childiew.children.add(child)
                addDevicesNode(it, child, childPos, deviceDistX / 2, deviceDistY / 2, angle)
                angle += deltaAngle
            })
        }
    }

    /**
     * The user has performed a down [MotionEvent] and not performed
     * a move or up yet. This event is commonly used to provide visual
     * feedback to the user to let them know that their action has been
     * recognized i.e. highlight an element.
     *
     * @param e The down motion event
     */
    override fun onShowPress(e: MotionEvent?) {
    }

    /**
     * Notified when a tap occurs with the up [MotionEvent]
     * that triggered it.
     *
     * @param e The up motion event that completed the first tap
     * @return true if the event is consumed, else false
     */
    override fun onSingleTapUp(event: MotionEvent?): Boolean {
        Log.i(TAG, "tap action: " + event?.actionMasked)
        if (event != null ){
            val found = devicesPos?.find(event.x, event.y)
            if (found != null) {
                if (event.actionMasked == MotionEvent.ACTION_UP) {
                    Log.i(TAG, "found tap " + found.id)
                }
                return true
            } else
                Log.i(TAG, "not found at " + event.x + ", " + event.y)
        }
        return true;
    }

    /**
     * Notified when a tap occurs with the down [MotionEvent]
     * that triggered it. This will be triggered immediately for
     * every down event. All other events should be preceded by this.
     *
     * @param e The down motion event.
     */
    override fun onDown(e: MotionEvent?) = false

    /**
     * Notified of a fling event when it occurs with the initial on down [MotionEvent]
     * and the matching up [MotionEvent]. The calculated velocity is supplied along
     * the x and y axis in pixels per second.
     *
     * @param e1 The first down motion event that started the fling.
     * @param e2 The move motion event that triggered the current onFling.
     * @param velocityX The velocity of this fling measured in pixels per second
     * along the x axis.
     * @param velocityY The velocity of this fling measured in pixels per second
     * along the y axis.
     * @return true if the event is consumed, else false
     */
    override fun onFling( e1: MotionEvent?, e2: MotionEvent?, velocityX: Float, velocityY: Float) = false

    /**
     * Notified when a scroll occurs with the initial on down [MotionEvent] and the
     * current move [MotionEvent]. The distance in x and y is also supplied for
     * convenience.
     *
     * @param e1 The first down motion event that started the scrolling.
     * @param e2 The move motion event that triggered the current onScroll.
     * @param distanceX The distance along the X axis that has been scrolled since the last
     * call to onScroll. This is NOT the distance between `e1`
     * and `e2`.
     * @param distanceY The distance along the Y axis that has been scrolled since the last
     * call to onScroll. This is NOT the distance between `e1`
     * and `e2`.
     * @return true if the event is consumed, else false
     */
    override fun onScroll( e1: MotionEvent?, e2: MotionEvent?, distanceX: Float, distanceY: Float) = false

    /**
     * Notified when a long press occurs with the initial on down [MotionEvent]
     * that trigged it.
     *
     * @param e The initial on down motion event that started the longpress.
     */
    override fun onLongPress(event: MotionEvent?) {
        Log.i(TAG, "long press action: " + event?.actionMasked)
        if (event != null ){
            val found = devicesPos?.find(event.x, event.y)
            if (found != null) {
                if (event.actionMasked == MotionEvent.ACTION_UP) {
                    Log.i(TAG, "found long press " + found.id)
                }
            } else
                Log.i(TAG, "not found at " + event.x + ", " + event.y)
        }
    }
}
