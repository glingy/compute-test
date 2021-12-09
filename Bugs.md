
LED doesn't turn on!
 - Check wiring (0/1)
 - Check output direction

Help! A peripheral isn't working
 - Is it enabled in APB? - Did you wait after enabling it for the clock to enable?
 - Does it need AHB enabled?
 - Is it enabled?
 - Is it's GCLK enabled?

Help! I bricked a board!
 - If it's a compute, put it in the compute tester and follow the instructions to wipe it. (once it exists)
 - If it's a blue dev board... build openocd using the patches and run the command listed here: https://sourceforge.net/p/openocd/mailman/message/35884360/. Or hand it to Gregory.
   - `~/.platformio/debug-openocd/openocd-code/src/openocd -s ~/.platformio/packages/tool-openocd/scripts -f interface/cmsis-dap.cfg -f target/at91samdXX.cfg -c cmsis_dap_init_samd_cold_plug -c init -c "at91samd chip-erase; shutdown"`