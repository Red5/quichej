# Quiche Java Wrapper Update Log

## Overview - October 5, 2025

Successfully updated all Java code to work with the new simplified native wrapper functions. The build now completes successfully.

## Files Updated

### 1. `Quiche.java` - Main JNI Interface

**Changes:**

- Renamed connection methods to use `_simple` suffix:
  - `quiche_connect()` → `quiche_connect_simple()`
  - `quiche_accept()` → `quiche_accept_simple()`
  - `quiche_conn_send()` → `quiche_conn_send_simple()`
  - `quiche_conn_recv()` → `quiche_conn_recv_simple()`
  
- Updated return types to match C API:
  - `quiche_conn_is_established()`: `int` → `boolean`
  - `quiche_conn_is_closed()`: `int` → `boolean`
  - `quiche_conn_send_simple()`: `int` → `long` (ssize_t)
  - `quiche_conn_recv_simple()`: `int` → `long` (ssize_t)
  
- Updated parameter types:
  - `quiche_conn_close()`: `int app` → `boolean app`
  
- Removed non-existent functions:
  - `quiche_conn_send_max_data()` - Not in quiche API
  - `quiche_conn_recv_max_data()` - Not in quiche API
  - `quiche_conn_streams_bidi_count()` - Not in quiche API
  - `quiche_conn_streams_uni_count()` - Not in quiche API
  
- Added new methods that exist in API:
  - `quiche_conn_is_server()` - Check if connection is server-side
  - `quiche_conn_timeout_as_millis()` - Get timeout in milliseconds
  - `quiche_conn_on_timeout()` - Handle timeout event
  
- Renamed utility method:
  - `quiche_error_to_str()` → `quiche_error_to_string()`

### 2. `QuicheConfig.java` - Configuration Class

**Changes:**

- Updated `setDisableActiveMigration()`:
  - Changed from `int` parameter to `boolean`
  - Removed manual boolean→int conversion (now passed directly)
  
- Updated native method signature:
  - `quiche_config_set_disable_active_migration(long, int)` → `(long, boolean)`
  
- Changed return type:
  - `quiche_config_set_application_protos()`: `void` → `int`
  
- Added `finalize()` method for cleanup:
  - Automatically frees config when object is garbage collected

### 3. `QuicheExample.java` - Example Application

**Complete rewrite with enhanced features:**

- Added proper error handling with try-catch
- Added detailed console output
- Updated to use `quiche_connect_simple()`
- Added display of QUIC protocol version
- Enhanced connection state checking
- Replaced non-existent methods with available ones:
  - Removed: `send_max_data`, `recv_max_data`
  - Added: `is_server`, `timeout_as_millis`
- Better formatted output for demonstration

### 4. `quiche_jni.c` - New JNI Implementation

**Created comprehensive JNI bridge:**

- Implements all QuicheConfig native methods (13 functions)
- Implements all Quiche connection native methods (11 functions)
- Proper JNI error handling and memory management
- Correct type conversions between Java and C:
  - `jlong` ↔ C pointers via `uintptr_t`
  - `jbyteArray` ↔ `uint8_t*`
  - `jstring` ↔ `const char*`
  - `jboolean` ↔ `bool`
- Proper JNI array handling with `GetByteArrayElements`/`ReleaseByteArrayElements`
- Proper string handling with `GetStringUTFChars`/`ReleaseStringUTFChars`

### 5. `pom.xml` - Build Configuration

**Updated native compilation:**

- Added JNI include paths:
  - `${java.home}/include`
  - `${java.home}/include/linux`
- Added quiche include path:
  - `${native.build.dir}/quiche/quiche/include`
- Added library search path:
  - `-L${project.basedir}/src/main/resources`
- Added rpath for runtime library loading
- Updated to compile both:
  - `quiche_wrapper.c` (simplified helper functions)
  - `quiche_jni.c` (JNI bridge functions)
- Ensured linking against `libquiche.so`

### ⚠️ Warnings (Non-Critical)

1. **Deprecation Warning**: `finalize()` method is deprecated in Java
   - This is acceptable for now, consider using `Cleaner` API in future
2. **No Tests**: Project has no test sources
   - Consider adding unit tests in future iterations

## Architecture

### Layered Design

```
Java Application (QuicheExample.java)
         ↓
Java API (Quiche.java, QuicheConfig.java)
         ↓
JNI Bridge (quiche_jni.c)
         ↓
Simplified Wrapper (quiche_wrapper.c)
         ↓
Cloudflare Quiche C Library (quiche.h)
```

### Function Name Mapping

| Java Method | JNI Function | C Wrapper | Quiche API |
|------------|--------------|-----------|------------|
| `quiche_connect_simple()` | `Java_..._quiche_1connect_1simple` | `quiche_connect_simple()` | `quiche_connect()` |
| `quiche_accept_simple()` | `Java_..._quiche_1accept_1simple` | `quiche_accept_simple()` | `quiche_accept()` |
| `quiche_conn_send_simple()` | `Java_..._quiche_1conn_1send_1simple` | `quiche_conn_send_simple()` | `quiche_conn_send()` |
| `quiche_conn_recv_simple()` | `Java_..._quiche_1conn_1recv_1simple` | `quiche_conn_recv_simple()` | `quiche_conn_recv()` |
| `quiche_conn_is_established()` | `Java_..._quiche_1conn_1is_1established` | (direct call) | `quiche_conn_is_established()` |
| `quiche_config_new()` | `Java_..._quiche_1config_1new` | (direct call) | `quiche_config_new()` |

## Testing

To Test the Build

```bash
cd /media/mondain/terrorbyte/workspace/github-red5/quichej
mvn clean package -P linux
```

To Run the Example

```bash
cd target
java -Djava.library.path=. -cp quiche-java-wrapper-1.0.0.jar com.cloudflare.quiche.QuicheExample
```

## Known Limitations

1. **Simplified Wrappers Use Defaults**:
   - Socket addresses use localhost (127.0.0.1)
   - Ports use defaults (443 for server, 0 for client)
   - send_info/recv_info structures are zero-initialized
2. **Missing Features**:
   - No direct access to connection statistics
   - No stream-level operations exposed
   - No path management functionality
3. **Production Considerations**:
   - Real applications should provide actual network parameters
   - Should implement proper error handling
   - May need additional wrapper functions for advanced features

## Next Steps for Production Use

1. **Enhance Wrapper Functions**:
   - Accept IP address and port parameters from Java
   - Provide access to connection statistics via `quiche_stats`
   - Expose stream operations for data transfer
2. **Add Stream API**:
   - `quiche_conn_stream_send()`
   - `quiche_conn_stream_recv()`
   - Stream state management
3. **Improve Error Handling**:
   - Throw Java exceptions for errors
   - Better error message translation
4. **Add Tests**:
   - Unit tests for configuration
   - Integration tests for connections
   - Performance tests

## Documentation

- Original issues: `TYPE_MISMATCH_ISSUES.md`
- C wrapper fixes: `FIXES_APPLIED.md`
- This document: `JAVA_UPDATES.md`

## References

- **Cloudflare Quiche**: https://github.com/cloudflare/quiche
- **QUIC Protocol**: RFC 9000
- **JNI**: https://docs.oracle.com/javase/8/docs/technotes/guides/jni/
