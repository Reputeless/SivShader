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
	Window::SetTitle(L"SivShader");
	Window::SetStyle(WindowStyle::Sizeable);
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
	bool hasError = false;

	while (System::Update())
	{
		if (Input::KeySpace.clicked || (monitor.hasChanged() && monitor.retrieve() != FileAction::None))
		{
			if (PixelShader tmp{ shaderPath })
			{
				std::swap(tmp, ps);
				stopwatch.restart();
				System::ResetFrameCount();
				hasError = false;
			}
			else
			{
				hasError = true;
			}
		}

		if (Dragdrop::HasItems())
		{
			if (Texture tmp{ Dragdrop::GetFilePaths()[0] })
			{
				std::swap(tmp, texture);
				stopwatch.restart();
				System::ResetFrameCount();
			}
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
			Window::ClientRect()(texture).draw();
		}
		Graphics2D::EndPS();

		if (hasError)
		{
			Window::ClientRect().draw(ColorF(0.8, 0.4, 0.2, Sin(stopwatch.ms() / 200.0)*0.5 + 0.5));
		}
	}
}
