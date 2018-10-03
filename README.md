```
shopt -s extglob
```

```
rm -rf !(Qt5Cored.dll|Qt5Guid.dll|Qt5Widgetsd.dll)
```

```
cmake -G "Visual Studio 15 2017 Win64" -DCUDA_TOOLKIT_ROOT_DIR="C:\Program Files\NVIDIA GPU Computing Toolkit\CUDA\v9.2" -T v140,cuda=9.2 ..
```