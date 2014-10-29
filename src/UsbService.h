/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef USBSERVICE_H_
#define USBSERVICE_H_

#include <vector>
#include <cstdint>
#include <libusb.h>
#include <iostream>

/**
 * USB stuff for anyKey.
 */
class UsbService {
public:

        typedef std::vector <uint8_t> Buffer;

        UsbService ();
        ~UsbService ();

        UsbService (UsbService const &) = delete;
        UsbService &operator= (UsbService const &) = delete;

        /**
         * Connects to the device, and claims its interface.
         */
        void init ();

        /**
         * Releases the interface.
         */
        void destroy ();

        /**
         * Prints all the available USB devices connected to the host we are running on.
         */
        void printDevs ();

        void transmit (Buffer const &buf);

private:

        // PIMPL idiom prevents exposing usb headers to user (I am the only user, but who cares).
        struct Impl;
        Impl *impl;
};

/**
 * RAII capabilities for UsbService.
 */
template <typename Service>
struct UsbServiceGuard {
        UsbServiceGuard ()
        {
                service.init ();
        }

        ~UsbServiceGuard ()
        {
                try {
                        service.destroy ();
                }
                catch (std::exception const &e) {
                        std::cerr << "An exception has occured in ~UsbServiceGuard. Message : " << e.what () << std::endl;
                }
                catch (...) {
                        std::cerr << "Unknown exception has occured in ~UsbServiceGuard." << std::endl;
                }
        }

        Service service;
};

#endif /* USBSERVICE_H_ */
