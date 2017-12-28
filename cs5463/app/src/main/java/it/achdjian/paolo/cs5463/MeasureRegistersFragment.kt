package it.achdjian.paolo.cs5463

import android.arch.lifecycle.ViewModelProviders
import android.os.Bundle
import android.support.v4.app.Fragment
import android.view.LayoutInflater
import android.view.View
import android.view.ViewGroup
import android.widget.ListView
import dagger.android.support.DaggerFragment
import it.achdjian.paolo.cs5463.Register.LoadRegister
import it.achdjian.paolo.cs5463.Register.RegistersValue
import it.achdjian.paolo.cs5463.dagger.DaggerMeasureRegistersFragmentComponent
import it.achdjian.paolo.cs5463.dagger.FragmentModule
import it.achdjian.paolo.cs5463.domusEngine.DomusEngine
import javax.inject.Inject

/**
 * Created by Paolo Achdjian on 11/21/17.
 */
class MeasureRegistersFragment  : Fragment() {
    @Inject
    lateinit var registerAdapter: RegistersAdapter
    @Inject
    lateinit var loadRegister: LoadRegister
    @Inject
    lateinit var registersValue: RegistersValue

    override fun onCreateView(inflater: LayoutInflater, container: ViewGroup?,
                              savedInstanceState: Bundle?): View? {
        DaggerMeasureRegistersFragmentComponent.builder().fragmentModule(FragmentModule(this)).build().inject(this)

        ViewModelProviders.of(this).get(CS5463ViewModel::class.java).data.observe(this,loadRegister)
        val rootView = inflater.inflate(R.layout.measure_registers, container, false)

        val listView = rootView.findViewById<ListView>(R.id.registers)
        listView.adapter = registerAdapter
        registersValue.addListView(listView)
        DomusEngine.addAttributeListener(registersValue)
        return rootView
    }

    companion object {
        fun newInstance() = MeasureRegistersFragment()
    }
}