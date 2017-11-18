package it.achdjian.paolo.temperaturemonitor.graphic

import android.arch.lifecycle.MutableLiveData
import android.arch.lifecycle.ViewModel
import it.achdjian.paolo.temperaturemonitor.domusEngine.TemperatureDataListener

/**
 * Created by Paolo Achdjian on 11/15/17.
 */
class GraphViewModel : ViewModel() , TemperatureDataListener {
    override fun newTemperatureData(data: List<TemperatureData>) {

        graphicData.postValue(GraphicData(data));
    }

    val graphicData = MutableLiveData<GraphicData>()


}