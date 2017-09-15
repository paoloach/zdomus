package it.achdjian.paolo.temperaturemonitor.rajawali

import android.content.Context
import android.util.Log
import it.achdjian.paolo.temperaturemonitor.R
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
class Rooms @Inject constructor(@ForApplication val context: Context, val cache: TemperatureCache) : OnObjectPickedListener {
    val rooms = ArrayList<RoomObject>()
    val planes = ArrayList<List<String>>()
    var isInit = false

    fun getSelected(): RoomObject? {
        rooms.forEach({ if (it.selected) return it })
        return null
    }

    fun selectRoom(name: String) {
        rooms.forEach({
            if (it.name == name)
                it.select()
            else
                it.deselect()
        })
    }

    fun initRooms() {
        Log.i("INIT","init rooms")
        val plane0 = listOf("Taverna", "Scale_taverna", "Sottoscala", "Ingresso-Garage", "Lavanderia")
        planes.add(plane0)

        val objParser = LoaderOBJ(context.resources, TextureManager.getInstance(), R.raw.casa_obj)
        try {
            objParser.parse()
            val mObjectGroup = objParser.parsedObject
            Log.d("INIT", "num objects: " + mObjectGroup.numChildren)
            for (i in 0..mObjectGroup.numChildren - 1) {
                val child = mObjectGroup.getChildAt(i)
                if (isPlan0(child.name)) {
                    val room = RoomObject(child, cache)
                    Log.i("INIT", child.name)
                    rooms.add(room)
                }
            }
        } catch (e: ParsingException) {
            e.printStackTrace()
        }
        isInit=true
    }

    private fun isPlan0(name: String): Boolean {
        planes[0].forEach { if (it.length <= name.length && it == name.substring(0, it.length)) return true }
        return false
    }

    fun initScene(currentScene: Scene, picker: ObjectColorPicker) = rooms.forEach({ it.init3D(currentScene, picker) })

    fun getRoom(room: String): RoomObject? {
        rooms.forEach({ if (it.name == room) return it })
        return null
    }

    fun getMin(planeIndex: Int): Vector3 {
        if (planeIndex < 0 || planeIndex >= planes.size) {
            throw RuntimeException("Plane index out of range: " + planeIndex)
        }

        val planeRooms = planes[planeIndex]
        val min = Vector3(Integer.MAX_VALUE.toDouble(), Integer.MAX_VALUE.toDouble(), Integer.MAX_VALUE.toDouble())

        for (roomName in planeRooms) {
            val room = getRoom(roomName)

            if (room != null) {
                val boundingBox = room.object3D.geometry.boundingBox
                val childMin = boundingBox.min

                min.x = Math.min(min.x, childMin.x)
                min.y = Math.min(min.y, childMin.y)
                min.z = Math.min(min.z, childMin.z)
            }
        }
        return min
    }

    fun getMax(planeIndex: Int): Vector3 {
        if (planeIndex < 0 || planeIndex >= planes.size) {
            throw RuntimeException("Plane index out of range: " + planeIndex)
        }

        val planeRooms = planes[planeIndex]
        val max = Vector3(Integer.MIN_VALUE.toDouble(), Integer.MIN_VALUE.toDouble(), Integer.MIN_VALUE.toDouble())

        for (roomName in planeRooms) {
            val room = getRoom(roomName)

            if (room != null) {
                val boundingBox = room.object3D.geometry.boundingBox
                val childMax = boundingBox.max
                max.x = Math.max(max.x, childMax.x)
                max.y = Math.max(max.y, childMax.y)
                max.z = Math.max(max.z, childMax.z)
            }
        }
        return max
    }

    /**
     * Called when no object was detected during picking.
     */
    override fun onNoObjectPicked() {
    }

    override fun onObjectPicked(objFound: Object3D) {
        rooms.forEach {
            if (it.object3D == objFound) {
                if (!it.selected)
                    select(it)
                else
                    it.deselect()
            }
        }
    }

    private fun select(toSelect: RoomObject) {
        rooms.forEach({ if (it == toSelect) it.select() else it.deselect() })
    }
}
