#include "../LC_Task.h"

#include <IO/CK_Logger.h>

#define DEBUG_LC_CALLBACK 1
#define LDBG DEBUG_LC_CALLBACK && DBG

UI		* Task::o_ui = NULL;
Storage	* Task::o_stor = NULL;

