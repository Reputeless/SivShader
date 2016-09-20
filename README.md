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

### サンプルシェーダ 1
```cpp
float4 PS(float4 position : SV_POSITION, float2 uv : TEXCOORD0) : SV_Target
{
	return float4(uv, 1, 1);
}
```

### サンプルシェーダ 2
```cpp
float4 PS(float4 position : SV_POSITION, float2 uv : TEXCOORD0) : SV_Target
{
	float d = 1.0 - distance(position.xy, g_mouse) / 200;
	
	if (g_leftPressed)
	{
		d = (d > 0.0);
	}

	return float4(d, d, d, 1) * texture0.Sample(sampler0, uv);
}
```

### サンプルシェーダ 3
```cpp
float4 PS(float4 position : SV_POSITION, float2 uv : TEXCOORD0) : SV_Target
{
	const float2 p = (position.xy - g_resolution / 2) / min(g_resolution.x, g_resolution.y);
	
	float3 c = float3(0, 0, 0);
	
	for (int i = 0; i < 20; ++i)
	{
		const float x = 0.4 * cos(2.0 * 3.14 * i / 20);
		const float y = 0.4 * sin(2.0 * 3.14 * i / 20);
		c += 0.01 / (distance(p, float2(x, y))) * float3(1, 1, 1);
	}

	return float4(c,1);
}
```

### サンプルシェーダ 4
```cpp

```
