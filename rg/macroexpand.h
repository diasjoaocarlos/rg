#define MACROEXPAND_H

#define STR(s) #s
#define XSTR(s) STR(s)

#define CONCAT(a,b) a##b
#define XCONCAT(a,b) CONCAT(a,b)


