package it.achdjian.paolo.temperaturemonitor.graphic

import android.arch.lifecycle.ViewModelProviders
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

    lateinit var graphViewModel: GraphViewModel


    companion object {
        val NETWORK_ADDRESS = "networkAddress"
        val ENDPOINT = "endpoint"
    }

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        (application as TemperatureApplication).component.inject(this)
        val networkAddress = intent.extras.getInt(NETWORK_ADDRESS)
        graphViewModel = ViewModelProviders.of(this).get(GraphViewModel::class.java)

        setContentView(R.layout.graphic)
        domusEngine.addListener(graphViewModel)
        val graphViewScale = GraphViewScale(networkAddress, this, domusEngine)
        graph.setOnTouchListener(graphViewScale)
        graphViewModel.graphicData.observe(this, graph)

        domusEngine.getTemperatureData(networkAddress, graphViewScale.start, graphViewScale.end)
    }

    override fun onDestroy() {
        super.onDestroy()
        domusEngine.removeListener(graphViewModel)
    }

}
