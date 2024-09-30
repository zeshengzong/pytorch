#pragma once

#include <c10/core/Device.h>
#include <c10/core/Stream.h>
#include <c10/core/Allocator.h>
#include <ATen/core/Generator.h>
C10_DIAGNOSTIC_PUSH_AND_IGNORED_IF_DEFINED("-Wunused-parameter")
namespace at {

// AcceleratorHooksInterface is a shared interface provided by all
// accelerators to allow generic code.
// This inferface is hook-based as it corresponds to all the functions
// that are going to be called in a generic way from the CPU code.

struct TORCH_API AcceleratorHooksInterface {
  // This should never actually be implemented, but it is used to
  // squelch -Werror=non-virtual-dtor
  virtual ~AcceleratorHooksInterface() = default;

  // Whether the device at device_index is fully initialized or not.
  virtual bool hasPrimaryContext(DeviceIndex device_index) const = 0;

  virtual DeviceIndex deviceCount() const {
    return 0;
  }

  virtual void setCurrentDevice(DeviceIndex device) const {
    TORCH_CHECK(false, "Backend doesn't support setCurrentDevice()");
  }

  virtual DeviceIndex getCurrentDevice() const {
    TORCH_CHECK(false, "Backend doesn't support getCurrentDevice()");
  }

  virtual DeviceIndex exchangeDevice(DeviceIndex device) const {
    TORCH_CHECK(false, "Backend doesn't support exchangeDevice()");
  }

  virtual DeviceIndex maybeExchangeDevice(DeviceIndex device) const {
    TORCH_CHECK(false, "Backend doesn't support maybeExchangeDevice()");
  }

  virtual bool isPinnedPtr(const void* data) const {
    return false;
  }

  virtual Allocator* getPinnedMemoryAllocator() const {
    TORCH_CHECK(false, "Backend doesn't support getPinnedMemoryAllocator()");
  }

  virtual const Generator& getDefaultGenerator(const DeviceIndex device_index = -1) const {
    TORCH_CHECK(false, "Backend doesn't support getDefaultGenerator()");
  }
};

} // namespace at
C10_DIAGNOSTIC_POP()
