
#include <rice/Module.hpp>
using namespace Rice;

#include "calib3d.h"
#include "reproj.h"

namespace CVRice {

  void init_calib3d( Module &parent )
  {
    init_reproj( parent );
  } 

}
