package com.example.jnitriangle;

import android.app.Activity;
import android.app.ActivityManager;
import android.content.Context;
import android.content.pm.ConfigurationInfo;
import android.opengl.GLSurfaceView;
import android.os.Bundle;
import android.util.Log;

/**
 * Created by Jameskun on 2017/11/3.
 */

public class JNITriangleActivity extends Activity {
    private static final String TAG = "TriangleActivity";
    private JNITriangleView mView;

    @Override
    protected void onCreate(Bundle saveInstanceState){
        super.onCreate(saveInstanceState);
        mView = new JNITriangleView(getApplication());
        setContentView(mView);
    }

    @Override
    protected void onPause()
    {
        super.onPause();
        mView.onPause();
    }

    @Override
    protected void onResume()
    {
        super.onResume();
        mView.onResume();
    }
}
