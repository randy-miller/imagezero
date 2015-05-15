package test;

public class ImageZeroJNI {
    static {
        System.loadLibrary("izwrapper");
    }    

    public static native int encodeImage(byte[] input, byte[] output);
    public static native int getImageSize(byte[] input);
    public static native void decodeImage(byte[] input, byte[] output);
}
