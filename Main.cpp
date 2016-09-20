# include <Siv3D.hpp>

struct ShaderInput
{
	Float2 resolution;
	float  time;
	float  frame;
	Float2 mouse;
	float  leftPressed;
	float  rightPressed;
	Float2 textureResolution;
	Float2 _unused;
};

void Main()
{
	const FilePath shaderPath = L"Shader.hlsl";

	Texture texture(Image(640, 480, Palette::White));

	FileMonitor monitor(shaderPath);

	PixelShader ps(shaderPath);

	if (!ps)
	{
		return;
	}

	ConstantBuffer<ShaderInput> cb;

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

		cb->resolution	= Window::Size();
		cb->time		= stopwatch.ms() / 1000.0f;
		cb->frame		= static_cast<float>(System::FrameCount());
		cb->mouse		= Mouse::Pos();
		cb->leftPressed	= Input::MouseL.pressed;
		cb->rightPressed	= Input::MouseR.pressed;
		cb->textureResolution	= texture.size;

		Graphics2D::BeginPS(ps);
		{
			Graphics2D::SetConstant(ShaderStage::Pixel, 1, cb);

			texture.draw();
		}
		Graphics2D::EndPS();
	}
}
