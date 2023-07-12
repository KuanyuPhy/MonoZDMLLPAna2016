#ifndef USERCOLORINDEX_H // include guard
#define USERCOLORINDEX_H
#include <TROOT.h>

class GlobalColor
{
public:
    // static const GlobalColor gGC = GlobalColor();
    // static const GlobalColor getgGC() { return gGC; };

    Int_t KON;//(紺)深藍
    Int_t HIWAMOEGI;//(亮綠色)
    Int_t KARACHA;//(樺查色)(咖啡色)
    Int_t JINZAMOMI;//(甚三紅)(亮紅色)
    Int_t BENIUKON;//(紅鬱金)(亮橘色)
    Int_t SHIRACHA;//(白茶色)(亮咖啡色)
    Int_t KARIYASU;//黃色
    Int_t MIZUASAGI;//(水蔥色)淺藍色
    Int_t MATSUBA;//松葉色(綠色)

    TColor *KON_color;
    TColor *HIWAMOEGI_color;
    TColor *KARACHA_color;
    TColor *JINZAMOMI_color;
    TColor *BENIUKON_color;
    TColor *SHIRACHA_color;
    TColor *KARIYASU_color;
    TColor *MIZUASAGI_color;
    TColor *MATSUBA_color;

    // TColor HIWAMOEGI_color;

    GlobalColor()
    {
        KON = TColor::GetFreeColorIndex();
        KON_color = new TColor(KON, 0.06, 0.15, 0.25);
        HIWAMOEGI = TColor::GetFreeColorIndex();
        HIWAMOEGI_color = new TColor(HIWAMOEGI, 0.56, 0.71, 0.29);
        KARACHA = TColor::GetFreeColorIndex();
        KARACHA_color = new TColor(KARACHA, 0.71, 0.44, 0.34);
        JINZAMOMI = TColor::GetFreeColorIndex();
        JINZAMOMI_color = new TColor(JINZAMOMI, 0.92, 0.478, 0.46);
        BENIUKON = TColor::GetFreeColorIndex();
        BENIUKON_color = new TColor(BENIUKON, 0.913, 0.545, 0.16);
        SHIRACHA = TColor::GetFreeColorIndex();
        SHIRACHA_color = new TColor(SHIRACHA, 0.73, 0.623, 0.47);
        KARIYASU = TColor::GetFreeColorIndex();
        KARIYASU_color = new TColor(KARIYASU, 0.913, 0.803, 0.298);
        MIZUASAGI = TColor::GetFreeColorIndex();
        MIZUASAGI_color = new TColor(MIZUASAGI, 0.4, 0.729, 0.718);
        MATSUBA = TColor::GetFreeColorIndex();
        MATSUBA_color = new TColor(MATSUBA, 0.259, 0.376, 0.176);
    };
};
const GlobalColor kGlobalColor;
#endif