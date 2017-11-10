package com.example.jnitriangle;

import android.content.Context;
import android.opengl.GLSurfaceView;

import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.opengles.GL10;


/**
 * Created by Jameskun on 2017/11/3.
 */

public class JNITriangleRender implements GLSurfaceView.Renderer {

    private final Context context;

    public JNITriangleRender(Context context)
    {
        this.context = context;
    }

    public void onDrawFrame(GL10 gl)
    {
        JNILib.step();
    }

    public void onSurfaceChanged(GL10 gl, int width, int height)
    {
        JNILib.init(width, height,context.getResources().getAssets());
    }

    public void onSurfaceCreated(GL10 gl, EGLConfig config)
    {
        // Do nothing.
    }
}
