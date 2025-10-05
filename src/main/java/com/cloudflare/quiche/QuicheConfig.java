package com.cloudflare.quiche;

public class QuicheConfig {

    private long configPtr;
    
    public QuicheConfig(int version) {
        this.configPtr = quiche_config_new(version);
        if (this.configPtr == 0) {
            throw new RuntimeException("Failed to create quiche configuration");
        }
    }
    
    public void setApplicationProtos(byte[] protos) {
        if (configPtr != 0 && protos != null) {
            quiche_config_set_application_protos(configPtr, protos, protos.length);
        }
    }
    
    public void setMaxIdleTimeout(long timeout) {
        if (configPtr != 0) {
            quiche_config_set_max_idle_timeout(configPtr, timeout);
        }
    }
    
    public void setMaxRecvUdpPayloadSize(long size) {
        if (configPtr != 0) {
            quiche_config_set_max_recv_udp_payload_size(configPtr, size);
        }
    }
    
    public void setMaxSendUdpPayloadSize(long size) {
        if (configPtr != 0) {
            quiche_config_set_max_send_udp_payload_size(configPtr, size);
        }
    }
    
    public void setInitialMaxData(long maxData) {
        if (configPtr != 0) {
            quiche_config_set_initial_max_data(configPtr, maxData);
        }
    }
    
    public void setInitialMaxStreamDataBidiLocal(long maxStreamData) {
        if (configPtr != 0) {
            quiche_config_set_initial_max_stream_data_bidi_local(configPtr, maxStreamData);
        }
    }
    
    public void setInitialMaxStreamDataBidiRemote(long maxStreamData) {
        if (configPtr != 0) {
            quiche_config_set_initial_max_stream_data_bidi_remote(configPtr, maxStreamData);
        }
    }
    
    public void setInitialMaxStreamDataUni(long maxStreamData) {
        if (configPtr != 0) {
            quiche_config_set_initial_max_stream_data_uni(configPtr, maxStreamData);
        }
    }
    
    public void setInitialMaxStreamsBidi(long maxStreams) {
        if (configPtr != 0) {
            quiche_config_set_initial_max_streams_bidi(configPtr, maxStreams);
        }
    }
    
    public void setInitialMaxStreamsUni(long maxStreams) {
        if (configPtr != 0) {
            quiche_config_set_initial_max_streams_uni(configPtr, maxStreams);
        }
    }
    
    public void setAckDelayExponent(long exponent) {
        if (configPtr != 0) {
            quiche_config_set_ack_delay_exponent(configPtr, exponent);
        }
    }
    
    public void setMaxAckDelay(long delay) {
        if (configPtr != 0) {
            quiche_config_set_max_ack_delay(configPtr, delay);
        }
    }
    
    public void setDisableActiveMigration(boolean disable) {
        if (configPtr != 0) {
            quiche_config_set_disable_active_migration(configPtr, disable);
        }
    }
    
    protected void finalize() throws Throwable {
        if (configPtr != 0) {
            quiche_config_free(configPtr);
            configPtr = 0;
        }
    }

    public long getNativePtr() {
        return configPtr;
    }
    
    // Native methods - these call quiche API directly
    private native long quiche_config_new(int version);
    private native void quiche_config_free(long configPtr);
    private native int quiche_config_set_application_protos(long configPtr, byte[] protos, int len);
    private native void quiche_config_set_max_idle_timeout(long configPtr, long timeout);
    private native void quiche_config_set_max_recv_udp_payload_size(long configPtr, long size);
    private native void quiche_config_set_max_send_udp_payload_size(long configPtr, long size);
    private native void quiche_config_set_initial_max_data(long configPtr, long maxData);
    private native void quiche_config_set_initial_max_stream_data_bidi_local(long configPtr, long maxStreamData);
    private native void quiche_config_set_initial_max_stream_data_bidi_remote(long configPtr, long maxStreamData);
    private native void quiche_config_set_initial_max_stream_data_uni(long configPtr, long maxStreamData);
    private native void quiche_config_set_initial_max_streams_bidi(long configPtr, long maxStreams);
    private native void quiche_config_set_initial_max_streams_uni(long configPtr, long maxStreams);
    private native void quiche_config_set_ack_delay_exponent(long configPtr, long exponent);
    private native void quiche_config_set_max_ack_delay(long configPtr, long delay);
    private native void quiche_config_set_disable_active_migration(long configPtr, boolean disable);
}
