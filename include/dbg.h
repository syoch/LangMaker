#pragma once

#define  alert  fprintf(stderr,"\t#Alert %s:%d\n",__FILE__,__LINE__)
#define  debug(...) __VA_ARGS__
