#include "quiche_wrapper.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>

// Helper function to create a simple connection without socket addresses
quiche_conn* quiche_connect_simple(const char* server_name, const uint8_t* scid, size_t scid_len,
                                   quiche_config* config) {
    if (config == NULL || server_name == NULL || scid == NULL) {
        return NULL;
    }
    
    struct sockaddr_in local;
    memset(&local, 0, sizeof(local));
    local.sin_family = AF_INET;
    local.sin_port = htons(0);
    local.sin_addr.s_addr = INADDR_ANY;
    
    struct sockaddr_in peer;
    memset(&peer, 0, sizeof(peer));
    peer.sin_family = AF_INET;
    peer.sin_port = htons(443);
    inet_pton(AF_INET, "127.0.0.1", &peer.sin_addr);
    
    return quiche_connect(server_name, scid, scid_len,
                         (const struct sockaddr*)&local, sizeof(local),
                         (const struct sockaddr*)&peer, sizeof(peer),
                         config);
}

// Helper function to accept connection
quiche_conn* quiche_accept_simple(const uint8_t* scid, size_t scid_len, quiche_config* config) {
    if (config == NULL || scid == NULL) {
        return NULL;
    }
    
    uint8_t odcid[20];
    memcpy(odcid, scid, scid_len < 20 ? scid_len : 20);
    
    struct sockaddr_in local;
    memset(&local, 0, sizeof(local));
    local.sin_family = AF_INET;
    local.sin_port = htons(443);
    local.sin_addr.s_addr = INADDR_ANY;
    
    struct sockaddr_in peer;
    memset(&peer, 0, sizeof(peer));
    peer.sin_family = AF_INET;
    peer.sin_port = htons(0);
    inet_pton(AF_INET, "127.0.0.1", &peer.sin_addr);
    
    return quiche_accept(scid, scid_len,
                        odcid, scid_len < 20 ? scid_len : 20,
                        (const struct sockaddr*)&local, sizeof(local),
                        (const struct sockaddr*)&peer, sizeof(peer),
                        config);
}

// Simplified send
ssize_t quiche_conn_send_simple(quiche_conn* conn, uint8_t* out, size_t out_len) {
    if (conn == NULL || out == NULL) {
        return -1;
    }
    
    quiche_send_info send_info;
    memset(&send_info, 0, sizeof(send_info));
    
    return quiche_conn_send(conn, out, out_len, &send_info);
}

// Simplified recv
ssize_t quiche_conn_recv_simple(quiche_conn* conn, uint8_t* buf, size_t buf_len) {
    if (conn == NULL || buf == NULL) {
        return -1;
    }
    
    struct sockaddr_in from_addr;
    memset(&from_addr, 0, sizeof(from_addr));
    from_addr.sin_family = AF_INET;
    
    struct sockaddr_in to_addr;
    memset(&to_addr, 0, sizeof(to_addr));
    to_addr.sin_family = AF_INET;
    
    quiche_recv_info recv_info;
    recv_info.from = (struct sockaddr*)&from_addr;
    recv_info.from_len = sizeof(from_addr);
    recv_info.to = (struct sockaddr*)&to_addr;
    recv_info.to_len = sizeof(to_addr);
    
    return quiche_conn_recv(conn, buf, buf_len, &recv_info);
}

// Error to string
const char* quiche_error_to_string(int err) {
    switch (err) {
        case -1: return "QUICHE_ERR_DONE";
        case -2: return "QUICHE_ERR_BUFFER_TOO_SHORT";
        case -3: return "QUICHE_ERR_UNKNOWN_VERSION";
        case -4: return "QUICHE_ERR_INVALID_FRAME";
        case -5: return "QUICHE_ERR_INVALID_PACKET";
        case -6: return "QUICHE_ERR_INVALID_STATE";
        case -7: return "QUICHE_ERR_INVALID_STREAM_STATE";
        case -8: return "QUICHE_ERR_INVALID_TRANSPORT_PARAM";
        case -9: return "QUICHE_ERR_CRYPTO_FAIL";
        case -10: return "QUICHE_ERR_TLS_FAIL";
        case -11: return "QUICHE_ERR_FLOW_CONTROL";
        case -12: return "QUICHE_ERR_STREAM_LIMIT";
        case -13: return "QUICHE_ERR_FINAL_SIZE";
        case -14: return "QUICHE_ERR_CONGESTION_CONTROL";
        case -15: return "QUICHE_ERR_STREAM_STOPPED";
        case -16: return "QUICHE_ERR_STREAM_RESET";
        case -17: return "QUICHE_ERR_ID_LIMIT";
        case -18: return "QUICHE_ERR_OUT_OF_IDENTIFIERS";
        case -19: return "QUICHE_ERR_KEY_UPDATE";
        case -20: return "QUICHE_ERR_CRYPTO_BUFFER_EXCEEDED";
        default: return "UNKNOWN_ERROR";
    }
}
