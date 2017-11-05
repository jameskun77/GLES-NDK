package com.example.glesjniseries;

public class GL2JNILib {

     static {
         System.loadLibrary("native-lib");
     }

     public static native void init(int width, int height);
     public static native void step();
}
