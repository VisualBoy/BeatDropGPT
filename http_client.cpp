#include <windows.h>
#include <winhttp.h>
#include <string>
#include <thread>
#include <iostream>

#pragma comment(lib, "winhttp.lib")

class HttpClient {
public:
    static void SendAsyncRequest(const std::wstring& url, const std::wstring& apiKey, const std::wstring& prompt) {
        std::thread([=]() {
            HINTERNET hSession = WinHttpOpen(L"ChatGPT Plugin/1.0", WINHTTP_ACCESS_TYPE_DEFAULT_PROXY, WINHTTP_NO_PROXY_NAME, WINHTTP_NO_PROXY_BYPASS, 0);
            if (!hSession) {
                std::wcerr << L"Failed to open HTTP session." << std::endl;
                return;
            }

            HINTERNET hConnect = WinHttpConnect(hSession, L"api.openai.com", INTERNET_DEFAULT_HTTPS_PORT, 0);
            if (!hConnect) {
                std::wcerr << L"Failed to connect to server." << std::endl;
                WinHttpCloseHandle(hSession);
                return;
            }

            HINTERNET hRequest = WinHttpOpenRequest(hConnect, L"POST", url.c_str(), NULL, WINHTTP_NO_REFERER, WINHTTP_DEFAULT_ACCEPT_TYPES, WINHTTP_FLAG_SECURE);
            if (!hRequest) {
                std::wcerr << L"Failed to open HTTP request." << std::endl;
                WinHttpCloseHandle(hConnect);
                WinHttpCloseHandle(hSession);
                return;
            }

            std::wstring headers = L"Content-Type: application/json\r\nAuthorization: Bearer " + apiKey;
            std::wstring body = L"{\"prompt\": \"" + prompt + L"\", \"max_tokens\": 100}";

            BOOL bResults = WinHttpSendRequest(hRequest, headers.c_str(), -1, (LPVOID)body.c_str(), body.size() * sizeof(wchar_t), body.size() * sizeof(wchar_t), 0);
            if (!bResults) {
                std::wcerr << L"Failed to send HTTP request." << std::endl;
            } else {
                WinHttpReceiveResponse(hRequest, NULL);
                DWORD dwSize = 0;
                WinHttpQueryDataAvailable(hRequest, &dwSize);
                std::wstring response(dwSize / sizeof(wchar_t), 0);
                WinHttpReadData(hRequest, &response[0], dwSize, NULL);
                std::wcout << L"Response: " << response << std::endl;
            }

            WinHttpCloseHandle(hRequest);
            WinHttpCloseHandle(hConnect);
            WinHttpCloseHandle(hSession);
        }).detach();
    }
};
