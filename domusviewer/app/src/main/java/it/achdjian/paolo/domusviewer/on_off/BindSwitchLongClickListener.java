package it.achdjian.paolo.domusviewer.on_off;

import android.support.annotation.NonNull;
import android.view.View;

import it.achdjian.paolo.domusviewer.Element;
import it.achdjian.paolo.domusviewer.R;

/**
 * Created by Paolo Achdjian on 06/05/16.
 */
class BindSwitchLongClickListener implements View.OnLongClickListener {
    private final ElementSelected selected;
    private final Binding binding;

    public BindSwitchLongClickListener(@NonNull ElementSelected selected, @NonNull Binding binding) {
        this.selected = selected;
        this.binding = binding;
    }

    @Override
    public boolean onLongClick(View v) {
        Object tag = v.getTag(R.id.element_value);
        if (tag instanceof Element && selected.isLight()) {
            if (v.isActivated()) {
                binding.unbind((Element) tag, selected.selected);
            } else {
                binding.bind((Element) tag, selected.selected);
            }
            return true;
        } else {
            return false;
        }
    }
}
