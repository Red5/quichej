#ifndef QUICHE_WRAPPER_H
#define QUICHE_WRAPPER_H

#include <quiche.h>

#ifdef __cplusplus
extern "C" {
#endif

// Note: All structures and types are defined in quiche.h
// This wrapper provides simplified helper functions for JNI

// Helper function to create a simple connection without socket addresses
// Note: This is a simplified version - real usage requires proper socket addresses
quiche_conn* quiche_connect_simple(const char* server_name, const uint8_t* scid, size_t scid_len,
                                   quiche_config* config);

// Helper function to accept connection without all parameters
// Note: This is a simplified version - real usage requires proper socket addresses  
quiche_conn* quiche_accept_simple(const uint8_t* scid, size_t scid_len, quiche_config* config);

// Simplified send that handles send_info internally
ssize_t quiche_conn_send_simple(quiche_conn* conn, uint8_t* out, size_t out_len);

// Simplified recv that handles recv_info internally
ssize_t quiche_conn_recv_simple(quiche_conn* conn, uint8_t* buf, size_t buf_len);

// Utility function to convert error code to string
const char* quiche_error_to_string(int err);

#ifdef __cplusplus
}
#endif

#endif // QUICHE_WRAPPER_H
