/**
 * @platform:
 * @problem: process of production
 * @version:
 * @author: VenusHui
 * @date: 2022-12-08
 */

#include <bits/stdc++.h>
#include "production.h"

int main()
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    // 同时实现原型模式和空对象模式
    hjh::CoreFactory *coreFactory = new hjh::CoreFactory();
    hjh::Client::ClientCode(*coreFactory); // 执行客户端代码段
    delete coreFactory;

    std::cout << '\n';

    return 0;
}
