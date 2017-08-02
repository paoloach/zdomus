package it.achdjian.paolo.temperaturemonitor.rajawali

import android.content.Context
import android.util.Log
import android.view.MotionEvent
import org.rajawali3d.math.vector.Vector3
import org.rajawali3d.renderer.Renderer
import org.rajawali3d.util.GLU
import org.rajawali3d.util.ObjectColorPicker
import javax.inject.Inject
import kotlin.coroutines.experimental.EmptyCoroutineContext.plus

/**
 * Created by Paolo Achdjian on 7/6/17.
 */
class TemperatureRender(context: Context,val rooms: Rooms) : Renderer(context) {
    private val TEMPERATURE_UPDATE = 5.0

    lateinit var picker: ObjectColorPicker
    private var roomToUpdate: RoomObject? = null
    private var width = 0
    private var height = 0
    private var time = 0.0
    private var nextTempUpdate = 0.0

    override fun onOffsetsChanged(xOffset: Float, yOffset: Float, xOffsetStep: Float, yOffsetStep: Float, xPixelOffset: Int, yPixelOffset: Int) {
    }

    override fun onTouchEvent(event: MotionEvent?) {
        Log.d(javaClass.name, "event: " + event!!.getX() + " , " + event.getY())
    }

    override fun initScene() {
        rooms.afterInject()
        picker = ObjectColorPicker(this)
        rooms.initScene(currentScene, picker = picker)

        val maxRooms = rooms.getMax(0)
        val minRooms = rooms.getMin(0)
        Log.d("RENDER", "max: $maxRooms, min: $minRooms")
        val camera = currentCamera
        val lookAt = Vector3(0.0, 0.0, minRooms.z)
        camera.lookAt = lookAt
        val cameraPos = Vector3((maxRooms.x + minRooms.x) / 2, (maxRooms.y + minRooms.y) / 2, maxRooms.z + 15)
        camera.position = cameraPos
        currentScene.switchCamera(camera)
        mSurface.requestRenderUpdate()
        adjustCamera()
        picker.setOnObjectPickedListener(rooms)
    }

    private fun adjustCamera() {
        val currentCamera = currentCamera
        var z = currentCamera.z
        val maxRooms = rooms.getMax(0)
        val minRooms = rooms.getMin(0)
        while (true) {
            val viewMatrix = currentCamera.viewMatrix
            val projectionMatrix = currentCamera.projectionMatrix

            val viewPort = intArrayOf(0, 0, viewportWidth, viewportHeight)
            val posMin = DoubleArray(4)
            val posMax = DoubleArray(4)
            GLU.gluProject(minRooms.x, minRooms.y, minRooms.z, viewMatrix.doubleValues, 0, projectionMatrix.doubleValues, 0, viewPort, 0, posMin, 0)

            GLU.gluProject(maxRooms.x, maxRooms.y, maxRooms.z, viewMatrix.doubleValues, 0, projectionMatrix.doubleValues, 0, viewPort, 0, posMax, 0)

            val widthObj = posMax[0] - posMin[0]
            val heightObj = posMax[1] - posMin[1]
            if (Math.abs(widthObj - width) < 1 && height > heightObj) {
                break
            }
            if (Math.abs(heightObj - height) < 1 && width > widthObj) {
                break
            }
            if (widthObj > width) {
                z += 0.01
            } else {
                z -= 0.01
            }
            currentCamera.z = z
        }
    }

    fun onSurfaceViewLayoutChange(left: Int, top: Int, right: Int, bottom: Int) {
        width = right - left
        height = bottom - top
    }

    override fun onRender(elapsedTime: Long, deltaTime: Double) {
        time += deltaTime
        if (time > nextTempUpdate) {
            nextTempUpdate += TEMPERATURE_UPDATE
            for (room in rooms.rooms) {
                room.updateTemp()

            }
        } else {
            roomToUpdate?.updateTemp()
            roomToUpdate = null
        }

        super.onRender(elapsedTime, deltaTime)
    }

    fun getObjectAt(x: Float, y: Float) = picker.getObjectAt(x, y)
    fun notifyFirstTemperature(room: String) {
        roomToUpdate = rooms.getRoom(room)
        if (roomToUpdate != null) {
            //temperatures.invalidate(roomToUpdate.name)
        }
    }

}