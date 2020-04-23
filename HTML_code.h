#pragma once
#include <iostream>
#include <fstream>
#include <winsock.h>
#include <stdio.h>
#include <sstream>
#include <string>
#include <windows.h>
#include <WinInet.h>
#include <vector>                                 
#include <conio.h> 
#include <algorithm>
#include "Sravnenie_HTML.h"

#pragma comment (lib, "Wininet.lib")

using namespace std;

enum EProtocol { P_HTTP, P_HTTPS };

// convert strings
wstring StringToWstring(const std::string& _str)
{
    wstring wstr;
    wstr.assign(_str.begin(), _str.end());
    return wstr;
}


std::string StringReplacer(const std::string& inputStr, const std::string& src, const std::string& dst)
{
    std::string result(inputStr);

    size_t pos = result.find(src);
    while (pos != std::string::npos) {
        result.replace(pos, src.size(), dst);
        pos = result.find(src, pos);
    }
    return result;
}

// send request
string SendInetRequest(const EProtocol _eProtocol, const wstring& _server, const wstring& _page, const wstring& _params = L"")
{
    char szData[1024]; string recvStr;

    // initialize WinInet
    HINTERNET hInternet = ::InternetOpen(TEXT("WinInet Test"), INTERNET_OPEN_TYPE_PRECONFIG, NULL, NULL, 0);
    if (hInternet != NULL) {
        INTERNET_PORT port = NULL;  DWORD flags = NULL;

        switch (_eProtocol) {
        case P_HTTP:
            port = INTERNET_DEFAULT_HTTP_PORT;
            flags = INTERNET_FLAG_KEEP_CONNECTION;
            break;
        case P_HTTPS:
            port = INTERNET_DEFAULT_HTTPS_PORT;
            flags = INTERNET_FLAG_SECURE;
            break;
        default:
            return NULL;
        }

        // open HTTP session
        HINTERNET hConnect = ::InternetConnect(hInternet, _server.c_str(), port, NULL, NULL, INTERNET_SERVICE_HTTP, 0, 1);
        if (hConnect != NULL)
        {
            wstring request;     wstring method = L"GET";
            wstring headers;      string data;

            request = _page + (_params.empty() ? L"" : (L"?" + _params));

            // open request
            HINTERNET hRequest = ::HttpOpenRequest(hConnect, method.c_str(), (LPCWSTR)request.c_str(), NULL, NULL, 0, flags, 1);
            if (hRequest != NULL) {
                // send request
                BOOL isSend = ::HttpSendRequest(hRequest, headers.c_str(), headers.length(), (LPVOID)data.c_str(), data.length());

                if (isSend) {
                    for (;;) {
                        // reading data
                        DWORD dwByteRead;
                        BOOL isRead = ::InternetReadFile(hRequest, szData, sizeof(szData) - 1, &dwByteRead);

                        // break cycle if error or end
                        if (isRead == FALSE || dwByteRead == 0)
                            break;

                        // saving result
                        recvStr.append(szData, dwByteRead);
                        string res = StringReplacer(recvStr, "\n", " ");
                        recvStr = res;
                        string res2 = StringReplacer(recvStr, "\t", " ");
                        recvStr = res2;
                        string res3 = StringReplacer(recvStr, "\r", " ");
                        recvStr = res3;

                        szData[dwByteRead] = 0;
                    }
                }
                // close request
                ::InternetCloseHandle(hRequest);
            }
            // close session
            ::InternetCloseHandle(hConnect);
        }
        // close WinInet
        ::InternetCloseHandle(hInternet);
    }
    //std::cout << "\n" << recvStr;
    return recvStr;
}
