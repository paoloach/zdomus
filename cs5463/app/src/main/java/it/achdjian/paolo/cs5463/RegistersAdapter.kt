package it.achdjian.paolo.cs5463

import android.arch.lifecycle.ViewModelProviders
import android.database.DataSetObserver
import android.support.v4.app.FragmentActivity
import android.view.LayoutInflater
import android.view.View
import android.view.ViewGroup
import android.widget.Adapter.IGNORE_ITEM_VIEW_TYPE
import android.widget.ImageButton
import android.widget.ListAdapter
import android.widget.TextView
import it.achdjian.paolo.cs5463.Register.LoadRegister
import it.achdjian.paolo.cs5463.Register.RegistersWithValues
import javax.inject.Inject
import javax.inject.Singleton

/**
 * Created by Paolo Achdjian on 11/22/17.
 */
@Singleton
class RegistersAdapter @Inject constructor(val activity: MainActivity, val loadRegister:LoadRegister) : ListAdapter {

    init {
        ViewModelProviders.of(activity).get(CS5463ViewModel::class.java).data.observe(activity,loadRegister)
    }

    /**
     * @return true if this adapter doesn't contain any data.  This is used to determine
     * whether the empty view should be displayed.  A typical implementation will return
     * getCount() == 0 but since getCount() includes the headers and footers, specialized
     * adapters might want a different behavior.
     */
    override fun isEmpty() = false

    /**
     * Get a View that displays the data at the specified position in the data set. You can either
     * create a View manually or inflate it from an XML layout file. When the View is inflated, the
     * parent View (GridView, ListView...) will apply default layout parameters unless you use
     * [android.view.LayoutInflater.inflate]
     * to specify a root view and to prevent attachment to the root.
     *
     * @param position The position of the item within the adapter's data set of the item whose view
     * we want.
     * @param convertView The old view to reuse, if possible. Note: You should check that this view
     * is non-null and of an appropriate type before using. If it is not possible to convert
     * this view to display the correct data, this method can create a new view.
     * Heterogeneous lists can specify their number of view types, so that this View is
     * always of the right type (see [.getViewTypeCount] and
     * [.getItemViewType]).
     * @param parent The parent that this view will eventually be attached to
     * @return A View corresponding to the data at the specified position.
     */
    override fun getView(position: Int, oldView: View?, parent: ViewGroup?): View {
        val view: View
        if (oldView == null) {
            val inflater = LayoutInflater.from(activity)
            view = inflater.inflate(R.layout.register, parent, false)
        } else {
            view = oldView
        }

        val register = RegistersWithValues.values().get(position)

        val label = view.findViewById<TextView>(R.id.label)
        label.setText(register.label)

        val refreshButton = view.findViewById<ImageButton>(R.id.refresh)
        refreshButton.tag = register
        refreshButton.setOnClickListener(loadRegister)
        return view
    }

    /**
     * Register an observer that is called when changes happen to the data used by this adapter.
     *
     * @param observer the object that gets notified when the data set changes.
     */
    override fun registerDataSetObserver(observer: DataSetObserver?) {
    }

    /**
     * Get the type of View that will be created by [.getView] for the specified item.
     *
     * @param position The position of the item within the adapter's data set whose view type we
     * want.
     * @return An integer representing the type of View. Two views should share the same type if one
     * can be converted to the other in [.getView]. Note: Integers must be in the
     * range 0 to [.getViewTypeCount] - 1. [.IGNORE_ITEM_VIEW_TYPE] can
     * also be returned.
     * @see .IGNORE_ITEM_VIEW_TYPE
     */
    override fun getItemViewType(position: Int) = IGNORE_ITEM_VIEW_TYPE

    /**
     * Get the data item associated with the specified position in the data set.
     *
     * @param position Position of the item whose data we want within the adapter's
     * data set.
     * @return The data at the specified position.
     */
    override fun getItem(position: Int) = RegistersWithValues.values().get(position)

    /**
     *
     *
     * Returns the number of types of Views that will be created by
     * [.getView]. Each type represents a set of views that can be
     * converted in [.getView]. If the adapter always returns the same
     * type of View for all items, this method should return 1.
     *
     *
     *
     * This method will only be called when the adapter is set on the
     *
     *
     * @return The number of types of Views that will be created by this adapter
     */
    override fun getViewTypeCount() = 1

    /**
     * Returns true if the item at the specified position is not a separator.
     * (A separator is a non-selectable, non-clickable item).
     *
     * The result is unspecified if position is invalid. An [ArrayIndexOutOfBoundsException]
     * should be thrown in that case for fast failure.
     *
     * @param position Index of the item
     *
     * @return True if the item is not a separator
     *
     * @see .areAllItemsEnabled
     */
    override fun isEnabled(position: Int) = true

    /**
     * Get the row id associated with the specified position in the list.
     *
     * @param position The position of the item within the adapter's data set whose row id we want.
     * @return The id of the item at the specified position.
     */
    override fun getItemId(position: Int) = position.toLong()

    /**
     * Indicates whether the item ids are stable across changes to the
     * underlying data.
     *
     * @return True if the same id always refers to the same object.
     */
    override fun hasStableIds() = true

    /**
     * Indicates whether all the items in this adapter are enabled. If the
     * value returned by this method changes over time, there is no guarantee
     * it will take effect.  If true, it means all items are selectable and
     * clickable (there is no separator.)
     *
     * @return True if all items are enabled, false otherwise.
     *
     * @see .isEnabled
     */
    override fun areAllItemsEnabled() = true

    /**
     * Unregister an observer that has previously been registered with this
     * adapter via [.registerDataSetObserver].
     *
     * @param observer the object to unregister.
     */
    override fun unregisterDataSetObserver(observer: DataSetObserver?) {
    }

    /**
     * How many items are in the data set represented by this Adapter.
     *
     * @return Count of items.
     */
    override fun getCount() = RegistersWithValues.values().size
}