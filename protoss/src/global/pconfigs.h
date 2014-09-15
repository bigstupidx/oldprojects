// pconfigs.h
//
// Copyright 2013 by Cooee. All rights reserved.
//
// Hongwei Li lihw81@gmail.com
//

#ifndef PCONFIGS_H
#define PCONFIGS_H

#ifndef P_CONTEXT_MAX_COUNT
# define P_CONTEXT_MAX_COUNT 16 // We can support up to 16 contexts in one activity.
#endif

#define P_CONTEXT_INVALID_ID  (P_CONTEXT_MAX_COUNT + 1)

#ifndef P_EVENT_QUEUE_LENGTH
# define P_EVENT_QUEUE_LENGTH 64 // The maximum event number in the event queue.
#endif

#ifndef P_INPUT_MAXIMUM_TOUCH
# define P_INPUT_MAXIMUM_TOUCH 5 // The maximum touch point supported
#endif

#ifndef P_INPUT_EVENT_QUEUE_INITIAL_SIZE
# define P_INPUT_EVENT_QUEUE_INITIAL_SIZE 32 // The initial input queue length
#endif

#if defined P_DEBUG
# define P_LOG_ENABLED // Enable the logging
#endif


#endif // !PCONFIGS_H
