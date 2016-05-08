package it.achdjian.paolo.domusviewer.on_off;

import android.support.annotation.NonNull;
import android.view.View;

import it.achdjian.paolo.domusviewer.Element;
import it.achdjian.paolo.domusviewer.R;

/**
 * Created by Paolo Achdjian on 06/05/16.
 */
class BindLightLongClickListener implements View.OnLongClickListener {
    private final ElementSelected selected;
    private final Binding binding;

    public BindLightLongClickListener(@NonNull ElementSelected selected, @NonNull Binding binding) {
        this.selected = selected;
        this.binding = binding;
    }

    @Override
    public boolean onLongClick(View v) {
        Object tag = v.getTag(R.id.element_value);
        if (tag instanceof Element && selected.isSwitch()) {
            if (v.isActivated()) {
                binding.unbind(selected.selected, (Element) tag);
            } else {
                binding.bind(selected.selected, (Element) tag);
            }
            return true;
        } else {
            return false;
        }
    }
}
