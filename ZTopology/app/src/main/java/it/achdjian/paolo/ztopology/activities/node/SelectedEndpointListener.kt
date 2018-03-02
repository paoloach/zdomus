package it.achdjian.paolo.ztopology.activities.node

import android.support.design.widget.TabLayout
import android.view.View
import android.widget.AdapterView
import it.achdjian.paolo.ztopology.zigbee.clusterToString

/**
 * Created by Paolo Achdjian on 2/23/18.
 */
class SelectedEndpointListener(
            val clusterTab: TabLayout,
            val clusterTabSelectedListener: ClusterTabSelectedListener

                ) :
    AdapterView.OnItemSelectedListener {
    /**
     * Callback method to be invoked when the selection disappears from this
     * view. The selection can disappear for instance when touch is activated
     * or when the adapter becomes empty.
     *
     * @param parent The AdapterView that now contains no selected item.
     */
    override fun onNothingSelected(parent: AdapterView<*>?) {
    }

    /**
     *
     * Callback method to be invoked when an item in this view has been
     * selected. This callback is invoked only when the newly selected
     * position is different from the previously selected position or if
     * there was no selected item.
     *
     * Impelmenters can call getItemAtPosition(position) if they need to access the
     * data associated with the selected item.
     *
     * @param parent The AdapterView where the selection happened
     * @param view The view within the AdapterView that was clicked
     * @param position The position of the view in the adapter
     * @param id The row id of the item that is selected
     */
    override fun onItemSelected(parent: AdapterView<*>?, view: View?, position: Int, id: Long) {
        if (parent != null) {
            val adapter = parent.adapter as EndpointAdapter
            val zEndpoint = adapter[position]
            clusterTab.removeAllTabs()
            var firstTab: TabLayout.Tab? = null
            zEndpoint.inCluster.forEach {
                val tab = clusterTab.newTab()
                if (firstTab == null)
                    firstTab = tab
                tab.text = it.name
                tab.tag = it
                clusterTab.addTab(tab)
            }
            clusterTabSelectedListener.zEndpoint = zEndpoint
            if (firstTab != null)
                clusterTabSelectedListener.onTabSelected(firstTab)
        }
    }
}