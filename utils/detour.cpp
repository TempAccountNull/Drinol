#include "stdafx.h"
detour::detour() {
}

detour::~detour() {
	this->_function = 0;
	this->_location = 0;
}

bool detour::create(uintptr_t location, void* function) {
	MH_STATUS status = MH_Initialize();
	if (status == MH_ERROR_ALREADY_INITIALIZED || status == MH_OK) {
		this->_location = location;
		this->_function = function;
		if (MH_CreateHook(reinterpret_cast<void*>(this->_location), this->_function, &this->_stub) == MH_OK) {
			if (this->enable()) {
				spdlog::debug("hook created at 0x{:X} going to {}", this->_location, this->_function);
			}
		}
	}
	return false;
}

bool detour::enable() {
	if (MH_QueueEnableHook(reinterpret_cast<void*>(this->_location)) == MH_OK) {
		return true;
	}
	return false;
}

bool detour::disable() {
	if (MH_QueueDisableHook(reinterpret_cast<void*>(this->_location)) == MH_OK) {
		return true;
	}
	return false;
}