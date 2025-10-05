package com.cloudflare.quiche;

public class QuicheExample {
    public static void main(String[] args) {
        System.out.println("Quiche Java Wrapper Example");
        System.out.println("============================");
        
        try {
            // Create a configuration with QUIC version 1
            QuicheConfig config = new QuicheConfig(Quiche.QUICHE_PROTOCOL_VERSION);
            
            // Configure the connection parameters
            config.setInitialMaxStreamsBidi(100);
            config.setInitialMaxStreamsUni(100);
            config.setMaxIdleTimeout(30000); // 30 seconds
            config.setInitialMaxData(10000000); // 10MB
            
            System.out.println("Configuration created successfully");
            System.out.println("QUIC Protocol Version: 0x" + Integer.toHexString(Quiche.QUICHE_PROTOCOL_VERSION));
            
            // Create a connection using simplified wrapper
            byte[] scid = "test_scid_1234567890".getBytes();
            long conn = Quiche.quiche_connect_simple("example.com", scid, scid.length, config.getNativePtr());
            
            if (conn != 0) {
                System.out.println("Connection pointer created: " + conn);
                
                // Check connection state
                boolean established = Quiche.quiche_conn_is_established(conn);
                boolean closed = Quiche.quiche_conn_is_closed(conn);
                boolean isServer = Quiche.quiche_conn_is_server(conn);
                
                System.out.println("Connection established: " + established);
                System.out.println("Connection closed: " + closed);
                System.out.println("Is server: " + isServer);
                
                // Get connection timeout
                long timeout = Quiche.quiche_conn_timeout_as_millis(conn);
                System.out.println("Timeout (ms): " + timeout);
                
                // Example of sending data (this is a simplified example)
                byte[] data = "Hello QUIC!".getBytes();
                long sent = Quiche.quiche_conn_send_simple(conn, data, data.length);
                System.out.println("Sent result: " + sent + " (negative means error or DONE)");
                
                // Clean up
                Quiche.quiche_conn_free(conn);
                System.out.println("Connection freed successfully");
            } else {
                System.err.println("Failed to create connection");
            }
            
        } catch (Exception e) {
            System.err.println("Error: " + e.getMessage());
            e.printStackTrace();
        }
        
        System.out.println("============================");
        System.out.println("Example completed");
    }
}