#pragma once
#include <string>
#include <vector>
#include <stdexcept>
#ifdef _WIN32
#include <winsock2.h>
#include <ws2tcpip.h>
#pragma comment(lib, "Ws2_32.lib")
#endif

class RlsUdpClient {
public:
    RlsUdpClient() : m_port(0)
#ifdef _WIN32
    , m_socket(INVALID_SOCKET)
#endif
    {}

    ~RlsUdpClient() { disconnect(); }

    void setScalesIp(const std::string& ip) { m_ip = ip; }
    void setScalesPort(int port) { m_port = port; }

    void setSleep(int milliseconds) { m_sleepMs = milliseconds; }

    void connectToScales();
    void disconnect();

    // High-level operations mirrored from TMAClient so CConnector can route
    void addPLUToScales(/*const*/ int /*placeholder*/);
    void bindPLUToKey(/*const*/ int /*placeholder*/);
    void setTime(int year, int month, int day, int hour, int minute, int seconds);
    void clearPLU(int number);

    std::string getTime();
    std::string getInfo();
    std::string getMAC();
    std::string getScalesAccaunt(int number);

    std::string sendConstTMT(int fieldNumber, const std::string& value);

    const std::string& getException() const { return m_lastError; }

private:
    std::string m_ip;
    int m_port;
    int m_sleepMs {0};
    std::string m_lastError;

#ifdef _WIN32
    SOCKET m_socket;
    sockaddr_in m_addr { };
#endif

    void setError(const std::string& err) { m_lastError = err; }
    bool validateEndpoint();
    bool sendBytes(const std::vector<unsigned char>& payload);
    static std::vector<unsigned char> cp1251Encode(const std::string& utf8);
};
