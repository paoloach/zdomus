package it.achdjian.paolo.cs5463.domusEngine

import it.achdjian.paolo.cs5463.domusEngine.rest.Attributes

interface AttributesListener {
    fun newAttributes( attributes: Attributes)
}