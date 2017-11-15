package com.example.textureblend;

import android.content.res.AssetManager;
import android.graphics.Bitmap;

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
    public static native void setTextureData(int col,int row,int[] pix);
    public static native void setTextureBimap(Bitmap bimap);
}
