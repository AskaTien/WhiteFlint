#pragma once

#include <winrt/base.h>
#include <winrt/Windows.Foundation.h>
#include <winrt/Windows.Storage.h>
#include <winrt/Windows.Storage.Streams.h>
#include <winrt/Windows.ApplicationModel.h>

#include <ppltasks.h>	// For create_task

namespace DX
{
	inline void ThrowIfFailed(HRESULT hr)
	{
		winrt::check_hresult(hr);
	}

	// Function that reads from a binary file asynchronously.
	inline Concurrency::task<std::vector<byte>> ReadDataAsync(const std::wstring& filename)
	{
		using namespace winrt::Windows::Foundation;
		using namespace winrt::Windows::Storage;
		using namespace Concurrency;

		auto folder = winrt::Windows::ApplicationModel::Package::Current().InstalledLocation();

		return create_task([&]
			{
				return folder.GetFileAsync(winrt::hstring(filename.c_str()));
			}).then([](IAsyncOperation<StorageFile> file)
				{
					return FileIO::ReadBufferAsync(file.GetResults());
				}).then([](IAsyncOperation<Streams::IBuffer> fileBuffer) -> std::vector<byte>
					{
						std::vector<byte> returnBuffer;
						returnBuffer.resize(fileBuffer.GetResults().Length());
						std::vector<byte> bytes(returnBuffer.data(), returnBuffer.data() + fileBuffer.GetResults().Length());
						Streams::DataReader::FromBuffer(fileBuffer.GetResults()).ReadBytes(bytes);
						return returnBuffer;
					});
	}

	// Converts a length in device-independent pixels (DIPs) to a length in physical pixels.
	inline float ConvertDipsToPixels(float dips, float dpi)
	{
		static const float dipsPerInch = 96.0f;
		return floorf(dips * dpi / dipsPerInch + 0.5f); // Round to nearest integer.
	}

#if defined(_DEBUG)
	// Check for SDK Layer support.
	inline bool SdkLayersAvailable()
	{
		HRESULT hr = D3D11CreateDevice(
			nullptr,
			D3D_DRIVER_TYPE_NULL,       // There is no need to create a real hardware device.
			0,
			D3D11_CREATE_DEVICE_DEBUG,  // Check for the SDK layers.
			nullptr,                    // Any feature level will do.
			0,
			D3D11_SDK_VERSION,          // Always set this to D3D11_SDK_VERSION for Microsoft Store apps.
			nullptr,                    // No need to keep the D3D device reference.
			nullptr,                    // No need to know the feature level.
			nullptr                     // No need to keep the D3D device context reference.
		);

		return SUCCEEDED(hr);
	}
#endif
}
