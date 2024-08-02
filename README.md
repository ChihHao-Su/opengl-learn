# opengl-learn
文盲學 OpenGL。

## 目標
- 融合 Dear ImGUI。
- 使用 FB 實現後處理。
- 它必須理論上可移植。
	- 如果可能，盡量避免依賴平臺 API。
- 它必須是現代的，開發和編譯必須很簡單。
	- 使用**標準的**現代 C++。
	- 使用現代 CMake。
	- 使用包管理器管理依賴。

## 構建
```sh
vcpkg install .
cmake --preset=default
```

