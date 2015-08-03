/*
 * Mailbox-msg.h
 *
 *  Created on: Aug 2, 2015
 *      Author: Matt Gramlich
 */

#ifndef MAILBOX_MSG_H_
#define MAILBOX_MSG_H_

#include "Data-msg.h"

namespace mail
{
	struct mail_t
	{
		uint16_t length;
		uint8_t inUse;
		char * data;
	};
}


#endif /* MAILBOX_MSG_H_ */
