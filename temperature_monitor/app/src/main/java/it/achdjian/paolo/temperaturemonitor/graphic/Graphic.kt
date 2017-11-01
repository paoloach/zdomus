package it.achdjian.paolo.temperaturemonitor.graphic

import android.os.Bundle
import android.support.v7.app.AppCompatActivity
import it.achdjian.paolo.temperaturemonitor.R
import it.achdjian.paolo.temperaturemonitor.dagger.TemperatureApplication
import it.achdjian.paolo.temperaturemonitor.domusEngine.DomusEngine
import kotlinx.android.synthetic.main.graphic.*
import javax.inject.Inject

class Graphic : AppCompatActivity() {
    @Inject
    lateinit var domusEngine: DomusEngine

    val graphicData =  GraphicData()

    companion object {
        val NETWORK_ADDRESS="networkAddress"
        val ENDPOINT="endpoint"
    }

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        (application as TemperatureApplication).component.inject(this)
        setContentView(R.layout.graphic)
        domusEngine.addListener(graphicData)
        graph.graphicData = graphicData
        graphicData.addView(graph)

        domusEngine.getTemperatureData(intent.extras.getInt(NETWORK_ADDRESS))
    }

    override fun onDestroy(){
        super.onDestroy()
        domusEngine.removeListener(graphicData)
    }

}
