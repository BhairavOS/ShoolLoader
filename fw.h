#pragma once

#include <hal/vmm.h>
#include <handover/builder.h>
#include <kapalaframe-base/rc.h>
#include <kapalaframe-base/res.h>

namespace ShoolLoader::Fw {

Res<Arc<Hal::Vmm>> createVmm();

Res<> finalizeHandover(Handover::Builder& builder);

void enterKernel(usize entry, Handover::Payload& payload, usize stack, Hal::Vmm& vmm);

Hal::PmmRange imageRange();

} // namespace ShoolLoader::Fw
