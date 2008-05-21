/***************************************************************************
*   Copyright (C) 2007 by BOP                                             *
*   polepolek@gmail.com                                                   *
*                                                                         *
*   This program is free software; you can redistribute it and/or modify  *
*   it under the terms of the GNU General Public License as published by  *
*   the Free Software Foundation; either version 2 of the License, or     *
*   (at your option) any later version.                                   *
*                                                                         *
*   This program is distributed in the hope that it will be useful,       *
*   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
*   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
*   GNU General Public License for more details.                          *
*                                                                         *
*   You should have received a copy of the GNU General Public License     *
*   along with this program; if not, write to the                         *
*   Free Software Foundation, Inc.,                                       *
*   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
***************************************************************************/
#ifndef EBHOOK_H
#define EBHOOK_H

#include <eb/eb.h>
#include <eb/text.h>

#include "ebcache.h"

class EBook;

class EbHook : public QObject
{

public:
    EbHook()
        : QObject()
    {
    }

    void init(EbCache *cache, int fsize, QHash<QString, QString> *flist,
           int ioffset = 50, bool rb = true) 
    {
        ebCache = cache;
        fontSize = fsize;
        fontList = flist;
        indentOffset = ioffset;
        ruby = rb;
        monoWidth = 0;
        monoHeight = 0;
        imageCount = 0;
        indented = false;
    }

    QByteArray begin_decoration(int deco_code);
    QByteArray end_decoration();
    QByteArray set_indent(int val);
    QByteArray begin_reference();
    QByteArray end_reference(int page, int offset);
    QByteArray begin_candidate();
    QByteArray begin_candidate_menu();
    QByteArray end_candidate_group(int page, int offset);
    QByteArray end_candidate_group_menu(EB_Book *book, int page, int offset);
    QByteArray narrow_font(EB_Book *book, int code);
    QByteArray wide_font(EB_Book *book, int code);
    QByteArray end_mono_graphic(EB_Book *book, int page, int offset);
    QByteArray begin_mpeg();
    QByteArray begin_wave(EB_Book *book, int start_page, int start_offset,
                          int end_page, int end_offset);
    QByteArray begin_color_bmp(EB_Book *book, int page, int offset);
    QByteArray begin_color_jpeg(EB_Book *book, int page, int offset);
    QByteArray errorString(const QByteArray &error_string)
    { return "<em class=err>" + error_string + "</em>"; }
    QByteArray begin_subscript()
    { return (ruby) ? "<sub>" : QByteArray(); }
    QByteArray end_subscript()
    { return (ruby) ? "</sub>" : QByteArray(); }
    void end_mpeg(EB_Book *book, const unsigned int *p);
    void begin_mono_graphic(int height, int width)
    {
        monoHeight = height;
        monoWidth = width;
        imageCount++;
    }
    QByteArray makeFname(const QByteArray &type, int p1, int p2)
    {
        return QByteArray::number(p1) + 'x' + QByteArray::number(p2) +
               '.' + type;
    }


    EbCache *ebCache;
    int monoWidth;
    int monoHeight;
    int fontSize;
    QHash<QString, QString> *fontList;
    int indentOffset;
    int imageCount;
    bool ruby;
    bool indented;
    QStack <int> decoStack;
    QList <QByteArray> refList;
    int refPosition;
    QStringList candList;
    QList <QByteArray> mpegList;

};

#define HookFunc(name) \
    EB_Error_Code name(EB_Book *, EB_Appendix *, void*, EB_Hook_Code, int, \
                       const unsigned int*)

HookFunc( hook_newline );
HookFunc( hook_iso8859_1 );
HookFunc( hook_narrow_jisx0208 );
HookFunc( hook_wide_jisx0208 );
HookFunc( hook_gb2312 );
HookFunc( hook_set_indent );
HookFunc( hook_begin_narrow );
HookFunc( hook_end_narrow );
HookFunc( hook_begin_subscript );
HookFunc( hook_end_subscript );
HookFunc( hook_begin_superscript );
HookFunc( hook_end_superscript );
HookFunc( hook_begin_emphasize );
HookFunc( hook_end_emphasize );
HookFunc( hook_begin_candidate );
HookFunc( hook_begin_candidate_menu );
HookFunc( hook_end_candidate_leaf );
HookFunc( hook_end_candidate_group );
HookFunc( hook_end_candidate_group_menu );
HookFunc( hook_begin_reference );
HookFunc( hook_end_reference );
HookFunc( hook_begin_keyword );
HookFunc( hook_end_keyword );
HookFunc( hook_begin_decoration );
HookFunc( hook_end_decoration );
HookFunc( hook_begin_mono_graphic );
HookFunc( hook_end_mono_graphic );
HookFunc( hook_begin_color_bmp );
HookFunc( hook_begin_color_jpeg );
HookFunc( hook_end_color_graphic );
HookFunc( hook_begin_in_color_bmp );
HookFunc( hook_begin_in_color_jpeg );
HookFunc( hook_end_in_color_graphic );
HookFunc( hook_begin_mpeg );
HookFunc( hook_end_mpeg );
HookFunc( hook_narrow_font );
HookFunc( hook_wide_font );
HookFunc( hook_begin_wave );
HookFunc( hook_end_wave );

const EB_Hook hooks[] = {
    //{EB_HOOK_NEWLINE,  hook_newline},
    //{EB_HOOK_ISO8859_1,  hook_iso8859_1},
    { EB_HOOK_NARROW_JISX0208,      hook_narrow_jisx0208      },
    //{ EB_HOOK_WIDE_JISX0208,        hook_wide_jisx0208        },
    //{EB_HOOK_GB2312,  hook_gb2312},
    //{EB_HOOK_BEGIN_NARROW,  hook_begin_narrow},
    //{EB_HOOK_END_NARROW,  hook_end_narrow},
    //{ EB_HOOK_SET_INDENT,           hook_set_indent           },
    { EB_HOOK_BEGIN_SUBSCRIPT,      hook_begin_subscript      },
    { EB_HOOK_END_SUBSCRIPT,        hook_end_subscript        },
    { EB_HOOK_BEGIN_SUPERSCRIPT,    hook_begin_superscript    },
    { EB_HOOK_END_SUPERSCRIPT,      hook_end_superscript      },
    { EB_HOOK_BEGIN_EMPHASIS,       hook_begin_emphasize      },
    { EB_HOOK_END_EMPHASIS,         hook_end_emphasize        },
    { EB_HOOK_NARROW_FONT,          hook_narrow_font          },
    { EB_HOOK_WIDE_FONT,            hook_wide_font            },
    { EB_HOOK_BEGIN_CANDIDATE,      hook_begin_candidate      },
    { EB_HOOK_END_CANDIDATE_LEAF,   hook_end_candidate_leaf   },
    { EB_HOOK_END_CANDIDATE_GROUP,  hook_end_candidate_group  },
    { EB_HOOK_BEGIN_REFERENCE,      hook_begin_reference      },
    { EB_HOOK_END_REFERENCE,        hook_end_reference        },
    //{EB_HOOK_BEGIN_KEYWORD,  hook_begin_keyword},
    //{EB_HOOK_END_KEYWORD,  hook_end_keyword},
    { EB_HOOK_BEGIN_DECORATION,     hook_begin_decoration     },
    { EB_HOOK_END_DECORATION,       hook_end_decoration       },
    { EB_HOOK_BEGIN_MONO_GRAPHIC,   hook_begin_mono_graphic   },
    { EB_HOOK_END_MONO_GRAPHIC,     hook_end_mono_graphic     },
    { EB_HOOK_BEGIN_COLOR_BMP,      hook_begin_color_bmp      },
    { EB_HOOK_BEGIN_COLOR_JPEG,     hook_begin_color_jpeg     },
    { EB_HOOK_END_COLOR_GRAPHIC,    hook_end_color_graphic    },
    { EB_HOOK_BEGIN_IN_COLOR_BMP,   hook_begin_in_color_bmp   },
    { EB_HOOK_BEGIN_IN_COLOR_JPEG,  hook_begin_in_color_jpeg  },
    { EB_HOOK_END_IN_COLOR_GRAPHIC, hook_end_in_color_graphic },
    { EB_HOOK_BEGIN_MPEG,           hook_begin_mpeg           },
    { EB_HOOK_END_MPEG,             hook_end_mpeg             },
    { EB_HOOK_BEGIN_WAVE,           hook_begin_wave           },
    { EB_HOOK_END_WAVE,             hook_end_wave             },
    { EB_HOOK_NULL,                 NULL                      }
};

const EB_Hook hooks_cand[] = {
    //{EB_HOOK_NEWLINE,  hook_newline},
    //{EB_HOOK_ISO8859_1,  hook_iso8859_1},
    { EB_HOOK_NARROW_JISX0208,      hook_narrow_jisx0208          },
    //{ EB_HOOK_WIDE_JISX0208,        hook_wide_jisx0208            },
    //{EB_HOOK_GB2312,  hook_gb2312},
    //{EB_HOOK_BEGIN_NARROW,  hook_begin_narrow},
    //{EB_HOOK_END_NARROW,  hook_end_narrow},
    { EB_HOOK_SET_INDENT,           hook_set_indent               },
    { EB_HOOK_BEGIN_SUBSCRIPT,      hook_begin_subscript          },
    { EB_HOOK_END_SUBSCRIPT,        hook_end_subscript            },
    { EB_HOOK_BEGIN_SUPERSCRIPT,    hook_begin_superscript        },
    { EB_HOOK_END_SUPERSCRIPT,      hook_end_superscript          },
    { EB_HOOK_BEGIN_EMPHASIS,       hook_begin_emphasize          },
    { EB_HOOK_END_EMPHASIS,         hook_end_emphasize            },
    { EB_HOOK_NARROW_FONT,          hook_narrow_font              },
    { EB_HOOK_WIDE_FONT,            hook_wide_font                },
    { EB_HOOK_BEGIN_CANDIDATE,      hook_begin_candidate_menu     },
    //{EB_HOOK_END_CANDIDATE_LEAF,  hook_end_candidate_leaf},
    { EB_HOOK_END_CANDIDATE_GROUP,  hook_end_candidate_group_menu },
    { EB_HOOK_BEGIN_REFERENCE,      hook_begin_reference          },
    { EB_HOOK_END_REFERENCE,        hook_end_reference            },
    //{EB_HOOK_BEGIN_KEYWORD,  hook_begin_keyword},
    //{EB_HOOK_END_KEYWORD,  hook_end_keyword},
    { EB_HOOK_BEGIN_DECORATION,     hook_begin_decoration         },
    { EB_HOOK_END_DECORATION,       hook_end_decoration           },
    { EB_HOOK_BEGIN_MONO_GRAPHIC,   hook_begin_mono_graphic       },
    { EB_HOOK_END_MONO_GRAPHIC,     hook_end_mono_graphic         },
    { EB_HOOK_BEGIN_COLOR_BMP,      hook_begin_color_bmp          },
    { EB_HOOK_BEGIN_COLOR_JPEG,     hook_begin_color_jpeg         },
    { EB_HOOK_END_COLOR_GRAPHIC,    hook_end_color_graphic        },
    { EB_HOOK_BEGIN_IN_COLOR_BMP,   hook_begin_in_color_bmp       },
    { EB_HOOK_BEGIN_IN_COLOR_JPEG,  hook_begin_in_color_jpeg      },
    { EB_HOOK_END_IN_COLOR_GRAPHIC, hook_end_in_color_graphic     },
    { EB_HOOK_BEGIN_MPEG,           hook_begin_mpeg               },
    { EB_HOOK_END_MPEG,             hook_end_mpeg                 },
    { EB_HOOK_BEGIN_WAVE,           hook_begin_wave               },
    { EB_HOOK_END_WAVE,             hook_end_wave                 },
    { EB_HOOK_NULL,                 NULL                          }
};
const EB_Hook hooks_font[] = {
    { EB_HOOK_NARROW_FONT,          hook_narrow_font              },
    { EB_HOOK_WIDE_FONT,            hook_wide_font                },
    { EB_HOOK_NULL,                 NULL                          }
};

#endif
