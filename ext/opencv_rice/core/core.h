
#include <rice/Module.hpp>
#include <rice/to_from_ruby_defn.hpp>

#include "to_from_ruby.h"
#include "mat_conversions.h"

#include "keypoint.h"
#include "dmatch.h"
#include "mat.h"

#ifndef __CORE_H__
#define __CORE_H__

void init_core( Rice::Module &rb_mCVRice );

#endif
