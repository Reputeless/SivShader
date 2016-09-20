# SivShader

### 使い方
- Main.cpp と Shader.hlsl を Siv3D プロジェクトにコピー

### 操作
- HLSL ファイルを更新するとシェーダを更新
- 画像ファイルを画面にドロップするとテクスチャを更新
- スペースキーを押すと `g_time` をリセット

### シェーダ入力

|型|名前|説明|
|----|----|----|
|float2|g_resolution|ウィンドウの解像度|
|float|g_time|経過時間（秒）|
|float|g_frame|経過フレーム|
|float2|g_mouse|マウス座標|
|float|g_leftPressed|左クリック|
|float|g_rightPressed|右クリック|
|float2|g_textureResolution|テクスチャのサイズ|
|Texture2D|texture0|テクスチャ|
|SamplerState|sampler0|サンプラー|
