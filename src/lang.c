#include <stdlib.h>
#include <string.h>
#include "lang.h"

/** Keyword definition */
KeyWord KEY_WORDS[] = {
  {"asm"   }, {"auto"    }, {"break"   }, {"case"    },
  {"char"  }, {"const"   }, {"continue"}, {"default" },
  {"do"    }, {"double"  }, {"else"    }, {"enum"    },
  {"extern"}, {"float"   }, {"for"     }, {"goto"    },
  {"if"    }, {"int"     }, {"long"    }, {"register"},
  {"return"}, {"short"   }, {"signed"  }, {"sizeof"  },
  {"static"}, {"struct"  }, {"switch"  }, {"typedef" },
  {"union" }, {"unsigned"}, {"void"    }, {"volatile"},
  {"while" }
};


int compKW(
    const void *a,
    const void *b
){
  KeyWord *wa = (KeyWord *) a;
  KeyWord *wb = (KeyWord *) b;
  return strcmp(wa->word, wb->word);
}


int findKWID(
    char *value
){
  KeyWord w = {value};
  KeyWord *res = bsearch(&w, KEY_WORDS, KI_COUNT, sizeof(KeyWord), compKW);
  if (res == NULL){
    return 0;
  } else {
    return 1 + (res - KEY_WORDS);
  }
}
