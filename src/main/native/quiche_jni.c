#include <jni.h>
#include "quiche_wrapper.h"
#include <string.h>
#include <stdlib.h>

// JNI Implementation for Quiche Java Wrapper
// This file bridges Java native methods to the quiche C library

// ============================================================================
// QuicheConfig JNI Methods
// ============================================================================

JNIEXPORT jlong JNICALL
Java_com_cloudflare_quiche_QuicheConfig_quiche_1config_1new(JNIEnv *env, jobject obj, jint version) {
    quiche_config *config = quiche_config_new((uint32_t)version);
    return (jlong)(uintptr_t)config;
}

JNIEXPORT void JNICALL
Java_com_cloudflare_quiche_QuicheConfig_quiche_1config_1free(JNIEnv *env, jobject obj, jlong configPtr) {
    quiche_config *config = (quiche_config*)(uintptr_t)configPtr;
    if (config != NULL) {
        quiche_config_free(config);
    }
}

JNIEXPORT jint JNICALL
Java_com_cloudflare_quiche_QuicheConfig_quiche_1config_1set_1application_1protos(
    JNIEnv *env, jobject obj, jlong configPtr, jbyteArray protos, jint len) {
    
    quiche_config *config = (quiche_config*)(uintptr_t)configPtr;
    if (config == NULL || protos == NULL) {
        return -1;
    }
    
    jbyte *protos_bytes = (*env)->GetByteArrayElements(env, protos, NULL);
    if (protos_bytes == NULL) {
        return -1;
    }
    
    int result = quiche_config_set_application_protos(config, (uint8_t*)protos_bytes, (size_t)len);
    
    (*env)->ReleaseByteArrayElements(env, protos, protos_bytes, JNI_ABORT);
    return result;
}

JNIEXPORT void JNICALL
Java_com_cloudflare_quiche_QuicheConfig_quiche_1config_1set_1max_1idle_1timeout(
    JNIEnv *env, jobject obj, jlong configPtr, jlong timeout) {
    
    quiche_config *config = (quiche_config*)(uintptr_t)configPtr;
    if (config != NULL) {
        quiche_config_set_max_idle_timeout(config, (uint64_t)timeout);
    }
}

JNIEXPORT void JNICALL
Java_com_cloudflare_quiche_QuicheConfig_quiche_1config_1set_1max_1recv_1udp_1payload_1size(
    JNIEnv *env, jobject obj, jlong configPtr, jlong size) {
    
    quiche_config *config = (quiche_config*)(uintptr_t)configPtr;
    if (config != NULL) {
        quiche_config_set_max_recv_udp_payload_size(config, (size_t)size);
    }
}

JNIEXPORT void JNICALL
Java_com_cloudflare_quiche_QuicheConfig_quiche_1config_1set_1max_1send_1udp_1payload_1size(
    JNIEnv *env, jobject obj, jlong configPtr, jlong size) {
    
    quiche_config *config = (quiche_config*)(uintptr_t)configPtr;
    if (config != NULL) {
        quiche_config_set_max_send_udp_payload_size(config, (size_t)size);
    }
}

JNIEXPORT void JNICALL
Java_com_cloudflare_quiche_QuicheConfig_quiche_1config_1set_1initial_1max_1data(
    JNIEnv *env, jobject obj, jlong configPtr, jlong maxData) {
    
    quiche_config *config = (quiche_config*)(uintptr_t)configPtr;
    if (config != NULL) {
        quiche_config_set_initial_max_data(config, (uint64_t)maxData);
    }
}

JNIEXPORT void JNICALL
Java_com_cloudflare_quiche_QuicheConfig_quiche_1config_1set_1initial_1max_1stream_1data_1bidi_1local(
    JNIEnv *env, jobject obj, jlong configPtr, jlong maxStreamData) {
    
    quiche_config *config = (quiche_config*)(uintptr_t)configPtr;
    if (config != NULL) {
        quiche_config_set_initial_max_stream_data_bidi_local(config, (uint64_t)maxStreamData);
    }
}

JNIEXPORT void JNICALL
Java_com_cloudflare_quiche_QuicheConfig_quiche_1config_1set_1initial_1max_1stream_1data_1bidi_1remote(
    JNIEnv *env, jobject obj, jlong configPtr, jlong maxStreamData) {
    
    quiche_config *config = (quiche_config*)(uintptr_t)configPtr;
    if (config != NULL) {
        quiche_config_set_initial_max_stream_data_bidi_remote(config, (uint64_t)maxStreamData);
    }
}

JNIEXPORT void JNICALL
Java_com_cloudflare_quiche_QuicheConfig_quiche_1config_1set_1initial_1max_1stream_1data_1uni(
    JNIEnv *env, jobject obj, jlong configPtr, jlong maxStreamData) {
    
    quiche_config *config = (quiche_config*)(uintptr_t)configPtr;
    if (config != NULL) {
        quiche_config_set_initial_max_stream_data_uni(config, (uint64_t)maxStreamData);
    }
}

JNIEXPORT void JNICALL
Java_com_cloudflare_quiche_QuicheConfig_quiche_1config_1set_1initial_1max_1streams_1bidi(
    JNIEnv *env, jobject obj, jlong configPtr, jlong maxStreams) {
    
    quiche_config *config = (quiche_config*)(uintptr_t)configPtr;
    if (config != NULL) {
        quiche_config_set_initial_max_streams_bidi(config, (uint64_t)maxStreams);
    }
}

JNIEXPORT void JNICALL
Java_com_cloudflare_quiche_QuicheConfig_quiche_1config_1set_1initial_1max_1streams_1uni(
    JNIEnv *env, jobject obj, jlong configPtr, jlong maxStreams) {
    
    quiche_config *config = (quiche_config*)(uintptr_t)configPtr;
    if (config != NULL) {
        quiche_config_set_initial_max_streams_uni(config, (uint64_t)maxStreams);
    }
}

JNIEXPORT void JNICALL
Java_com_cloudflare_quiche_QuicheConfig_quiche_1config_1set_1ack_1delay_1exponent(
    JNIEnv *env, jobject obj, jlong configPtr, jlong exponent) {
    
    quiche_config *config = (quiche_config*)(uintptr_t)configPtr;
    if (config != NULL) {
        quiche_config_set_ack_delay_exponent(config, (uint64_t)exponent);
    }
}

JNIEXPORT void JNICALL
Java_com_cloudflare_quiche_QuicheConfig_quiche_1config_1set_1max_1ack_1delay(
    JNIEnv *env, jobject obj, jlong configPtr, jlong delay) {
    
    quiche_config *config = (quiche_config*)(uintptr_t)configPtr;
    if (config != NULL) {
        quiche_config_set_max_ack_delay(config, (uint64_t)delay);
    }
}

JNIEXPORT void JNICALL
Java_com_cloudflare_quiche_QuicheConfig_quiche_1config_1set_1disable_1active_1migration(
    JNIEnv *env, jobject obj, jlong configPtr, jboolean disable) {
    
    quiche_config *config = (quiche_config*)(uintptr_t)configPtr;
    if (config != NULL) {
        quiche_config_set_disable_active_migration(config, (bool)disable);
    }
}

// ============================================================================
// Quiche Connection JNI Methods
// ============================================================================

JNIEXPORT jlong JNICALL
Java_com_cloudflare_quiche_Quiche_quiche_1connect_1simple(
    JNIEnv *env, jclass cls, jstring serverName, jbyteArray scid, jint scidLen, jlong configPtr) {
    
    quiche_config *config = (quiche_config*)(uintptr_t)configPtr;
    if (config == NULL || serverName == NULL || scid == NULL) {
        return 0;
    }
    
    const char *server_name_str = (*env)->GetStringUTFChars(env, serverName, NULL);
    if (server_name_str == NULL) {
        return 0;
    }
    
    jbyte *scid_bytes = (*env)->GetByteArrayElements(env, scid, NULL);
    if (scid_bytes == NULL) {
        (*env)->ReleaseStringUTFChars(env, serverName, server_name_str);
        return 0;
    }
    
    quiche_conn *conn = quiche_connect_simple(server_name_str, (uint8_t*)scid_bytes, (size_t)scidLen, config);
    
    (*env)->ReleaseByteArrayElements(env, scid, scid_bytes, JNI_ABORT);
    (*env)->ReleaseStringUTFChars(env, serverName, server_name_str);
    
    return (jlong)(uintptr_t)conn;
}

JNIEXPORT jlong JNICALL
Java_com_cloudflare_quiche_Quiche_quiche_1accept_1simple(
    JNIEnv *env, jclass cls, jbyteArray scid, jint scidLen, jlong configPtr) {
    
    quiche_config *config = (quiche_config*)(uintptr_t)configPtr;
    if (config == NULL || scid == NULL) {
        return 0;
    }
    
    jbyte *scid_bytes = (*env)->GetByteArrayElements(env, scid, NULL);
    if (scid_bytes == NULL) {
        return 0;
    }
    
    quiche_conn *conn = quiche_accept_simple((uint8_t*)scid_bytes, (size_t)scidLen, config);
    
    (*env)->ReleaseByteArrayElements(env, scid, scid_bytes, JNI_ABORT);
    
    return (jlong)(uintptr_t)conn;
}

JNIEXPORT void JNICALL
Java_com_cloudflare_quiche_Quiche_quiche_1conn_1free(JNIEnv *env, jclass cls, jlong connPtr) {
    quiche_conn *conn = (quiche_conn*)(uintptr_t)connPtr;
    if (conn != NULL) {
        quiche_conn_free(conn);
    }
}

JNIEXPORT jlong JNICALL
Java_com_cloudflare_quiche_Quiche_quiche_1conn_1send_1simple(
    JNIEnv *env, jclass cls, jlong connPtr, jbyteArray out, jint outLen) {
    
    quiche_conn *conn = (quiche_conn*)(uintptr_t)connPtr;
    if (conn == NULL || out == NULL) {
        return -1;
    }
    
    jbyte *out_bytes = (*env)->GetByteArrayElements(env, out, NULL);
    if (out_bytes == NULL) {
        return -1;
    }
    
    ssize_t sent = quiche_conn_send_simple(conn, (uint8_t*)out_bytes, (size_t)outLen);
    
    (*env)->ReleaseByteArrayElements(env, out, out_bytes, 0);
    
    return (jlong)sent;
}

JNIEXPORT jlong JNICALL
Java_com_cloudflare_quiche_Quiche_quiche_1conn_1recv_1simple(
    JNIEnv *env, jclass cls, jlong connPtr, jbyteArray buf, jint bufLen) {
    
    quiche_conn *conn = (quiche_conn*)(uintptr_t)connPtr;
    if (conn == NULL || buf == NULL) {
        return -1;
    }
    
    jbyte *buf_bytes = (*env)->GetByteArrayElements(env, buf, NULL);
    if (buf_bytes == NULL) {
        return -1;
    }
    
    ssize_t received = quiche_conn_recv_simple(conn, (uint8_t*)buf_bytes, (size_t)bufLen);
    
    (*env)->ReleaseByteArrayElements(env, buf, buf_bytes, 0);
    
    return (jlong)received;
}

JNIEXPORT jint JNICALL
Java_com_cloudflare_quiche_Quiche_quiche_1conn_1close(
    JNIEnv *env, jclass cls, jlong connPtr, jboolean app, jlong err, jbyteArray reason, jint reasonLen) {
    
    quiche_conn *conn = (quiche_conn*)(uintptr_t)connPtr;
    if (conn == NULL) {
        return -1;
    }
    
    uint8_t *reason_bytes = NULL;
    if (reason != NULL) {
        jbyte *tmp = (*env)->GetByteArrayElements(env, reason, NULL);
        reason_bytes = (uint8_t*)tmp;
    }
    
    int result = quiche_conn_close(conn, (bool)app, (uint64_t)err, reason_bytes, (size_t)reasonLen);
    
    if (reason != NULL && reason_bytes != NULL) {
        (*env)->ReleaseByteArrayElements(env, reason, (jbyte*)reason_bytes, JNI_ABORT);
    }
    
    return result;
}

JNIEXPORT jboolean JNICALL
Java_com_cloudflare_quiche_Quiche_quiche_1conn_1is_1established(JNIEnv *env, jclass cls, jlong connPtr) {
    quiche_conn *conn = (quiche_conn*)(uintptr_t)connPtr;
    if (conn == NULL) {
        return JNI_FALSE;
    }
    return quiche_conn_is_established(conn) ? JNI_TRUE : JNI_FALSE;
}

JNIEXPORT jboolean JNICALL
Java_com_cloudflare_quiche_Quiche_quiche_1conn_1is_1closed(JNIEnv *env, jclass cls, jlong connPtr) {
    quiche_conn *conn = (quiche_conn*)(uintptr_t)connPtr;
    if (conn == NULL) {
        return JNI_TRUE;
    }
    return quiche_conn_is_closed(conn) ? JNI_TRUE : JNI_FALSE;
}

JNIEXPORT jboolean JNICALL
Java_com_cloudflare_quiche_Quiche_quiche_1conn_1is_1server(JNIEnv *env, jclass cls, jlong connPtr) {
    quiche_conn *conn = (quiche_conn*)(uintptr_t)connPtr;
    if (conn == NULL) {
        return JNI_FALSE;
    }
    return quiche_conn_is_server(conn) ? JNI_TRUE : JNI_FALSE;
}

JNIEXPORT jlong JNICALL
Java_com_cloudflare_quiche_Quiche_quiche_1conn_1timeout_1as_1millis(JNIEnv *env, jclass cls, jlong connPtr) {
    quiche_conn *conn = (quiche_conn*)(uintptr_t)connPtr;
    if (conn == NULL) {
        return 0;
    }
    return (jlong)quiche_conn_timeout_as_millis(conn);
}

JNIEXPORT void JNICALL
Java_com_cloudflare_quiche_Quiche_quiche_1conn_1on_1timeout(JNIEnv *env, jclass cls, jlong connPtr) {
    quiche_conn *conn = (quiche_conn*)(uintptr_t)connPtr;
    if (conn != NULL) {
        quiche_conn_on_timeout(conn);
    }
}

JNIEXPORT jstring JNICALL
Java_com_cloudflare_quiche_Quiche_quiche_1error_1to_1string(JNIEnv *env, jclass cls, jint err) {
    const char *error_str = quiche_error_to_string((int)err);
    if (error_str == NULL) {
        return NULL;
    }
    return (*env)->NewStringUTF(env, error_str);
}
