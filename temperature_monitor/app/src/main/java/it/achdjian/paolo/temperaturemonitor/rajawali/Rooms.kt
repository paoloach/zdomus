package it.achdjian.paolo.temperaturemonitor.rajawali

import android.content.Context
import android.util.Log
import it.achdjian.paolo.temperaturemonitor.R
import org.rajawali3d.loader.LoaderOBJ
import org.rajawali3d.loader.ParsingException
import org.rajawali3d.materials.textures.TextureManager
import org.rajawali3d.math.vector.Vector3
import org.rajawali3d.scene.Scene
import org.rajawali3d.util.ObjectColorPicker

/**
 * Created by Paolo Achdjian on 7/5/17.
 */
class Rooms(val context: Context) {

    val rooms = ArrayList<RoomObject>()
    val planes = ArrayList<List<String>>()

    fun afterInject(){
        val plane0 = listOf("Taverna", "Scale_taverna","Sottoscala","Ingresso-Garage","Lavanderia" )
        planes.add(plane0)

        val objParser = LoaderOBJ(context.getResources(), TextureManager.getInstance(), R.raw.pianoterra2_obj)
        try {
            objParser.parse()
            val mObjectGroup = objParser.parsedObject
            Log.d(javaClass.name, "num objects: " + mObjectGroup.numChildren)
            for (i in 0..mObjectGroup.numChildren - 1) {
                val child = mObjectGroup.getChildAt(i)
                val room = RoomObject(child)
                rooms.add(room)
            }
        } catch (e: ParsingException) {
            e.printStackTrace()
        }

    }

    fun initScene(currentScene: Scene, picker: ObjectColorPicker) {
        for (room in rooms) {
            room.init3D(currentScene, picker)
        }
    }

    fun getRoom(room: String): RoomObject? {
        for (roomObject in rooms) {
            if (roomObject.name.equals(room)) {
                return roomObject
            }
        }
        Log.e(javaClass.name, "Room $room not found")
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
                val boundingBox = room.object3D.getGeometry().getBoundingBox()
                val childMin = boundingBox.getMin()

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
                val boundingBox = room.object3D.getGeometry().getBoundingBox()
                val childMax = boundingBox.getMax()
                max.x = Math.max(max.x, childMax.x)
                max.y = Math.max(max.y, childMax.y)
                max.z = Math.max(max.z, childMax.z)
            }
        }
        return max
    }
}