#pragma once
#include<string>
class HttpRequest;
class HttpParser{
public:
    static HttpRequest httpRequestFromString(const std::string &message);
};