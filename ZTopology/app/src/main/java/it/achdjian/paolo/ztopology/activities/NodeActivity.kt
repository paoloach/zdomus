package it.achdjian.paolo.ztopology.activities

import android.os.Bundle
import android.support.v7.app.AppCompatActivity
import android.view.Menu
import android.view.MenuItem
import it.achdjian.paolo.ztopology.DeviceCallback
import it.achdjian.paolo.ztopology.DomusEngine
import it.achdjian.paolo.ztopology.EndpointCallback
import it.achdjian.paolo.ztopology.R
import it.achdjian.paolo.ztopology.activities.node.ClusterTabSelectedListener
import it.achdjian.paolo.ztopology.activities.node.EndpointAdapter
import it.achdjian.paolo.ztopology.activities.node.SelectedEndpointListener
import it.achdjian.paolo.ztopology.zigbee.Topology
import kotlinx.android.synthetic.main.activity_node.*
import kotlinx.android.synthetic.main.activity_node.view.*

class NodeActivity : AppCompatActivity() {
    companion object {
        val TOPOLOGY = "topology"
        val ENDPOINT = "endpoint"
    }
    private lateinit var topology: Topology

    lateinit var endpointAdapter: EndpointAdapter
    lateinit var endpointListener: SelectedEndpointListener

    override fun onDestroy() {
        super.onDestroy()
        DomusEngine.removeCallback(endpointAdapter as DeviceCallback)
        DomusEngine.removeCallback(endpointAdapter as EndpointCallback)
    }

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)

        if (intent != null){
            topology = intent.getSerializableExtra(TOPOLOGY) as Topology
        }
        setContentView(R.layout.activity_node)

        setSupportActionBar(toolbar)
        supportActionBar?.setDisplayShowTitleEnabled(false)
        endpointAdapter = EndpointAdapter(toolbar.context, topology.nwkAddress)
        DomusEngine.addCallback(endpointAdapter as DeviceCallback)
        DomusEngine.addCallback(endpointAdapter as EndpointCallback)

        val clusterTabSelectedListener = ClusterTabSelectedListener(supportFragmentManager)
        endpointListener = SelectedEndpointListener(clusterTab, clusterTabSelectedListener)
        clusterTab.addOnTabSelectedListener(clusterTabSelectedListener)
        // Setup spinner
        spinner.adapter =endpointAdapter;
        spinner.onItemSelectedListener = endpointListener

        nwkValue.text = topology.nwkAddress.toString(16)
        lqiValue.text = topology.lqi.toString()
        macValue.text = topology.extendedAddr
    }


    override fun onCreateOptionsMenu(menu: Menu): Boolean {
        // Inflate the menu; this adds items to the action bar if it is present.
        menuInflater.inflate(R.menu.menu_node, menu)
        return true
    }

    override fun onOptionsItemSelected(item: MenuItem): Boolean {
        // Handle action bar item clicks here. The action bar will
        // automatically handle clicks on the Home/Up button, so long
        // as you specify a parent activity in AndroidManifest.xml.
        val id = item.itemId

        if (id == R.id.action_settings) {
            return true
        }

        return super.onOptionsItemSelected(item)
    }

}
