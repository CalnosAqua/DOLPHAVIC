/**	@file	SD3D12Resource.cpp
 *	@brief	リソース
 */
#include "d3d12/SD3D12Resource.hpp"
#include "d3d12/CD3D12Device.hpp"

namespace dlav {
	SD3D12Resource::SD3D12Resource(SD3D12Resource&& arg) noexcept :
		SD3D12Resource()
	{
		rsrc = arg.rsrc;
		arg.rsrc = nullptr;
	}

	SD3D12Resource& SD3D12Resource::operator=(SD3D12Resource&& rhs) noexcept {
		safe_release(rsrc);

		rsrc = rhs.rsrc;
		rhs.rsrc = nullptr;

		return *this;
	}

	SD3D12Resource::SD3D12Resource() noexcept :
		cpu{ 0U },
		gpu{ 0U },
		rsrc(nullptr)
	{}

	SD3D12Resource::~SD3D12Resource() noexcept {
		safe_release(rsrc);
	}

	ID3D12Resource2* SD3D12Resource::operator->() const noexcept {
		return rsrc;
	}
}