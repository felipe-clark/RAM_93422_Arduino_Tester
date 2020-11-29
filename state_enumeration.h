/*******************************************************************************
 *                  Arduino memory tester for RAM 93422
 *******************************************************************************
 * Declaration of the states of the main state-machine
 * -- Arduino IDE Version 1.8.13
 * -- Author: Felipe Sander Pereira Clark
 *
 * -- October, 2020
 *******************************************************************************/

#pragma once

enum class State
{
    WAITING_FOR_BUTTON,
    WRITE_MEMORY_ONES,
    READ_MEMORY_ONES,
    WRITE_MEMORY_ZEROS,
    READ_MEMORY_ZEROS,
    FAILURE,
    SUCCESS,
    ABORT
};
