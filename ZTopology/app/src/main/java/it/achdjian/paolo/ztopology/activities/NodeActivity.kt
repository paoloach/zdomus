package it.achdjian.paolo.ztopology.activities

import android.content.Context
import android.content.res.Resources.Theme
import android.os.Bundle
import android.support.v4.app.Fragment
import android.support.v7.app.AppCompatActivity
import android.support.v7.widget.ThemedSpinnerAdapter
import android.view.*
import android.widget.ArrayAdapter
import it.achdjian.paolo.ztopology.DeviceCallback
import it.achdjian.paolo.ztopology.DomusEngine
import it.achdjian.paolo.ztopology.EndpointCallback
import it.achdjian.paolo.ztopology.R
import it.achdjian.paolo.ztopology.activities.node.EndpointAdapter
import kotlinx.android.synthetic.main.activity_node.*
import kotlinx.android.synthetic.main.fragment_node.view.*
import kotlinx.android.synthetic.main.list_item.view.*

class NodeActivity : AppCompatActivity() {
    companion object {
        val NETWORK_ID = "networkId"
    }
    private var networkId: Int = 0

    lateinit var endpointAdapter: EndpointAdapter

    override fun onDestroy() {
        super.onDestroy()
        DomusEngine.removeCallback(endpointAdapter as DeviceCallback)
        DomusEngine.removeCallback(endpointAdapter as EndpointCallback)
    }

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)

        if (intent != null){
            networkId = intent.getIntExtra(NETWORK_ID,0)
        }
        setContentView(R.layout.activity_node)

        setSupportActionBar(toolbar)
        supportActionBar?.setDisplayShowTitleEnabled(false)
        endpointAdapter = EndpointAdapter(toolbar.context, networkId)
        DomusEngine.addCallback(endpointAdapter as DeviceCallback)
        DomusEngine.addCallback(endpointAdapter as EndpointCallback)

        // Setup spinner
        spinner.adapter =endpointAdapter;

//                MyAdapter(
//            toolbar.context,
//            arrayOf("Section 1", "Section 2", "Section 3"))

//        spinner.onItemSelectedListener = object : OnItemSelectedListener {
//            override fun onItemSelected( parent: AdapterView<*>, view: View, position: Int, id: Long
//            ) {
//                // When the given dropdown item is selected, show its contents in the
//                // container view.
//                supportFragmentManager.beginTransaction()
//                    .replace(R.id.container, PlaceholderFragment.newInstance(position + 1))
//                    .commit()
//            }
//
//            override fun onNothingSelected(parent: AdapterView<*>) {}
//        }
//
//                    fab . setOnClickListener { view ->
//                Snackbar.make(view, "Replace with your own action", Snackbar.LENGTH_LONG)
//                    .setAction("Action", null).show()
//            }

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

    /**
     * A placeholder fragment containing a simple view.
     */
    class PlaceholderFragment : Fragment() {

        override fun onCreateView(
            inflater: LayoutInflater, container: ViewGroup?,
            savedInstanceState: Bundle?
        ): View? {
            val rootView = inflater.inflate(R.layout.fragment_node, container, false)
            rootView.section_label.text =
                    getString(R.string.section_format, arguments.getInt(ARG_SECTION_NUMBER))
            return rootView
        }

        companion object {
            /**
             * The fragment argument representing the section number for this
             * fragment.
             */
            private val ARG_SECTION_NUMBER = "section_number"

            /**
             * Returns a new instance of this fragment for the given section
             * number.
             */
            fun newInstance(sectionNumber: Int): PlaceholderFragment {
                val fragment = PlaceholderFragment()
                val args = Bundle()
                args.putInt(ARG_SECTION_NUMBER, sectionNumber)
                fragment.arguments = args
                return fragment
            }
        }
    }


}
