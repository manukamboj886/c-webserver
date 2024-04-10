#include <string>
#include <sstream>
#include <fstream>
#include <iostream>
#include <vector>
#include <iterator>
#include "WebServer.h"

void WebServer::onMessageReceived(int clientSocket, const char* msg, int length) {
    std::istringstream iss(msg);
    std::vector<std::string> parsed((std::istream_iterator<std::string>(iss)), std::istream_iterator<std::string>());

    std::string content = "<h1>404 Not Found</h1>";
    std::string htmlFile = "/index.html";
    int errorCode = 404;

    if (parsed.size() >= 3 && parsed[0] == "GET") {
        htmlFile = parsed[1];
        if (htmlFile == "/") {
            htmlFile = "/index.html";
        }
        else if (htmlFile == "/signup") {
            htmlFile = "/signup.html";
        }
    }

    if (parsed.size() >= 2 && parsed[0] == "POST" && parsed[1] == "/add-login") {
        std::string requestBody(msg, length);
        size_t endOfHeaders = requestBody.find("\r\n\r\n");
        if (endOfHeaders != std::string::npos) {
            requestBody = requestBody.substr(endOfHeaders + 4); 

            size_t usernameStart = requestBody.find("username=");
            size_t usernameEnd = requestBody.find_first_of("&=", usernameStart + 9);
            std::string username = requestBody.substr(usernameStart + 9, usernameEnd - usernameStart - 9);

            size_t passwordStart = requestBody.find("password=");
            std::string password = requestBody.substr(passwordStart + 9);

            std::ofstream file("signup_credentials.txt", std::ios::app);
            if (file.is_open()) {
                file << "Username: " << username << ", Password: " << password << std::endl;
                file.close();
                std::cout << "Credentials stored successfully." << std::endl;
            }
            else {
                std::ofstream errorLog("error.log", std::ios::app);
                if (errorLog.is_open()) {
                    errorLog << "Failed to open file: signup_credentials.txt" << std::endl;
                    errorLog.close();
                }
                std::cerr << "Failed to open file: signup_credentials.txt" << std::endl;
            }

            std::string redirectUrl = "/signup-success.html";
            std::ostringstream oss;
            oss << "HTTP/1.1 302 Found\r\n";
            oss << "Location: " << redirectUrl << "\r\n";
            oss << "Content-Length: 0\r\n";
            oss << "\r\n";
            std::string output = oss.str();
            int size = output.size() + 1;
            sendToClient(clientSocket, output.c_str(), size);
            return;
        }
    }

    std::string filePath = ".\\wwwroot" + htmlFile;
    std::ifstream f(filePath);

    if (f.is_open()) {
        std::string str((std::istreambuf_iterator<char>(f)), std::istreambuf_iterator<char>());
        content = str;
        errorCode = 200;
    }
    else {
        std::ofstream errorLog("error.log", std::ios::app);
        if (errorLog.is_open()) {
            errorLog << "Failed to open file: " << filePath << std::endl;
            errorLog.close();
        }
        std::cerr << "Failed to open file: " << filePath << std::endl;
    }
    f.close();

    std::ostringstream oss;
    oss << "HTTP/1.1 " << errorCode << " OK\r\n";
    oss << "Cache-Control: no-cache, private\r\n";
    oss << "Content-Type: text/html\r\n";
    oss << "Content-Length: " << content.size() << "\r\n";
    oss << "\r\n";
    oss << content;
    std::string output = oss.str();
    int size = output.size() + 1;
    sendToClient(clientSocket, output.c_str(), size);
}

void WebServer::onClientConnected(int clientSocket) {
    std::ofstream connectionLog("connection.log", std::ios::app);
    if (connectionLog.is_open()) {
        connectionLog << "Client connected: " << clientSocket << std::endl;
        connectionLog.close();
    }
}

void WebServer::onClientDisconnected(int clientSocket) {
    std::ofstream connectionLog("connection.log", std::ios::app);
    if (connectionLog.is_open()) {
        connectionLog << "Client disconnected: " << clientSocket << std::endl;
        connectionLog.close();
    }
}