package it.achdjian.paolo.opengl.render;


/**
 * @author Jared Woolston (jwoolston@tenkiv.com)
 */
public abstract class AFrameTask implements Runnable {

    protected abstract void doTask();

    @Override
    public void run() {
        try {
            doTask();
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}
