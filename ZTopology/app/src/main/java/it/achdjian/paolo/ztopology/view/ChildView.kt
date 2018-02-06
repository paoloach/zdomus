package it.achdjian.paolo.ztopology.view

import android.graphics.*
import it.achdjian.paolo.ztopology.LogicalType
import it.achdjian.paolo.ztopology.zigbee.DeviceConnectionStatus
import it.achdjian.paolo.ztopology.zigbee.Topology

/**
 * Created by Paolo Achdjian on 1/22/18.
 */
class ChildView(private val center: PointF, networkId: Int, private val status: Topology) {
    companion object {
        const val TAG = "TopologyView"
        const val COORDINATOR_RADIOUS=70f
        const val ROUTER_RADIOUS=50f
        const val END_DEVICE_RADIOUS=30f
        val deviceBorderConnected = Paint(Paint.ANTI_ALIAS_FLAG)
        val deviceWaitConnection = Paint(Paint.ANTI_ALIAS_FLAG)
        val deviceWaitInfo = Paint(Paint.ANTI_ALIAS_FLAG)
        val deviceId = Paint(Paint.ANTI_ALIAS_FLAG)
        val deviceLine = Paint(Paint.ANTI_ALIAS_FLAG)
        val deviceDisconnect = Paint(Paint.ANTI_ALIAS_FLAG)

        init {
            deviceBorderConnected.color = Color.GREEN
            deviceBorderConnected.style = Paint.Style.STROKE
            deviceBorderConnected.strokeWidth=2f
            deviceWaitConnection.color = Color.LTGRAY
            deviceWaitConnection.style = Paint.Style.FILL_AND_STROKE
            deviceWaitConnection.strokeWidth=0f

            deviceWaitInfo.color = Color.LTGRAY
            deviceWaitInfo.style = Paint.Style.FILL_AND_STROKE
            deviceWaitInfo.strokeWidth=0f

            deviceLine.color = Color.BLACK
            deviceLine.style = Paint.Style.STROKE
            deviceId.color = Color.BLACK
            deviceId.textSize = 20f
            deviceDisconnect.color = Color.RED
            deviceDisconnect.strokeWidth=2f
            deviceDisconnect.style = Paint.Style.FILL_AND_STROKE
        }
    }


    val id = networkId.toString(16)
    val children = ArrayList<ChildView>()
    private val leftText: Float
    private val topText: Float
    private val region: RectF
    private val radius: Float

    init {
        val rect = Rect()
        deviceId.getTextBounds(id, 0, id.length, rect)
        leftText = center.x - rect.width() / 2
        topText = center.y + rect.height() / 2
        when(status.logicalType) {
            LogicalType.ZigbeeEnddevice -> radius = END_DEVICE_RADIOUS
            LogicalType.ZigbeeCordinator -> radius = COORDINATOR_RADIOUS
            LogicalType.ZigbeeRouter -> radius = ROUTER_RADIOUS
            LogicalType.Invalid -> radius = END_DEVICE_RADIOUS
        }
        region = createRegion(radius)
    }

    fun paint(canvas: Canvas) {

        children.forEach {
            canvas.drawLine(center.x, center.y, it.center.x, it.center.y, deviceLine)
            it.paint(canvas)
        }
        when(status.connectionStatus){
            DeviceConnectionStatus.WAITING ->
                canvas.drawCircle(center.x, center.y, radius, deviceWaitConnection)
            DeviceConnectionStatus.CONNECTED ->
                if (status.logicalType == LogicalType.Invalid)
                    canvas.drawCircle(center.x, center.y, radius, deviceWaitInfo)
                else
                    canvas.drawCircle(center.x, center.y, radius, deviceBorderConnected)
            DeviceConnectionStatus.DISCONNECTED ->
                canvas.drawCircle(center.x, center.y, radius, deviceDisconnect)
        }
        canvas.drawText(id, leftText, topText, deviceId)
    }

    fun find(x: Float, y: Float): ChildView? {
        if (region.contains(x, y)) {
            return this
        }
        return children.map { it.find(x, y) }.firstOrNull { it != null }
    }

    fun createRegion(radious: Float): RectF = RectF(center.x - radious, center.y - radious, center.x + radious, center.y + radious)
}