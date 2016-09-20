# include <Siv3D.hpp>

struct ShaderInput
{
	Float2 resolution;
	float  time;
	float  frame;
	Float2 mouse;
	float  leftPressed;
	float  rightPressed;
	Float4 textureResolution;
};

void Main()
{
	const FilePath shaderPath = L"Shader.hlsl";
	Texture texture(Image(640, 480, Palette::White));
	ConstantBuffer<ShaderInput> cb;

	PixelShader ps(shaderPath);
	if (!ps)
	{
		return;
	}

	FileMonitor monitor(shaderPath);
	Stopwatch stopwatch(true);

	while (System::Update())
	{
		if (monitor.hasChanged() && monitor.retrieve() == FileAction::Modified)
		{
			if (PixelShader tmp{ shaderPath })
			{
				std::swap(tmp, ps);
				stopwatch.restart();
			}
		}

		if (Dragdrop::HasItems())
		{
			if (Texture tmp{ Image(Dragdrop::GetFilePaths()[0]).fit(1280, 720, false) })
			{
				std::swap(tmp, texture);
				Window::Resize(texture.size);
				stopwatch.restart();
			}
		}

		if (Input::KeySpace.clicked)
		{
			stopwatch.restart();
		}

		cb->resolution = Window::Size();
		cb->time = stopwatch.ms() / 1000.0f;
		cb->frame = static_cast<float>(System::FrameCount());
		cb->mouse = Mouse::Pos();
		cb->leftPressed = Input::MouseL.pressed;
		cb->rightPressed = Input::MouseR.pressed;
		cb->textureResolution = Float4(Float2(texture.size), 1, 1);

		Graphics2D::BeginPS(ps);
		{
			Graphics2D::SetConstant(ShaderStage::Pixel, 1, cb);
			texture.draw();
		}
		Graphics2D::EndPS();
	}
}
