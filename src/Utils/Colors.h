#include <sys/types.h>

using uchar = unsigned char;

struct Color {
    uchar r;
    uchar g;
    uchar b;
};

namespace enmColors {
    const Color black{0, 0, 0};
    const Color dark_blue{0, 55, 218};
    const Color dark_green{19, 161, 14};
    const Color dark_cyan{58, 150, 221};
    const Color dark_red{197, 15, 31};
    const Color dark_magenta{136, 23, 152};
    const Color dark_yellow{193, 156, 0};
    const Color light_gray{204, 204, 204};
    const Color dark_gray{118, 118, 118};
    const Color light_blue{59, 120, 255};
    const Color light_green{22, 198, 12};
    const Color light_cyan{97, 214, 214};
    const Color light_red{231, 72, 86};
    const Color light_magenta{180, 0, 158};
    const Color light_yellow{249, 241, 165};
    const Color white{242, 242, 242};
}