/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include <glibtop.h>
#include <glibtop/mem.h>
#include <glibtop/cpu.h>
#include <glib.h>
#include <unistd.h>
#include <iostream>
#include "UsbService.h"
#include "Constants.h"

/*--------------------------------------------------------------------------*/

int main(int argc, char **argv)
{
        UsbServiceGuard <UsbService> guard;

        glibtop_mem buf;

        glibtop_init();
        glibtop_get_mem(&buf);

        guint64 lastTotal = 0;
        guint64 lastUse = 0;

        while (1) {
                glibtop_cpu cpu;
                glibtop_get_cpu (&cpu);

                guint64 nowTotal = cpu.total;
                guint64 nowUse = cpu.user + cpu.nice + cpu.sys;

                guint64 total = nowTotal - lastTotal;
                guint64 use = nowUse - lastUse;

                if (lastTotal) {
                        double load = double (use) / std::max (double (total), 1.0);
                        std::cerr << 100.0 * load  << "%" << std::endl;

                        uint16_t load16 = load * TOTAL_USTEPS;

                        UsbService::Buffer buffer (OUTPUT_DATA_SIZE);
                        buffer[0] = (load16 & 0xff00) >> 8;
                        buffer[1] = (load16 & 0x00ff);
                        guard.service.transmit (buffer);
                }

                lastTotal = nowTotal;
                lastUse = nowUse;

//                usleep (40000); // 40ms = 25fps
                usleep (1000000 / 5); // 200ms
//                usleep (1000000); // 1 s
        }

        glibtop_close();

        return 0;
}


