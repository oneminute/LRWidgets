#ifndef EXPORTLRWIDGETS_H
#define EXPORTLRWIDGETS_H

#if defined(BUILD_SHARED_LIBRARY)
#   if defined(EXPORT_LRWIDGETS)
#       define LRWIDGET_EXPORT Q_DECL_EXPORT
#   else
#       define LRWIDGET_EXPORT Q_DECL_IMPORT
#   endif
#else
#   define LRWIDGET_EXPORT
#endif


#endif // EXPORTLRWIDGETS_H