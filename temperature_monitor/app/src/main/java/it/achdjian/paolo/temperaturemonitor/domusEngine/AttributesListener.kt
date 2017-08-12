package it.achdjian.paolo.temperaturemonitor.domusEngine

import it.achdjian.paolo.temperaturemonitor.domusEngine.rest.Attributes

interface AttributesListener {
    fun newAttributes( attributes: Attributes)
}