/*
**
** Made by Applelo
**
*/

#include "../include/Menu.hh"

int main() {

	int run = 1;

	sceCtrlSetSamplingMode(SCE_CTRL_MODE_ANALOG);

	vita2d_init();
	vita2d_set_clear_color(RGBA8(0x00, 0x00, 0x00, 0xFF));

	Menu* menu = new Menu();

	while (run) {
		vita2d_start_drawing();
		vita2d_clear_screen();
		vita2d_draw_rectangle(0, 0, SCREEN_L, SCREEN_H, BACKGROUND);
        vita2d_draw_rectangle(SCREEN_L - 300, 0, SCREEN_L, SCREEN_H, BACKGROUND2);

		if (menu->getMenu() == Step::MAIN)
			menu->main();
		if (menu->getMenu() == Step::AUTO_SWITCH)
			menu->auto_switch();
		if (menu->getMenu() == Step::SWITCH_TO_UX0)
			menu->switch_to(UX0);
		if (menu->getMenu() == Step::SWITCH_TO_UMA0)
			menu->switch_to(UMA0);
        if (menu->getMenu() == Step::SWITCH_TO_XMC0)
            menu->switch_to(XMC0);
        if (menu->getMenu() == Step::SWITCH_TO_IMC0)
            menu->switch_to(IMC0);
        if (menu->getMenu() == Step::SWITCH_TO_GRW0)
            menu->switch_to(GRW0);
		if (menu->getMenu() == Step::UNINSTALL)
			menu->uninstall();
		if (menu->getMenu() == Step::EXIT)
			run = 0;


		vita2d_end_drawing();
		vita2d_swap_buffers();
	}
	vita2d_fini();

	sceKernelExitProcess(0);
	return (0);
}
