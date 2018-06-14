package laud.ripoll.flappybird;

import android.content.Context;
import android.graphics.PixelFormat;
import android.opengl.GLSurfaceView;
import android.util.AttributeSet;
import android.util.Log;
import android.view.KeyEvent;
import android.view.MotionEvent;

import javax.microedition.khronos.egl.EGL10;
import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.egl.EGLContext;
import javax.microedition.khronos.egl.EGLDisplay;
import javax.microedition.khronos.opengles.GL10;

public class FlappyBirdView extends GLSurfaceView {

    public FlappyBirdView(Context context)
    {
        super(context);

        setEGLConfigChooser(8, 8, 8, 0, 16, 0);
        setEGLContextClientVersion(2);
        setPreserveEGLContextOnPause(true);

        setRenderer(new Renderer());
    }

    private static class Renderer implements GLSurfaceView.Renderer {
        public void onDrawFrame(GL10 gl) {
            FlappyBirdLib.Update();
        }

        public void onSurfaceChanged(GL10 gl, int width, int height) {
            //FlappyBirdLib.Resize(width, height);
        }

        public void onSurfaceCreated(GL10 gl, EGLConfig config) {
            FlappyBirdLib.Init();
        }

    }
}
