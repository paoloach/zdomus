package it.achdjian.paolo.temperaturemonitor.rajawali

import android.util.SparseIntArray

/**
 * Created by Paolo Achdjian on 07/09/16.
 */
object TemperatureColorMap {
    private val MAP_TEMP_COLOR = SparseIntArray()

    init {
        MAP_TEMP_COLOR.put(13, 0xFF0000E0.toInt())
        MAP_TEMP_COLOR.put(14, 0xFF0000C0.toInt())
        MAP_TEMP_COLOR.put(15, 0xFF0000A0.toInt())
        MAP_TEMP_COLOR.put(16, 0xFF000080.toInt())
        MAP_TEMP_COLOR.put(17, 0xFF000060.toInt())
        MAP_TEMP_COLOR.put(18, 0xFF000040.toInt())
        MAP_TEMP_COLOR.put(19, 0xFF008020.toInt())
        MAP_TEMP_COLOR.put(20, 0xFF00FA00.toInt())
        MAP_TEMP_COLOR.put(21, 0xFF19E100.toInt())
        MAP_TEMP_COLOR.put(22, 0xFF32C800.toInt())
        MAP_TEMP_COLOR.put(23, 0xFF4BAF00.toInt())
        MAP_TEMP_COLOR.put(24, 0xFF649600.toInt())
        MAP_TEMP_COLOR.put(25, 0xFF7D7D00.toInt())
        MAP_TEMP_COLOR.put(26, 0xFF966400.toInt())
        MAP_TEMP_COLOR.put(27, 0xFFAF4B00.toInt())
        MAP_TEMP_COLOR.put(28, 0xFFC83200.toInt())
        MAP_TEMP_COLOR.put(29, 0xFFE11900.toInt())
        MAP_TEMP_COLOR.put(30, 0xFFFA0000.toInt())
    }

    fun getColor(temperature: Int): Int {
        val temp = temperature / 100
        val color: Int
        if (temp < 13) {
            color = 0xFF0000FF.toInt()
        } else if (temp > 30) {
            color = 0xFFFF0000.toInt()
        } else {
            color = MAP_TEMP_COLOR[temp]
        }
        return color
    }
}
