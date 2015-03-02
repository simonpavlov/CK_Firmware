#include "../LC_Callback.h"

#include <IO/CK_Logger.h>

#define DEBUG_LC_CALLBACK 1
#define LDBG DEBUG_LC_CALLBACK && DBG

void select_callback::run(){
	if(!new_res) return;
	LDBG << "new_res: " << new_res << " res: " << res << std::endl;
	if(res == 3) m_logic->m_ui.pop();
	new_res = false;
}

