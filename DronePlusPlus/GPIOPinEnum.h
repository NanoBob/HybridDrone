#pragma once

enum class GPIOPinDirection {
	IN,
	OUT,
	UNKNOWN
};

enum class GPIOPinValue {
	HIGH,
	LOW,
	UNKNOWN
};

enum class GPIOPinState {
	ENABLED,
	DISABLED,
	UNKNOWN
};
