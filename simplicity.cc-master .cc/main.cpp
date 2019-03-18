/*      simplicity.cc v1.2
 *
 *  - Recoil crosshair, wonky line
 *  - Active weapon, move down a little
 *  - Draw backtrack, dont draw if its too old
 *  - Y RCS
 *  - Auto shoot, crashes
 *
 *
 *
 */

#include "main.h"
#include "hooker.h"

int __attribute__((constructor)) main()
{
    init_interfaces();
    
    init_hooks();
    
    get_offsets();
    
    hook_functions();
    
    init_settings();
    
    return EXIT_SUCCESS;
}
