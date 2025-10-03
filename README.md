# TMADriver dual driver + UDP RLS1000 gateway (.dll)

This DLL accepts Common Protocol commands (existing TMA TCP path) and, optionally, forwards commands in binary RLS1000 format over UDP.

Usage:
- Default mode (Common Protocol over existing TCP):
  - Use `setScalesIp("<ip or host>")` and `setScalesPort(<port>)` as before.
- RLS1000 UDP mode:
  - Pass a URI-style endpoint to toggle UDP routing: `setScalesIp("udp://<ip or host>")` or `setScalesIp("rls://<ip or host>")`.
  - Then set port via `setScalesPort(<udp_port>)`.

Notes:
- Current UDP implementation contains stubs for many commands and a minimal `sendConstTMT` datagram skeleton. Extend frames per the RLS1000 spec.
- `getException` returns transport-specific errors when UDP mode is enabled.
