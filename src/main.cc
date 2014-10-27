#include <glibtop.h>
#include <glibtop/mem.h>
#include <glibtop/cpu.h>
#include <glib.h>
#include <unistd.h>
#include <iostream>

int main(int argc, char **argv)
{
        glibtop_mem buf;

        glibtop_init();

        g_print("%lx\n", glibtop_global_server->features);

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
                        double load = 100.0 * double (use) / std::max (double (total), 1.0);
                        std::cerr << load  << "%" << std::endl;
                }

                lastTotal = nowTotal;
                lastUse = nowUse;

                usleep (100000);
        }

        glibtop_close();

        return 0;
}

