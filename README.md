[![C++ CI](https://github.com/JustCallMeRay/UDP_Matchmaking/actions/workflows/c-cpp.yml/badge.svg)](https://github.com/JustCallMeRay/UDP_Matchmaking/actions/workflows/c-cpp.yml)

[![Run on Repl.it](https://replit.com/badge/github/JustCallMeRay/UDP_Matchmaking)](https://replit.com/new/github/JustCallMeRay/UDP_Matchmaking)
# UDP_Matchmaking

<sub>
A small note: I often mention web3 in this page, by this I mean a decentralised network in which systems are connected to eachother by UDP and avoid a regular TCP, server to client, platform based network. I am avoiding talking about cyber security, and password protection for web3 as the code doesnt relate to this, if you are looking for this I would recommend [GUN.js], it's a non-blockchain decentralised network libary aimed at browser applications. </sub>

## Web3 style matchmaking system, 

After learning about UDP/serverless gameplay netcode like in for honour, I wanted to create a method of (elo based) matchmaking which allows for a game to run comlpetely serverless.* Many games see how player bases often outlast the expected lifetime of a game, resulting in a difficult decision for publishers; continue hosting a server which is unlikely to turn a profit or close the servers, suffering bad press and effectively removing a product from sale. Including the ability for a user to host their own server extends the lifetime of the game (eg: Quake, Counter Strike, Minecraft) and often reduces the problem but not emlimnate it. (see Team Fortress' current situatuion and the "#savetf2" movement.) Not to mention the cost pushed onto the host-ers, sometimes resulting in shady/grey/black market servers like pay to win (see Minecraft's terms of service) which reflects badly on the publishers and is not profitable. 

Thus UDP/net/web3 style netcode is the ultimate solution.



\* One or more inital node(s) need to be always be availble for an inital connection but effectively acts as a proxy and should require a similar amount of compute. 

[GUN.js]: <https://github.com/amark/gun>
