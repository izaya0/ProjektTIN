#pragma once

#define _GNU_SOURCE 201112L

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
bool libnet_init(unsigned char *tags_to_register, unsigned tags_to_register_number) __attribute__((warn_unused_result));

/**
 * @brief
 * 	start libnet thread. must be called after init, before any other actions
 */
bool libnet_thread_start(char *address, char *service);

// TODO(florek) better error handling
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
bool libnet_send(unsigned char tag, size_t length, unsigned char *value) __attribute__((warn_unused_result));

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
ssize_t libnet_wait_for_tag(unsigned char tag, char *buffer, size_t length) __attribute__((warn_unused_result));

