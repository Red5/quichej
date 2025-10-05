package com.cloudflare.quiche;

public class Quiche {
    static {
        try {
            // Load the native library
            System.loadLibrary("quiche");
        } catch (UnsatisfiedLinkError e) {
            throw new RuntimeException("Failed to load quiche native library", e);
        }
    }
    
    public static final int QUICHE_PROTOCOL_VERSION = 0x00000001;
    
    // Connection methods - using simplified wrappers
    public static native long quiche_connect_simple(String serverName, byte[] scid, int scidLen, long configPtr);
    public static native long quiche_accept_simple(byte[] scid, int scidLen, long configPtr);
    public static native void quiche_conn_free(long connPtr);
    
    // Send/Recv methods - using simplified wrappers
    public static native long quiche_conn_send_simple(long connPtr, byte[] out, int outLen);
    public static native long quiche_conn_recv_simple(long connPtr, byte[] buf, int bufLen);
    
    // Connection state methods - these call quiche API directly
    public static native int quiche_conn_close(long connPtr, boolean app, long err, byte[] reason, int reasonLen);
    public static native boolean quiche_conn_is_established(long connPtr);
    public static native boolean quiche_conn_is_closed(long connPtr);
    public static native boolean quiche_conn_is_server(long connPtr);
    
    // Connection info methods
    public static native long quiche_conn_timeout_as_millis(long connPtr);
    public static native void quiche_conn_on_timeout(long connPtr);
    
    // Utility methods
    public static native String quiche_error_to_string(int err);
}
