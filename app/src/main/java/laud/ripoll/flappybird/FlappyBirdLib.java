package laud.ripoll.flappybird;

public class FlappyBirdLib {
    static {
        System.loadLibrary("Application");
    }

    //Implement native methods that come from C++ classes


    public static native boolean Init();
    public static native boolean Update();
    public static native void SendTap();
    public static native boolean CleanUp();

    //public static native void Resize(int width, int height);

}
