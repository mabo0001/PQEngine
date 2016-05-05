#ifndef PQENGINE_GLOBAL_H
#define PQENGINE_GLOBAL_H

#define PQENGINE_MAJOR_VERSION 0
#define PQENGINE_MINOR_VERSION 5
#define PQENGINE_RELEASE_VERSION 2
#define PQENGINE_CODENAME "HOROLOGIUM"
#define PQENGINE_VERSION "0.5.2"
#define PQENGINE_VERSION_ID 52

extern void default_ub_write(const QString &msg, const QString &title);
extern QByteArray getCorename();

#ifdef PQDEBUG
extern int pqdbg_get_current_lvl();
extern QString pqdbg_get_current_line();
extern void pqdbg_current_line_inc();
extern void pqdbg_set_current_lvl(int lvl);
#endif

#define Z_OBJCE_NAME(zval)          (Z_OBJCE((zval)))->name->val
#define Z_OBJCE_NAME_P(zval_p)      Z_OBJCE_NAME(*(zval_p))

#ifdef PQDEBUG
    #include <QDebug>

    #define PQDBG_LVL_D int __pq_debug_level
    #define PQDBG_LVL_DC , PQDBG_LVL_D
    #define PQDBG_LVL_C __pq_debug_level
    #define PQDBG_LVL_CC , PQDBG_LVL_C
    #define PQDBG_LVL_N pqdbg_get_current_lvl()
    #define PQDBG_LVL_NC , PQDBG_LVL_N
    /* Increase debugging level. Affects to level in current scope! */
    #define PQDBG_LVL_UP() PQDBG_LVL_C++

    /* Returns increased debug level. Not affects to level in current scope */
    #define PQDBG_LVL_PUP(up) (PQDBG_LVL_C+up)

    #define PQDBG(msg) default_ub_write(msg, "D0: ");
    #define PQDBG2(line1, line2) default_ub_write(QString("%1 %2").arg(QString(line1)).arg(QString(line2)), "D0: ");

    /* Print debug message */
    #define PQDBGL(msg) {\
        pqdbg_current_line_inc();\
        QString m(msg);\
        for(int l = 0; l < PQDBG_LVL_C; l++) { m.prepend("  "); }\
        default_ub_write(m, QString("D:%1 L%2: ").arg(pqdbg_get_current_line()).arg(PQDBG_LVL_C));\
    }

    /* Start new debug with level 0 */
    #define PQDBG_LVL_START(function_name) \
        PQDBG_LVL_D = pqdbg_get_current_lvl()+1;\
        pqdbg_set_current_lvl(PQDBG_LVL_C);\
        PQDBGL(function_name);

    /* Proceed debugging with increased level */
    #define PQDBG_LVL_PROCEED(function_name) \
        PQDBG_LVL_UP();\
        pqdbg_set_current_lvl(PQDBG_LVL_C);\
        PQDBGL(function_name);

    /* Increase debug level and print. Not affects to level in current scope */
    #define PQDBGLPUP(msg) {\
        QString m(msg);\
        m.prepend("> ");\
        PQDBGL(m);\
    }

    #define PQDBG_LVL_DONE() {\
        PQDBG_LVL_C = PQDBG_LVL_C - 1;\
        pqdbg_set_current_lvl(PQDBG_LVL_C);\
    }

    #define PQDBG_LVL_DONE_LPUP() {\
        PQDBGLPUP("done");\
        PQDBG_LVL_DONE();\
    }\

#else
    #define PQDBG_LVL_D void
    #define PQDBG_LVL_DC
    #define PQDBG_LVL_C
    #define PQDBG_LVL_CC
    #define PQDBG_LVL_UP
    #define PQDBG_LVL_PUP(up)

    #define PQDBG(msg)
    #define PQDBG2(line1, line2)
    #define PQDBGL(level, msg)
    #define PQDBGLPUP(level)
    #define PQDBG_LVL_N
    #define PQDBG_LVL_NC

    #define PQDBG_LVL_DONE()
    #define PQDBG_LVL_DONE_LPUP()
#endif


#ifdef PQSTATIC
# define PQDLAPI
# define PQAPI
#else
# ifdef PHP_WIN32
#   ifdef PQEXPORT
#     define PQDLAPI __declspec(dllexport)
#     define PQAPI __declspec(dllexport)
#   else
#     define PQDLAPI __declspec(dllimport)
#     define PQAPI __declspec(dllimport)
#   endif
# else
#   define PQDLAPI __attribute__ ((visibility("default")))
#   define PQAPI __attribute__ ((visibility("default")))
# endif
#endif

#endif // PQENGINE_GLOBAL_H
