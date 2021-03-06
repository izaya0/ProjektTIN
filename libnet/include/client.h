/*
 * 					HEADER_HEAD
 * author: Mikolaj Florkiewicz
 * 					HEADER_TAIL
 */
#pragma once

#define XSTR(x) STR(x)
#define STR(x) #x

#if !defined _GNU_SOURCE || _GNU_SOURCE == 1
# define _GNU_SOURCE 201112L
#else
# if _GNU_SOURCE == 201112L
//ok
# else
#  pragma message "_GNU_SOURCE = " XSTR(_GNU_SOURCE)
#  error Somebody was messing with our _GNU_SOURCE
# endif
#endif

#include <stdbool.h>
#include <stdlib.h>
#include <sys/types.h>

/**
 * @brief
 * 	initialize libnet, required before everything else
 * @param tags_to_register
 * 	table of tags that will be used by libnet client
 * @param tags_to_register_number
 * 	number of tags in table
 */
bool libnet_init(const unsigned char *tags_to_register,
		const unsigned tags_to_register_number)
	__attribute__((warn_unused_result));

/**
 * @brief
 * 	start libnet thread. must be called after init, before any other actions
 */
bool libnet_thread_start(const char *address, const char *service);

/**
 * @brief
 * 	Send message
 * @param tag
 * 	tag used
 * @param length
 * 	value size
 * @param value
 * 	message data
 */
bool libnet_send(const unsigned char tag, const size_t length,
		const unsigned char *value) __attribute__((warn_unused_result));

#define ENOTAG 1 // specified tag has not been registered
#define EQUEUE 2 // queue in inconsistent state (something is very wrong)
#define ESIZE  3 // provided buffer too small
/**
 * @brief
 * 	return message with specified tag, may block if no such message in recv queue
 * @param tag
 * 	wait for message with specified tag
 * @param buffer
 * 	buffer to copy message to
 * @param length
 * 	provided buffer length
 */
ssize_t libnet_wait_for_tag(const unsigned char tag, unsigned char *buffer, const size_t length,
		const bool block) __attribute__((warn_unused_result));

/**
 * @brief
 * 	stop libnet thread
 * // messages in queue are left in unspecified state for now -- florek
 */
bool libnet_thread_shutdown();

/**
 * @brief
 * 	block until any new message becomes available
 */
bool libnet_wait_for_new_message();

/**
 * @brief
 * 	wait till libnet init is finished
 */

bool libnet_wait_for_initialization_finish();

