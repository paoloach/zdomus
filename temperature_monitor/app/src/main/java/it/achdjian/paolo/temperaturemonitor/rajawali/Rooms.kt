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
    val rooms = ArrayList<ArrayList<RoomObject>>()
    val planes = ArrayList<List<String>>()
    var isInit = false
    var planeSelected = 0;

    fun getSelected(): RoomObject? {
        rooms.get(planeSelected).forEach({ if (it.selected) return it })
        return null
    }

    fun selectRoom(name: String) {
        rooms.get(planeSelected).forEach({
            if (it.name == name)
                it.select()
            else
                it.deselect()
        })
    }

    fun initRooms() {
        Log.i("INIT", "init rooms")
        val plane0 = listOf("Taverna", "Scale_taverna", "Sottoscala", "Ingresso-Garage", "Lavanderia")
        val plane1 = listOf("Soggiorno", "bagno-terra", "Cucina", "scale_camere", "Termostato")
        planes.add(plane0)
        planes.add(plane1)

        rooms.add(ArrayList());
        rooms.add(ArrayList());

        val objParser = LoaderOBJ(context.resources, TextureManager.getInstance(), R.raw.casa_obj)
        try {
            objParser.parse()
            val mObjectGroup = objParser.parsedObject
            Log.d("INIT", "num objects: " + mObjectGroup.numChildren)
            for (i in 0..mObjectGroup.numChildren - 1) {
                val child = mObjectGroup.getChildAt(i)
                Log.i("DESIGN", "object name: " + child.name)
                if (isPlan0(child.name)) {
                    val room = RoomObject(child, cache)
                    Log.i("INIT", child.name)
                    rooms.get(0).add(room)
                }
                if (isPlan1(child.name)) {
                    val room = RoomObject(child, cache)
                    Log.i("INIT", child.name)
                    rooms.get(1).add(room)
                }
            }
        } catch (e: ParsingException) {
            e.printStackTrace()
        }
        isInit = true
    }

    private fun isPlan0(name: String): Boolean {
        planes[0].forEach { if (it.length <= name.length && it == name.substring(0, it.length)) return true }
        return false
    }

    private fun isPlan1(name: String): Boolean {
        planes[1].forEach { if (it.length <= name.length && it == name.substring(0, it.length)) return true }
        return false
    }

    fun initScene(currentScene: Scene, picker: ObjectColorPicker) = rooms.forEach({ it.forEach({ it.init3D(currentScene, picker) }) })

    fun enable() = rooms[planeSelected].forEach({ it.enable() })
    fun disable() = rooms[planeSelected].forEach({ it.disable() })

    fun getRoom(room: String): RoomObject? {
        rooms.get(planeSelected).forEach({ if (it.name == room) return it })
        return null
    }

    fun getMin(): Vector3 {
        val min = Vector3(Integer.MAX_VALUE.toDouble(), Integer.MAX_VALUE.toDouble(), Integer.MAX_VALUE.toDouble())

        rooms[planeSelected].forEach({
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
        rooms[planeSelected].forEach({
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
        rooms.get(planeSelected).forEach {
            if (it.object3D == objFound) {
                if (!it.selected)
                    select(it)
                else
                    it.deselect()
            }
        }
    }

    private fun select(toSelect: RoomObject) {
        rooms.get(planeSelected).forEach({ if (it == toSelect) it.select() else it.deselect() })
    }
}
