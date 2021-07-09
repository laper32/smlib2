# SourceMod Library 2

## Introduction
The library to simplify SourceMod plugins development.

For native language reader, you can choose the table below for a better reading.
|Language|Link|
|--------|----|
|en-US|[Link](./README.md)|
|zh-CN|[Link](./README_zhCN.md)|

Highlights of the library
- Less dependencies (Only requires DHook, but you should install it at first)
- Wide covered (You can find most of the functions what you want to use here)
- Safe to use (You can use it directly without considering any issue about crashing/etc)

## Available games
|Game|Status|
|----|------|
|CS:GO|√|
|Others|-|
```
√: Tested, and OK
×: Not supported
-: Unknown (Further test required)
```

## Quick start
Before using this library, you must ensure that your SourceMod version satisfies the following condition:

**1.10.6480+**
> At least your compiler version is 1.10

I recommend you using 6502+ to use, and stay in the version of 1.10.
> Not recommend you using 1.11+ due to many bugs, and they are unexpected.

At the beginning of your `.sp` file, please specify with following:
```c
#pragma semicolon 1
#pragma newdecls required
```

Then, includes the following pre-requirement lib:
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
```

Next, include the lib
```c
#include <smlib2>
```

By combine of above, it should be looked like this:
```c
#include <sourcemod>
#include <sdktools>
#include <sdkhooks>

#include <dhooks>
// #include <PTaH> // Optional for you

// #include <cstrike>
// #include ...

#include <smlib2>
```

From now on, everything is set, you can enjoy it!

## Contributing
Yes, you are welcomed for contributing the library, but you need to keep the author of the project.

## Kind regards
|Author|Project|
|----|----|
|[@Kxnrl](https://www.github.com/Kxnrl)|[sourcemod-utils](https://www.github.com/Kxnrl/sourcemod-utils)|
|[@qubka](https://github.com/qubka)|[Zombie-Plague](https://github.com/qubka/Zombie-Plague)|
|[@bcserv](https://github.com/bcserv)|[smlib](https://github.com/bcserv/smlib)|

And any other libraries what have collected for referencing.