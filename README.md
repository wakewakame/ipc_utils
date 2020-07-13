# オレオレIPC通信備忘録
boostのmessage_queueを使ってIPC通信を行うデモ。  

## Ubuntu
```
$ sudo apt install cmake make gcc wget git
$ git clone https://github.com/wakewakame/ipc_utils
$ cd ipc_utils
$ mkdir build && cd build
$ cmake ..
$ make
$ ./ipc_utils
```

## MacOS
Xcodeが必要かもしれない。  
```
$ brew install cmake make wget git
$ git clone https://github.com/wakewakame/ipc_utils
$ cd ipc_utils
$ mkdir build && cd build
$ cmake ..
$ make
$ ./ipc_utils
```

## Windows
Git、CMake、Visual Studioが必要。  
これら全てchocolateyでインストールできたはず。  
```
> git clone https://github.com/wakewakame/ipc_utils
> cd ipc_utils
> mkdir build && cd build
> cmake ..
```
buildディレクトリ内にipc_utils.slnが生成されるので、Visual Studioで開いてビルドする。  
