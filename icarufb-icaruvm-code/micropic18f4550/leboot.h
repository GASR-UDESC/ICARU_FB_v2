
#define LOADER_END  0x4FF
#define LOADER_SIZE	0x3FF

#ifndef _bootloader

#if defined(__PCM__)
   #build(reset=LOADER_END+1, interrupt=LOADER_END+5)
#elif defined(__PCH__)
   #build(reset=LOADER_END+1, interrupt=LOADER_END+9)
#endif

#org 0, LOADER_END {}

#endif