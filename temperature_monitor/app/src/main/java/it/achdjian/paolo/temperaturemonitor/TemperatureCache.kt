package it.achdjian.paolo.temperaturemonitor

import android.util.Log
import com.google.common.base.Optional
import com.google.common.cache.CacheBuilder
import com.google.common.cache.CacheLoader
import com.google.common.cache.LoadingCache
import it.achdjian.paolo.temperaturemonitor.domusEngine.AttributesListener
import it.achdjian.paolo.temperaturemonitor.domusEngine.DomusEngine
import it.achdjian.paolo.temperaturemonitor.domusEngine.rest.Attributes
import java.util.concurrent.TimeUnit
import javax.inject.Inject
import javax.inject.Singleton

/**
 * Created by Paolo Achdjian on 02/09/16.
 */
@Singleton
class TemperatureCache @Inject constructor() : CacheLoader<String, Optional<Int>>(), AttributesListener {

    lateinit var domusEngine: DomusEngine
    @Inject
    lateinit var tempSensorLocationDS: TempSensorLocationDS

    override fun newAttributes(attributes: Attributes) {
        if (attributes.clusterId == Constants.TEMPERATURE_MEASUREMENT) {
            attributes.jSonAttribute.forEach {
                if (it.id == 0 && it.isAvailable) {
                    val room = tempSensorLocationDS.getRoom(attributes.networkId, attributes.endpointId)
                    if (room.isNotBlank()) {
                        cache.put(room, Optional.of(Integer.valueOf(it.value)))
                    }
                }
            }
        }
    }

    private var cache: LoadingCache<String, Optional<Int>> = CacheBuilder.newBuilder()
            .expireAfterWrite(1, TimeUnit.MINUTES)
            .build(this)


    fun getTemperature(roomName: String): Optional<Int> {
        Log.i("ZIGBEE COM", "temp request for " + roomName);
        return cache.getUnchecked(roomName)
    }


    override fun load(roomName: String): Optional<Int> {
        val element = tempSensorLocationDS.getElement(roomName)
        if (element != null) {
            domusEngine.getAttribute(element.shortAddress, element.endpointId, Constants.TEMPERATURE_MEASUREMENT, 0)
        }
        return Optional.absent<Int>()
    }

    fun invalidate(room: String) {
        cache.invalidate(room)
    }
}
