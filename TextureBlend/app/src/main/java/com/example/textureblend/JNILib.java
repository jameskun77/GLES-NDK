package com.example.textureblend;

import android.content.res.AssetManager;

/**
 * Created by Jameskun on 2017/11/3.
 */

public class JNILib {
    static {
        System.loadLibrary("jinlib");
    }

    public static native void init(int width, int height,AssetManager assetMgr);
    public static native void step();
    public static native void setTextures(int[] textureID);
}
