#include "source/neslib_asm/neslib.h"
#include "source/menus/title.h"
#include "source/globals.h"
#include "source/configuration/game_states.h"
#include "source/configuration/system_constants.h"
#include "source/menus/text_helpers.h"
#include "source/graphics/palettes.h"
#include "source/configuration/game_info.h"

CODE_BANK(PRG_BANK_TITLE);

void draw_title_screen(void) {
    ppu_off();
	pal_bg(titlePalette);
	pal_spr(titlePalette);

	set_chr_bank_0(CHR_BANK_MENU);
    set_chr_bank_1(CHR_BANK_MENU);
	clear_screen();
	oam_clear();

    
    put_str(NTADR_A(7, 5), "Falling Deeper");
	
	put_str(NTADR_A(0, 24), "   A Ludum Dare 48 Compo Entry  ");
	put_str(NTADR_A(0, 26), "     Theme: We must go deeper   ");
	
	put_str(NTADR_A(2, 28), "Copyright");
	put_str(NTADR_A(12, 28), "2021");
	put_str(NTADR_A(17, 28), "@cppchriscpp");

	put_str(NTADR_A(10, 16), "Press Start!");
	ppu_on_all();

	gameState = GAME_STATE_TITLE_INPUT;
}

void handle_title_input(void) {
	if (pad_trigger(0) & PAD_START) {
		gameState = GAME_STATE_POST_TITLE;
	}
}