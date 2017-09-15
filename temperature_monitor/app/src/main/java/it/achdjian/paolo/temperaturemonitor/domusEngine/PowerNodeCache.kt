package it.achdjian.paolo.temperaturemonitor.domusEngine

import com.google.common.base.Optional
import com.google.common.cache.CacheBuilder
import com.google.common.cache.CacheLoader
import com.google.common.cache.LoadingCache
import it.achdjian.paolo.temperaturemonitor.zigbee.PowerNode
import java.util.concurrent.TimeUnit
import javax.inject.Inject
import javax.inject.Singleton

/**
 * Created by Paolo Achdjian on 9/14/17.
 */
@Singleton
class PowerNodeCache @Inject constructor(var domusEngine: DomusEngine) : CacheLoader<Int, Optional<PowerNode>>(),PowerListener {
    override fun newPower(powerNode: PowerNode) {
        cache.put(powerNode.nwkId, Optional.of(powerNode))
    }

    override fun load(nwkId: Int?):Optional<PowerNode> {
        if (nwkId != null) {
            domusEngine.requestPower(nwkId)
        }
        return Optional.absent()
    }

    fun get(nwkId: Int) = cache[nwkId]

    private var cache: LoadingCache<Int, Optional<PowerNode>> = CacheBuilder.newBuilder()
            .expireAfterWrite(30, TimeUnit.MINUTES)
            .build(this)
}