package it.achdjian.paolo.temperaturemonitor.graphic

import android.util.Log
import it.achdjian.paolo.temperaturemonitor.domusEngine.TemperatureDataListener
import org.joda.time.LocalDateTime

/**
 * Created by Paolo Achdjian on 10/31/17.
 */
class GraphicData : TemperatureDataListener {
    var views: MutableSet<TemperatureDataViewer> = HashSet()
    var data: List<TemperatureData> = ArrayList()
    var tempMin = 15
    var tempMax = 25
    var timeMin: LocalDateTime = LocalDateTime().minusDays(1)
    var timeMax: LocalDateTime = LocalDateTime()
    var division: Int = 10
    var temperatureDiv: List<Int> = calcTemperatureDivision()

    fun addView(view: TemperatureDataViewer) = views.add(view)
    private fun invalidate() = views.forEach { it.newData() }

    override fun newTemperatureData(data: List<TemperatureData>) {
        Log.i("GRAPH-DATA", "new data")
        this.data = data

        calcTempMinMax()
        calcTimeMinMax()
        temperatureDiv = calcTemperatureDivision()
        invalidate()
    }

    private fun calcTimeMinMax() {
        if (!data.isEmpty()) {
            timeMin = data[0].time
            timeMax = data[data.size - 1].time
        }

    }

    private fun calcTempMinMax() {
        tempMax = Int.MIN_VALUE
        tempMin = Int.MAX_VALUE
        data.forEach({
            if (tempMin > (it.value.toInt() - 1))
                tempMin = it.value.toInt() - 1
            if (tempMax < (it.value.toInt() + 1))
                tempMax = it.value.toInt() + 1
        })

    }

    private fun calcTemperatureDivision(): List<Int> {
        val div = ArrayList<Int>()

        var temp = tempMin
        while (temp <= tempMax) {
            div.add(temp)
            temp++
        }

        return div
    }
}