/*
 *  hooker.h
 */
#pragma once

void init_interfaces();
void init_hooks();
void hook_functions();
void init_settings();

#define CLIENTMODE_SIG  (unsigned char*)"\x48\x8B\xB7\x00\x00\x00\x00\x48\x8D\x3D\x00\x00\x00\x00\x5D\xE9"
#define CLIENTMODE_MASK "xxx????xxx????xx"

#define GLOBALS_SIG     (unsigned char*)"\x48\x8D\x05\x00\x00\x00\x00\x48\x8B\x00\xF3\x0F\x10\x00\x00\xF3\x0F\x11\x83\x00\x00\x00\x00"
#define GLOBALS_MASK    "xxx????xxxxxx??xxxx????"

#define RANKREVEAL_SIG  (unsigned char*)"\x48\x89\x85\x28\xFE\xFF\xFF\x48\xC7\x85\x30\xFE\xFF\xFF\x00\x00\x00\x00\x48\x8D\x05\x00\x00\x00\x00"
#define RANKREVEAL_MASK "xxxxxxxxxxxxxx????xxx????"

#define CLANTAG_SIG     (unsigned char*)"\x48\x8D\x3D\x00\x00\x00\x00\x48\x89\xFE\xE8\x00\x00\x00\x00\xE9\x00\x00\x00\x00"
#define CLANTAG_MASK    "xxx????xxxx????x????"

#define SENDPACKET_SIG  (unsigned char*)"\x41\xB5\x00\x84\xC0\x74\x11"
#define SENDPACKET_MASK "xx?xxxx"
