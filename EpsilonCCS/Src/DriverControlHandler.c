#include "cmsis_os.h"

#include "DriverControlHandler.h"
#include "Util.h"

void handleDriverMsgTask(void const* arg)
{
	 osEvent evt = osMessagePeek(canQueue, osWaitForever); // Blocks

	 if (evt.status == osEventMessage)
	 {

		 CanMsg* msg = (CanMsg*)evt.value.p;
		 if(msg->StdId == DRIVER_STDID) {

			 // (de-)activate horn
			 HAL_GPIO_WritePin(HORN_GPIO_Port, HORN_Pin,
					((msg->Data[3] & 0x10) == 0) ? GPIO_PIN_RESET : GPIO_PIN_SET);

			 // TODO package remaining information and send

			 // Deallocate CAN message
			 osMessageGet(canQueue, 0); // waiting should never be required as peek already blocks TODO osWaitForever?
			 osPoolFree(canPool, msg);
		 }

	 }
}

