package it.achdjian.paolo.temperaturemonitor.rajawali

import android.content.Context
import android.os.Handler
import android.util.Log
import it.achdjian.paolo.temperaturemonitor.MainActivity
import it.achdjian.paolo.temperaturemonitor.R
import it.achdjian.paolo.temperaturemonitor.TempSensorLocationDS
import it.achdjian.paolo.temperaturemonitor.TemperatureCache
import it.achdjian.paolo.temperaturemonitor.dagger.ForApplication
import org.rajawali3d.Object3D
import org.rajawali3d.loader.LoaderOBJ
import org.rajawali3d.loader.ParsingException
import org.rajawali3d.materials.textures.TextureManager
import org.rajawali3d.math.vector.Vector3
import org.rajawali3d.scene.Scene
import org.rajawali3d.util.ObjectColorPicker
import org.rajawali3d.util.OnObjectPickedListener
import javax.inject.Inject
import javax.inject.Singleton

/**
 * Created by Paolo Achdjian on 7/5/17.
 */
@Singleton
class Rooms @Inject constructor(
        @ForApplication val context: Context,
        private val planes: Planes,
        private val cache: TemperatureCache,
        private val dataSource: TempSensorLocationDS) : OnObjectPickedListener {
    var isInit = false
    lateinit var mainActivity: MainActivity
    private val mainHandler = Handler()
    val selected: RoomObject? get() = planes.selected.firstOrNull { it.selected }


    fun selectRoom(name: String) = planes.selected.firstOrNull { it.name == name }?.select()

    fun initRooms() {
        Log.i("INIT", "init rooms")

        val objParser = LoaderOBJ(context.resources, TextureManager.getInstance(), R.raw.casa_obj)
        try {
            objParser.parse()
            val mObjectGroup = objParser.parsedObject
            Log.d("INIT", "num objects: " + mObjectGroup.numChildren)
            for (i in 0..mObjectGroup.numChildren - 1) {
                val child = mObjectGroup.getChildAt(i)
                Log.i("DESIGN", "object name: " + child.name)
                planes.add(RoomObject(child, cache, context, dataSource))
            }
        } catch (e: ParsingException) {
            e.printStackTrace()
        }
        isInit = true
    }


    fun initScene(currentScene: Scene, picker: ObjectColorPicker) {
        planes.getPlane(0).forEach({ it.init3D(currentScene, picker) })
        planes.getPlane(1).forEach({ it.init3D(currentScene, picker) })
    }

    fun enable() = planes.selected.forEach({ it.enable() })
    fun disable() = planes.selected.forEach({ it.disable() })

    fun getMin(): Vector3 {
        val min = Vector3(Integer.MAX_VALUE.toDouble(), Integer.MAX_VALUE.toDouble(), Integer.MAX_VALUE.toDouble())

        planes.selected.forEach({
            val boundingBox = it.object3D.geometry.boundingBox
            val childMin = boundingBox.min

            min.x = Math.min(min.x, childMin.x)
            min.y = Math.min(min.y, childMin.y)
            min.z = Math.min(min.z, childMin.z)
        })
        return min
    }

    fun getMax(): Vector3 {
        val max = Vector3(Integer.MIN_VALUE.toDouble(), Integer.MIN_VALUE.toDouble(), Integer.MIN_VALUE.toDouble())
        planes.selected.forEach({
            val boundingBox = it.object3D.geometry.boundingBox
            val childMax = boundingBox.max
            max.x = Math.max(max.x, childMax.x)
            max.y = Math.max(max.y, childMax.y)
            max.z = Math.max(max.z, childMax.z)
        })

        return max
    }

    /**
     * Called when no object was detected during picking.
     */
    override fun onNoObjectPicked() {
    }

    override fun onObjectPicked(objFound: Object3D) {
        val temp = planes.selected.firstOrNull({ it.isTemperatureLabel(objFound) })
        temp?.displayGraphics(mainActivity)
        val room = planes.selected.firstOrNull({ it.object3D == objFound })
        room?.invertSelection()
    }

    fun removeLabel(room: String) = planes.getRoom(room)?.removeLabels()
    fun initRoom(room: String) {
        val roomObject = planes.getRoom(room)
        roomObject?.initLabels()
        roomObject?.updateTemp()
    }
}
