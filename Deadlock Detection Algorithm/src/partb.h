#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stddef.h>

/*
 * Structure the LockManager holds (this is a single lock)
 */
struct Lock {
    bool is_owned;  /** lock status (true if owned by someone) */
    int by_child;   /** PID of the process that's holding the lock */
};

/**
 * Children send this request to the lock manager.
 */
enum LockAction {
    LOCK = 100,   /** Child requests to lock a resource */
    RELEASE_ALL = 200 /** Child requests to release all its resources */
};

/**
 * Children send this message to request a lock.
 */
struct msg_requestLock {
    int lockID; /** this a number from 0 up to (MAXLOCKS-1) */
    int Action; /** LockAction (LOCK, RELEASE_ALL) */
};

/**
 * Lock manager sends back this response depending on what happened to the request
 */
enum LockRequestStatus {
    GRANTED = 1,     /** The lock has been granted to you. */
    NOT_GRANTED = 2, /** Lock has not been granted. Some else already owns it so wait. */
    YOU_OWN_IT = 3,  /** You already own the lock! */
    PREVENT = 4      /** Deadlock detected! Request is rejected */
};

/**
 * LockManager sends status of request to children.
 */
struct msg_requestStatus {
    int status;   /** LockRequestStatus (GRANTED, NOT_GRANTED, YOU_OWN_IT, PREVENT) */
    int by_child; /** if not granted, who owns it */
};

void abortAll();

#ifdef __cplusplus
}
#endif

