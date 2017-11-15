package com.example.textureblend;

import android.content.Context;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.opengl.GLES20;
import android.opengl.GLSurfaceView;
import android.util.Log;

import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.opengles.GL10;

import static android.opengl.GLES20.GL_LINEAR;
import static android.opengl.GLES20.GL_LINEAR_MIPMAP_LINEAR;
import static android.opengl.GLES20.GL_TEXTURE_2D;
import static android.opengl.GLES20.GL_TEXTURE_MAG_FILTER;
import static android.opengl.GLES20.GL_TEXTURE_MIN_FILTER;
import static android.opengl.GLES20.glBindTexture;
import static android.opengl.GLES20.glGenTextures;
import static android.opengl.GLES20.glGenerateMipmap;
import static android.opengl.GLES20.glTexParameteri;
import static android.opengl.GLUtils.texImage2D;


/**
 * Created by Jameskun on 2017/11/3.
 */

public class TextureBlendRender implements GLSurfaceView.Renderer {

    private static final String TAG = "TextureBlendRender";
    private final Context context;
    private int[] textureID = new int[1];

    private Bitmap bitmap;
    private int col;
    private int row;
    int[] pix;


    public TextureBlendRender(Context context)
    {
        this.context = context;
        bitmap = loadBitmap(context,R.drawable.wall);
        col = bitmap.getWidth();
        row = bitmap.getHeight();
        pix = new int[col * row];
    }

    public void onDrawFrame(GL10 gl)
    {
        JNILib.step();
    }

    public void onSurfaceChanged(GL10 gl, int width, int height)
    {
        //JNILib.setTextureData(col,row,pix);
        JNILib.init(width, height,context.getResources().getAssets());
    }

    public void onSurfaceCreated(GL10 gl, EGLConfig config)
    {
        //setTextureObjID();
        //bitmap.getPixels(pix,0,col,0,0,col,row);
        JNILib.setTextureBimap(bitmap);
    }

    private void setTextureObjID() //设置纹理ID的方式
    {
        Bitmap bitmap = loadBitmap(context,R.drawable.wall);

        glGenTextures(1,textureID,0);
        if (textureID[0] == 0) {
            Log.e(TAG, "Could not generate a new OpenGL texture object.");
            return ;
        }

        glBindTexture(GL_TEXTURE_2D,textureID[0]);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        texImage2D(GL_TEXTURE_2D, 0, bitmap, 0);

        glGenerateMipmap(GL_TEXTURE_2D);
        bitmap.recycle();

        JNILib.setTextures(textureID);

        // Unbind from the texture.
        glBindTexture(GL_TEXTURE_2D, 0);
    }

    private Bitmap loadBitmap(Context context,int resID)
    {
        BitmapFactory.Options options = new BitmapFactory.Options();
        options.inScaled = false;

        final Bitmap bitmap = BitmapFactory.decodeResource(context.getResources(),resID,options);

        if (bitmap == null) {
           Log.e(TAG,"loadBitmap failed!");
        }

        return  bitmap;
    }
}
