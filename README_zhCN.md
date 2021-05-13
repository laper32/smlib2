# smlib2

## 简介
SourceMod Library 2

该库旨在于简化SM插件开发流程

本库两点
- 依赖少（只需要DHook，然而这个扩展是基础控件）
- 覆盖广（几乎你想要的都能在这里找到）
- 使用安全（你不需要考虑可能的炸服务端问题）
  
## 支持的游戏
|游戏|状态|
|----|------|
|CS:GO|√|
|Others|-|
```
√: 测试通过，且支持
×: 不支持
-: 未知(还需更多测试)
```

## 快速开始
在使用该库之前，请确保你的SM编译器版本至少在该版本或以上：

 **1.10.6480** 

> 至少大版本是1.10

建议你使用6502版本或以上，以及锁版本在1.10
> - 不考虑1.10以下的版本
> - 目前来说不推荐1.11，因为现在的bug实在是太多了。

现在，假设你的检查完成了，我们打开一个文件。

在最开始的地方，写下如下的预处理内容：
```c
#pragma semicolon 1
#pragma newdecls required
```

然后，写入如下内容
```c
#include <sourcemod>
#include <sdktools>
#include <sdkhooks>

#include <dhooks>
// #include <PTaH> // Optional for you

// #include <cstrike>
// #include ...
```

下一步，引入该库
```c
#include <smlib2>
```

现在把上面的整合到一起，看起来是这样的：
```c
#pragma semicolon 1
#pragma newdecls required

#include <sourcemod>
#include <sdktools>
#include <sdkhooks>

#include <dhooks>
// #include <PTaH> // Optional for you

// #include <cstrike>
// #include ...

#include <smlib2>
```

到目前为止，一切都弄好了，你现在可以安心做你的开发了。

## 维护
是的，我们很欢迎你来帮忙维护该库，只不过请保留对应的版权信息。

## 特别感谢
|作者|项目|
|----|----|
|[@Kxnrl](https://www.github.com/Kxnrl)|[sourcemod-utils](https://www.github.com/Kxnrl/sourcemod-utils)|
|[@qubka](https://github.com/qubka)|[Zombie-Plague](https://github.com/qubka/Zombie-Plague)|
|[@bcserv](https://github.com/bcserv)|[smlib](https://github.com/bcserv/smlib)|

还有许多参考项目，但未在此处列出。