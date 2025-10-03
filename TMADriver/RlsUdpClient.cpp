#include "RlsUdpClient.h"
#include <thread>

#ifdef _WIN32
static bool ensure_wsa_started() {
    static bool started = false;
    static WSADATA wsaData;
    if (!started) {
        if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
            return false;
        }
        started = true;
    }
    return true;
}
#endif

bool RlsUdpClient::validateEndpoint() {
    if (m_ip.empty() || m_port <= 0 || m_port > 65535) {
        setError("Invalid RLS UDP endpoint");
        return false;
    }
    return true;
}

void RlsUdpClient::connectToScales() {
#ifdef _WIN32
    if (!validateEndpoint()) return;
    if (!ensure_wsa_started()) { setError("WSAStartup failed"); return; }
    if (m_socket != INVALID_SOCKET) return; // already

    m_socket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if (m_socket == INVALID_SOCKET) { setError("socket() failed"); return; }

    ZeroMemory(&m_addr, sizeof(m_addr));
    m_addr.sin_family = AF_INET;
    m_addr.sin_port = htons(static_cast<u_short>(m_port));

    // Try numeric first
    if (inet_pton(AF_INET, m_ip.c_str(), &m_addr.sin_addr) != 1) {
        // resolve hostname
        addrinfo hints{}; hints.ai_family = AF_INET; hints.ai_socktype = SOCK_DGRAM; hints.ai_protocol = IPPROTO_UDP;
        addrinfo* result = nullptr;
        std::string portStr = std::to_string(m_port);
        if (getaddrinfo(m_ip.c_str(), portStr.c_str(), &hints, &result) == 0 && result) {
            memcpy(&m_addr, result->ai_addr, sizeof(sockaddr_in));
            freeaddrinfo(result);
        } else {
            setError("Failed to resolve host");
            closesocket(m_socket);
            m_socket = INVALID_SOCKET;
            return;
        }
    }
#else
    (void)0;
#endif
}

void RlsUdpClient::disconnect() {
#ifdef _WIN32
    if (m_socket != INVALID_SOCKET) {
        closesocket(m_socket);
        m_socket = INVALID_SOCKET;
    }
#endif
}

bool RlsUdpClient::sendBytes(const std::vector<unsigned char>& payload) {
#ifdef _WIN32
    if (m_socket == INVALID_SOCKET) {
        setError("Not connected");
        return false;
    }
    int sent = sendto(m_socket, reinterpret_cast<const char*>(payload.data()), static_cast<int>(payload.size()), 0,
                      reinterpret_cast<const sockaddr*>(&m_addr), sizeof(m_addr));
    if (sent != static_cast<int>(payload.size())) {
        setError("sendto() failed");
        return false;
    }
    if (m_sleepMs > 0) std::this_thread::sleep_for(std::chrono::milliseconds(m_sleepMs));
    return true;
#else
    (void)payload; setError("UDP not supported on this platform build"); return false;
#endif
}

// Placeholder: in absence of exact RLS1000 spec, we simply send the UTF-8 payload bytes as-is.
// Callers must pass CP1251 already if required by device. We expose a basic CP1251 stub for future use.
std::vector<unsigned char> RlsUdpClient::cp1251Encode(const std::string& utf8) {
    // For now, passthrough. Integrate real conversion if needed.
    return std::vector<unsigned char>(utf8.begin(), utf8.end());
}

void RlsUdpClient::addPLUToScales(int) {
    setError("RLS addPLUToScales not implemented");
}

void RlsUdpClient::bindPLUToKey(int) {
    setError("RLS bindPLUToKey not implemented");
}

void RlsUdpClient::setTime(int year, int month, int day, int hour, int minute, int seconds) {
    (void)year; (void)month; (void)day; (void)hour; (void)minute; (void)seconds;
    setError("RLS setTime not implemented");
}

void RlsUdpClient::clearPLU(int number) {
    (void)number; setError("RLS clearPLU not implemented");
}

std::string RlsUdpClient::getTime() {
    setError("RLS getTime not implemented");
    return std::string();
}

std::string RlsUdpClient::getInfo() {
    setError("RLS getInfo not implemented");
    return std::string();
}

std::string RlsUdpClient::getMAC() {
    setError("RLS getMAC not implemented");
    return std::string();
}

std::string RlsUdpClient::getScalesAccaunt(int number) {
    (void)number; setError("RLS getScalesAccaunt not implemented");
    return std::string();
}

std::string RlsUdpClient::sendConstTMT(int fieldNumber, const std::string& value) {
    if (!validateEndpoint()) return std::string();
    connectToScales();

    // Very minimalistic frame: [0x52 0x4C 0x53 0x31 'R''L''S''1'] [fieldNumber 1B] [lenHi lenLo] [payload]
    std::vector<unsigned char> payload;
    payload.reserve(4 + 1 + 2 + value.size());
    payload.push_back(0x52); payload.push_back(0x4C); payload.push_back(0x53); payload.push_back(0x31);
    payload.push_back(static_cast<unsigned char>(fieldNumber & 0xFF));
    const auto data = cp1251Encode(value);
    unsigned short len = static_cast<unsigned short>(data.size());
    payload.push_back(static_cast<unsigned char>((len >> 8) & 0xFF));
    payload.push_back(static_cast<unsigned char>(len & 0xFF));
    payload.insert(payload.end(), data.begin(), data.end());

    if (!sendBytes(payload)) return std::string();
    return std::string();
}
