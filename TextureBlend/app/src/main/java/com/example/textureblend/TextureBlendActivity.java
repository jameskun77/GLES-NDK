package com.example.textureblend;

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

public class TextureBlendActivity extends Activity {
    private static final String TAG = "TriangleActivity";
    private TextureBlendView mView;

    @Override
    protected void onCreate(Bundle saveInstanceState){
        super.onCreate(saveInstanceState);
        mView = new TextureBlendView(getApplication());
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
