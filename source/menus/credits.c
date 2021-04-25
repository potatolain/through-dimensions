#include "source/menus/credits.h"
#include "source/graphics/palettes.h"
#include "source/configuration/system_constants.h"
#include "source/globals.h"
#include "source/neslib_asm/neslib.h"
#include "source/configuration/game_states.h"
#include "source/menus/text_helpers.h"
#include "source/configuration/game_info.h"

#include "graphics/credits.h"
#include "graphics/badend.h"
#include "graphics/goodend.h"

CODE_BANK(PRG_BANK_CREDITS_MENU);

void draw_win_screen(void) {
    set_vram_update(NULL);
    ppu_off();
    oam_clear();
    clear_screen();
    // We reuse the title palette here, though we have the option of making our own if needed.
    pal_bg(real_title);
	pal_spr(mainSpritePalette);
    scroll(0, 0);

	set_chr_bank_0(0x0a);
    set_chr_bank_1(CHR_BANK_SPRITES);

    // Add whatever you want here; NTADR_A just picks a position on the screen for you. Your options are 0, 0 to 32, 30
    /*put_str(NTADR_A(7, 2), "- Congratulations -");

    put_str(NTADR_A(4, 8), "You did the thing, and");
    put_str(NTADR_A(4, 9), "thus won the game!");
    */

    if (goodEnding) {
        sfx_play(SFX_WIN, SFX_CHANNEL_1);
        // FIXME: Put an ending here

        vram_adr(0x2000);
        vram_unrle(goodend);
        oam_spr(15 * 8, 23 * 8-2, 0x80, 0, 16);
	    oam_spr(16 * 8, 23 * 8-2, 0x81, 0, 20);
	    oam_spr(15 * 8, 24 * 8-2, 0x90, 0, 24);
	    oam_spr(16 * 8, 24 * 8-2, 0x91, 0, 28);

    } else {
        sfx_play(0x07, SFX_CHANNEL_1);
        vram_adr(0x2000);
        vram_unrle(badend);

        oam_spr(14 * 8, 20 * 8-2, 0x80, 0, 16);
	    oam_spr(15 * 8, 20 * 8-2, 0x81, 0, 20);
	    oam_spr(14 * 8, 21 * 8-2, 0x90, 0, 24);
	    oam_spr(15 * 8, 21 * 8-2, 0x91, 0, 28);

    }

    // Hide all existing sprites
    ppu_on_all();

}

void draw_credits_screen(void) {
    set_vram_update(NULL);
    ppu_off();
    //clear_screen_with_border();
    // We reuse the title palette here, though we have the option of making our own if needed.
    pal_bg(titlePalette);
	pal_spr(titlePalette);
    scroll(0, 0);

	set_chr_bank_0(CHR_BANK_MENU);
    set_chr_bank_1(CHR_BANK_MENU);

    // Add whatever you want here; NTADR_A just picks a position on the screen for you. Your options are 0, 0 to 32, 30
    /*
    put_str(NTADR_A(11, 5), "- Credits -");

    put_str(NTADR_A(2, 6), "Game Design and Logic");
    put_str(NTADR_A(4, 8), gameAuthor);

    put_str(NTADR_A(2, 11), "Music");
    put_str(NTADR_A(4, 13), "Wolfgang (OpenGameArt)");

    put_str(NTADR_A(2, 16), "Artwork");
    put_str(NTADR_A(4, 18), "Refresh Games (OpenGameArt)");

    put_str(NTADR_A(6, 24), "Created in");
    put_str(NTADR_A(17, 24), currentYear);
    put_str(NTADR_A(22, 24), "by");

    put_str(NTADR_A(8, 26), gameAuthor);
    */
   vram_adr(0x2000);
   vram_unrle(credits);


    // Hide all existing sprites
    oam_clear();
    ppu_on_all();
}