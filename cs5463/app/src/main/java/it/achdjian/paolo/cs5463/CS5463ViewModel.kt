package it.achdjian.paolo.cs5463

import android.arch.lifecycle.MutableLiveData
import android.arch.lifecycle.ViewModel
import javax.inject.Inject

/**
 * Created by Paolo Achdjian on 11/23/17.
 */
class CS5463ViewModel @Inject constructor(): ViewModel() {
    val data = MutableLiveData<CS5463Data>()
}