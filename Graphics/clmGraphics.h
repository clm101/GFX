#ifndef CLM_GRAPHICS_H
#define CLM_GRAPHICS_H

#include "ExceptionBase.h"
#include "GraphicsDebugDefines.h"
#include "Windows.h"
#include "d3d11.h"
#include "Windows.Foundation.h"
#include "wrl\wrappers\corewrappers.h"
#include "wrl\client.h"
#include "dxgi1_3.h"
#include "Dxgi1_6.h"
#include <vector>
#include "DxgiInfoManager.h"
#include <d2d1.h>
#include <d2d1_1.h>

namespace mswrl = Microsoft::WRL;

class Graphics {
private:
	// Set up device
	// D3D11
	mswrl::ComPtr<IDXGIFactory> ptrFactory;
	mswrl::ComPtr<IDXGIAdapter> ptrAdapter;
	mswrl::ComPtr<ID3D11Device> ptrDevice;
	mswrl::ComPtr<IDXGISwapChain> ptrSwapChain;
	mswrl::ComPtr<ID3D11DeviceContext> ptrDeviceContext;
	mswrl::ComPtr<ID3D11RenderTargetView> ptrTarget;

	// Pixel Shader
	mswrl::ComPtr<ID3D11PixelShader> ptrPixelShader;
	mswrl::ComPtr<ID3DBlob> ptrPSBlob;
	mswrl::ComPtr<ID3DBlob> ptrPSErrorBlob;
	mswrl::ComPtr<ID3D11Buffer> ptrPSBuffer;

	// Vertex Shader
	mswrl::ComPtr<ID3D11VertexShader> ptrVertexShader;
	mswrl::ComPtr<ID3DBlob> ptrVSBlob;
	mswrl::ComPtr<ID3DBlob> ptrVSErrorBlob;
	mswrl::ComPtr<ID3D11Buffer> ptrVBuffer;
	mswrl::ComPtr<ID3D11InputLayout> ptrInputLayout;
	DB_INFO_MANAGER_DECL();
public:
	class GFXExceptionBase : public ExceptionBase {
		using ExceptionBase::ExceptionBase;
	public:
		static std::string getGfxErrorString(HRESULT) noexcept;
	};
	class GFXException : public GFXExceptionBase {
	private:
		HRESULT hrError;
		std::string strErrorMsg;
		std::string strInfoMsgs;
	public:
		GFXException(int, const char*, HRESULT, std::vector<std::string> = {}) noexcept;
		const char* getType() const noexcept override;
		const std::string& getErrorMsg() const noexcept;
		const std::string& getInfoMsgs() const noexcept;
		const char* what() const noexcept override;
	};

	Graphics(HWND);
	~Graphics();
	Graphics(const Graphics&) = delete;
	Graphics& operator=(const Graphics&) = delete;

	void BeginFrame(const double);
	void EndFrame();
	void ClearBuffer(const double);
};

#endif