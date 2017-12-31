package it.achdjian.paolo.cs5463

import android.arch.lifecycle.MutableLiveData
import android.arch.lifecycle.ViewModel
import javax.inject.Inject

/**
 * Created by Paolo Achdjian on 11/23/17.
 */
class SmartPlugViewModel @Inject constructor(): ViewModel() {
    val smartPlug = MutableLiveData<SmartPlugData>()
}