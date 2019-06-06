#pragma once
#include<functional>
using ReadCallBack = std::function<void()>;
using WriteCallBack = std::function<void()>;
using ErrorCallBack = std::function<void()>;