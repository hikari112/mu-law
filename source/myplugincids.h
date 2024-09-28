//------------------------------------------------------------------------
// Copyright(c) 2024 Hikari Audio.
//------------------------------------------------------------------------

#pragma once

#include "pluginterfaces/base/funknown.h"
#include "pluginterfaces/vst/vsttypes.h"

namespace MyCompanyName {
//------------------------------------------------------------------------
static const Steinberg::FUID kmuLawProcessorUID (0xC0DA7046, 0x76815B91, 0x9799DDCE, 0x9EFF8FC1);
static const Steinberg::FUID kmuLawControllerUID (0xE97A8F93, 0xE8DC5A3E, 0xB2DF434B, 0x9C6DD883);

#define muLawVST3Category "Fx"

//------------------------------------------------------------------------
} // namespace MyCompanyName