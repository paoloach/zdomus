package it.achdjian.paolo.temperaturemonitor.rajawali

import android.content.Context
import android.graphics.BitmapFactory
import android.graphics.Color
import it.achdjian.paolo.temperaturemonitor.R
import org.rajawali3d.materials.Material
import org.rajawali3d.materials.textures.Texture
import org.rajawali3d.math.vector.Vector3
import org.rajawali3d.primitives.Plane

/**
 * Created by Paolo Achdjian on 10/20/17.
 */
class GraphIcon (room: RoomObject, tempPos: Vector3?, context: Context): Plane(getMaxWidth(room), getMaxHeight(room), 3, 3)  {

    init {
        name = "graphIcon"+ room.name
        val bitmap = BitmapFactory.decodeResource(context.resources, R.drawable.graph, null)
        val newMaterial = Material(true)
        newMaterial.color= Color.BLACK
        newMaterial.addTexture(Texture("graph", bitmap))
        material = newMaterial
        if (tempPos != null) {
            val pos = Vector3(tempPos.x+1, tempPos.y, tempPos.z)
            position = pos
        }
        isDoubleSided = true

    }

    companion object {
        var WIDTH = 0.5f
        var HEIGHT = 0.5f

        private fun getMaxWidth(room: RoomObject): Float {
            val minWidth = (room.max.x - room.min.x).toFloat()
            return if (minWidth < WIDTH) minWidth else WIDTH
        }

        private fun getMaxHeight(room: RoomObject): Float {
            val minHeight = (room.max.y - room.min.y).toFloat()
            return if (minHeight < HEIGHT) minHeight else HEIGHT
        }
    }
}