package it.achdjian.paolo.temperaturemonitor.rajawali

import android.graphics.Bitmap
import android.graphics.Canvas
import android.graphics.Color
import android.graphics.Paint
import org.rajawali3d.materials.Material
import org.rajawali3d.materials.textures.ATexture
import org.rajawali3d.materials.textures.Texture
import org.rajawali3d.math.vector.Vector3
import org.rajawali3d.primitives.Plane
import java.util.*

/**
 * Created by Paolo Achdjian on 17/04/17.
 */

class TemperatureLabel(room: RoomObject) : Plane(getMaxWidth(room), getMaxHeight(room), 3, 3) {
    private var previousTemp = java.lang.Float.NaN

    val pos: Vector3
        get() = position

    init {
        val name = "TempSensor" + room.name
        setName(name)
        setText("N.D.", Color.GREEN)
        val pos = Vector3(room.mean.x, room.mean.y, room.max.z)
        position = pos
        isDoubleSided = true
    }

    fun setTemperature(temp: Float, background: Int) {
        if (temp != previousTemp) {
            previousTemp = temp
            val strTemp = String.format(Locale.US, "%.2f", temp)
            setText(strTemp, background)
        }
    }

    private fun setText(text: String, background: Int) {
        val temperatureMaterial = Material(true)
        temperatureMaterial.color = background
        val bitmap = textAsBitmap(text, Color.WHITE)
        try {
            val maxTextureName = 18
            val name = name.substring(0, if (name.length > maxTextureName) maxTextureName else name.length)
            temperatureMaterial.addTexture(Texture(name, bitmap))
            material = temperatureMaterial
        } catch (e: ATexture.TextureException) {
            e.printStackTrace()
        }

    }

    private fun textAsBitmap(text: String, textColor: Int): Bitmap {
        val paint = Paint()
        paint.textSize = 30f
        paint.strokeWidth = 10f
        paint.color = textColor
        val baseline = (-paint.ascent() + 0.5f).toInt().toFloat()


        val image = Bitmap.createBitmap(128, 32, Bitmap.Config.ARGB_8888)
        val canvas = Canvas(image)
        val widthText = paint.measureText(text).toInt()
        canvas.drawText(text, ((128 - widthText) / 2).toFloat(), baseline, paint)
        return image
    }

    companion object {
        var WIDTH = 1.5f
        var HEIGHT = 0.4f

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
