package com.example.glesjniseries;

import android.app.Activity;
import android.os.Bundle;

/**
 * Created by 123 on 2017/11/5.
 */

public class cubeActivity extends Activity {
    GL2JNIView mView;

    @Override
    protected void onCreate(Bundle icicle) {
        super.onCreate(icicle);
        mView = new GL2JNIView(getApplication(),true,8,8);
        setContentView(mView);
    }

    @Override
    protected void onPause() {
        super.onPause();
        mView.onPause();
    }

    @Override
    protected void onResume() {
        super.onResume();
        mView.onResume();
    }
}
